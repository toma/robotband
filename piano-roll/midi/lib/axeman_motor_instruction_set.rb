require 'midilib/sequence'
require 'midilib/io/seqreader'
require './tempo_mapping'

# TODO: Convert to class that encapsulates TempoMapping behavior
MidiPitchAndTemporalInterval = Struct.new(:ticks, :tempo_mapping, :fret_position)

class AxemanMotorInstructionSet

  def initialize(pick_hand_midi_file, fret_hand_midi_file)
    @seq = MIDI::Sequence.new()
    @event_track = nil
    @milliseconds_per_quarter_note = 0
    @pick_hand_midi_file = pick_hand_midi_file
    @fret_hand_midi_file = fret_hand_midi_file
  end

  def load_event_track(midi_file)
    File.open(midi_file, 'rb') { |file|
      @seq.read(file) { |track, num_tracks, i|
        @event_track = track if i = num_tracks
      }
    }
  end

  def generate_axeman_piano_roll()

    puts "GENERATING PICK HAND INSTRUCTIONS"
    load_event_track(@pick_hand_midi_file)
    pick_hand_intervals = convert_intervals_to_instructions(events_to_pitch_and_temporal_intervals(), &method(:picking_instructions))

    puts "GENERATING FRET HAND INSTRUCTIONS"
    load_event_track(@fret_hand_midi_file)
    fret_hand_instructions = convert_intervals_to_instructions(events_to_pitch_and_temporal_intervals(), &method(:fretting_instructions))

    # puts "total_ph_instructions: #{pick_hand_intervals.length} total_lh_instrutions:#{fret_hand_intervals.length}"

    normalize_instruction_arrays(pick_hand_intervals, fret_hand_instructions)
    merge_instruction_lists(pick_hand_intervals, fret_hand_instructions)

  end

  def merge_instruction_lists(pick_hand_intervals, fret_hand_intervals)

    merged_instructions = []

    (0..pick_hand_intervals.length-1).each do |i|
      merged_instructions << "#{pick_hand_intervals[i]},#{fret_hand_intervals[i]}"
    end

    merged_instructions
  end

  #TODO: This is a hack. Remove once differing instruction sizes per hand is fixed
  def normalize_instruction_arrays(pick_hand_intervals, fret_hand_intervals)
    if (fret_hand_intervals.length > pick_hand_intervals.length)
      (0..(fret_hand_intervals.length - pick_hand_intervals.length)-1).each {
        pick_hand_intervals << "75,0"
      }
    elsif (fret_hand_intervals.length < pick_hand_intervals.length)
      (0..(pick_hand_intervals.length - fret_hand_intervals.length)-1).each {
        fret_hand_intervals << "0"
      }
    end
  end

  def events_to_pitch_and_temporal_intervals()
    tempo_mapping = nil
    intervals = []
    total_ticks = 0
    last_event = MIDI::NoteOff

    @event_track.events.each { |event|

      if event.kind_of?(MIDI::Tempo)
        tempo_mapping = TempoMapping.new(event.tempo, @seq.ppqn)
      end

      if note_on_or_off_event?(event)
        #TODO: why event.kind_of?(last_event) no worky??
        if (event.class.name != last_event.class.name)
          delta = intervals.empty? ? event.time_from_start : event.delta_time
          interval = MidiPitchAndTemporalInterval.new(delta, tempo_mapping, (event.note % 40))
          last_event = event

          total_ticks += delta

          intervals << interval
        end
      end
    }

    # TODO: Complete this checksum including tempo changes
    # puts "TOTAL 16th notes for FretHand tempo mapping: total_ticks=#{total_ticks} total_sixteenths:#{tempo_mapping.ticks_to_sixteenth_note_count(total_ticks)}"

    intervals

  end

  def fretting_instructions(interval, note_duration)
    interval.fret_position
  end

  def picking_instructions(interval, note_duration)
    "#{interval.tempo_mapping.bpm()},#{note_duration}"
  end

  def convert_intervals_to_instructions(intervals, &instruction_block)

    event_count = 0
    instructions = []
    total_sixteenths = 0

    intervals.each { |interval|

      sixteenth_note_count = interval.tempo_mapping.ticks_to_sixteenth_note_count(interval.ticks)
      total_sixteenths += sixteenth_note_count

      instructions << interval_to_instructions(event_count, interval, &instruction_block)

      # puts "event_count:#{event_count} 16th_count: #{sixteenth_note_count} fromTicks:#{interval.ticks}"

      event_count += 1
    }

    instructions.flatten

  end

  def interval_to_instructions(event_count, interval, &instruction_block)
    instructions = []

    sixteenth_note_count = interval.tempo_mapping.ticks_to_sixteenth_note_count(interval.ticks)

    # puts "Round Up Count: #{interval.tempo_mapping.round_up_count} Round Down Count: #{interval.tempo_mapping.round_down_count}" if interval.tempo_mapping

    if (event_count % 2 == 0)
      (1..sixteenth_note_count).each { instructions << instruction_block.call(interval, "0") }
    else
      if (sixteenth_note_count == 1)
        instructions << instruction_block.call(interval, "16")
      else
        quarters = (sixteenth_note_count / 4).floor
        remaining_sixteenths = (sixteenth_note_count % 4).floor
        eights = (remaining_sixteenths / 2).floor

        (1..(quarters*4)).each { instructions << instruction_block.call(interval, "4") }

        (1..(eights*2)).each { instructions << instruction_block.call(interval, "8") }

        if (remaining_sixteenths % 2 > 0)
          instructions << instruction_block.call(interval, "16")
        end
      end
    end

    instructions

  end

  def note_on_or_off_event?(event)
    event.kind_of?(MIDI::NoteOn) || event.kind_of?(MIDI::NoteOff)
  end

end