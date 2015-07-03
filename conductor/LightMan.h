class LightMan {
  public:
    void setup();
    void setState(unsigned char state[2]);
  private:
    void setLightState(unsigned char pin, unsigned char state);
};