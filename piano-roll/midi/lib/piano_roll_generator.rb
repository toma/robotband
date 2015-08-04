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
      puts "Parsing Section #{section["Section"]}"

      section['temporal_mappings'].each do |mapping|
        pick_instructions = []
        mapping['picking_pattern'].each do |pattern|
          pick_instructions.concat repeatSection(pattern['pattern'], pattern['repetitions'])
        end
        
        fret_instructions = []
        mapping['fret_hand_pattern'].each do |pattern|
          fret_instructions.concat repeatSection(pattern['pattern'], pattern['repetitions'])
        end

        pixel0_instructions = []
        pixel1_instructions = []
        pixel2_instructions = []
        pixel3_instructions = []
        pixel4_instructions = []
        pixel5_instructions = []
        pixel6_instructions = []

        mapping['lighting_pattern'].each do |pattern|

          pixel0_instructions.concat repeatSection(pattern['pixel0'], pattern['repetitions'])
          pixel1_instructions.concat repeatSection(pattern['pixel1'], pattern['repetitions'])
          pixel2_instructions.concat repeatSection(pattern['pixel2'], pattern['repetitions'])
          pixel3_instructions.concat repeatSection(pattern['pixel3'], pattern['repetitions'])
          pixel4_instructions.concat repeatSection(pattern['pixel4'], pattern['repetitions'])
          pixel5_instructions.concat repeatSection(pattern['pixel5'], pattern['repetitions'])
          pixel6_instructions.concat repeatSection(pattern['pixel6'], pattern['repetitions'])
        end
        tempoArray = Array.new(pick_instructions.length, mapping['tempo'])
        pianoRollArray.concat tempoArray.zip(pick_instructions, fret_instructions, pixel0_instructions, pixel1_instructions, pixel2_instructions, pixel3_instructions, pixel4_instructions, pixel5_instructions, pixel6_instructions)
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
    puts "ex. ./piano_roll_generator.rb ../data/pianoRolls/LEADGUIT/VERSEV.csv ../data/template/VerseV_Axeman1.json"
    exit
  end

  outFile, jsonFiles = ARGV

  PianoRollGenerator.generatePianoRoll(outFile, jsonFiles)
end
