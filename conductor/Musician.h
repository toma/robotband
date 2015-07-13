class Musician {
  public:
    static Musician *makeMusician(int musicianType);
    virtual void setup();
    virtual void setState(unsigned char* state);
    virtual void setState2(unsigned char value1, unsigned char value2);
};
