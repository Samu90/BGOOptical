#include "MyCounter.hh"

MyCounter::MyCounter() :
  countU_(0),
  countD_(0),
  coincidence_(0),
  countC_(0),
  totCount_(0),
  triple_(0)
{}

double MyCounter::GetEff()
{
  return (((double)coincidence_)/totCount_);
}

double MyCounter::GetNoGoodEvents(){
  return (((double)triple_)/coincidence_);
}
  
