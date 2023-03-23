#include "expression.h"
#include <math.h>
#include <variant>
#include <string.h>
Expression::Expression(std::string x,std::string y,char c) : m_x{x},m_y{y},m_c(c) {}
Expression::Expression(std::string x,operation e) : m_x(x),m_c(e) {}
double Expression::evaluate() { 
 try {
  double x{stod(m_x)};
  if(const auto c = std::get_if<char>(&m_c)) {
  double y{stod(m_y)};
    switch(*c) {
      case '*':
        return x * y;
      case '/':
        return x/y;
      case '+':
        return x+y;
      case '-':
        return x-y;
      case '^':
        return pow(x,y);
    }
  } else if(const auto e = std::get_if<operation>(&m_c)) {
    switch(*e) {
      case operation::sine:
        return sin(x);
      case operation::square:
        return pow(x,2);
      case operation::tangent:
        return tan(x);
      case operation::cosine:
        return cos(x);
    }
  }
    } catch(...) {
   //just in case anything breaks
    return -INFINITY;
    }
  }
std::string Expression::str() {
  if(const auto c = std::get_if<char>(&m_c)) {
    return m_x + c + m_y;
  } else if(const auto e = std::get_if<operation>(&m_c)) {
    return operationToString(*e) + m_x;
  }
}
void Expression::clear() {
  m_x = {};
  m_y = {};
  m_c = {};
}
std::string operationToString(operation o) {
  switch(o) {
    case operation::sine:
      return "sine(";
    case operation::cosine:
      return "cos(";
    case operation::square:
      return "square(";
    case operation::tangent:
      return "tan(";
    case operation::power:
      return "power(";
  }
}