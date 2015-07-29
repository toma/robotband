require_relative './axeman_motor_instruction_set'


def write_piano_roll(filename, instructions)
  piano_roll_file = open(filename, 'a')
  instructions.each do |instruction|
    piano_roll_file.puts "#{instruction}"
  end
end

puts "Generating Instructions for VerseV Axeman1"
instruction_set = AxemanMotorInstructionSet.new('../data/VerseV_Axeman1_RH.mid', '../data/VerseV_Axeman1_LH.mid')
write_piano_roll('../rolls/versev/axeman1/VerseV.csv', instruction_set.generate_axeman_piano_roll())

puts "Generating Instructions for VerseV Axeman2"
instruction_set = AxemanMotorInstructionSet.new('../data/VerseV_Axeman2_RH.mid', '../data/VerseV_Axeman2_LH.mid')
write_piano_roll('../rolls/versev/axeman2/VerseV.csv', instruction_set.generate_axeman_piano_roll())

