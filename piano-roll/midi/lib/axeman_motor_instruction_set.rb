require 'midilib/sequence'
require 'midilib/io/seqreader'
require './tempo_mapping'

MidiTemporalInterval = Struct.new(:ticks, :tempo_mapping)
MidiPitchAndTemporalInterval = Struct.new(:ticks, :tempo_mapping, :fret_position)

class AxemanMotorInstructionSet

  def initialize(pick_hand_midi_file, fret_hand_midi_file)
    @seq = MIDI::Sequence.new()
    @event_track = nil
    @milliseconds_per_quarter_note = 0
    @pick_hand_midi_file = pick_hand_midi_file
    @fret_hand_midi_file = fret_hand_midi_file
  end

  def instructions()
    # TODO: Implement me!
    # return [] 'bpm,fret_hand_instruction,pick_hand_instruction'
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
    pick_hand_intervals = process_picking_intervals(compute_temporal_intervals())

    # pick_hand_intervals.each { |instruction|
    #   puts "Instruction: #{instruction}"
    # }

    # puts "GENERATING FRET HAND INSTRUCTIONS"
    # load_event_track(@fret_hand_midi_file)
    # left_hand_intervals = process_pitch_and_temporal_intervals(compute_pitch_and_temporal_intervals())
    # left_hand_intervals.each { |instruction|
    #   puts "Left Hand Instruction: #{instruction}"
    # }

    # TODO: Complete me. (generate bpm,lh_instruction,rh_instruction csv file)

  end

  def compute_pitch_and_temporal_intervals()
    tempo_mapping = nil
    intervals = []
    total_ticks = 0

    @event_track.events.each { |event|

      if event.kind_of?(MIDI::Tempo)
        tempo_mapping = TempoMapping.new(event.tempo, @seq.ppqn)
      end

      if note_on_or_off_event?(event)
        # If the very first on event, use time_from_start otherwise use delta
        delta = intervals.empty? ? event.time_from_start : event.delta_time
        interval = MidiPitchAndTemporalInterval.new(delta, tempo_mapping, (event.note % 40))

        total_ticks += delta

        intervals << interval
      end
    }

    # puts "TOTAL LEFT HAND TICKS: #{total_ticks}"

    intervals

  end

  def compute_temporal_intervals()
    tempo_mapping = nil
    intervals = []
    total_ticks = 0

    @event_track.events.each { |event|

      if event.kind_of?(MIDI::Tempo)
        tempo_mapping = TempoMapping.new(event.tempo, @seq.ppqn)
      end

      if note_on_or_off_event?(event)
        # If the very first on event, use time_from_start otherwise use delta
        delta = intervals.empty? ? event.time_from_start : event.delta_time
        interval = MidiTemporalInterval.new(delta, tempo_mapping)

        total_ticks += delta

        intervals << interval
      end
    }

    intervals

  end

  # TODO: this is the code to columnize our right-hand instructions.
  def process_picking_intervals(intervals)
    event_count = 0
    instructions = []
    total_sixteenths = 0

    intervals.each { |interval|

      sixteenth_note_count = interval.tempo_mapping.ticks_to_sixteenth_note_count(interval.ticks)
      total_sixteenths += sixteenth_note_count

      if event_count % 2 == 0
        (1..sixteenth_note_count).each {
          instructions << 0
        }
      else
        if sixteenth_note_count < 2
          instructions << 16
        else

          quarters = sixteenth_note_count / 4
          sixteenths = sixteenth_note_count % 4
          eights = sixteenths / 2

          (1..quarters).each {
            instructions << 4

            (1..3).each {
              instructions << "x"
            }
          }

          (1..eights).each {
            instructions << 8
            instructions << "x"
          }

          instructions << 16

        end
      end

      event_count += 1
    }

    instructions

  end

  def process_pitch_and_temporal_intervals(intervals)

    event_count = 0
    instructions = []
    total_sixteenths = 0

    intervals.each { |interval|

      sixteenth_note_count = interval.tempo_mapping.ticks_to_sixteenth_note_count(interval.ticks)
      total_sixteenths += sixteenth_note_count

      if event_count % 2 == 0
        (1..sixteenth_note_count).each {
          instructions << interval.fret_position
        }
      else
        if sixteenth_note_count < 2
          instructions << interval.fret_position
        else
          quarters = sixteenth_note_count / 4
          sixteenths = sixteenth_note_count % 4
          eights = sixteenths / 2

          (1..quarters).each {
            (1..4).each {
              instructions << interval.fret_position
            }
          }

          (1..eights).each {
            (1..2).each {
              instructions << interval.fret_position
            }
          }

          instructions << interval.fret_position

        end
      end

      event_count += 1
    }

    instructions

  end

  def note_on_or_off_event?(event)
    event.kind_of?(MIDI::NoteOn) || event.kind_of?(MIDI::NoteOff)
  end

  def print_pick_hand_instructions(pick_hand_instructions)
    puts "Articulation,Direction,AbsoluteStrikeTime,StrikeTimeDelta,NextStrikeDelta"
    pick_hand_instructions.each { |instruction|
      puts ",#{instruction.direction},#{instruction.absolute_strike_time},#{instruction.strike_time_delta},#{instruction.next_strike_delta}"
    }
  end

end