#include <Servo.h>
#include "NewPing.h"

//CONTROL SERVO
Servo myservo;
int servopin =3;
int ang=90;
int angactual;

//PINES DEL MOTOR
int adelante =5;
int atras =6;
//int enableA=7;


// Ultrasonico
int echopin=14;
int triggerpin=15;

long duracion, distancia;


void setup() {
  myservo.attach(3);
  pinMode(adelante, OUTPUT);
  pinMode(atras, OUTPUT);
  Serial.begin(9200);
  angactual=ang;
}


void loop() {
  medir(echopin,triggerpin);
  int frente=distancia;
  if (frente < 20)
  {
    parar();

    girarizquierda(60);
    delay(200);
    moverfrente();
    delay(400);

    parar();

    centro();
    girarderecha(60);
    delay(200)
    moverfrente();
    delay(400);

    parar();


  }
  else
  {
    moverfrente();
  }

}


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

//MOVER FRENTE
void moverfrente()
{
  Serial.print("Moviendo adelante");
  digitalWrite(adelante, HIGH);
  digitalWrite(atras, LOW);
}

//MOVER ATRAS
void moveratras()
{
  Serial.print("Moviendo adelante");
  digitalWrite(adelante, LOW);
  digitalWrite(atras, HIGH);
}

//GIRAR IZQUIERDA
void girarizquierda(int giro)
{
  Serial.print("Girando izquierda");
  myservo.write(angactual+giro);
  angactual=angactual-giro;
}

//GIRAR DERECHA
void girarderecha(int giro)
{
  Serial.print("Girando derecha");
  myservo.write(angactual-giro);
  angactual=angactual-giro;
}
//DEPENDIENDO DE LA POSICION ACTUAL, VOLVERA AL ANGULO INICIAL
void centro()
{
  Serial.print("Centreando");
  myservo.write(ang);
}
//PARAR
void parar()
{
  Serial.print("Parando");
  digitalWrite(adelante, LOW);
  digitalWrite(atras, LOW);
}
