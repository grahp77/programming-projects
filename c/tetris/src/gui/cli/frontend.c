
#include "frontend.h"

/**
 * @brief Инициализирует библиотеку ncurses.
 *
 * Данная функция выполняет первоначальную настройку ncurses, включая
 * инициализацию экрана, установку режима cbreak (отключение буферизации строк),
 * отключение эхо-вывода введенных символов, включение обработки клавиш
 * управления курсором, отключение задержки при чтении ввода и скрытие курсора.
 */
void initNcurses() {
  initscr();
  cbreak();
  noecho();
  keypad(stdscr, TRUE);
  nodelay(stdscr, TRUE);
  curs_set(0);
}

/**
 * @brief Обрабатывает ввод пользователя и определяет соответствующее действие.
 *
 * В зависимости от введенного символа (или клавиши), функция устанавливает
 * соответствующее значение в структуре `current_action`, указывающее на
 * действие, которое должен выполнить пользователь (движение влево, вправо,
 * вверх, вниз, пауза, действие, старт или выход).
 *
 * @param ch Введенный символ (или код клавиши).
 * @param current_action Указатель на структуру `UserAction_t`, в которой
 *        будет сохранено действие пользователя.
 */
void inputProcessing(int ch, UserAction_t *current_action) {
  switch (ch) {
    case KEY_LEFT:
      *current_action = Left;
      break;
    case KEY_RIGHT:
      *current_action = Right;
      break;
    case KEY_UP:
      *current_action = Up;
      break;
    case KEY_DOWN:
      *current_action = Down;
      break;
    case 'p':
      *current_action = Pause;
      break;
    case ' ':
      *current_action = Action;
      break;
    case 10:
      *current_action = Start;
      break;
    case 'e':
      *current_action = Exit;
      break;
    default:
      *current_action = Terminate;
      break;
  }
}

/**
 * @brief Выводит на экран информацию об игре.
 *
 * Данная функция отвечает за отображение игрового поля, стартового экрана,
 * экрана паузы, следующей фигуры, границы и статистики (счет, рекорд, уровень,
 * скорость). Она использует другие функции для отрисовки отдельных элементов.
 *
 * @param backend Структура `GameInfo_t`, содержащая текущее состояние игры.
 */
void printGameInfo(GameInfo_t backend) {
  printField(backend);
  if (backend.pause == PAUSE_START) {
    printStart();
  }
  if (backend.pause == PAUSE_PAUSE) {
    printPause();
  }
  printFigure(backend);
  printBorder();
  printStat(backend);
}

/**
 * @brief Отрисовывает игровое поле.
 *
 * Функция перебирает все ячейки игрового поля и выводит символ " " (пробел)
 * с инвертированным цветом, если ячейка занята, и обычный пробел, если ячейка
 * свободна. Использует функцию `mvaddch` из ncurses для вывода символов
 * в указанные координаты экрана.
 *
 * @param CurrentState Структура `GameInfo_t`, содержащая текущее состояние
 * игры, включая информацию об игровом поле.
 */
void printField(GameInfo_t CurrentState) {
  for (int i = 0; i < HEIGHT; i++) {
    for (int j = 0; j < WIDTH; j++) {
      if (CurrentState.field[i][j]) {
        mvaddch(i + 1, j * 2 + BORDER_OFFSET, ' ' | A_REVERSE);
        mvaddch(i + 1, j * 2 + 1 + BORDER_OFFSET, ' ' | A_REVERSE);
      } else {
        mvaddch(i + 1, j * 2 + BORDER_OFFSET, ' ');
        mvaddch(i + 1, j * 2 + 1 + BORDER_OFFSET, ' ');
        // mvaddch(i + 1, j * 2 + BORDER_OFFSET, ACS_CKBOARD);
        // mvaddch(i + 1, j * 2 + 1 + BORDER_OFFSET, ACS_CKBOARD);
      }
    }
  }
}

/**
 * @brief Выводит на экран текст "Press 'Enter' to start the game".
 *
 * Функция использует функцию `snprintf` для форматирования строки и функцию
 * `mvaddstr` для вывода строки на экран в указанные координаты.
 */
void printStart() {
  char buffer[80] = {0};
  snprintf(
      buffer, sizeof(buffer),
      " Press 'Enter' to\n     start the game\n\n           and\n\n    'e' "
      "exit the game");
  mvaddstr(7, 3, buffer);
}

/**
 * @brief Выводит на экран текст "Press 'P' to continue the game".
 *
 * Функция использует функцию `snprintf` для форматирования строки и функцию
 * `mvaddstr` для вывода строки на экран в указанные координаты.
 */
void printPause() {
  char buffer[80] = {0};
  snprintf(buffer, sizeof(buffer),
           "   Press 'P' to\n   continue the game\n\n           and\n\n   'e' "
           "exit the game");
  mvaddstr(7, 3, buffer);
}

/**
 * @brief Отрисовывает следующую фигуру.
 *
 * Функция перебирает ячейки массива `CurrentState.next` и выводит символ " "
 * (пробел) с инвертированным цветом, если ячейка занята, и обычный пробел,
 * если ячейка свободна. Использует функцию `mvaddch` из ncurses для вывода
 * символов в указанные координаты экрана.
 *
 * @param CurrentState Структура `GameInfo_t`, содержащая текущее состояние
 * игры, включая информацию о следующей фигуре.
 */
void printFigure(GameInfo_t CurrentState) {
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      if (CurrentState.next[i][j]) {
        mvaddch(i + NEXT_FIG_POS_X, j * 2 + NEXT_FIG_POS_Y, ' ' | A_REVERSE);
        mvaddch(i + NEXT_FIG_POS_X, j * 2 + NEXT_FIG_POS_Y + 1,
                ' ' | A_REVERSE);
      } else {
        mvaddch(i + NEXT_FIG_POS_X, j * 2 + NEXT_FIG_POS_Y, ' ');
        mvaddch(i + NEXT_FIG_POS_X, j * 2 + NEXT_FIG_POS_Y + 1, ' ');
        // mvaddch(i + NEXT_FIG_POS_X, j * 2 + NEXT_FIG_POS_Y, ACS_CKBOARD);
        // mvaddch(i + NEXT_FIG_POS_X, j * 2 + 1 + NEXT_FIG_POS_Y, ACS_CKBOARD);
      }
    }
  }
}

/**
 * @brief Отрисовывает границу игрового поля и информационной панели.
 *
 * Функция перебирает указанные координаты и выводит символ `ACS_CKBOARD`
 * (шахматная доска) в тех местах, где должна быть граница. Использует функцию
 * `mvaddch` из ncurses для вывода символов в указанные координаты экрана.
 */
void printBorder() {
  for (int i = FIELD_TOP; i <= FIELD_BOTTOM; i++) {
    for (int j = FIELD_LEFT; j <= INFO_PANEL_RIGHT; j++) {
      if (i == FIELD_TOP || j == FIELD_LEFT || i == FIELD_BOTTOM ||
          j == FIELD_RIGHT || j == INFO_PANEL_RIGHT) {
        mvaddch(i, j * 2, ACS_CKBOARD);
        mvaddch(i, j * 2 + 1, ACS_CKBOARD);
      }
    }
  }
}

/**
 * @brief Выводит на экран статистику игры (счет, рекорд, уровень, скорость).
 *
 * Функция использует функцию `snprintf` для форматирования строк и функцию
 * `mvaddstr` для вывода строк на экран в указанные координаты.
 *
 * @param CurrentState Структура `GameInfo_t`, содержащая текущее состояние
 * игры, включая информацию о счете, рекорде, уровне и скорости.
 */
void printStat(GameInfo_t CurrentState) {
  char buffer[30] = {0};
  snprintf(buffer, sizeof(buffer), "score");
  mvaddstr(SCORE_X, SCORE_Y, buffer);
  snprintf(buffer, sizeof(buffer), "%5.5d", CurrentState.score);
  mvaddstr(SCORE_NUM_X, SCORE_NUM_Y, buffer);
  snprintf(buffer, sizeof(buffer), "hi-score");
  mvaddstr(HI_SCORE_X, HI_SCORE_Y, buffer);
  snprintf(buffer, sizeof(buffer), "%5.5d", CurrentState.high_score);
  mvaddstr(HI_SCORE_NUM_X, HI_SCORE_NUM_Y, buffer);
  snprintf(buffer, sizeof(buffer), "NEXT");
  mvaddstr(NEXT_X, NEXT_Y, buffer);
  snprintf(buffer, sizeof(buffer), "level");
  mvaddstr(LEVEL_X, LEVEL_Y, buffer);
  snprintf(buffer, sizeof(buffer), "%2.2d", CurrentState.level);
  mvaddstr(LEVEL_NUM_X, LEVEL_NUM_Y, buffer);
  snprintf(buffer, sizeof(buffer), " speed");
  mvaddstr(SPEED_X, SPEED_Y, buffer);
  snprintf(buffer, sizeof(buffer), "%2.2d", CurrentState.speed);
  mvaddstr(SPEED_NUM_X, SPEED_NUM_Y, buffer);
}
