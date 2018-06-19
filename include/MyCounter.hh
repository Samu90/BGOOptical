#ifndef MyCounter_hh
#define MyCounter_hh

class MyCounter{
public:
  MyCounter();
  
  void IncreaseS1(){countSci1++;}
  void IncreaseC1(){countChe1++;}
  void IncreaseS2(){countSci2++;}
  void IncreaseC2(){countChe2++;}

  int GetS1(){return countSci1;}
  int GetC1(){return countChe1;}
  int GetS2(){return countSci2;}
  int GetC2(){return countChe2;}
  
    
private:
  int countSci1;
  int countChe1;
  int countSci2;
  int countChe2;
};

#endif
