// A state is the position of an action
// A state set is the series of states for a musician
// An instruction set is the ordered series of state sets and corresponding
//     delays for the entire performance

class PianoRoll {
  public: 
    void initSD();
    int getDelay();
    int getMusicianType();
    unsigned char* getStateSet();
    void readLine();
    bool hasRows();
};
