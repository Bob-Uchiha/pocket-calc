#include "expression.h"
#include "functions.h"
#include <iostream>
#include <menu.h>
#include <ncurses.h>
#include <deque>
int main() {
  initscr(); noecho(); cbreak();
  // initializes a box the size of the screen on the bottom side
  WINDOW *keybinds = newwin(LINES, COLS / 2, 0, COLS - COLS / 2);
  // initializes a box the size of the screen on the left side
  WINDOW *term = newwin(3, COLS / 2, 0, 0); keypad(term,0);
  WINDOW *enter = newwin(3, COLS / 2, 3, 0);
  WINDOW *history = newwin(LINES - 6, COLS / 2, 6, 0);
  box(term, 0, 0);
  box(history, 0, 0);
  box(enter, 0, 0);
  box(keybinds, 0, 0);
  wrefresh(term);
  wrefresh(enter);
  wrefresh(keybinds);
  wrefresh(history);
  bool running{true}, side{0};
  char c, op;

  // horizontal positioning of cursor
  int pos{1}, cpos{0};
  // let stod do the heavy lifting
  Expression expression;
  std::deque<Expression> hist;
  while (running) {
    c = wgetch(term);
    switch (c) {
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
    case '8':
    case '9':
    case '0':
    case '.':
      mvwaddch(term, 1, pos++, c);
      if (side == 0)
        expression.m_x += c;
      else
        expression.m_y += c;
      break;
    case '*':
    case '/':
    case '+':
    case '-':
    case '^':
      expression.m_c = c;
      if (side == 1) {
        mvwaddch(term, 1, cpos, c);
      } else {
        side = 1;
        cpos = pos;
        mvwaddch(term, 1, pos++, c);
      }
      break;
    case 'q':
      endwin();
      running = false;
      break;
    case 't':
      c = wgetch(term);
      switch (c) {
        case 's':
          expression.m_c = sine;
          break;
        case 't':
          expression.m_c = tangent;
          break;
        case 'c':
          expression.m_c = cosine;
          break;
      }
    case KEY_ENTER:
    case 10:
      wclear(term);
      wclear(history);
      pos = 1;
      side = 0;
      hist.push_front(expression);
      mvwprintw(enter, 1, 1, "%s = %f", expression.str().c_str(),
                expression.evaluate());
      mvwprintw(history, 1, 1, "%s", dequeToString(hist).c_str());
      expression.clear();
      box(term, 0, 0);
      box(history, 0, 0);
      wrefresh(history);
      wrefresh(enter);
      break;
    default:
      break;
    }
  }
  endwin();
  return 0;
}