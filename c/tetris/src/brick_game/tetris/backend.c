#include "backend.h"

/**
 * @brief Обновляет текущее состояние игры.
 *
 * Эта функция извлекает текущее состояние игры из функции `movementFigure`.
 *
 * @return Копия структуры `GameInfo_t`, представляющая текущее состояние игры.
 */
GameInfo_t updateCurrentState() {
  All_t *ptr = movementFigure();
  return ptr->CurrentState;
}

/**
 * @brief Обрабатывает ввод пользователя и соответствующим образом обновляет
 * состояние игры.
 *
 * Эта функция обрабатывает действия пользователя, такие как перемещение фигуры,
 * приостановка игры, начало новой игры или выход из игры.
 *
 * @param action Действие пользователя, которое необходимо обработать (например,
 * Left, Right, Up, Down, Pause, Start, Exit).
 * @param hold Логическое значение, указывающее, удерживает ли пользователь
 * кнопку действия.
 */
void userInput(UserAction_t action, bool hold) {
  if (hold && action) {
    All_t *info = movementFigure();
    if (info->CurrentState.pause == 3 && action != Start && action != Exit) {
      if (action == Left) {
        info->current_action = Left;
      } else if (action == Right) {
        info->current_action = Right;
      } else if (action == Up || action == Action) {
        info->current_action = Action;
      } else if (action == Down) {
        info->current_action = Down;
      }
      info->State = Moving;
    }
    if (action == Pause && info->CurrentState.pause != 1) {
      if (info->CurrentState.pause == 2) {
        info->CurrentState.pause = 3;
        info->State = Shifting;
      } else {
        info->current_action = Pause;
        info->CurrentState.pause = 2;
      }
    } else if (action == Start && info->CurrentState.pause == 1) {
      info->current_action = Start;
      info->State = Start_game;
    } else if (action == Exit && (info->CurrentState.pause == 1 ||
                                  info->CurrentState.pause == 2)) {
      info->current_action = Exit;
      info->State = Start_game;
    }
  }
}

/**
 * @brief Управляет движением фигуры и состоянием игры с использованием
 * конечного автомата.
 *
 * Эта функция извлекает соответствующее действие из конечного автомата на
 * основе текущего состояния игры и ввода пользователя, а затем выполняет это
 * действие.
 *
 * @return Указатель на структуру `All_t`, содержащую обновленную информацию об
 * игре.
 */
All_t *movementFigure() {
  action act = NULL;
  static All_t info = {0};
  memoryAllcationAll(&info);
  act = fsm_state(info.State, info.current_action);
  if (act) {
    act(&info);
  }
  return &info;
}

/**
 * @brief Выделяет память для структур данных игры.
 *
 * Эта функция выделяет память для игрового поля, следующей фигуры, текущей
 * фигуры и временной фигуры. Она гарантирует, что память будет выделена только
 * один раз в начале игры.
 *
 * @param info Указатель на структуру `All_t`, где будет храниться выделенная
 * память.
 */
void memoryAllcationAll(All_t *info) {
  if (!info->start) {
    info->start = 1;
    info->CurrentState.pause = 1;
    memoryAllocation(&info->CurrentState.field, HEIGHT, WIDTH);
    memoryAllocation(&info->CurrentState.next, 4, 4);
    memoryAllocation(&info->current_figure, 4, 4);
    memoryAllocation(&info->temp_figure, 4, 4);
  }
}

/**
 * @brief Выделяет память для двумерной матрицы целых чисел.
 *
 * Эта функция выделяет память для двумерной матрицы целых чисел с указанным
 * количеством строк и столбцов. Она обрабатывает ошибки выделения памяти и
 * возвращает код ошибки в случае сбоя выделения.
 *
 * @param matrix Указатель на указатель на указатель на целое число. Это будет
 * установлено для указания на выделенную матрицу.
 * @param rows Количество строк в матрице.
 * @param cols Количество столбцов в матрице.
 * @return 0 в случае успеха, 1 в случае неудачи.
 */
int memoryAllocation(int ***matrix, int rows, int cols) {
  int ret = 0;
  *matrix = (int **)calloc(rows, sizeof(int *));
  if (*matrix == NULL) {
    ret = 1;
  }
  for (int i = 0; i < rows && !ret; i++) {
    (*matrix)[i] = (int *)calloc(cols, sizeof(int));
    if ((*matrix)[i] == NULL) {
      for (int k = 0; k < i; k++) {
        free((*matrix)[k]);
      }
      free(*matrix);
      *matrix = NULL;
      ret = 1;
    }
  }
  return ret;
}

/**
 * @brief Извлекает соответствующее действие из таблицы конечного автомата.
 *
 * Эта функция возвращает указатель на функцию, которую необходимо выполнить, на
 * основе текущего состояния игры и текущего действия пользователя.
 *
 * @param State Текущее состояние игры (например, Start_game, Spawn, Shifting).
 * @param current_action Текущее действие, выполняемое пользователем (например,
 * Left, Right, Action).
 * @return Указатель на функцию, соответствующую текущему состоянию и действию.
 */
action fsm_state(int State, int current_action) {
  static const action fsm_table[7][9] = {
      {NULL, startGame, NULL, NULL, NULL, NULL, NULL, NULL, exitGame},
      {spawn, spawn, spawn, spawn, spawn, spawn, spawn, spawn, spawn},
      {NULL, NULL, NULL, moving, moving, moving, moving, moving, moving},
      {shifting, shifting, shifting, shifting, shifting, shifting, shifting,
       shifting, shifting},
      {checkAttaching, checkAttaching, checkAttaching, checkAttaching,
       checkAttaching, checkAttaching, checkAttaching, checkAttaching,
       checkAttaching},
      {NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL},
      {gameOver, gameOver, gameOver, gameOver, gameOver, gameOver, gameOver,
       gameOver}};
  return fsm_table[State][current_action];
}

/**
 * @brief Начинает новую игру.
 *
 * Эта функция инициализирует состояние игры, загружает рекорд, генерирует
 * первую фигуру и устанавливает состояние игры в Spawn.
 *
 * @param info Указатель на структуру `All_t`, содержащую информацию об игре.
 */
void startGame(All_t *info) {
  info->CurrentState.pause = 3;
  info->interval = 1000;
  info->CurrentState.score = 0;
  info->CurrentState.level = 0;
  info->CurrentState.speed = 0;
  info->CurrentState.high_score = load_highscore();
  info->number_random_figure = (rand() % (MAX - MIN + 1)) + MIN;
  figure(&info->CurrentState, info->number_random_figure);
  info->State = Spawn;
}

/**
 * @brief Загружает рекорд из файла.
 *
 * Эта функция считывает рекорд из файла, указанного в `HIGHSCORE_FILE`.
 *
 * @return Рекорд, загруженный из файла.
 */
int load_highscore() {
  FILE *file = fopen(HIGHSCORE_FILE, "r");
  int highscore = 0;
  fscanf(file, "%d", &highscore);
  fclose(file);
  return highscore;
}

/**
 * @brief Создает новую фигуру в верхней части игрового поля.
 *
 * Эта функция устанавливает начальную позицию новой фигуры, копирует следующую
 * фигуру в текущую фигуру, генерирует новую следующую фигуру и устанавливает
 * состояние игры в Shifting.
 *
 * @param info Указатель на структуру `All_t`, содержащую информацию об игре.
 */
void spawn(All_t *info) {
  info->move = FIGURE_START_X;
  info->left_right = FIGURE_START_Y;
  info->prev_move = info->move;
  copyMatrix(info->current_figure, info->CurrentState.next);
  matrixNull(info->CurrentState.next);
  info->number_cur_figure = info->number_random_figure;
  info->number_random_figure = (rand() % (MAX - MIN + 1)) + MIN;
  figure(&info->CurrentState, info->number_random_figure);
  info->State = Shifting;
}

/**
 * @brief Копирует содержимое одной двумерной матрицы целых чисел в другую.
 *
 * @param result Указатель на целевую матрицу.
 * @param matrix Указатель на исходную матрицу.
 */
void copyMatrix(int **result, int **matrix) {
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      result[i][j] = matrix[i][j];
    }
  }
}

/**
 * @brief Устанавливает все элементы двумерной матрицы целых чисел в 0.
 *
 * @param matrix Указатель на матрицу, которую нужно обнулить.
 */
void matrixNull(int **matrix) {
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      matrix[i][j] = 0;
    }
  }
}

/**
 * @brief Определяет форму следующей фигуры для появления.
 *
 * Эта функция устанавливает значения в матрице `CurrentState->next`, чтобы
 * представить форму следующей случайным образом выбранной фигуры.
 *
 * @param CurrentState Указатель на структуру `GameInfo_t`, содержащую состояние
 * игры.
 * @param number_random_figure Целое число, представляющее тип фигуры, которую
 * нужно создать.
 */
void figure(GameInfo_t *CurrentState, int number_random_figure) {
  if (number_random_figure == 1) {
    CurrentState->next[0][2] = 1;
    CurrentState->next[1][1] = 1;
    CurrentState->next[1][2] = 1;
    CurrentState->next[2][1] = 1;
  }
  if (number_random_figure == 2) {
    CurrentState->next[0][1] = 1;
    CurrentState->next[1][1] = 1;
    CurrentState->next[1][2] = 1;
    CurrentState->next[2][2] = 1;
  }
  if (number_random_figure == 3) {
    CurrentState->next[0][0] = 1;
    CurrentState->next[0][1] = 1;
    CurrentState->next[1][1] = 1;
    CurrentState->next[2][1] = 1;
  }
  if (number_random_figure == 4) {
    CurrentState->next[0][1] = 1;
    CurrentState->next[0][2] = 1;
    CurrentState->next[1][1] = 1;
    CurrentState->next[2][1] = 1;
  }
  if (number_random_figure == 5) {
    CurrentState->next[0][1] = 1;
    CurrentState->next[1][0] = 1;
    CurrentState->next[1][1] = 1;
    CurrentState->next[1][2] = 1;
  }
  if (number_random_figure == 6) {
    CurrentState->next[1][1] = 1;
    CurrentState->next[1][2] = 1;
    CurrentState->next[2][1] = 1;
    CurrentState->next[2][2] = 1;
  }
  if (number_random_figure == 7) {
    CurrentState->next[0][1] = 1;
    CurrentState->next[1][1] = 1;
    CurrentState->next[2][1] = 1;
    CurrentState->next[3][1] = 1;
  }
}

/**
 * @brief Сдвигает текущую фигуру вниз.
 *
 * Эта функция перемещает текущую фигуру вниз по игровому полю до тех пор, пока
 * она не столкнется с дном или другой фигурой. Она использует таймер для
 * управления скоростью сдвига.
 *
 * @param info Указатель на структуру `All_t`, содержащую информацию об игре.
 */
void shifting(All_t *info) {
  long long current_time = get_milliseconds();
  if (info->last_time == 0 ||
      (current_time - info->last_time) >= info->interval) {
    info->last_time = current_time;
    figureMooveNull(info);
    if (collisionCheck(info)) {
      info->move--;
      info->State = Attaching;
    }
    figureMoove(info);

    info->prev_move = info->move;
    info->move++;
  }
}

/**
 * @brief Возвращает текущее время в миллисекундах.
 *
 * @return Текущее время в миллисекундах.
 */
long long get_milliseconds() {
  struct timespec ts;
  clock_gettime(CLOCK_MONOTONIC, &ts);
  return (long long)(ts.tv_sec * 1000LL + ts.tv_nsec / 1000000);
}

/**
 * @brief Удаляет текущую фигуру с игрового поля.
 *
 * Эта функция устанавливает ячейки на игровом поле, занятые текущей фигурой, в
 * 0. Это делается перед перемещением фигуры на новую позицию.
 *
 * @param info Указатель на структуру `All_t`, содержащую информацию об игре.
 */
void figureMooveNull(All_t *info) {
  for (int i = info->prev_move, x = 0; i < info->prev_move + 4; i++, x++) {
    for (int j = info->left_right, y = 0; j < info->left_right + 4; j++, y++) {
      if (i >= 0 && info->current_figure[x][y] == 1) {
        info->CurrentState.field[i][j] = 0;
      }
    }
  }
}

/**
 * @brief Проверяет столкновения между текущей фигурой и игровым полем.
 *
 * Эта функция проверяет, сталкивается ли текущая фигура с границами игрового
 * поля или с другими фигурами, которые уже находятся в поле.
 *
 * @param info Указатель на структуру `All_t`, содержащую информацию об игре.
 * @return 1, если происходит столкновение, 0 в противном случае.
 */
int collisionCheck(All_t *info) {
  int flag = 0;
  for (int i = info->move + 3, x = 3; i >= info->move && !flag; i--, x--) {
    for (int j = info->left_right, y = 0; j < info->left_right + 4 && !flag;
         j++, y++) {
      if ((j == -1 && info->current_figure[x][y] == 1) ||
          (j == 10 && info->current_figure[x][y] == 1)) {
        flag = 1;
      } else if ((i == 20 && info->current_figure[x][y] == 1) ||
                 (i >= 0 && info->current_figure[x][y] == 1 &&
                  info->CurrentState.field[i][j] == 1)) {
        flag = 1;
      }
    }
  }
  return flag;
}

/**
 * @brief Перемещает текущую фигуру на игровое поле.
 *
 * Эта функция устанавливает ячейки на игровом поле, занятые текущей фигурой,
 * в 1.
 *
 * @param info Указатель на структуру `All_t`, содержащую информацию об игре.
 */
void figureMoove(All_t *info) {
  for (int i = info->move, x = 0; i < info->move + 4; i++, x++) {
    for (int j = info->left_right, y = 0; j < info->left_right + 4; j++, y++) {
      if (i >= 0 && info->current_figure[x][y] == 1) {
        info->CurrentState.field[i][j] = info->current_figure[x][y];
      }
    }
  }
}

/**
 * @brief Перемещает фигуру в соответствии с вводом пользователя.
 *
 * Эта функция обрабатывает ввод пользователя влево, вправо, вниз и действие
 * (поворот) для перемещения текущей фигуры, проверяя столкновения.
 *
 * @param info Указатель на структуру `All_t`, содержащую информацию об игре.
 */
void moving(All_t *info) {
  bool flag = false;
  info->State = Shifting;
  figureMooveNull(info);
  info->move--;
  if (info->current_action == Left) {
    moveleft(info);
  } else if (info->current_action == Right) {
    moveright(info);
  } else if (info->current_action == Action) {
    moveup(info);
  } else if (info->current_action == Down) {
    movedown(info);
    flag = true;
  }
  if (!flag) {
    figureMoove(info);
    info->prev_move = info->move;
    info->move++;
  }
}

/**
 * @brief Перемещает фигуру влево.
 *
 * @param info Указатель на структуру `All_t`, содержащую информацию об игре.
 */
void moveleft(All_t *info) {
  info->left_right--;
  if (collisionCheck(info)) {
    info->left_right++;
  }
}

/**
 * @brief Перемещает фигуру вправо.
 *
 * @param info Указатель на структуру `All_t`, содержащую информацию об игре.
 */
void moveright(All_t *info) {
  info->left_right++;
  if (collisionCheck(info)) {
    info->left_right--;
  }
}

/**
 * @brief Перемещает фигуру вниз как можно быстрее.
 *
 * @param info Указатель на структуру `All_t`, содержащую информацию об игре.
 */
void movedown(All_t *info) {
  while (!collisionCheck(info)) {
    info->move++;
  }
  info->move--;
  figureMoove(info);
  info->State = Attaching;
}

/**
 * @brief Поворачивает фигуру.
 *
 * @param info Указатель на структуру `All_t`, содержащую информацию об игре.
 */
void moveup(All_t *info) {
  copyMatrix(info->temp_figure, info->current_figure);
  turn(info);
  info->previous_left_right = info->left_right;
  if (collisionCheck(info) && info->left_right < 0) {
    info->left_right++;
  }
  if (collisionCheck(info) && info->left_right > 6) {
    info->left_right--;
  }
  if (collisionCheck(info)) {
    info->left_right = info->previous_left_right;
    copyMatrix(info->current_figure, info->temp_figure);
  }
}

/**
 * @brief Применяет логику вращения к матрице фигуры.
 *
 * @param info Указатель на структуру `All_t`, содержащую информацию об игре.
 */
void turn(All_t *info) {
  int x = 0;
  if (info->number_cur_figure > 2 && info->number_cur_figure < 6) {
    x = 2;
  } else
    x = 3;
  for (int i = 0, z = x; i <= x; i++, z--) {
    for (int j = 0; j <= x; j++) {
      info->current_figure[i][j] = info->temp_figure[j][z];
    }
  }
}

/**
 * @brief Проверяет, прикрепилась ли фигура к дну или к другой фигуре.
 *
 * Если фигура прикрепилась, она очищает любые заполненные линии и затем создает
 * новую фигуру.
 *
 * @param info Указатель на структуру `All_t`, содержащую информацию об игре.
 */
void checkAttaching(All_t *info) {
  clearLineAndScore(info);
  info->State = Spawn;
  int flag = 0;
  for (int i = info->move + 3, x = 3; i >= info->move && !flag; i--, x--) {
    for (int j = info->left_right, y = 0; j < info->left_right + 4 && !flag;
         j++, y++) {
      if (i == 0 && info->current_figure[x][y] == 1 &&
          info->CurrentState.field[i][j] == 1) {
        info->State = Game_over;
        info->CurrentState.pause = 1;
        info->move = 20;
        flag = 1;
      }
    }
  }
}

/**
 * @brief Очищает завершенные линии и обновляет счет.
 *
 * Эта функция выполняет итерацию по игровому полю и проверяет наличие
 * завершенных линий. Если линия завершена, она сдвигает линии над ней вниз,
 * обновляет счет, уровень и скорость.
 *
 * @param info Указатель на структуру `All_t`, содержащую информацию об игре.
 */
void clearLineAndScore(All_t *info) {
  int score = 0;
  for (int i = 0; i < 20; i++) {
    for (int j = 0, count = 0; j < 10; j++) {
      if (info->CurrentState.field[i][j]) {
        count++;
      } else
        count--;
      if (count == 10) {
        shiftingDownwards(info, i);
        score++;
      }
    }
  }
  if (score == 1) {
    info->CurrentState.score += 100;
  } else if (score == 2) {
    info->CurrentState.score += 300;
  } else if (score == 3) {
    info->CurrentState.score += 700;
  } else if (score == 4) {
    info->CurrentState.score += 1500;
  }
  if (info->CurrentState.level < 10) {
    info->CurrentState.level = info->CurrentState.score / 600;
    if (info->CurrentState.level > 10) {
      info->CurrentState.level = 10;
    }
    info->interval = 1000 - info->CurrentState.level * 80;
  }
  info->CurrentState.speed = info->CurrentState.level;
  if (info->CurrentState.score > info->CurrentState.high_score) {
    info->CurrentState.high_score = info->CurrentState.score;
    save_highscore(info->CurrentState.high_score);
  }
}

/**
 * @brief Сдвигает линии над заданной линией вниз.
 *
 * Эта функция сдвигает все линии над заданной линией вниз на одну строку, чтобы
 * заполнить очищенную линию.
 *
 * @param info Указатель на структуру `All_t`, содержащую информацию об игре.
 * @param line Индекс линии, которая была очищена.
 */
void shiftingDownwards(All_t *info, int line) {
  for (int i = line; i >= 0; i--) {
    for (int j = 0; j < 10; j++) {
      if (i > 0) {
        info->CurrentState.field[i][j] = info->CurrentState.field[i - 1][j];
      } else if (i == 0) {
        info->CurrentState.field[i][j] = 0;
      }
    }
  }
}

/**
 * @brief Сохраняет рекорд в файл.
 *
 * Эта функция сохраняет текущий рекорд в файл, указанный в `HIGHSCORE_FILE`.
 *
 * @param highscore Рекорд, который нужно сохранить.
 */
void save_highscore(int highscore) {
  FILE *file = fopen(HIGHSCORE_FILE, "w");

  fprintf(file, "%d", highscore);
  fclose(file);
}

/**
 * @brief Обрабатывает состояние "игра окончена".
 *
 * Эта функция анимирует последовательность "игра окончена", перемещая линию по
 * полю.
 *
 * @param info Указатель на структуру `All_t`, содержащую информацию об игре.
 */
void gameOver(All_t *info) {
  long long current_time = get_milliseconds();
  long long interval = 1;
  static long long last_time = 0;
  static int flag = 0;
  if (last_time == 0 || (current_time - last_time) >= interval) {
    last_time = current_time;
    if (info->move > 0 && !flag) {
      info->move--;
      grafic(info, 1);
    } else if (info->move < 20) {
      grafic(info, 0);
      info->move++;
      flag = 1;
    } else if (info->move == 20 && flag) {
      info->State = Start_game;
      info->CurrentState.pause = 1;
      info->current_action = 0;
      flag = 0;
    }
  }
  matrixNull(info->CurrentState.next);
  matrixNull(info->current_figure);
  matrixNull(info->temp_figure);
}

/**
 * @brief Заполняет линию на поле.
 *
 * Эта функция заполняет линию 1 или 0 в зависимости от значения x.
 *
 * @param info Указатель на структуру `All_t`, содержащую информацию об игре.
 * @param x Значение, которым нужно заполнить линию.
 */
void grafic(All_t *info, bool x) {
  for (int j = 0; j < WIDTH; j++) {
    info->CurrentState.field[info->move][j] = x;
  }
}

/**
 * @brief Освобождает всю выделенную память и сбрасывает паузу
 *
 * Эта функция вызывается при выходе из игры для освобождения памяти.
 *
 * @param info Указатель на структуру `All_t`, содержащую информацию об игре.
 */
void exitGame(All_t *info) {
  removeAllocation(&info->CurrentState.field, HEIGHT);
  removeAllocation(&info->CurrentState.next, 4);
  removeAllocation(&info->current_figure, 4);
  removeAllocation(&info->temp_figure, 4);
  info->CurrentState.pause = 0;
}

/**
 * @brief Удаляет выделенную матрицу
 *
 * Эта функция освобождает память, выделенную для двойного указателя, то есть
 * матрицы.
 *
 * @param matrix Тройной указатель на матрицу.
 * @param rows Количество строк матрицы.
 */
void removeAllocation(int ***matrix, int rows) {
  if (matrix != NULL && *matrix != NULL) {
    for (int i = 0; i < rows; i++) {
      if ((*matrix)[i] != NULL) {
        free((*matrix)[i]);
        (*matrix)[i] = NULL;
      }
    }
    free(*matrix);
    *matrix = NULL;
  }
}
