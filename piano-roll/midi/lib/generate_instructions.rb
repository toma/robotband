require_relative './axeman_motor_instruction_set'

instruction_set = AxemanMotorInstructionSet.new('data/VerseV_Axeman1_RH.mid', 'data/VerseV_Axeman1_LH.mid')
instruction_set.generate_axeman_piano_roll()