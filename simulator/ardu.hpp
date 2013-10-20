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
private:
  KKComm *kkcom;
};

class KKComm : public QThread {
  Q_OBJECT
public:
  KKComm(KK2 *kk2);
  void setArduino(Arduino *ardu);
  void sayHello(const char *);
protected:
  Arduino *ardu;
  
  void run();
  KK2 *kk2;
};
