# Decimal Library (C Language Implementation)

[![C](https://img.shields.io/badge/Language-C-blue.svg)](https://en.wikipedia.org/wiki/C_(programming_language))
[![Check](https://img.shields.io/badge/Testing-Check%20Framework-red.svg)](https://libcheck.github.io/check/)
[![Coverage](https://img.shields.io/badge/Coverage-lcov-green.svg)](http://ltp.sourceforge.net/coverage/lcov.php)
[![Standard](https://img.shields.io/badge/Coding%20Standard-C11-yellow.svg)](https://en.wikipedia.org/wiki/C11_(C_standard_revision))

Библиотека `s21_decimal` - это реализация типа данных decimal для языка C, аналогичная decimal в C#. Проект предоставляет точные арифметические операции с фиксированной запятой, что исключает ошибки округления при работе с финансовыми вычислениями.

## 📚 Оглавление

- [Особенности](#-особенности)
- [Структура проекта](#-структура-проекта)
- [Установка и сборка](#-установка-и-сборка)
- [Использование](#-использование)
- [Основные функции](#основные-функции)
- [Тестирование](#-тестирование)
- [Покрытие кода](#-покрытие-кода)
- [Команды Make](#команды-make)
- [Архитектура](#-архитектура)

## ✨ Особенности
```
- Точная арифметика** - операции без ошибок округления
- Полный набор операций** - арифметические, сравнения, преобразования
- Поддержка больших чисел** - работа с числами до 79,228,162,514,264,337,593,543,950,335
- Кросс-платформенность** - работает на Linux и macOS
- Полное тестовое покрытие** - проверка всех边界 случаев
```
## 📁 Структура проекта
```
decimal/
├── src
│ ├── s21_decimal.c
│ ├── s21_decimal.h
├── tests
│ ├── s21_tests_main.c
│ ├── s21_test_arithmetic.c
│ ├── s21_test_comparison.c│ 
├── Makefile
└── README.md
```

## 🛠 Установка и сборка

### Предварительные требования

Для Linux (Ubuntu/Debian):
```
sudo apt-get install build-essential check lcov
brew install check lcov
```
## 📖 Использование
```
Подключение библиотеки
#include "s21_decimal.h"

int main() {
    s21_decimal a = {0};
    s21_decimal b = {0};
    s21_decimal result = {0};
    
    // Инициализация значений
    s21_from_int_to_decimal(10, &a);
    s21_from_int_to_decimal(20, &b);
    
    // Сложение
    s21_add(a, b, &result);
    
    return 0;
}
```
## Основные функции
```
Арифметические операции:
s21_add() - сложение
s21_sub() - вычитание
s21_mul() - умножение
s21_div() - деление

Операции сравнения:
s21_is_less() - меньше
s21_is_greater() - больше
s21_is_equal() - равно

Преобразования:
s21_from_int_to_decimal() - из int в decimal
s21_from_decimal_to_int() - из decimal в int
s21_from_float_to_decimal() - из float в decimal
s21_from_decimal_to_float() - из decimal в float
```
## 🧪 Тестирование
```
Запуск тестов
make test
Тесты используют фреймворк Check и покрывают:
✅ Арифметические операции
✅ Операции сравнения
✅ Преобразования типов
✅ Граничные случаи
✅ Обработка ошибок
```

## 📊 Покрытие кода
```
Генерация отчета о покрытии
make gcov_report
Отчет будет сгенерирован в директории gcov_report/ и откроется в браузере.
```
## Команды Make
```
Команда	Описание
make all	Сборка статической библиотеки
make test	Запуск unit-тестов
make gcov_report	Генерация отчета о покрытии кода
make clean	Очистка проекта от временных файлов
```
## 🏗 Архитектура
```
Библиотека реализует тип s21_decimal как структуру из 4х 32-битных целых чисел, где:
Биты 0-15: не используются
Биты 16-23: степень десяти (exponent)
Бит 31: знак (0 - положительный, 1 - отрицательный)
Биты 32-95: мантисса (96-битное целое число)
```
