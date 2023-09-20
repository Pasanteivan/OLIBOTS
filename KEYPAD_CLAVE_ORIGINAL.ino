//Proyecto caja fuerte
/*Link de simulacion wokwik:
https://wokwi.com/projects/376418171433447425
*/

#include <Servo.h>  //Libreria servo
#include <Keypad.h>  //Libreia keypad
#include <LiquidCrystal_I2C.h>  //Libreria lcd i2c
Servo servo;
int servopin=10; //pin del servo
int angle=0;  //angulo inicial
LiquidCrystal_I2C lcd(0x27, 16, 2); // Se establece el lcd como objeto
const byte ROWS = 4; // Cuatro filas
const byte COLS = 4; // Cuatro columnas
char customKey; 
char password[] = "1234"; // Tu contraseña de 4 caracteres
// se puede cambiar
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
  servo.write(angle); // se pone el servo en posicion inicial
  lcd.init();
  lcd.backlight();
  lcd.print("Ingrese la clave");
  lcd.setCursor(6,1);
  lcd.print("# Cerrar");
}

void loop(){
  customKey = keypad.getKey();
  if (customKey){ //verifica si se presiono una tecla
    // Imprime la tecla presionada en el LCD
    lcd.setCursor(strlen(inputPassword), 1); // Coloca el cursor en la fila 1
    lcd.print("*");
    // Almacena la tecla en el arreglo de la contraseña ingresada
    if (strlen(inputPassword) < 4) {
      inputPassword[strlen(inputPassword)] = customKey;
      if(inputPassword[0]=='#') // Si presionamos primero #, se cerrara la caja
      // fuerte, verifica que el primer valor del array sea exactamente #
      {
        lcd.clear();
        lcd.print("CERRANDO");
        servo.write(angle);
        delay(500);
        lcd.clear();
        customKey=0;
        lcd.setCursor(0,0);
        lcd.print("Ingrese la clave:");
        lcd.setCursor(6,1);
        lcd.print("# Cerrar");
        memset(inputPassword, 0, sizeof(inputPassword));
      }
    }
    
    // Verifica si se ha ingresado la contraseña completa
    if (strlen(inputPassword) == 4){
      // Compara la contraseña ingresada con la contraseña predefinida
      if (strcmp(inputPassword, password) == 0) // compara si la contraseña ingresada
      // es igual a la contraseña de ingreso
      {
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Clave");
        lcd.setCursor(0,1);
        lcd.print("Correcta");
        delay(2000); // Muestra el mensaje durante 2 segundos
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Ingrese la clave:");
        lcd.setCursor(6,1);
        lcd.print("# Cerrar");
        servo.write(angle+90);//se mueve el servo motor para abrir la puerta
        memset(inputPassword, 0, sizeof(inputPassword)); // Borra la contraseña ingresada
        
      } 
      else 
      {
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Clave");
        lcd.setCursor(0,1);
        lcd.print("Incorrecta");
        delay(2000); // Muestra el mensaje durante 2 segundos
        lcd.clear();    
        lcd.setCursor(0,0);
        lcd.print("Ingrese la clave:");
        lcd.setCursor(6,1);
        lcd.print("# Cerrar");
        memset(inputPassword, 0, sizeof(inputPassword)); // Borra la contraseña ingresada
        servo.write(angle); // el servo cierra la puerta si se puso la contraseña incorrecta
        }
      }
    }
}
