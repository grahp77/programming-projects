# 🎮 Tetris (C Language Implementation)

[![C](https://img.shields.io/badge/Language-C-blue.svg)](https://en.wikipedia.org/wiki/C_(programming_language))
[![Ncurses](https://img.shields.io/badge/UI-Ncurses-green.svg)](https://invisible-island.net/ncurses/)
[![Check](https://img.shields.io/badge/Testing-Check%20Framework-red.svg)](https://libcheck.github.io/check/)
[![License](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)

Классическая игра Тетрис, реализованная на языке C с использованием библиотеки ncurses для терминального интерфейса. Проект демонстрирует модульную архитектуру, unit-тестирование и покрытие кода.

## 📚 Оглавление
- [Особенности](#-особенности)
- [Структура проекта](#-структура-проекта)
- [Предварительные требования](#предварительные-требования)
- [Полная сборка и запуск игры](#полная-сборка-и-запуск-игры)
- [Управление в игре](#-управление-в-игре)
- [Тестирование](#-тестирование)
- [Документация](#-документация)
- [Создание дистрибутива](#-создание-дистрибутива)
- [Архитектура](#-архитектура)

## 🎯 Особенности

- **Классический геймплей** Тетрис с всеми знакомыми фигурами (тетрамино)
- **Терминальный интерфейс** на базе ncurses
- **Система рекордов** с сохранением результатов
- **Модульная архитектура** с разделением на backend и frontend
- **Полное покрытие unit-тестами** с использованием Check framework
- **Поддержка разных платформ** (Linux, macOS)

## 📁 Структура проекта
```
tetris/
├── brick_game/tetris/ # Логика игры (backend)
│ ├── backend.c
│ └── backend.h
├── gui/cli/ # Пользовательский интерфейс (frontend)
│ ├── frontend.c
│ └── frontend.h
├── test/ # Unit-тесты
│ ├── test.c
│ └── test_utils.c
├── tetris.c # Главный файл приложения
├── tetris.h # Основные заголовочные файлы
├── struct.h
├── highscore.txt # Таблица рекордов
├── Makefile # Система сборки
└── Doxyfile # Конфигурация документации
```


# 🛠 Сборка и установка

## Предварительные требования
```
Для Linux (Ubuntu/Debian):**
bash
sudo apt-get install build-essential check lcov doxygen graphviz
sudo apt-get install libncurses5-dev libncursesw5-dev
Для macOS:
brew install check lcov doxygen graphviz ncurses
```
## Полная сборка и запуск игры
```
make all
# Или поэтапно:
make install
# Запуск unit-тестов                         make test
# Генерация отчета о покрытии кода           make gcov_report
# Создание документации (Doxygen)            make dvi
# Проверка стиля кода                        make clang_format
# Создание дистрибутива                      make dist
# Очистка проекта                            make clean
```

## 🎮 Управление в игре
```
← → - Движение фигуры влево/вправо
↓ - Ускорение падения
↑ - Поворот фигуры
Пробел - Мгновенное падение (Drop)
P - Пауза
Q - Выход из игры
```

## 🧪 Тестирование
```
Проект включает комплекс unit-тестов для проверки корректности работы игровой логики:
make test
Для просмотра детального отчета о покрытии кода:
make gcov_report
```

## 📚 Документация
```
Генерация документации с помощью Doxygen:
make dvi
Документация будет создана в директории doc/html/ и автоматически откроется в браузере.
```
## 📦 Создание дистрибутива
```
Для создания архива с исходным кодом:
make dist
Будет создан архив tetris-1.0.tar.gz, содержащий все необходимые файлы проекта.
```
## 🏗 Архитектура
```
Проект построен по модульному принципу:
Backend (brick_game/tetris/) - чистая игровая логика
Frontend (gui/cli/) - отрисовка и взаимодействие с пользователем
Testing (test/) - модульные тесты и утилиты тестирования
```
## 🎯Наслаждайтесь игрой!
