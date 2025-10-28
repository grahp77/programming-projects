#include "tetris.h"

int main() {
  tetris();
  return 0;
}

void tetris() {
  GameInfo_t backend = {0};
  UserAction_t action = -1;
  bool hold = 1;
  srand(time(NULL));
  initNcurses();

  do {
    clear();

    backend = updateCurrentState();
    inputProcessing(getch(), &action);
    userInput(action, hold);

    if (backend.pause) {
      printGameInfo(backend);
    }

    refresh();
    napms(20);
  } while (backend.pause);

  curs_set(1);
  endwin();
}