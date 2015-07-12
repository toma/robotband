class Musician {
  public:
    static Musician *makeMusician(int musicianType);
    virtual void setup();
    virtual void setState(unsigned char state[2]);
};
