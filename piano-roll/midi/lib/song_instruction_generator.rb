#!/usr/bin/ruby

require 'json'
require 'midilib/sequence'
require 'midilib/io/seqreader'
require_relative 'song_event_memo'
require_relative 'song_instruction_sequence'
require_relative 'section'
require_relative 'tempo_mapping'

class SongInstructionGenerator

  def initialize(midi_session_file)
    @seq = MIDI::Sequence.new()
    @event_track = nil
    @midi_session_file = midi_session_file
  end

  def load_event_track()
    File.open(@midi_session_file, 'rb') { |file|
      @seq.read(file) { |track, num_tracks, i|
        @event_track = track if i = num_tracks
      }
    }
  end

  def generate_template_json()

    load_event_track()
    event_groups = group_events()

    events = []
    event_groups.keys.sort.each { |k|
      events << event_groups[k].sort! { |a, b| a.class.name <=> b.class.name }
    }

    events.flatten!

    song_event_memo = SongEventMemo.new(@seq.ppqn)

    events.each { | event |

      # puts "Event: #{event} delta: #{event.time_from_start}"

      case event

        when MIDI::Marker
          # puts "    marker_data: #{event.data_as_str}"
          song_event_memo.section_opened(event)

          break if event.data_as_str.downcase == "out"

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

    JSON.dump(song_instruction_sequence)

  end

  def write_song_template(song_instruction_template, output_file)
    File.open(output_file, 'w') { |file|
      file.puts(song_instruction_template)
    }
  end

  private

  def group_events()
    event_groups = {}

    @event_track.events.reject { |e| e.kind_of?(MIDI::NoteOn) || e.kind_of?(MIDI::NoteOff) }.each { | event |
      # puts "------------"
      # puts "Event type:#{event.to_s} delta_time:#{event.delta_time} time_from_start:#{event.time_from_start}"
      event_groups[event.time_from_start] ? event_groups[event.time_from_start] << event : event_groups[event.time_from_start] = [event]
    }
    event_groups
  end


end

if __FILE__ == $0
  if ARGV.length != 2
    puts "Usage: $ song_instruction_generator.rb <input-midi-file> <output-template-json-file>"
  end

  input_midi_file, output_template_json_file = ARGV

  instruction_generator = SongInstructionGenerator.new(input_midi_file)
  instruction_generator.write_song_template(instruction_generator.generate_template_json(), output_template_json_file)

end

