# String+ (s21_string)

[![C](https://img.shields.io/badge/Language-C-blue.svg)](https://en.wikipedia.org/wiki/C_(programming_language))
[![Standard](https://img.shields.io/badge/Standard-C11-yellow.svg)](https://en.wikipedia.org/wiki/C11_(C_standard_revision))
[![Check](https://img.shields.io/badge/Testing-Check%20Framework-red.svg)](https://libcheck.github.io/check/)
[![Coverage](https://img.shields.io/badge/Coverage-Gcov/Lcov-green.svg)](http://ltp.sourceforge.net/coverage/lcov.php)

Полнофункциональная реализация стандартной библиотеки string.h на языке C с дополнительными функциями для работы со строками. Проект включает собственную реализацию основных строковых функций и частичную реализацию sprintf.

## 📋 Оглавление

- [О проекте](#-о-проекте)
- [Функциональность](#-функциональность)
- [Сборка и установка](#-сборка-и-установка)
- [Использование](#-использование)
- [Команды Makefile](#-команды-makefile)
- [Структура проекта](#-структура-проекта)

## 🚀 О проекте

**String+** — это образовательный проект, представляющий собой перереализация стандартной библиотеки string.h. Библиотека включает:
```
- Все основные функции из string.h с префиксом s21_
- Частичную реализацию функции sprintf
- Дополнительные функции обработки строк
- Полное покрытие unit-тестами

Проект разработан для глубокого понимания внутреннего устройства строк в языке C и принципов работы стандартных библиотек.
```
## ✨ Функциональность

```### Основные функции string.h
- **s21_memchr**, **s21_memcmp**, **s21_memcpy**, **s21_memmove**, **s21_memset**
- **s21_strcat**, **s21_strncat**, **s21_strchr**, **s21_strcmp**, **s21_strncmp**
- **s21_strcpy**, **s21_strncpy**, **s21_strcspn**, **s21_strerror**
- **s21_strlen**, **s21_strpbrk**, **s21_strrchr**, **s21_strspn**
- **s21_strstr**, **s21_strtok**
```
```### Функция s21_sprintf
- Поддержка спецификаторов: `c`, `d`, `f`, `s`, `u`, `%`
- Флаги: `-`, `+`, (пробел)
- Ширина поля: (число)
- Точность: `.`(число)
- Модификаторы длины: `h`, `l`
```
```### Дополнительные функции
- Специальные функции обработки строк из класса String
```
## 🛠 Сборка и установка
```### Предварительные требования
- Компилятор GCC
- Библиотека Check (для тестирования)
- Lcov (для отчетов о покрытии)
- Операционная система Linux/macOS
```
## 📖 Использование
```#include "s21_string.h"

int main() {
    char src[] = "Hello, World!";
    char dest[20];
    
    // Использование s21_strcpy
    s21_strcpy(dest, src);
    
    // Использование s21_sprintf
    char buffer[100];
    s21_sprintf(buffer, "Number: %d, String: %s", 42, "test");
    
    return 0;
}
```
## 🎯 Команды Makefile
```
Полная сборка                       make all
Компиляция и запуск unit-тестов     make test
Генерация отчета о покрытии (gcovr) make gcov_report
Генерация отчета о покрытии (lcov)  make gcov_report_lcov
Проверка утечек памяти с Valgrind   make valg
Очистка проекта                     make clean
```
## 📁 Структура проекта
```
s21_string/
├── src/
│   ├── s21_string.h          # Основной заголовочный файл
│   ├── s21_*.c              # Исходные файлы функций
│   └── Makefile             # Файл сборки
├── tests/
│   ├── tests.c              # Unit-тесты
│   └── test_utils.c         # Вспомогательные функции для тестов
├── report_gcov/             # HTML отчеты покрытия
├── report_lcov/             # LCOV отчеты покрытия
└── README.md
```
