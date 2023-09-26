int joystick_x = 0; // posicion x del joystick
int joystick_y = 0; // posicion y del joystick
#include "LedControl.h" // libreria de control de matriz de leds
LedControl lc=LedControl(8,10,9,1); // ponemos los pines a los que se conecta la matriz de leds

void setup() {
  // Modo input para
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  lc.shutdown(0,false);// activamos la matriz de leds
  lc.setIntensity(0,8);// brillo, podemos poner hasta 15
  lc.clearDisplay(0);// limpia la pantalla
}
void loop() {
  joystick_x = analogRead(A0); // lectura de joystick en x
  joystick_y = analogRead(A1); // lectura del joystick en y
  char posicion_x = map(joystick_x, 1021, 0, 7, 0); //Convierte lo que lee el joystick a la posicion 
                                            //el plano x
  char posicion_y = map(joystick_y, 1021, 0, 0, 7); //Lo mismo para el plano y
  lc.clearDisplay(0); // limpiamos la pantalla
  lc.setLed(0,posicion_x,posicion_y,true);  // se setea la posicion del led 
                                              // a la posicion actual del joystick
  delay(150);
}
