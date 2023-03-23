#include <vector>
#include <ncurses.h>
#include "expression.h"
class WList{
public:
WList(int sx,int sy,int lx,int ly);
void printlw();
void push_back(Expression e);
void box(int x,int y);
void refresh();
private:
std::vector<Expression>m_list;
WINDOW * m_window;
};