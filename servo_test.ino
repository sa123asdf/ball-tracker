#include <Servo.h>

Servo myservo;  // Servo motor nesnesi oluşturuluyor

int pos = 0;    // Servo motorun başlangıç pozisyonu

void setup() {
  myservo.attach(9);  // Servo motorun sinyal pini Arduino'nun D9 pinine bağlanıyor
}

void loop() {
  // Servo motoru 0 dereceden 180 dereceye hareket ettir
  for (pos = 0; pos <= 180; pos += 1) {
    myservo.write(pos);              // Servo motoru belirtilen pozisyona hareket ettir
    delay(15);                       // Hareketin düzgün olmasını sağlamak için kısa bir gecikme
  }
  // Servo motoru 180 dereceden 0 dereceye hareket ettir
  for (pos = 180; pos >= 0; pos -= 1) {
    myservo.write(pos);              // Servo motoru belirtilen pozisyona hareket ettir
    delay(15);                       // Hareketin düzgün olmasını sağlamak için kısa bir gecikme
  }
}
