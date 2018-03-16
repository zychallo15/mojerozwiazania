//
// Created by mwypych on 02.02.17.
//
#include "Factorial.h"

int Factorial(int value) {
  if(value==0){
      return 1;
  }else if(value>0 && value<13){
      return value* Factorial(value - 1);
  }else if(value<0 && value>-13){
      return value* Factorial(value + 1);
  }else{
      return 0;
  }
}
