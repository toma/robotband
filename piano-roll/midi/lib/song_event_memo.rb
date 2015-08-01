require 'midilib/sequence'
require 'midilib/io/seqreader'
require_relative 'song_instruction_sequence'
require_relative 'section'
require_relative 'tempo_mapping'

Meter = Struct.new(:ticks_from_start, :numerator, :denominator)

class SongEventMemo

  def initialize(ppqn)
    @ppqn = ppqn
    @sections = []
    @open_section_count = 0
    @current_section = nil
    @current_tempo_mapping = nil
    @current_meter = nil
  end

  def sections()
    @sections
  end

  def section_opened(event)
    @open_section_count += 1
    if (@open_section_count > 1)
      @current_section.close_and_process(event.time_from_start)
      @sections << @current_section
      @open_section_count -= 1
    end

    @current_section = Section.new(event.data_as_str, event.time_from_start, @current_tempo_mapping, @current_meter)
  end

  def tempo_changed(event)
    tempo_mapping = TempoMapping.new(event.tempo, @ppqn)

    if (event.time_from_start == @current_section.ticks_from_start)
      @current_section.set_initial_tempo_mapping(tempo_mapping)
    else
      @current_section.memoize_temporal_info(tempo_mapping)
    end

    @current_tempo_mapping = tempo_mapping

  end

  def meter_changed(event)
    meter = Meter.new(event.time_from_start, event.numerator, (2**event.denominator))

    if (event.time_from_start == @current_section.ticks_from_start)
      @current_section.set_initial_meter(meter)
    else
      @current_section.memoize_temporal_info(meter)
    end

    @current_meter = meter

  end

end