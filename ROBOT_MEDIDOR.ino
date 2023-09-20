//PROYECTO #
//ROBOT MEDIDOR DE DISTANCIAS A SU ALREDEDOR

/*SIMULACION EN WOKWI
https://wokwi.com/projects/376413149908613121
*/

#include <LiquidCrystal_I2C.h>  //Libreria lcd i2c
LiquidCrystal_I2C lcd(0x27, 16, 2); // Se establece el lcd como objeto

#include "NewPing.h" //LIBRERIA DEL ULTRASONICO


long duracion, distancia, frente, izquierda, derecha; //VARIABLES PARA MEDICIONES DE
// DISTANCIA

// PRIMER ULTRASONICO DERECHA
#define ECHO_PIN1 4
#define TRIGGER_PIN1 5

// SEGUNDO ULTRASONICO FRENTE

#define ECHO_PIN2 6
#define TRIGGER_PIN2 7

// TERCER ULTRASONICO IZQUIERDA

#define ECHO_PIN3 9
#define TRIGGER_PIN3 8

//FUNCION DE MEDIR DISTANCIA
void medir(int trigPin, int echoPin)
{
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duracion = pulseIn(echoPin, HIGH);
  distancia = (duracion)*0.017;
}

void setup() {
  // PINES DE LOS ULTRASONICOS
  // ULTRASONICO 1
  pinMode(TRIGGER_PIN1, OUTPUT);
  pinMode(ECHO_PIN1, INPUT);
  // ULTRASONICO 2
  pinMode(TRIGGER_PIN2, OUTPUT);
  pinMode(ECHO_PIN2, INPUT);
  // ULTRASONICO 3
  pinMode(TRIGGER_PIN3, OUTPUT);
  pinMode(ECHO_PIN3, INPUT);
  lcd.init();
  lcd.backlight();
  lcd.setCursor(1,0);
  lcd.print("MEDIDOR");
  lcd.setCursor(1,1);
  lcd.print("DISTANCIA");
  delay(2000);
}

void loop() {
  lcd.clear();
  // Mostrar la distancia de al frente
  medir(TRIGGER_PIN1,ECHO_PIN1);
  derecha=distancia;
  lcd.setCursor(1, 0);  // Establecer la posición del cursor en la primera fila, primera columna
  lcd.print("DISTANCIA");
  lcd.setCursor(0, 1);  // Establecer la posición del cursor en la segunda fila, primera columna
  lcd.print("DERECHA: ");
  lcd.print(derecha);
  lcd.print(" cm");
  delay(2000);
  
  // Mostrar la distancia de la derecha
  lcd.clear();
  medir(TRIGGER_PIN2,ECHO_PIN2);
  frente=distancia;
  lcd.setCursor(1, 0);  // Establecer la posición del cursor en la primera fila, primera columna
  lcd.print("DISTANCIA");
  lcd.setCursor(0, 1);  // Establecer la posición del cursor en la segunda fila, primera columna
  lcd.print("FRENTE: ");
  lcd.print(frente);
  lcd.print(" cm");
  delay(2000);

  // Mostrar la distancia de la izquierda
  lcd.clear();
  medir(TRIGGER_PIN3,ECHO_PIN3);
  izquierda=distancia;
  lcd.setCursor(1,0);
  lcd.print("DISTANCIA");
  lcd.setCursor(0,1);
  lcd.print("IZQUIERDA:");
  lcd.print(izquierda);
  lcd.print(" cm");
  delay(2000);
}
