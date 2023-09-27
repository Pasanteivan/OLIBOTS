int rojo = 3;
int amarillo = 5;
int verde = 7;

int verpeaton = 9;
int rojpeaton = 11;
int peaton = 13;

int contR = 5;
int contV = 5;
int contA = 5;

void setup() {
  pinMode(rojo, OUTPUT);
  pinMode(amarillo, OUTPUT);
  pinMode(verde, OUTPUT);
  pinMode(verpeaton, OUTPUT);
  pinMode(rojpeaton, OUTPUT);
  pinMode(peaton, INPUT_PULLUP);
}

void loop() {
  for (int i = 0; i < contR + contV + contA; i++) {
    if (i < contV) {
      // Estado Verde
      digitalWrite(rojo, LOW);
      digitalWrite(verde, HIGH);
      digitalWrite(amarillo, LOW);
      // Luces peatón
      digitalWrite(rojpeaton, HIGH);
      digitalWrite(verpeaton, LOW);
      if (digitalRead(peaton) == HIGH) {
        // Peatón cruzando
        digitalWrite(rojo, LOW);
        digitalWrite(verde, LOW);
        digitalWrite(amarillo, HIGH);
        digitalWrite(rojpeaton, LOW);
        digitalWrite(verpeaton, HIGH);
      }
    } else if (i < contA + contV) {
      // Estado Amarillo
      digitalWrite(rojo, LOW);
      digitalWrite(verde, LOW);
      digitalWrite(amarillo, HIGH);
      digitalWrite(rojpeaton, LOW);
      digitalWrite(verpeaton, HIGH);
     
    } else {
      // Estado Rojo
      digitalWrite(rojo, HIGH);
      digitalWrite(verde, LOW);
      digitalWrite(amarillo, LOW);
      digitalWrite(rojpeaton, LOW);
      digitalWrite(verpeaton, HIGH);
      
    }
    delay(1000);
  }
}
