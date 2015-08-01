#!/usr/bin/ruby

require 'json'

class PianoRollGenerator
  def self.generatePianoRoll(outFile, jsonFile)
    instructionSet = parseJson(jsonFile)
    pianoRollArray = playInstructions(instructionSet)
    writePianoRoll(pianoRollArray, outFile)
  end

  def self.parseJson(jsonFile)
    file = File.read(jsonFile)
    instructionSet = JSON.parse(file)
  end

  def self.playInstructions(instructionSet)
    pianoRollArray = []

    instructionSet["SongInstructionSequence"].each do |section|
      puts "Parsing Section #{section["Section"]["name"]}"
      
      section['Section']['temporal_mappings'].each do |mapping|
        pick_instructions = []
        mapping['TemporalMapping']['picking_pattern'].each do |pattern|
          pick_instructions.concat repeatSection(pattern['pattern'], pattern['repetition_count'])
        end
        
        fret_instructions = []
        mapping['TemporalMapping']['fret_hand_pattern'].each do |pattern|
          fret_instructions.concat repeatSection(pattern['pattern'], pattern['repetition_count'])
        end
        
        tempoArray = Array.new(pick_instructions.length, mapping['TemporalMapping']['tempo'])
        pianoRollArray.concat tempoArray.zip(pick_instructions, fret_instructions)
      end
    end
    pianoRollArray
  end

  def self.writePianoRoll(pianoRollArray, outFile)
    File.open(outFile, 'w') { |file|
      for line in pianoRollArray
        file.puts(line.join(','))
      end
    }
  end

  def self.repeatSection(pattern, count)
    temp = Array.new(count, pattern).join(',').split(',')
  end

end

if __FILE__ == $0
  if ARGV.length != 2
    puts "requires two arguments"
    puts "piano_roll_generator.rb <outputFile> <jsonFile>"
  end

  outFile, jsonFiles = ARGV

  PianoRollGenerator.generatePianoRoll(outFile, jsonFiles)
end
