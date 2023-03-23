#include "wlist.h"
WList::WList(int sx, int sy, int lx, int ly)
    : m_window{newwin(sx, sy, lx, ly)} {}
void WList::printlw() {
  for (size_t i = 1; i != m_list.size(); i++) {
    mvwprintw(m_window, 1, i, "%s", m_list.at(i).str().c_str());
  }
}
void WList::box(int x, int y) { ::box(m_window, x, y); }
void WList::refresh() { wrefresh(m_window); }
void WList::push_back(const Expression e) {
  // TODO: SCROLL
  m_list.push_back(e);
  refresh();
}