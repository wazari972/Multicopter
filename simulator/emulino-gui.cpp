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

#include <stdio.h>

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
  state = true;
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
  this->state = true;
  this->id = id;
    
}
void Button::mousePressEvent(QMouseEvent *event)
{
  this->color = Qt::blue;
  update();
}

void Button:: mouseReleaseEvent(QMouseEvent *event)
{
  this->color = Qt::red;
  update();
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

/***
 *
 * PWMs 
 *
 ***/

PWM::PWM(QColor color, QWidget *parent, int id) : QWidget(parent){
  this->color = color;
  this->state = true;
  this->id = id;
}

void PWM::paintEvent(QPaintEvent *event)
{
  QPainter painter(this);
  if (state) {
    painter.setPen(color);
    painter.setBrush(color);
    painter.drawEllipse(rect());
  }
}

void PWM::setPWM(long pwm) {
  
}

long PWM::getPWM(void) {
  return -1;
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

/***
 *
 * KK2
 *
 ***/

KK2::KK2(QFrame *frame) {
  lcd = new Lcd(frame);
  lcd->setGeometry(130, 280, LCD_X*LCD_PIXEL, LCD_Y*LCD_PIXEL);
  lcd->writeText("hello\nworld", 10, 10);
  
  led = new Led(Qt::yellow, frame);
  led->setGeometry(165, 163, 20, 10);
  
#define DIST 138
  for (int i = 0; i <  BT_CNT; i++) {
    buttons[i] = new Button(frame, i);
    buttons[i]->setGeometry(170+i*DIST, 685, 30, 30);
  }
#undef DIST

#define DIST 50
  for (int i = 0; i < PWM_IN_CNT; i++) {
    in_pwns[i] = new PWM(Qt::green, frame, i);
    in_pwns[i]->setGeometry(83, 290+i*DIST, 10, 10);
  }
#undef DIST

#define DIST 50
  for (int i = 0; i < PWM_OUT_CNT; i++) {
    out_pwns[i] = new PWM(Qt::blue, frame, i);
    out_pwns[i]->setGeometry(688, 281+i*DIST, 10, 10);
  }
#undef DIST
}

void KK2::ledState(bool st) {
  led->setState(st);
}

long KK2::getInPWM(int id) {
  return in_pwns[id]->getPWM();
}

void KK2::setOutPWM(int id, long pwm) {
  out_pwns[id]->setPWM(pwm);
}

bool KK2::btPressed(int id) {
  return false;
}

bool KK2::btReleased(int id) {
  return false;
}

int main(int argc, char *argv[])
{
  EmulinoApp a(argc, argv);
  QFrame frame;
  BoardWidget board(&frame);

  KK2 *kk2 = new KK2(&frame);
  
  frame.show();
  
  return a.exec();
}

#include "emulino-gui.moc"
