require 'bigdecimal'

class TempoMapping

  def initialize(midi_tempo, resolution)
    @midi_tempo = midi_tempo # in microseconds
    @resolution = resolution
    @bpm = (60 * 1000000) / @midi_tempo
    @millis_per_tick = ((@midi_tempo / @resolution).to_f / 1000).to_f
    @millis_per_quarter_note = 60000 / @bpm
    @millis_per_sixteenth_note = @millis_per_quarter_note / 4
  end

  def ticks_to_sixteenth_note_count(ticks)
    duration = round_to_most_significant(ticks_to_millis(ticks))
    puts "ticks: #{ticks} ticks_to_millis: #{ticks_to_millis(ticks)} rounded_duration: #{duration}"
    duration / @millis_per_sixteenth_note
  end

  private

  def ticks_to_millis(ticks)
    @millis_per_tick * ticks
  end

  def round_to_most_significant(millis)

    partial = millis % @millis_per_sixteenth_note
    whole = millis - partial

    (1..partial.to_i.to_s.length-1).each do |x|
      partial = BigDecimal.new(partial.to_s).round(-x, BigDecimal::ROUND_HALF_EVEN).to_i
    end

    whole + partial

  end

end