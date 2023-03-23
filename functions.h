#pragma once
#include <ncurses.h>
#include <string>
#include <math.h>
#include <deque>
#include "expression.h"
//takes sets of characters/ints and returns numbers

//display a deque in a window
std::string dequeToString(std::deque<Expression>v) {
  std::string tmp;
  for(auto e : v) {
    tmp += e.str() + " = " +  std::to_string(e.evaluate()) + "\n ";
  }
  return tmp;
}