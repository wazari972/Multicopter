/*
 * emulino - arduino emulator GUI
 * Copyright 2009 Greg Hewgill
 *
 * This file is part of Emulino.
 *
 * Emulino is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Emulino is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Emulino.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <qapplication.h>
#include <qframe.h>
#include <qhash.h>
#include <qlayout.h>
#include <qmessagebox.h>
#include <qpainter.h>
#include <qpushbutton.h>
#include <qtimer.h>
#include <stdio.h>

#include "ardu.h"

class EmulinoApp: public QApplication {
  Q_OBJECT
public:
  EmulinoApp(int &argc, char *argv[]);
public slots:
  void onIdle();
  void onButtonPress();
  void onButtonRelease();
private:
  QTimer timer;
};

EmulinoApp::EmulinoApp(int &argc, char *argv[]) : QApplication(argc, argv)
{
//  connect(&timer, SIGNAL(timeout()), this, SLOT(onIdle()));
//  timer.start(0);
}

void EmulinoApp::onIdle()
{
  printf("idle\n");
}

void EmulinoApp::onButtonPress()
{
  printf("button pressed\n");
}

void EmulinoApp::onButtonRelease()
{
  printf("button released\n");
}

class BoardWidget: public QWidget {
  Q_OBJECT
public:
  BoardWidget(QWidget *parent = 0);
protected:
  void paintEvent(QPaintEvent *event);
private:
  QImage board;
};

BoardWidget::BoardWidget(QWidget *parent) : QWidget(parent)
{
  board.load("arduino.jpg");
  setMinimumSize(board.size());
}

void BoardWidget::paintEvent(QPaintEvent *event)
{
  QPainter painter(this);
  painter.drawImage(board.rect(), board, board.rect());
}

class Component {
public:
    virtual ~Component() {}
    virtual void setPin(int pin, bool state) = 0;
};


class Led: public QWidget {
  Q_OBJECT
public:
  Led(QColor color, QWidget *parent = 0);
public slots:
  void setState(bool newState);
protected:
  void paintEvent(QPaintEvent *event);
  QColor color;
  bool state;
};

Led::Led(QColor color, QWidget *parent) : QWidget(parent)
{
  this->color = color;
  state = true;
}

void Led::setState(bool newState)
{
  state = newState;
  update();
}

void Led::paintEvent(QPaintEvent *event)
{
  QPainter painter(this);
  if (state) {
    painter.setPen(color);
    painter.setBrush(color);
    painter.drawEllipse(rect());
  }
}

class Button: public QWidget {
  Q_OBJECT
public:
  Button(QColor color, QWidget *parent = 0);
public slots:
  void setState(bool newState);
protected:
  void paintEvent(QPaintEvent *event);
  QColor color;
  bool state;
};

Button::Button(QColor color, QWidget *parent) : QWidget(parent){
  this->color = color;
  state = true;
}

void Button::paintEvent(QPaintEvent *event)
{
  QPainter painter(this);
  if (state) {
    painter.setPen(color);
    painter.setBrush(color);
    painter.drawEllipse(rect());
  }
}

#define LCD_X 128
#define LCD_Y  64
#define LCD_PIXEL 4

#define CHAR_WIDTH 5
#define CHAR_HEIGHT 8
#define CHAR_INTER_LINE 0

class Lcd: public QWidget, public Component {
  Q_OBJECT
public:
  Lcd(QWidget *parent = 0);
  enum Pin {pinRS, pinRW, pinE, pinD4, pinD5, pinD6, pinD7};
  void writeText(char *chr, int x, int y);
  void setPixel(bool val, int x, int y);
public slots:
  void setPin(int pin, bool state);
protected:
  void paintEvent(QPaintEvent *event);
private:
  bool display[LCD_X][LCD_Y];
  int cursor;
};

#include "lcd.inc"

Lcd::Lcd(QWidget *parent) : QWidget(parent), cursor(0)
{
  memset(display, 0, sizeof(display));
}

void Lcd::setPin(int _pin, bool state) {}

void Lcd::paintEvent(QPaintEvent *event)
{
  bool print = true;
  QPainter painter(this);
  painter.setPen(Qt::white);
  painter.setBrush(Qt::white);
  painter.drawRect(rect());
  painter.setBrush(Qt::black);

  for (int x = 0; x < LCD_X; x++) {
    for (int y = 0; y < LCD_Y; y++) {
      if (display[x][y]) {
	painter.drawRect(LCD_PIXEL*x, LCD_PIXEL*y, LCD_PIXEL, LCD_PIXEL);
      }
    }
  }
}
void Lcd::setPixel(bool val, int x, int y) {
  display[x][y] = val;
}

void Lcd::writeText(char *chr, int x, int y) {
  int init_x = x;
  while(*chr) {
    if (*chr == '\n') {
      x = init_x;
      y += CHAR_HEIGHT + CHAR_INTER_LINE ;
      goto cont;
    }
    
    for (int cx = 0; cx < CHAR_WIDTH && (x + cx < LCD_X); cx++) {
      for (int cy = 0; cy < CHAR_HEIGHT && (y + cy < LCD_Y); cy++) {
	setPixel(Chars[*chr][cx] & (0x80 >> cy), x + cx, y + cy);
      }
    }

    x += CHAR_WIDTH;
  cont:
    chr++;
  }
}

class Pin: public QObject {
  Q_OBJECT
public:
  Pin();
  void setState(bool newState);
signals:
  void stateChanged(bool state);
private:
  bool state;
};

Pin::Pin() : state(false)
{
}

void Pin::setState(bool newState)
{
  if (newState != state) {
    state = newState;
    stateChanged(state);
  }
}

void pin_change(int pin, bool state)
{
  fprintf(stderr, "pin %d %d\n", pin, state);
}

int main(int argc, char *argv[])
{
  EmulinoApp a(argc, argv);
  QFrame frame;
  BoardWidget board(&frame);
  
  Lcd lcd(&frame);
  lcd.setGeometry(130, 280, LCD_X*LCD_PIXEL, LCD_Y*LCD_PIXEL);
  lcd.writeText("hello\nworld", 10, 10);

  Led led(Qt::yellow, &frame);
  led.setGeometry(165, 163, 20, 10);
  
#define DIST 138
  for (int i = 0; i < 4; i++) {
    Button *bt = new Button(Qt::red, &frame);
    bt->setGeometry(170+i*DIST, 685, 30, 30);
  }
#undef DIST

#define DIST 50
  for (int i = 0; i < 5; i++) {
    Led *in = new Led(Qt::green, &frame);
    in->setGeometry(83, 290+i*DIST, 10, 10);
  }
#undef DIST

#define DIST 50
  for (int i = 0; i < 8; i++) {
    Led *out = new Led(Qt::blue, &frame);
    out->setGeometry(688, 281+i*DIST, 10, 10);
  }
#undef DIST
  
  frame.show();
  
  
  return a.exec();
}

#include "emulino-gui.moc"
