#include <Servo.h>  //Libreria servo
#include <Keypad.h>  //Libreia keypad
#include <LiquidCrystal_I2C.h>  //Libreria lcd i2c
Servo servo;
int servopin=10; //pin del servo
int angle=0;  //angulo inicial
int buzzer=13; //pin del buzzer
LiquidCrystal_I2C lcd(0x27, 16, 2); // Se establece el lcd como objeto
const byte ROWS = 4; // Cuatro filas
const byte COLS = 4; // Cuatro columnas
char customKey; 
char password[] = "1234"; // Tu contraseña de 4 caracteres
char inputPassword[5]; // Almacenará la contraseña ingresada

char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
}; //Establecer teclas del keypad

byte rowPins[ROWS] = {9, 8, 7, 6}; // Conectar a los pines de las filas
byte colPins[COLS] = {5, 4, 3, 2}; // Conectar a los pines de las columnas

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

void setup(){
  servo.attach(servopin);
  lcd.init();
  lcd.backlight();
  Serial.begin(9600);
  Serial.println("Ingrese la contraseña:"); //serial para comprobar que funcione bien si
  //se conecto mal el lcd
  lcd.print("Ingrese la clave");
}

void loop(){
  customKey = keypad.getKey();
  
  if (customKey){
    // Imprime la tecla presionada en el LCD
    lcd.setCursor(strlen(inputPassword), 1); // Coloca el cursor en la fila 1
    lcd.print(customKey);
    
    // Almacena la tecla en el arreglo de la contraseña ingresada
    if (strlen(inputPassword) < 4) {
      inputPassword[strlen(inputPassword)] = customKey;
    }
    
    // Verifica si se ha ingresado la contraseña completa
    if (strlen(inputPassword) == 4){
      // Compara la contraseña ingresada con la contraseña predefinida
      if (strcmp(inputPassword, password) == 0){
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Clave");
        lcd.setCursor(0,1);
        lcd.print("Correcta");
        delay(2000); // Muestra el mensaje durante 2 segundos
        lcd.clear();
        lcd.print("Ingrese la clave:");
        Serial.println("Clave correcta.");
        digitalWrite(buzzer,HIGH); //suena el buzzer
        delay(1000);
        digitalWrite(buzzer,LOW);
        servo.write(0);//se mueve el servo motor para abrir la puerta
        


        memset(inputPassword, 0, sizeof(inputPassword)); // Borra la contraseña ingresada
      } else {
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Clave");
        lcd.setCursor(0,1);
        lcd.print("Incorrecta");
        delay(2000); // Muestra el mensaje durante 2 segundos
        lcd.clear();
        lcd.print("Ingrese la clave:");
        Serial.println("Clave incorrecta.");
        memset(inputPassword, 0, sizeof(inputPassword));
        servo.write(90);
      }
    }
  }
}