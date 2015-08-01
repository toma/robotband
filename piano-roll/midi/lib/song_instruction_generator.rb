require 'json'
require 'midilib/sequence'
require 'midilib/io/seqreader'
require_relative 'song_event_memo'
require_relative 'song_instruction_sequence'
require_relative 'section'
require_relative 'tempo_mapping'

MidiPitchAndTemporalInterval = Struct.new(:ticks, :tempo_mapping, :fret_position)

class SongInstructionGenerator

  def initialize(midi_session_file)
    @seq = MIDI::Sequence.new()
    @event_track = nil
    @midi_session_file = midi_session_file
  end

  def load_event_track(midi_file)
    File.open(midi_file, 'rb') { |file|
      @seq.read(file) { |track, num_tracks, i|
        @event_track = track if i = num_tracks
      }
    }
  end

  song_instruction_sequence = SongInstructionSequence.new([])

  # section1 = Section.new("CountIn",
  #                        [{"meter" => "4/4", "repetition_count " => "2", "pattern" => "4,4,4,4"}],
  #                        [{"meter" => "4/4", "repetition_count" => "0|0,0|0,0|0,0|0,0|0,0|0,0|0,0|0,0|0,0|0,0|0,0|0,0|0,0|0,0|0,0|0"}])
  # section2 = Section.new("Intro A-I",
  #                        [{"meter" => "4/4", "repetition_count " => "*", "pattern" => "8,8,8,8,8,8,8,8"}],
  #                        [{"meter" => "4/4", "repetition_count" => "1", "pattern" => "0|0,0|0,0|0,0|0,0|0,0|0,0|0,0|0,0|0,0|0,0|0,0|0,0|0,0|0,0|0,0|0"},
  #                         {"meter" => "4/4", "repetition_count" => "1", "pattern" => "0|7,0|7,0|7,0|7,0|7,0|7,0|7,0|7,0|11,0|11,0|11,0|11,0|9,0|9,0|9,0|9"}])
  #
  # song_instruction_sequence.add_section(section1)
  # song_instruction_sequence.add_section(section2)
  #
  # puts "------------------"
  # puts "------------------"
  # puts "------------------"
  # puts JSON.dump(song_instruction_sequence)

  # Events Of Interest: Tempo TimeSig Marker

  def print_events()
    #TODO: EXTRACT TO METHOD
    real_track = nil
    seq = MIDI::Sequence.new()
    File.open(@midi_session_file, 'rb') { |file|
      seq.read(file) { |track, num_tracks, i|
        real_track = track if i = num_tracks
      }
    }
    # end todo

    event_groups = group_events(real_track)

    events = []
    event_groups.keys.sort.each { |k|
      # puts "sorted key: #{k} event:#{event_groups[k]}"
      events << event_groups[k].sort! { |a, b| a.class.name <=> b.class.name }
    }

    events.flatten!

    song_event_memo = SongEventMemo.new(@seq.ppqn)

    events.each { | event |

      puts "Event: #{event} delta: #{event.time_from_start}"

      case event
        when MIDI::Marker
          # puts "    marker_data: #{event.data_as_str}"
          break if event.data_as_str == "Out"

          song_event_memo.section_opened(event)

        when MIDI::Tempo
          # puts "    tempo: #{MIDI::Tempo.mpq_to_bpm(event.data).to_i}"
          song_event_memo.tempo_changed(event)

        when MIDI::TimeSig
          # puts "    #{event.numerator}/#{2**event.denominator}"
          song_event_memo.meter_changed(event)
        else
          "    WARNING!! Unknown or unexpected event: #{event.class.name}"
        end
    }

    song_instruction_sequence = SongInstructionSequence.new(song_event_memo.sections())

    puts JSON.dump(song_instruction_sequence)

  end

  private

  def group_events(track)
    event_groups = {}

    track.events.reject { |e| e.kind_of?(MIDI::NoteOn) || e.kind_of?(MIDI::NoteOff) }.each { | event |
      # puts "------------"
      # puts "Event type:#{event.to_s} delta_time:#{event.delta_time} time_from_start:#{event.time_from_start}"
      event_groups[event.time_from_start] ? event_groups[event.time_from_start] << event : event_groups[event.time_from_start] = [event]
    }
    event_groups
  end

end

SongInstructionGenerator.new('../data/VerseV_Song.mid').print_events()

