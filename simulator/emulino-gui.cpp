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

#include "emulino-gui.h"
#include "ardu.hpp"

#include <cstdlib>
#include <stdio.h>

class EmulinoApp: public QApplication {
  Q_OBJECT
public:
  EmulinoApp(int &argc, char *argv[]);
};

EmulinoApp::EmulinoApp(int &argc, char *argv[]) : QApplication(argc, argv) { }

class BoardWidget: public QWidget {
  Q_OBJECT
public:
  BoardWidget(QWidget *parent);
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

/***
 *
 * Led 
 *
 ***/

Led::Led(QColor color, QWidget *parent) : QWidget(parent)
{
  this->color = color;
  state = false;
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

void Led::setState(bool st) {
  this->state = st;
}

/***
 *
 * Buttons 
 *
 ***/

Button::Button(QWidget *parent, int id) : QWidget(parent){
  this->color = Qt::red;
  this->pressed = false;
  this->id = id;
    
}
void Button::mousePressEvent(QMouseEvent *event)
{
  this->color = Qt::blue;
  this->pressed = true;
  this->update();
}

void Button:: mouseReleaseEvent(QMouseEvent *event)
{
  this->color = Qt::red;
  this->pressed = false;
  this->update();
}

bool Button::isPressed(void) {
  return this->pressed;
}

void Button::paintEvent(QPaintEvent *event)
{
  QPainter painter(this);
  painter.setPen(color);
  painter.setBrush(color);
  painter.drawEllipse(rect());
}

/***
 *
 * PWMs 
 *
 ***/

PWM::PWM(bool in, QWidget *parent, int id) : QWidget(parent){
  this->state = false;
  this->id = id;
  this->in = in;
}

void PWM::paintEvent(QPaintEvent *event)
{
  QColor color;
  QPainter painter(this);
  if (this->in) {
    color = (state ? Qt::blue : Qt::green);
  } else {
    color = (state ? Qt::red : Qt::yellow);
  }

  painter.setPen(color);
  painter.setBrush(color);
  painter.drawEllipse(rect());
}

void PWM::setState(bool st) {
  this->state = st;
}


/***
 *
 * LCD
 *
 ***/

#include "lcd.inc"

Lcd::Lcd(QWidget *parent) : QWidget(parent), cursor(0)
{
  memset(display, 0, sizeof(display));
}

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
  display[x][LCD_Y - y] = val;
}

void Lcd::clear(void) {
  memset(display, 0, sizeof(display));
}

void Lcd::writeText(const char *chr, int x, int y) {
  int init_x = x;
  while(*chr) {
    if (*chr == '\n') {
      x = init_x;
      y += CHAR_HEIGHT;
      y += CHAR_INTER_LINE;
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

/***
 *
 * KK2
 *
 ***/

KK2::KK2(QFrame *frame) {
  this->lcd = new Lcd(frame);
  this->lcd->setGeometry(130, 280, LCD_X*LCD_PIXEL, LCD_Y*LCD_PIXEL);
  
  this->led = new Led(Qt::red, frame);
  this->led->setGeometry(165, 163, 20, 10);
  
#define DIST 138
  for (int i = 0; i <  BT_CNT; i++) {
    this->buttons[i] = new Button(frame, i);
    this->buttons[i]->setGeometry(170+i*DIST, 685, 30, 30);
  }
#undef DIST

#define DIST 50
  for (int i = 0; i < PWM_IN_CNT; i++) {
    in_pwns[i] = new PWM(true, frame, i);
    in_pwns[i]->setGeometry(83, 290+i*DIST, 10, 10);
  }
#undef DIST

#define DIST 50
  for (int i = 0; i < PWM_OUT_CNT; i++) {
    this->out_pwns[i] = new PWM(false, frame, i);
    this->out_pwns[i]->setGeometry(688, 281+i*DIST, 10, 10);
  }
#undef DIST
}

void KK2::ledState(bool st) {
  this->led->setState(st);
}

bool KK2::btPressed(int id) {
  return this->buttons[id]->isPressed();
}

bool KK2::btReleased(int id) {
  return !this->btPressed(id);
}

void KK2::update(void) {
  this->led->update();

  for (int i = 0; i < PWM_OUT_CNT; i++) {
    out_pwns[i]->update();
  }

  for (int i = 0; i < PWM_IN_CNT; i++) {
    in_pwns[i]->update();
  }

  this->lcd->update();
}

void KK2::lightOn(void) {
  this->led->setState(true);
  this->led->update();
}

void KK2::lightOff(void) {
  this->led->setState(false);
  this->led->update();
}

void KK2::pinState(int pin, bool state) {
  if (pin >= 0 && pin <= 4) {
    this->in_pwns[pin]->setState(state);
    this->in_pwns[pin]->update();
  }
  if (pin >= 5 && pin <= 12) {
    this->out_pwns[pin - 5]->setState(state);
    this->out_pwns[pin - 5]->update();
  }
  if (pin == 13) {
    this->led->setState(state);
    this->led->update();
  }
}

/***
 *
 * Simulator thread
 *
 ***/

#include <QThread>

KKComm::KKComm(KK2 *kk2) {
  this->kk2 = kk2;
  this->bat = 12;
  this->acc[0] = 0;
  this->acc[1] = 0;
  this->acc[2] = 0;

  this->gyr[0] = 0;
  this->gyr[1] = 0;
  this->gyr[2] = 0;
}

void KKComm::setArduino(Arduino *ardu) {
  this->ardu = ardu;
}

void KKComm::ledState(bool x) {
  if (x) {
    emit lightOn();
  } else {
    emit lightOff();
  }
}

void KKComm::setPinState(int pin, bool state) {
  emit pinState(pin, state);
}

void KKComm::drawPixel(int x, int y) {
  this->kk2->lcd->setPixel(true, x, y);
}

void KKComm::refreshScreen(void) { 
  emit refresh();
  usleep(5000);
}

bool KKComm::buttonPressed(int x) {
  return this->kk2->btReleased(x);
}

void KKComm::clearScreen(void) {
   this->kk2->lcd->clear();
}

int KKComm::getBat(void) {
  return this->bat;
}

int KKComm::getGyro(int pin) {
  int gyrId;
  if (pin == 1) gyrId = 0;
  if (pin == 2) gyrId = 1;
  if (pin == 4) gyrId = 2;

  this->gyr[gyrId] +=  rand() % 3 - 1;
  
  return this->gyr[gyrId];
}

int KKComm::getAcc(int pin) {
  int accId = pin - 5;

  this->acc[accId] +=  rand() % 21 - 10;
  
  return this->acc[accId];
}

void KKComm::run()
{
  this->ardu->ssetup();
  while(1) {
    this->ardu->lloop();
  }
}

/***
 *
 * Main
 *
 ***/


int main(int argc, char *argv[])
{
  EmulinoApp a(argc, argv);
  QFrame frame;
  BoardWidget board(&frame);

  KK2 *kk2 = new KK2(&frame);
  KKComm *com = new KKComm(kk2);
  
  QObject::connect(com, SIGNAL(refresh()), kk2, SLOT(update()));
  QObject::connect(com, SIGNAL(lightOff()), kk2, SLOT(lightOff()));
  QObject::connect(com, SIGNAL(lightOn()), kk2, SLOT(lightOn()));
  QObject::connect(com, SIGNAL(pinState(int,bool)), kk2, SLOT(pinState(int,bool)));
  
  Arduino *arduino = new Arduino(com);
  com->setArduino(arduino);

  frame.show();
  
  com->start();
  
  return a.exec();
}

#include "emulino-gui.moc"
