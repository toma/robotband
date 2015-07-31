class Section

  attr_accessor :name, :picking_patterns, :fret_hand_patterns

  def initialize(name, picking_patterns, fret_hand_patterns)
    @name = name
    @picking_patterns = picking_patterns
    @fret_hand_patterns = fret_hand_patterns
  end

  def self.json_create(o)
    # TODO: May need to tweek this. (Untested)
    new(*o['data'])
  end

  def to_json(*a)
    { self.class.name => name, "picking_patterns" => picking_patterns, "fret_hand_patterns" => fret_hand_patterns }.to_json(*a)
  end

end