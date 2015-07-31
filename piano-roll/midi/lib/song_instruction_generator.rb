require 'json'
require './song_instruction_sequence'
require './section'

json_data = '{
  "SongInstructionSequence": [
    {
      "Section": {
        "name": "CountIn",
        "picking_patterns": [
          {
            "repetition_count": "2",
            "pattern": "4,4,4,4"
          }
        ],
        "fret_hand_patterns": [
          {
            "repetition_count": "1",
            "pattern": "0|0,0|0,0|0,0|0,0|0,0|0,0|0,0|0,0|0,0|0,0|0,0|0,0|0,0|0,0|0,0|0"
          }
        ]
      }
    },
    {
      "Section": {
        "name": "Intro A-I",
        "picking_patterns": [
          {
            "repetition_count": "*",
            "pattern": "8,8,8,8,8,8,8,8"
          }
        ],
        "fret_hand_patterns": [
          {
            "repetition_count": "1",
            "pattern": "0|7,0|7,0|7,0|7,0|9,0|9,0|9,0|9,0|9,0|9,0|9,0|9,0|5,0|5,0|5,0|5"
          },
          {
            "repetition_count": "1",
            "pattern": "0|7,0|7,0|7,0|7,0|7,0|7,0|7,0|7,0|11,0|11,0|11,0|11,0|9,0|9,0|9,0|9"
          },
          {
            "repetition_count": "1",
            "pattern": "0|7,0|7,0|7,0|7,0|9,0|9,0|9,0|9,0|9,0|9,0|9,0|9,0|5,0|5,0|5,0|5"
          },
          {
            "repetition_count": "1",
            "pattern": "0|7,0|7,0|7,0|7,0|5,0|5,0|5,0|5,0|3,0|3,0|3,0|3,0|1,0|1,0|1,0|1"
          }
        ]
      }
    }
  ]
}'

data = JSON.parse(json_data)

# puts "data[SongInstructionSequence]: #{data['SongInstructionSequence']}"

data['SongInstructionSequence'].map { |section| puts "Section: #{section}" }

song_instruction_sequence = SongInstructionSequence.new

section1 = Section.new("CountIn",
                       [{ "repetition_count " =>"2", "pattern" => "4,4,4,4"}],
                       [{"repetition_count" => "0|0,0|0,0|0,0|0,0|0,0|0,0|0,0|0,0|0,0|0,0|0,0|0,0|0,0|0,0|0,0|0"}])
section2 = Section.new("Intro A-I",
                       [{ "repetition_count " =>"*", "pattern" => "8,8,8,8,8,8,8,8"}],
                       [{"repetition_count" => "1", "pattern" => "0|0,0|0,0|0,0|0,0|0,0|0,0|0,0|0,0|0,0|0,0|0,0|0,0|0,0|0,0|0,0|0"},
                        {"repetition_count" => "1", "pattern" => "0|7,0|7,0|7,0|7,0|7,0|7,0|7,0|7,0|11,0|11,0|11,0|11,0|9,0|9,0|9,0|9"}])

song_instruction_sequence.add_section(section1)
song_instruction_sequence.add_section(section2)

puts "------------------"
puts "------------------"
puts "------------------"
puts JSON.dump(song_instruction_sequence)
