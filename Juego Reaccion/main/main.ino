#include <TVout.h>
#include <fontALL.h>
#include <avr/pgmspace.h>
#include "SFTV.h"
#include "BitMap.h"

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
#define PUNTO_MUERTO_MAS 600
#define PUNTO_MUERTO_MENOS 400
// Resoluciones de la pantalla
#define HRES 120
#define VRES 96

#define PELOTA 3
#define BORDE_PELOTA 5
#define VELOCIDAD 4

#define MENU 0
#define JUEGO 1
#define RANKING 2

TVout TV;

int x = 60,y = 33;
int vidas = 0;
int estadoJuego = MENU;

int Xvalue = 0, Yvalue = 0, buttonValue = 1;

// Inicio de las clases
Joystick joystick(PINJOY_X, PINJOY_Y, PINJOYBUTTON);
Player jugador1;
Entidad enemigo;
Entidad objetivo;

long randNumber;
unsigned long tiempo,tiempoPrevio;
int puntaje = 0;
int movimiento;

void setup() {
    joystick.setup();  //Inicializar joystick
    Serial.begin(9600);
    TV.begin(PAL,HRES,VRES);
    // Generacion random
    randomSeed(analogRead(0));
    do { // Generacion random y evitando que los elementos se superpongan
        objetivo.mover(random(111), random(71));
        enemigo.mover(random(111), random(71));
    } while ((objetivo.getX() == jugador1.getX() && objetivo.getY() == jugador1.getY()) || (enemigo.getX() == jugador1.getX() && enemigo.getY() == jugador1.getY()));
    // Velocidad de enemigos
    enemigo.setVel(2,0);
}

void Limpiar(){
    // Limpiar pantalla y datos
    TV.delay_frame(1);
    TV.clear_screen();
}

void Actualizar(){
    // Actualizar valores de los controladores
    joystick.update();
}

void Gameplay(){
 if ( estadoJuego == JUEGO){
  Dibujo();
 }

 if ( vidas <= 0){
  estadoJuego = MENU;
 }

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
  switch (vidas) {
  case 1:
    TV.bitmap(80, 0, bit_corazon,0,10,10);
    break;
  case 2:
    TV.bitmap(80, 0, bit_corazon,0,10,10);
    TV.bitmap(90, 0, bit_corazon,0,10,10);
    break;
  case 3:
    TV.bitmap(80, 0, bit_corazon,0,10,10);
    TV.bitmap(90, 0, bit_corazon,0,10,10);
    TV.bitmap(100, 0, bit_corazon,0,10,10);
    break;
  default:
    break;
  }

  // Dibujo de la pelota
  TV.draw_circle(jugador1.getX(),jugador1.getY(),BORDE_PELOTA,WHITE);

  // Dibujo del objetivo
  TV.draw_circle(objetivo.getX(),objetivo.getY(),BORDE_PELOTA,WHITE,INVERT);

  // Dibujo del enemigo
  TV.draw_circle(enemigo.getX(),enemigo.getY(),BORDE_PELOTA,INVERT);
}

void MovimientoPelota(){
  // Arriba
  if (joystick.getY() > PUNTO_MUERTO_MAS){
    jugador1.mover(jugador1.getX(),jugador1.getY() + VELOCIDAD);
  }

  // Derecha
  if (joystick.getX() > PUNTO_MUERTO_MAS){
    jugador1.mover(jugador1.getX() + VELOCIDAD,jugador1.getY());
  }
  // Abajo
  if (joystick.getY() < PUNTO_MUERTO_MENOS){
    jugador1.mover(jugador1.getX(),jugador1.getY() - VELOCIDAD);
  }
  // Izquierda
  if (joystick.getX() < PUNTO_MUERTO_MENOS){
    jugador1.mover(jugador1.getX() - VELOCIDAD,jugador1.getY());
  }
}

void Limites(){
  // Limite derecha
  if ( jugador1.getX() > 110){
    jugador1.mover(110, jugador1.getY());
  }
  // Limite izquierda
  if ( jugador1.getX() < 5){
    jugador1.mover(5, jugador1.getY());
  }
  // Limite arriba
  if ( jugador1.getY() > 90){
    jugador1.mover(jugador1.getX(),90);
  }
  // Limite izquierda
  if ( jugador1.getY() < 5){
    jugador1.mover(jugador1.getX(),5);
  }
}

void Objetivos(){
  // Spawn
  if (jugador1.getX() < objetivo.getX() + BORDE_PELOTA * 2 && jugador1.getY() < objetivo.getY() + BORDE_PELOTA * 2 && jugador1.getX() > objetivo.getX() - BORDE_PELOTA * 2 && jugador1.getY() > objetivo.getY() - BORDE_PELOTA * 2){
    do {
        objetivo.mover(random(10,71), random(10,71));
        enemigo.mover(enemigo.getX(), random(10,71));
    } while ((jugador1.getX() < objetivo.getX() + BORDE_PELOTA * 2 && jugador1.getY() < objetivo.getY() + BORDE_PELOTA * 2 && jugador1.getX() > objetivo.getX() - BORDE_PELOTA * 2 && jugador1.getY() > objetivo.getY() - BORDE_PELOTA * 2) ||
             (jugador1.getX() < enemigo.getX() + BORDE_PELOTA * 2 && jugador1.getY() < enemigo.getY() + BORDE_PELOTA * 2 && jugador1.getX() > enemigo.getX() - BORDE_PELOTA * 2 && jugador1.getY() > enemigo.getY() - BORDE_PELOTA * 2));
    puntaje++;
  }
}

void Enemigos(){
  // Spawn / colisiones
  if (jugador1.getX() < enemigo.getX() + BORDE_PELOTA * 2 && jugador1.getY() < enemigo.getY() + BORDE_PELOTA * 2 && jugador1.getX() > enemigo.getX() - BORDE_PELOTA * 2 && jugador1.getY() > enemigo.getY() - BORDE_PELOTA * 2){
  do {
      objetivo.mover(random(10,71), random(10,71));
      enemigo.mover(random(10,111), random(10,71));
    } while (jugador1.getX() < enemigo.getX() + BORDE_PELOTA * 2 && jugador1.getY() < enemigo.getY() + BORDE_PELOTA * 2 && jugador1.getX() > enemigo.getX() - BORDE_PELOTA * 2 && jugador1.getY() > enemigo.getY() - BORDE_PELOTA * 2);
    vidas--;
    TV.bitmap(0, 0, bit_muerte,0,120,90);
    TV.delay(250);
  } else {
    if (millis() % 1000 < 10){
      // Movimiento Random
      enemigo.mover(enemigo.getX(),random(10,71));
      objetivo.mover(objetivo.getX(),random(10,71));
    }
  }
  
  // Movimiento enemigo
  enemigo.mover(enemigo.getX() + (enemigo.getVelX()),enemigo.getY() + (0));
  // Rebote derecha
  if (enemigo.getX() > 114){
    enemigo.setVel(-(enemigo.getVelX()),enemigo.getVelY());
  }
  // Rebote izquierda
  if (enemigo.getX() < 6){
    enemigo.setVel(-(enemigo.getVelX()),enemigo.getVelY());
  }
  
}

void loop() {

  // Liampiar pantalla
  Limpiar();
  
  // Update controladores
  Actualizar();

  // CMD - Joy
  Gameplay(); 

  if ( estadoJuego == MENU) {
    TV.bitmap(0, 0,bit_mono,0,120,90);
    TV.select_font(font6x8);
    TV.print(5, 10, "Escapa de la jungla");
    TV.print(10, 40, "Pulse para jugar");
    TV.delay(250);
    if (joystick.getButton() == 0){
      estadoJuego = JUEGO;
      puntaje = 0;
      vidas = 3;
    }
  }

  Serial.println(estadoJuego);
}