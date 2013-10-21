#ifndef EMULINO_GUI__CPP
#define EMULINO_GUI__CPP

#include <qapplication.h>
#include <qframe.h>
#include <qhash.h>
#include <qlayout.h>
#include <qmessagebox.h>
#include <qpainter.h>
#include <qpushbutton.h>
#include <qtimer.h>

/***
 *
 * Led 
 *
 ***/


class Led: public QWidget {
  Q_OBJECT
public:
  Led(QColor color, QWidget *parent);
  void setState(bool st);
protected:
  void paintEvent(QPaintEvent *event);
  QColor color;
  bool state;
};

/***
 *
 * Buttons 
 *
 ***/

class Button: public QWidget {
  Q_OBJECT
public:
  Button(QWidget *parent, int id);
  bool isPressed(void);
public slots:
  void mousePressEvent(QMouseEvent *event);
  void mouseReleaseEvent(QMouseEvent *event);
protected:
  void paintEvent(QPaintEvent *event);
  QColor color;
  bool pressed;
  int id;
};

/***
 *
 * PWMs 
 *
 ***/

class PWM: public QWidget {
  Q_OBJECT
public:
  PWM(QColor color, QWidget *parent, int id);
  void setPWM(long pwm);
  long getPWM(void);
protected:
  void paintEvent(QPaintEvent *event);
  QColor color;
  bool state;
  int id;
};

/***
 *
 * LCD
 *
 ***/

#define LCD_X 128
#define LCD_Y  64
#define LCD_PIXEL 4

#define CHAR_WIDTH 5
#define CHAR_HEIGHT 8
#define CHAR_INTER_LINE 0

class Lcd: public QWidget {
  Q_OBJECT
public:
  Lcd(QWidget *parent);
  void writeText(const char *chr, int x, int y);
  void setPixel(bool val, int x, int y);
  void clear(void);
protected:
  void paintEvent(QPaintEvent *event);
private:
  bool display[LCD_X][LCD_Y];
  int cursor;
};

/***
 *
 * KK2
 *
 ***/

#define BT_CNT 4
#define PWM_IN_CNT 5
#define PWM_OUT_CNT 8

class KK2 {
public:
  KK2(QFrame *parent);
  void ledState(bool);
  long getInPWM(int id);
  void setOutPWM(int id, long pwm);
  bool btPressed(int id);
  bool btReleased(int id);
  void update(void);

  Lcd *lcd;
protected:
  Led *led;
  Button *buttons[BT_CNT];
  PWM *in_pwns[PWM_IN_CNT];
  PWM *out_pwns[PWM_OUT_CNT];
};

#endif
