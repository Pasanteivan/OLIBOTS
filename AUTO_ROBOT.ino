#include <Servo.h>
#include <NewPing.h>

// Pines de control del motor (L298N)
const int MotorAdelante = 6;
const int MotorAtras = 7;

// Pines del sensor
#define trig_pin A1 // Entrada analógica 1
#define echo_pin A2 // Entrada analógica 2

#define distancia_maxima 200
boolean adelante = false;
int distancia = 100;
int angulo = 90;
const int ANGULO_GIRO = 45; // Constante para el ángulo de giro

NewPing sonar(trig_pin, echo_pin, distancia_maxima); // Función del sensor
Servo servo_sonar; 
Servo servo_direccion;

void setup(){

  pinMode(MotorAdelante, OUTPUT);
  pinMode(MotorAtras, OUTPUT);
  
  servo_sonar.attach(9); // Servo para el sensor ultrasónico
  servo_direccion.attach(10); // Servo para la dirección
  servo_direccion.write(angulo);
  servo_sonar.write(115);
  delay(2000);
  distancia = medir();
  delay(100);
  distancia = medir();
  delay(100);
  distancia = medir();
  delay(100);
  distancia = medir();
  delay(100);
}

void loop(){

  int distanciaDerecha = 0;
  int distanciaIzquierda = 0;
  delay(50);

  if (distancia <= 20){
    detenerse();
    delay(300);
    moverAtras();
    delay(400);
    detenerse();
    delay(300);
    distanciaDerecha = mirarDerecha();
    delay(300);
    distanciaIzquierda = mirarIzquierda();
    delay(300);

    if (distancia >= distanciaIzquierda){
      girarDerecha();
      detenerse();
    }
    else{
      girarIzquierda();
      detenerse();
    }
  }
  else{
    moverAdelante(); 
  }
  distancia = medir();
}

int mirarDerecha(){  
  servo_sonar.write(50);
  delay(500);
  int distance = medir();
  delay(100);
  servo_sonar.write(115);
  return distance;
}

int mirarIzquierda(){
  servo_sonar.write(170);
  delay(500);
  int distance = medir();
  delay(100);
  servo_sonar.write(115);
  return distance;
  delay(100);
}

int medir(){
  delay(70);
  int cm = sonar.ping_cm();
  if (cm == 0 || cm > distancia_maxima){ // Si la medición no es válida o excede la distancia máxima, considerar un valor de 250 cm.
    cm = 250;
    // Aquí podrías tomar otra acción, como mostrar un mensaje de error o ajustar el comportamiento del robot.
  }
  return cm;
}

void detenerse(){
  
  digitalWrite(MotorAdelante, LOW);
  digitalWrite(MotorAtras, LOW);
}

void moverAdelante(){

  if(!adelante){

    adelante = true;
    
    digitalWrite(MotorAdelante, HIGH);
    
    digitalWrite(MotorAtras, LOW);
  
  }
}

void moverAtras(){
  adelante = false;
  digitalWrite(MotorAtras, HIGH);
  digitalWrite(MotorAdelante, LOW);
}

void girarDerecha(){
  servo_direccion.write(angulo + ANGULO_GIRO);
  delay(500);
  moverAdelante();
}

void girarIzquierda(){
  servo_direccion.write(angulo - ANGULO_GIRO);
  delay(500);
  moverAdelante();
}
