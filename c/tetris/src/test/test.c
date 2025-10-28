#include "test.h"

#include "test_utils.h"

// --- Тестовые функции ---

START_TEST(test_empty_board) {
  All_t *info = movementFigure();
  // matrixNull(info->CurrentState.field, HEIGHT, WIDTH);
  clearLineAndScore(info);
  ck_assert_int_eq(info->CurrentState.score, 0);
  ck_assert_int_eq(info->CurrentState.level, 0);
  ck_assert_int_eq(info->interval, 1000);
  exitGame(info);
}
END_TEST

START_TEST(test_clear_one_line) {
  All_t *info = movementFigure();

  // Заполняем одну линию.
  for (int j = 0; j < WIDTH; j++) {
    info->CurrentState.field[0][j] = 1;
  }

  clearLineAndScore(info);
  ck_assert_int_eq(info->CurrentState.score, 100);
  exitGame(info);
}
END_TEST

START_TEST(test_clear_multiple_lines) {
  All_t *info = movementFigure();

  // Заполняем несколько линий.
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < WIDTH; j++) {
      info->CurrentState.field[i][j] = 1;
    }
  }

  clearLineAndScore(info);
  ck_assert_int_eq(info->CurrentState.score, 700);
  removeAllocation(&info->CurrentState.field, 20);
  exitGame(info);
}
END_TEST

START_TEST(test_lines_shifted_down) {
  All_t *info = movementFigure();

  // Заполняем первую и третью линии, чтобы проверить сдвиг.
  for (int j = 0; j < WIDTH; j++) {
    info->CurrentState.field[0][j] = 1;
    info->CurrentState.field[2][j] = 1;
  }

  clearLineAndScore(info);

  // Проверяем, что первые две линии очищены.
  for (int j = 0; j < WIDTH; j++) {
    ck_assert_int_eq(info->CurrentState.field[0][j], 0);
    ck_assert_int_eq(info->CurrentState.field[1][j], 0);
  }

  // Проверяем, что третья линия (теперь вторая) также очищена.
  for (int j = 0; j < WIDTH; j++) {
    ck_assert_int_eq(info->CurrentState.field[2][j], 0);
  }

  ck_assert_int_eq(info->CurrentState.score, 300);
  exitGame(info);
}
END_TEST

START_TEST(test_level_increase) {
  All_t *info = movementFigure();
  info->CurrentState.score = 700;

  // Заполняем линии так, чтобы после очистки счет стал больше 600.
  for (int i = 0; i < 1; i++) {
    for (int j = 0; j < WIDTH; j++) {
      info->CurrentState.field[i][j] = 1;
    }
  }
  clearLineAndScore(info);

  ck_assert_int_eq(info->CurrentState.level, 1);
  ck_assert_int_eq(info->interval, 920);  // 1000 - 1 * 80
  exitGame(info);
}
END_TEST

START_TEST(test_copyMatrix) {
  All_t *info = movementFigure();

  figure(&info->CurrentState, 1);
  copyMatrix(info->CurrentState.next, info->temp_figure);

  ck_assert_int_eq(matricesAreEqual(info->CurrentState.next, info->temp_figure),
                   1);
  exitGame(info);
}
END_TEST

START_TEST(test_nextFigureNull) {
  All_t *info = movementFigure();

  figure(&info->CurrentState, 2);
  matrixNull(info->CurrentState.next);

  ck_assert_int_eq(matrixesAreReset(&info->CurrentState), 1);
  exitGame(info);
}
END_TEST

START_TEST(test_load_highscore) {
  int highscore = 63700;
  save_highscore(highscore);

  ck_assert_int_eq(load_highscore(), 63700);
}
END_TEST

START_TEST(test_moveup) {
  All_t *info = movementFigure();
  spawn(info);
  int number_figure = 5;
  info->left_right = -1;
  info->move = 3;
  info->current_action = Action;
  figure(&info->CurrentState, number_figure);
  moving(info);

  ck_assert_int_eq(matricesAreEqual(info->current_figure, info->temp_figure),
                   1);
  exitGame(info);
}
END_TEST

START_TEST(test_movedown) {
  All_t *info = movementFigure();

  figure(&info->CurrentState, 1);
  spawn(info);
  info->current_action = Down;
  moving(info);
  int **field2;
  memoryAllocation(&field2, 20, 10);
  field2[17][6] = 1;
  field2[18][5] = 1;
  field2[18][6] = 1;
  field2[19][5] = 1;

  ck_assert_int_eq(matricesAreEqualField(info->CurrentState.field, field2), 1);
  exitGame(info);
  removeAllocation(&field2, 20);
}
END_TEST

START_TEST(test_moveright) {
  All_t *info = movementFigure();

  figure(&info->CurrentState, 1);
  spawn(info);
  info->move = 1;
  info->left_right = 4;
  info->current_action = Right;
  moving(info);
  int **field2;
  memoryAllocation(&field2, 20, 10);
  field2[0][7] = 1;
  field2[1][6] = 1;
  field2[1][7] = 1;
  field2[2][6] = 1;

  ck_assert_int_eq(matricesAreEqualField(info->CurrentState.field, field2), 1);
  exitGame(info);
  removeAllocation(&field2, 20);
}
END_TEST

START_TEST(test_moveleft) {
  All_t *info = movementFigure();

  figure(&info->CurrentState, 1);
  spawn(info);
  info->move = 1;
  info->left_right = 4;
  info->current_action = Left;
  moving(info);
  int **field2;
  memoryAllocation(&field2, 20, 10);
  field2[0][5] = 1;
  field2[1][4] = 1;
  field2[1][5] = 1;
  field2[2][4] = 1;

  ck_assert_int_eq(matricesAreEqualField(info->CurrentState.field, field2), 1);
  exitGame(info);
  removeAllocation(&field2, 20);
}
END_TEST

START_TEST(test_shifting) {
  All_t *info = movementFigure();

  figure(&info->CurrentState, 1);
  spawn(info);
  info->move = 0;
  info->left_right = 4;
  shifting(info);
  int **field2;
  memoryAllocation(&field2, 20, 10);
  field2[0][6] = 1;
  field2[1][5] = 1;
  field2[1][6] = 1;
  field2[2][5] = 1;

  ck_assert_int_eq(matricesAreEqualField(info->CurrentState.field, field2), 1);
  exitGame(info);
  removeAllocation(&field2, 20);
}
END_TEST

START_TEST(test_gameOver) {
  All_t *info = movementFigure();

  figure(&info->CurrentState, 5);
  spawn(info);
  info->move = 0;
  info->left_right = 4;
  shifting(info);
  while (info->State != Start_game) {
    gameOver(info);
  }
  int **field2;
  memoryAllocation(&field2, 20, 10);

  ck_assert_int_eq(matricesAreEqualField(info->CurrentState.field, field2), 1);
  exitGame(info);
  removeAllocation(&field2, 20);
}
END_TEST

START_TEST(test_userInput_Left) {
  All_t *info = movementFigure();
  UserAction_t action = 0;
  info->CurrentState.pause = 3;
  action = Left;
  userInput(action, 1);

  ck_assert_int_eq(info->current_action, Left);
  exitGame(info);
}
END_TEST

START_TEST(test_userInput_Right) {
  All_t *info = movementFigure();
  UserAction_t action = 0;
  info->CurrentState.pause = 3;
  action = Right;
  userInput(action, 1);

  ck_assert_int_eq(info->current_action, Right);
  exitGame(info);
}
END_TEST

START_TEST(test_userInput_Up) {
  All_t *info = movementFigure();
  UserAction_t action = 0;
  info->CurrentState.pause = 3;
  action = Up;
  userInput(action, 1);

  ck_assert_int_eq(info->current_action, Action);
  exitGame(info);
}
END_TEST

START_TEST(test_userInput_Down) {
  All_t *info = movementFigure();
  UserAction_t action = 0;
  info->CurrentState.pause = 3;
  action = Down;
  userInput(action, 1);

  ck_assert_int_eq(info->current_action, Down);
  exitGame(info);
}
END_TEST

START_TEST(test_userInput_Pause) {
  All_t *info = movementFigure();
  UserAction_t action = 0;
  info->CurrentState.pause = 2;
  action = Pause;
  userInput(action, 1);

  ck_assert_int_eq(info->State, Shifting);
  exitGame(info);
}
END_TEST

START_TEST(test_userInput_Start) {
  All_t *info = movementFigure();
  UserAction_t action = 0;
  info->CurrentState.pause = 1;
  action = Start;
  userInput(action, 1);

  ck_assert_int_eq(info->current_action, Start);
  exitGame(info);
}
END_TEST

START_TEST(test_userInput_Exit) {
  All_t *info = movementFigure();
  UserAction_t action = 0;
  info->CurrentState.pause = 1;
  action = Exit;
  userInput(action, 1);

  ck_assert_int_eq(info->current_action, Exit);
  exitGame(info);
}
END_TEST

START_TEST(test_startGame) {
  All_t *info = movementFigure();
  info->CurrentState.pause = 34;
  info->interval = 15;
  info->CurrentState.score = 2;
  info->CurrentState.level = 3;
  info->CurrentState.speed = 4;
  info->State = 45;
  startGame(info);

  ck_assert_int_eq(info->CurrentState.pause, 3);
  ck_assert_int_eq(info->interval, 1000);
  ck_assert_int_eq(info->CurrentState.score, 0);
  ck_assert_int_eq(info->CurrentState.level, 0);
  ck_assert_int_eq(info->CurrentState.speed, 0);
  ck_assert_int_eq(info->State, Spawn);
  exitGame(info);
}
END_TEST

START_TEST(test_checkAttaching) {
  All_t *info = movementFigure();
  figure(&info->CurrentState, 1);
  spawn(info);
  info->move = -2;
  info->left_right = 4;
  info->CurrentState.field[0][5] = 1;

  checkAttaching(info);

  ck_assert_int_eq(info->State, Game_over);
  exitGame(info);
}
END_TEST

START_TEST(test_figure_1) {
  All_t *info = movementFigure();
  figure(&info->CurrentState, 1);
  info->current_figure[0][2] = 1;
  info->current_figure[1][1] = 1;
  info->current_figure[1][2] = 1;
  info->current_figure[2][1] = 1;

  ck_assert_int_eq(
      matricesAreEqual(info->CurrentState.next, info->current_figure), 1);
  exitGame(info);
}
END_TEST

START_TEST(test_figure_2) {
  All_t *info = movementFigure();
  figure(&info->CurrentState, 2);
  info->current_figure[0][1] = 1;
  info->current_figure[1][1] = 1;
  info->current_figure[1][2] = 1;
  info->current_figure[2][2] = 1;

  ck_assert_int_eq(
      matricesAreEqual(info->CurrentState.next, info->current_figure), 1);
  exitGame(info);
}
END_TEST

START_TEST(test_figure_3) {
  All_t *info = movementFigure();
  figure(&info->CurrentState, 3);
  info->current_figure[0][0] = 1;
  info->current_figure[0][1] = 1;
  info->current_figure[1][1] = 1;
  info->current_figure[2][1] = 1;

  ck_assert_int_eq(
      matricesAreEqual(info->CurrentState.next, info->current_figure), 1);
  exitGame(info);
}
END_TEST

START_TEST(test_figure_4) {
  All_t *info = movementFigure();
  figure(&info->CurrentState, 4);
  info->current_figure[0][1] = 1;
  info->current_figure[0][2] = 1;
  info->current_figure[1][1] = 1;
  info->current_figure[2][1] = 1;

  ck_assert_int_eq(
      matricesAreEqual(info->CurrentState.next, info->current_figure), 1);
  exitGame(info);
}
END_TEST

START_TEST(test_figure_5) {
  All_t *info = movementFigure();
  figure(&info->CurrentState, 5);
  info->current_figure[0][1] = 1;
  info->current_figure[1][0] = 1;
  info->current_figure[1][1] = 1;
  info->current_figure[1][2] = 1;

  ck_assert_int_eq(
      matricesAreEqual(info->CurrentState.next, info->current_figure), 1);
  exitGame(info);
}
END_TEST

START_TEST(test_figure_6) {
  All_t *info = movementFigure();
  figure(&info->CurrentState, 6);
  info->current_figure[1][1] = 1;
  info->current_figure[1][2] = 1;
  info->current_figure[2][1] = 1;
  info->current_figure[2][2] = 1;

  ck_assert_int_eq(
      matricesAreEqual(info->CurrentState.next, info->current_figure), 1);
  exitGame(info);
}
END_TEST

START_TEST(test_figure_7) {
  All_t *info = movementFigure();
  figure(&info->CurrentState, 7);
  info->current_figure[0][1] = 1;
  info->current_figure[1][1] = 1;
  info->current_figure[2][1] = 1;
  info->current_figure[3][1] = 1;

  ck_assert_int_eq(
      matricesAreEqual(info->CurrentState.next, info->current_figure), 1);
  exitGame(info);
}
END_TEST

// --- Создание набора тестов и добавление тестов ---

Suite *backend_suite(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("Backend");

  /* Core test case */
  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_empty_board);
  tcase_add_test(tc_core, test_clear_one_line);
  tcase_add_test(tc_core, test_clear_multiple_lines);
  tcase_add_test(tc_core, test_lines_shifted_down);
  tcase_add_test(tc_core, test_level_increase);
  tcase_add_test(tc_core, test_copyMatrix);
  tcase_add_test(tc_core, test_nextFigureNull);
  tcase_add_test(tc_core, test_load_highscore);
  tcase_add_test(tc_core, test_moveup);
  tcase_add_test(tc_core, test_movedown);
  tcase_add_test(tc_core, test_moveright);
  tcase_add_test(tc_core, test_moveleft);
  tcase_add_test(tc_core, test_shifting);
  tcase_add_test(tc_core, test_gameOver);
  tcase_add_test(tc_core, test_userInput_Left);
  tcase_add_test(tc_core, test_userInput_Right);
  tcase_add_test(tc_core, test_userInput_Up);
  tcase_add_test(tc_core, test_userInput_Down);
  tcase_add_test(tc_core, test_userInput_Pause);
  tcase_add_test(tc_core, test_userInput_Start);
  tcase_add_test(tc_core, test_userInput_Exit);
  tcase_add_test(tc_core, test_startGame);
  tcase_add_test(tc_core, test_checkAttaching);
  tcase_add_test(tc_core, test_figure_1);
  tcase_add_test(tc_core, test_figure_2);
  tcase_add_test(tc_core, test_figure_3);
  tcase_add_test(tc_core, test_figure_4);
  tcase_add_test(tc_core, test_figure_5);
  tcase_add_test(tc_core, test_figure_6);
  tcase_add_test(tc_core, test_figure_7);
  suite_add_tcase(s, tc_core);

  return s;
}

int main(void) {
  int number_failed;
  Suite *s;
  SRunner *sr;

  s = backend_suite();
  sr = srunner_create(s);

  srunner_run_all(sr, CK_NORMAL);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);
  return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}