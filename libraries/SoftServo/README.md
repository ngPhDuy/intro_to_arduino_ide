[![Foo](https://img.shields.io/badge/Version-1.2-brightgreen.svg?style=flat-square)](#versions)
[![Foo](https://img.shields.io/badge/Website-AlexGyver.ru-blue.svg?style=flat-square)](https://alexgyver.ru/)
[![Foo](https://img.shields.io/badge/%E2%82%BD$%E2%82%AC%20%D0%9D%D0%B0%20%D0%BF%D0%B8%D0%B2%D0%BE-%D1%81%20%D1%80%D1%8B%D0%B1%D0%BA%D0%BE%D0%B9-orange.svg?style=flat-square)](https://alexgyver.ru/support_alex/)

[![Foo](https://img.shields.io/badge/README-ENGLISH-brightgreen.svg?style=for-the-badge)](https://github-com.translate.goog/GyverLibs/SoftServo?_x_tr_sl=ru&_x_tr_tl=en)

# SoftServo
Библиотека для программного управления Servo (на базе millis/micros)
- Не использует дополнительный аппаратный таймер
- Работает на millis() и micros()
- Синтаксис как у Servo.h
- Режим работы асинхронный и с delay
- Повышенная произвводительность для AVR

### Совместимость
Совместима со всеми Arduino платформами (используются Arduino-функции)

## Содержание
- [Установка](#install)
- [Инициализация](#init)
- [Использование](#usage)
- [Пример](#example)
- [Версии](#versions)
- [Баги и обратная связь](#feedback)

<a id="install"></a>
## Установка
- Библиотеку можно найти по названию **SoftServo** и установить через менеджер библиотек в:
    - Arduino IDE
    - Arduino IDE v2
    - PlatformIO
- [Скачать библиотеку](https://github.com/GyverLibs/SoftServo/archive/refs/heads/main.zip) .zip архивом для ручной установки:
    - Распаковать и положить в *C:\Program Files (x86)\Arduino\libraries* (Windows x64)
    - Распаковать и положить в *C:\Program Files\Arduino\libraries* (Windows x32)
    - Распаковать и положить в *Документы/Arduino/libraries/*
    - (Arduino IDE) автоматическая установка из .zip: *Скетч/Подключить библиотеку/Добавить .ZIP библиотеку…* и указать скачанный архив
- Читай более подробную инструкцию по установке библиотек [здесь](https://alexgyver.ru/arduino-first/#%D0%A3%D1%81%D1%82%D0%B0%D0%BD%D0%BE%D0%B2%D0%BA%D0%B0_%D0%B1%D0%B8%D0%B1%D0%BB%D0%B8%D0%BE%D1%82%D0%B5%D0%BA)

<a id="init"></a>
## Инициализация
```cpp
SoftServo myservo;
```

<a id="usage"></a>
## Использование
```cpp
void attach(int pin, int min = 500, int max = 2400);    // подключить с указанием мин и макс импульса
void detach();          // отключить
void asyncMode();       // переключить в асинхронный режим
void delayMode();       // переключить в режим задержки (по умолч)
bool tick();            // тикер, вызывать как можно чаще, в асинхронном режиме вернёт true во время отработки импульса
void write(int value);  // поставить на угол
void writeMicroseconds(int us); // поставить на импульс
int read();             // вернуть текущий угол
int readMicroseconds(); // вернуть текущий импульс
bool attached();        // true если серво подключена
```

<a id="example"></a>
## Пример
Остальные примеры смотри в **examples**!
```cpp
#include "SoftServo.h"

SoftServo myservo;

void setup() {
  myservo.attach(5);
  
  // asyncMode - вызов tick не блокирует код на величину импульса (0.7-2.5 мс)
  // но работа будет нестабильной при наличии задержек в коде
  // в этом режиме tick вернёт true на период импульса, можно запрещать
  // тяжёлые функции на этот период 
  myservo.asyncMode();
  
  // delayMode - вызов tick блокирует код на величину импульса (0.7-2.5 мс) - по умолчанию  
  myservo.delayMode();  
}

int val = 0;
void loop() {
  // тикер - вызывать как можно чаще для каждого экземпляра
  myservo.tick();
  
  // двигаем туда сюда
  static uint32_t tmr;
  if (millis() - tmr >= 50) {
    tmr = millis();    
    static int dir = 5;
    val += dir;    
    if (val >= 180 || val <= 0) dir = -dir;   // разворачиваем
    myservo.write(val);
  }
}
```

<a id="versions"></a>
## Версии
- v1.0
- v1.1 - переделан FastIO
- v1.1.1 - убран FastIO
- v1.2 - мелкие фиксы

<a id="feedback"></a>
## Баги и обратная связь
При нахождении багов создавайте **Issue**, а лучше сразу пишите на почту [alex@alexgyver.ru](mailto:alex@alexgyver.ru)  
Библиотека открыта для доработки и ваших **Pull Request**'ов!
