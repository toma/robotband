require 'midilib/sequence'
require 'midilib/io/seqreader'

# Expected Output: line1 is musician [Tristan, Erik, Johann Sebastian Kok] ; line2-n delay,Motor#[On|Off],Motor#[On|Off]
# For v.0.1 we won't track tempo changes (fine for VerseV) ** do we need to track tempo changes for Motors?? probably not

def load_event_track(filename)

  seq = MIDI::Sequence.new()

  event_track = nil

  File.open(filename, 'rb') { |file|
    seq.read(file) { |track, num_tracks, i|
      event_track = track if i = num_tracks
    }
  }

  event_track

end

# ************* Informational Methods *****************

def print_all_track_info(filename)
  # Create a new, empty sequence.
  seq = MIDI::Sequence.new()

  # Read the contents of a MIDI file into the sequence.
  File.open(filename, 'rb') { | file |
    seq.read(file) { | track, num_tracks, i |
      # Print something when each track is read.
      puts "read track #{i} of #{num_tracks}"
      puts "track inspection: #{track.inspect}"
    }
  }
end

# Read the contents of a MIDI file into the sequence.
def print_events(filename)
  real_track = nil
  seq = MIDI::Sequence.new()
  File.open(filename, 'rb') { |file|
    seq.read(file) { |track, num_tracks, i|
      real_track = track if i = num_tracks
    }
  }

  real_track.events[1..real_track.events.length].each { |event|
    puts "Event type:#{event.to_s} delta_time:#{event.delta_time} time_from_start:#{event.time_from_start}"
    # if on_off_event?(event)
    #   puts "event: note:#{event.note} delta_time:#{event.delta_time}, time_from_start:#{event.time_from_start}"
    #   puts "event: #{event.inspect}"
    # end
    puts "------------"
  }

end

def on_off_event?(event)
  event.kind_of?(MIDI::NoteOn) || event.kind_of?(MIDI::NoteOff)
end

def print_measure_event_mappings(filename)
  seq = MIDI::Sequence.new()
  file = File.open(filename, 'rb')

  real_track = nil
  seq.read(file) { |track, num_tracks, i|
    real_track = track if i = num_tracks
  }

  # Get all measures, so events can be mapped to measures:
  measures = seq.get_measures
  # print_measure_data(measures)

  real_track.each { |e|

    if on_off_event?(e)
      e.print_note_names = true
      # mbt = measure:beat:ticks
      puts "#{e.class.name} #{measures.to_mbt(e)} time_delta: #{e.delta_time} ch #{e.note_to_s}"
    end
  }

  file.close

end

puts ("AXEMAN-1 RIGHT HAND")
# print_all_track_info('../data/VerseV_Axeman1_RH.mid')
print_events('../data/TheGoldenRule.mid')
# print_measure_event_mappings('../data/VerseV_Axeman1_RH.mid')

puts ("AXEMAN-1 LEFT HAND")
# print_measure_event_mappings('../data/VerseV_Axeman1_LH.mid')
# print_all_track_info('../data/VerseV_Axeman1_LH.mid')

puts ("AXEMAN-2 RIGHT HAND")
# print_all_track_info('../data/VerseV_Axeman2_RH.mid')
puts ("AXEMAN-2 LEFT HAND")
# print_all_track_info('../data/VerseV_Axeman2_LH.mid')
