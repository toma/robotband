require_relative 'temporal_mapping'

class Section

  attr_accessor :name, :ticks_from_start, :temporal_mappings

  def initialize(name, ticks_from_start, initial_tempo_mapping, initial_meter)
    @name = name
    @ticks_from_start = ticks_from_start
    @duration_in_ticks = 0
    @initial_tempo_mapping = initial_tempo_mapping
    @initial_meter = initial_meter
    @temporal_infos = []
    @temporal_mappings = []
  end

  def set_initial_tempo_mapping(tempo_mapping)
    @initial_tempo_mapping = tempo_mapping
  end

  def set_initial_meter(meter)
    @initial_meter = meter
  end

  def memoize_temporal_info(mapping)
    @temporal_infos << mapping
  end

  # TODO: Try to separate these two for pipeline processing. Must guarantee close is called before process!
  def close_and_process(next_section_ticks_from_start)
    @duration_in_ticks = next_section_ticks_from_start - @ticks_from_start
    process()
  end

  def self.json_create(o)
    # TODO: May need to tweek this. (Untested)
    new(*o['data'])
  end

  def to_json(*a)
    { self.class.name => name, "temporal_mappings" => temporal_mappings }.to_json(*a)
  end

  private

  def process()
    if (@temporal_infos.empty?)
      tempo = @initial_tempo_mapping.bpm()
      meter = "#{@initial_meter.numerator}/#{@initial_meter.denominator}"
      sixteenths_per_measure = (16 / @initial_meter.denominator) * (@initial_meter.numerator)
      repetitions = @initial_tempo_mapping.ticks_to_sixteenth_note_count(@duration_in_ticks) / sixteenths_per_measure

      @temporal_mappings << TemporalMapping.new(tempo, meter, repetitions, sixteenths_per_measure)

    else
      # NOTE: The assumption is that all tempo changes coincide with section markers. Therefore, meter changes are the only
      #       temporal events memoized within a section.
      section_tick_offset = @ticks_from_start

      @temporal_infos.each { |ti|
        tempo = @initial_tempo_mapping.bpm()
        meter = "#{ti.numerator}/#{ti.denominator}"
        sixteenths_per_measure = (16 / ti.denominator) * (ti.numerator)
        repetitions = @initial_tempo_mapping.ticks_to_sixteenth_note_count(ti.ticks_from_start - section_tick_offset)
        section_tick_offset = ti.ticks_from_start

        @temporal_mappings << TemporalMapping.new(tempo, meter, repetitions, sixteenths_per_measure)
      }
    end
  end
end