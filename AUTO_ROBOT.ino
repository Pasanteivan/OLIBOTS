#include <Servo.h>
#include <Wire.h>
#include <Adafruit_TCS3200.h>
 
#define SERVO_RETENER_PIN 9
#define SERVO_DIVIDIR_PIN 10
#define S2 4
#define S3 5
#define OUT 3
 
Servo servoRetener;
Servo servoDividir;
Adafruit_TCS3200 colorSensor = Adafruit_TCS3200(TCS3200_CS, S2, S3, OUT, S1);
 
void setup() {
  servoRetener.attach(SERVO_RETENER_PIN);
  servoDividir.attach(SERVO_DIVIDIR_PIN);
  colorSensor.begin();
  Serial.begin(9600);
}
 
void loop() {
  // Lee el color del objeto
  colorSensor.readRGB();
  uint16_t red = colorSensor.readRed();
  uint16_t green = colorSensor.readGreen();
  uint16_t blue = colorSensor.readBlue();
 
  // Detecta el color y controla los servos
  if (red > green && red > blue) {
    // Objeto rojo detectado
    servoRetener.write(90); // Posición para retener el objeto
    servoDividir.write(0); // Posición para dividir el objeto
  } else if (green > red && green > blue) {
    // Objeto verde detectado
    servoRetener.write(0); // Posición para retener el objeto
    servoDividir.write(90); // Posición para dividir el objeto
  } else {
    // Otro color detectado (ajusta según tus necesidades)
    servoRetener.write(45); // Posición intermedia para retener el objeto
    servoDividir.write(45); // Posición intermedia para dividir el objeto
  }
}
