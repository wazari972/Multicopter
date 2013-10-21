#include <QThread>
#include <stdint.h>

class KKComm;
class KK2;

class Arduino {
public:
  Arduino(KKComm *kkcom);
  void pinMode(uint8_t p, uint8_t m);
  void digitalWrite(uint8_t v, uint8_t w);
  int digitalRead(uint8_t w);
  int analogRead(uint8_t w);
  int analogWrite(uint8_t w);
  void analogReference(uint8_t mode);
  
  void delay(unsigned long d);
  unsigned long millis(void);
  void delayMicroseconds(unsigned int us);

  void ssetup();

  void lloop();
  KKComm *kkcom;
private:
  
};

class KKComm : public QThread {
  Q_OBJECT
public:
  KKComm(KK2 *kk2);
  void setArduino(Arduino *ardu);

  void drawPixel(int x, int y);
  void clearScreen(void);
  void refreshScreen(void);
  
  bool buttonPressed(int x);
  void ledState(bool x);
  void pinState(bool x);
  
  int getBat(void);
  int getGyro(int pin);
  int getAcc(int ping);
  void setPinState(int pin, bool x);
  
signals:
  void refresh(void);
  void lightOn(void);
  void lightOff(void);
  void pinState(int pin, bool x);
  
protected:
  KK2 *kk2;
  Arduino *ardu;

  int bat;
  int acc[3];
  int gyr[3];
  void run();
  
};
