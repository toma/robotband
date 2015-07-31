require 'json'
require 'midilib/sequence'
require 'midilib/io/seqreader'
require_relative 'song_instruction_sequence'
require_relative 'section'
require_relative 'tempo_mapping'

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

  song_instruction_sequence = SongInstructionSequence.new

  section1 = Section.new("CountIn",
                         [{"meter" => "4/4", "repetition_count " => "2", "pattern" => "4,4,4,4"}],
                         [{"meter" => "4/4", "repetition_count" => "0|0,0|0,0|0,0|0,0|0,0|0,0|0,0|0,0|0,0|0,0|0,0|0,0|0,0|0,0|0,0|0"}])
  section2 = Section.new("Intro A-I",
                         [{"meter" => "4/4", "repetition_count " => "*", "pattern" => "8,8,8,8,8,8,8,8"}],
                         [{"meter" => "4/4", "repetition_count" => "1", "pattern" => "0|0,0|0,0|0,0|0,0|0,0|0,0|0,0|0,0|0,0|0,0|0,0|0,0|0,0|0,0|0,0|0"},
                          {"meter" => "4/4", "repetition_count" => "1", "pattern" => "0|7,0|7,0|7,0|7,0|7,0|7,0|7,0|7,0|11,0|11,0|11,0|11,0|9,0|9,0|9,0|9"}])

  song_instruction_sequence.add_section(section1)
  song_instruction_sequence.add_section(section2)

  puts "------------------"
  puts "------------------"
  puts "------------------"
  puts JSON.dump(song_instruction_sequence)

  # Events Of Interest: Tempo TimeSig Marker

  def print_events()
    real_track = nil
    seq = MIDI::Sequence.new()
    File.open(@midi_session_file, 'rb') { |file|
      seq.read(file) { |track, num_tracks, i|
        real_track = track if i = num_tracks
      }
    }

    # real_track.events[1..real_track.events.length].each { | event |
    real_track.events.reject { |e| e.kind_of?(MIDI::NoteOn) || e.kind_of?(MIDI::NoteOff)

    }.each { | event |
      puts "Event type:#{event.to_s} delta_time:#{event.delta_time} time_from_start:#{event.time_from_start}"
      # if on_off_event?(event)
      #   puts "event: note:#{event.note} delta_time:#{event.delta_time}, time_from_start:#{event.time_from_start}"
      #   puts "event: #{event.inspect}"
      # end
      puts "------------"
    }

  end

end

SongInstructionGenerator.new('../data/VerseV_Axeman1_LH.mid').print_events()
