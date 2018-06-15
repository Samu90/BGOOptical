#ifndef MyCounter_hh
#define MyCounter_hh

class MyCounter{
public:
  MyCounter();
  
  inline void IncreaseUp() {countU_+=1;}
  void IncreaseDown() {countD_+=1;}
  void IncreaseCoinc() {coincidence_+=1;}
  void IncreaseCher() {countC_+=1;}
  void IncreaseTri() {triple_+=1;}

  inline void IncreaseTotCount() {totCount_++;};

  inline int GetCountU() const {return countU_;}
  int GetCountD() {return countD_;}
  int GetCoincidence() {return coincidence_;}
  int GetCountC() {return countC_;}
  int GetTriple() {return triple_;}
  double GetEff();
  double GetNoGoodEvents();
  
    
private:
  int countU_;
  int countD_;
  int coincidence_;
  int countC_;
  int totCount_;
  int triple_;
};

#endif
