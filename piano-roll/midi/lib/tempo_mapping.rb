class TempoMapping

  def initialize(midi_tempo, resolution)
    @midi_tempo = midi_tempo # in microseconds
    @resolution = resolution
    @bpm = (60 * 1000000) / @midi_tempo
    @millis_per_tick = ((@midi_tempo / @resolution).to_f / 1000).to_f
    @millis_per_quarter_note = 60000 / @bpm
    @millis_per_sixteenth_note = @millis_per_quarter_note / 4
    @round_up_count = 0
    @round_down_count = 0
  end

  def ticks_to_sixteenth_note_count(ticks)
    duration = round_to_most_significant(ticks_to_millis(ticks))
    duration / @millis_per_sixteenth_note
  end

  def bpm()
    @bpm
  end

  def round_down_count
    @round_down_count
  end

  def round_up_count
    @round_up_count
  end

  private

  def ticks_to_millis(ticks)
    @millis_per_tick * ticks
  end

  def round_to_most_significant(millis)

    partial = millis % @millis_per_sixteenth_note
    whole = millis - partial
    round_multiplier = (partial / @millis_per_sixteenth_note).round
    duration = whole + (round_multiplier * @millis_per_sixteenth_note)

    if (partial > 0)
      if (round_multiplier == 0)
        @round_down_count += 1
      elsif (round_multiplier == 1)
        @round_up_count += 1
      else
        puts "WTF We did not round!! millis:#{millis} round_multiplier:#{round_multiplier} partial: #{partial}"
      end
    end

    duration

  end

end