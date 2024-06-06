#include <TVout.h>
#include <fontALL.h>
#include <avr/pgmspace.h>
/*
GND - GND
Vcc - 5v
VRx - A0
VRy - A1
SW -  D10
*/
#define PINJOY_X 0
#define PINJOY_Y 1
#define PINJOYBUTTON 10

#define PELOTA 3
#define BORDE_PELOTA 5
#define VELOCIDAD 2

TVout TV;

int x = 60,y = 33;

int Xvalue = 0;
int Yvalue = 0;
int buttonValue = 1;

long randNumber;
long xPosObjetivo,yPosObjetivo;
long xPosEnemigo,yPosEnemigo;
bool izquierdaEnemigo,derechaEnemigo,arribaEnemigo,abajoEnemigo;
int puntaje = 0;

void setup() {
  pinMode(PINJOYBUTTON , INPUT_PULLUP);  //activar resistencia pull up 
  Serial.begin(9600);
  TV.begin(PAL,120,96);
  // Generacion random
  randomSeed(analogRead(0));
  do { // Generacion random y evitando que los elementos se superpongan
    xPosObjetivo = random(111);
    yPosObjetivo = random(71);
    xPosEnemigo = random(111);
    yPosEnemigo = random(71);
  } while ((xPosObjetivo == x && yPosObjetivo == y) || (xPosEnemigo == x && yPosEnemigo == y));
}

void Limpiar(){
  // Limpiar pantalla y datos
  TV.delay_frame(1);
  TV.clear_screen();
}

void Actualizar(){
  // Actualizar valores de los controladores
  Xvalue = analogRead(PINJOY_X);
  //delay(10); // Agregado un pequeño retraso para estabilizar la lectura
  Yvalue = analogRead(PINJOY_Y);
  buttonValue = digitalRead(PINJOYBUTTON);
}

void Gameplay(){
  Dibujo();

  MovimientoPelota();

  Limites();

  Objetivos();

  Enemigos();
}

void Dibujo(){
  // Dibujo del puntaje
  TV.select_font(font6x8);
  TV.print("Puntaje:");
  TV.print(puntaje);

  // Dibujo de la pelota
  TV.draw_circle(x,y,PELOTA,WHITE);
  TV.draw_circle(x,y,BORDE_PELOTA,WHITE,INVERT);

  // Dibujo del objetivo
  TV.draw_circle(xPosObjetivo,yPosObjetivo,BORDE_PELOTA,WHITE);

  // Dibujo del enemigo
  TV.draw_circle(xPosEnemigo,yPosEnemigo,BORDE_PELOTA,WHITE,INVERT);
}

void MovimientoPelota(){
  // Arriba
  if (Yvalue > 600){
    y = y + VELOCIDAD;
  }

  // Derecha
  if (Xvalue > 600){
    x = x + VELOCIDAD;
  }
  // Abajo
  if (Yvalue < 400){
    y = y - VELOCIDAD;
  }
  // Izquierda
  if (Xvalue < 400){
    x = x - VELOCIDAD;
  }
}

void Limites(){
  // Limite derecha
  if ( x > 110){
    x  = 110;
  }
  // Limite izquierda
  if ( x < 5){
    x = 5;
  }
  // Limite arriba
  if ( y > 90){
    y = 90;
  }
  // Limite izquierda
  if ( y < 5){
    y = 5;
  }

  if (xPosEnemigo > 110){
    izquierdaEnemigo = true;
    
  }
}

void Objetivos(){
  // Spawn
  if (x < xPosObjetivo + BORDE_PELOTA && y < yPosObjetivo + BORDE_PELOTA && x > xPosObjetivo - BORDE_PELOTA && y > yPosObjetivo - BORDE_PELOTA){
    do {
      xPosObjetivo = random(106);
      yPosObjetivo = random(71);
      xPosEnemigo = random(106);
      yPosEnemigo = random(71);
    } while ((x < xPosObjetivo + BORDE_PELOTA && y < yPosObjetivo + BORDE_PELOTA && x > xPosObjetivo - BORDE_PELOTA && y > yPosObjetivo - BORDE_PELOTA) ||
             (x < xPosEnemigo + BORDE_PELOTA && y < yPosEnemigo + BORDE_PELOTA && x > xPosEnemigo - BORDE_PELOTA && y > yPosEnemigo - BORDE_PELOTA));
    puntaje++;
  }
}

void Enemigos(){
  // Spawn
  if (x < xPosEnemigo + BORDE_PELOTA && y < yPosEnemigo + BORDE_PELOTA && x > xPosEnemigo - BORDE_PELOTA && y > yPosEnemigo - BORDE_PELOTA){
  do {
      xPosEnemigo = random(106);
      yPosEnemigo = random(71);
    } while (x < xPosEnemigo + BORDE_PELOTA && y < yPosEnemigo + BORDE_PELOTA && x > xPosEnemigo - BORDE_PELOTA && y > yPosEnemigo - BORDE_PELOTA);
    puntaje--;
  } 
}


void loop() {

  // Liampiar pantalla
  Limpiar();
  
  // Update controladores
  Actualizar();

  // CMD - Joy
  Gameplay(); 

}