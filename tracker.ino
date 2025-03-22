#include <Servo.h>

Servo servoX;
Servo servoY;

int posX = 90; // Servo başlangıç pozisyonu
int posY = 90;

void setup() {
  servoX.attach(9);  // X ekseni için servo motorun bağlı olduğu pin
  servoY.attach(10); // Y ekseni için servo motorun bağlı olduğu pin
  Serial.begin(9600);
  servoX.write(posX);
  servoY.write(posY);
}

void loop() {
  if (Serial.available() > 0) {
    String data = Serial.readStringUntil('\n'); // Satır sonuna kadar gelen veriyi oku
    int commaIndex = data.indexOf(','); // Virgülün indeksini bul
    if (commaIndex > 0) {
      String xString = data.substring(0, commaIndex); // X değerini al
      String yString = data.substring(commaIndex + 1); // Y değerini al
      int x = xString.toInt();
      int y = yString.toInt();

      // X ekseni kontrolü (640 ortalanmış olarak varsayılıyor)
      if (x < 580) {
        posX = constrain(posX + 1, 0, 180); // Sol tarafa hareket ettir
      } else if (x > 700) {
        posX = constrain(posX - 1, 0, 180); // Sağ tarafa hareket ettir
      }

      // Y ekseni kontrolü (360 ortalanmış olarak varsayılıyor)
      if (y > 420) {
        posY = constrain(posY - 1, 0, 180); // Aşağıya hareket ettir
      } else if (y < 300) {
        posY = constrain(posY + 1, 0, 180); // Yukarıya hareket ettir
      }

      // Servo motorları yeni pozisyonlara ayarla
      servoX.write(posX);
      servoY.write(posY);
    }
  }
}
