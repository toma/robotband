class Musician {
  public:
    static Musician *makeMusician(int musicianType);
    virtual void setup();
    virtual void setState(unsigned char value1, unsigned char value2);
};
