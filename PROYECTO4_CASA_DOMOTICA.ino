#include <Servo.h> //LIBRERIA DEL SERVO
Servo servo;
int servopin=16; //pin del servo
int angle=0;  //angulo inicial
#include "NewPing.h" //LIBRERIA DEL ULTRASONICO

// PRIMER ULTRASONICO PUERTA
#define TRIGGER_PIN1 9
#define ECHO_PIN1 10

// SEGUNDO ULTRASONICO DERECHA
#define TRIGGER_PIN2 11
#define ECHO_PIN2 12

// TERCER ULTRASONICO IZQUIERDA
#define TRIGGER_PIN3 14
#define ECHO_PIN3 15

long duracion, distancia, puerta, izquierda, derecha; //VARIABLES PARA MEDICIONES DE
// DISTANCIA

//DEFINICION DE PINES DE LAS LUCES
int izquierdaroja = 2;
int izquierdaverde = 3;
int derecharoja = 4; 
int derechaverde = 5; 
int luzadentro = 6;

int pResistor=A7;//FOTORESISTENCIA

void setup() {
  Serial.begin(9600);
  // LUCES IZQUIERDA
  pinMode(izquierdaroja, OUTPUT);
  pinMode(izquierdaverde, OUTPUT);
  digitalWrite(izquierdaroja, HIGH);
  digitalWrite(izquierdaverde, LOW);
  // LUCES DERECHA
  pinMode(derecharoja, OUTPUT); // Agregué esta línea para configurar el pin de la luz derecha
  pinMode(derechaverde, OUTPUT); // Agregué esta línea para configurar el pin de la luz derecha

  // LUZ ADENTRO
  pinMode(luzadentro, OUTPUT); // Agregué esta línea para configurar el pin de la luz adentro
  
  // FOTO RESISTOR
  pinMode(pResistor, INPUT);

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

  // SETUP DEL SERVO MOTOR
  servo.attach(servopin);
  servo.write(angle);
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

//FUNCION DEL FOTORESISTOR SI LA LUZ DE ADENTRO ESTA APAGADA
void controlarLuzInterior() {
  int valorLuz = analogRead(pResistor); // Leer la luz con el fotoresistor
  Serial.println("LUZ=");
  Serial.print(valorLuz);
  Serial.println("\n");
  if (valorLuz > 400) {
    digitalWrite(luzadentro, LOW); // Apagar la luz interior si está oscuro
  } else {
    digitalWrite(luzadentro, HIGH); // Encender la luz interior si está claro
  }
}

void loop() 
{
  //MEDIR DISTANCIA EN LA PUERTA
  medir(TRIGGER_PIN1,ECHO_PIN1);
  puerta=distancia;
  //MEDIR DISTANCIA A LA DERECHA DE LA CASA
  medir(TRIGGER_PIN2,ECHO_PIN2);
  derecha=distancia;
  //MEDIR DISTNCIA A LA IZQUIERDA DE LA PUERTA
  medir(TRIGGER_PIN3,ECHO_PIN3);
  izquierda=distancia;

  // Control de las luces izquierda
  if (izquierda < 15) 
  {
    digitalWrite(izquierdaroja, LOW);   // Apaga la luz roja izquierda
    digitalWrite(izquierdaverde, HIGH); // Enciende la luz verde izquierda
  } else 
  {
    digitalWrite(izquierdaroja, HIGH);  // Enciende la luz roja izquierda
    digitalWrite(izquierdaverde, LOW);  // Apaga la luz verde izquierda
  }

  // Control de las luces derecha
  if (derecha < 15) 
  {
    digitalWrite(derecharoja, LOW);    // Apaga la luz roja derecha
    digitalWrite(derechaverde, HIGH);  // Enciende la luz verde derecha
  } else 
  {
    digitalWrite(derecharoja, HIGH);   // Enciende la luz roja derecha
    digitalWrite(derechaverde, LOW);   // Apaga la luz verde derecha
  }

  // Control de la puerta
  if (puerta < 15) 
    {
      digitalWrite(luzadentro, HIGH);  // Enciende la luz adentro
      servo.write(angle+90); //El servo se movera 90 grados más de la posición inicial
                             //en nuestro caso posicion inicial es 0
      delay(2000);
      servo.write(angle);  //servo vuelve a su posicion inicial cerrando la puerta
    }
  else 
    digitalWrite(luzadentro, LOW);   // Apaga la luz adentro

   //Este if va a ver si la luz de adentro esta apagada, en caso de estar apagada entonces
   //se hara el control inteligente de luz 
  if(digitalRead(luzadentro==LOW))
  {
    controlarLuzInterior();
  }
  
  delay(2000); // UN DELAY PARA QUE ESTE UN POCO MAS CONTROLADO LAS MEDICIONES SE PUEDE CAMBIAR
  // SEGUN QUERAMOS
}