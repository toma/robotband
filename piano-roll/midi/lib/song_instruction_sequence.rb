class SongInstructionSequence

  attr_accessor :sections

  def initialize()
    @sections = []
  end

  def add_section(section)
    sections << section
  end

  def self.json_create(o)
    new(*o['data'])
  end

  def to_json(*a)
    { self.class.name => sections }.to_json(*a)
  end

end