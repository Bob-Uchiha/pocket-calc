#pragma once
#include <variant>
#include <string>
enum operation{sine,power,square,tangent,cosine};
struct Expression {
Expression(std::string x,std::string y, char c);
Expression(std::string x,operation e);
Expression() = default;
double evaluate();
void clear();
std::string str();
std::string m_x,m_y;
std::variant<std::monostate,char,operation> m_c;
};
std::string operationToString(operation o);
