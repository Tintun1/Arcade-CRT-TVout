#include <TVout.h>
#include <fontALL.h>
#include <avr/pgmspace.h>
#include "SFTV.h"

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
#define VELOCIDAD 2

TVout TV;

int x = 60,y = 33;

int Xvalue = 0, Yvalue = 0, buttonValue = 1;

// Inicio de las clases
Joystick joystick(PINJOY_X, PINJOY_Y, PINJOYBUTTON);
Player jugador1;
Entidad enemigo;

long randNumber;
long xPosObjetivo,yPosObjetivo;
bool izquierdaEnemigo,derechaEnemigo,arribaEnemigo,abajoEnemigo;
int puntaje = 0;

void setup() {
    joystick.setup();  //Inicializar joystick
    Serial.begin(9600);
    TV.begin(PAL,HRES,VRES);
    // Generacion random
    randomSeed(analogRead(0));
    do { // Generacion random y evitando que los elementos se superpongan
        xPosObjetivo = random(111);
        yPosObjetivo = random(71);
        enemigo.mover(random(111), random(71));
    } while ((xPosObjetivo == jugador1.getX() && yPosObjetivo == jugador1.getY()) || (enemigo.getX() == jugador1.getX() && enemigo.getY() == jugador1.getY()));
    // Velocidad de enemigos
    enemigo.setVel(VELOCIDAD,VELOCIDAD);
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
  TV.draw_circle(jugador1.getX(),jugador1.getY(),BORDE_PELOTA,WHITE);

  // Dibujo del objetivo
  TV.draw_circle(xPosObjetivo,yPosObjetivo,BORDE_PELOTA,WHITE);

  // Dibujo del enemigo
  TV.draw_circle(enemigo.getX(),enemigo.getY(),BORDE_PELOTA,WHITE,INVERT);
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
  if (jugador1.getX() < xPosObjetivo + BORDE_PELOTA && jugador1.getY() < yPosObjetivo + BORDE_PELOTA && jugador1.getX() > xPosObjetivo - BORDE_PELOTA && jugador1.getY() > yPosObjetivo - BORDE_PELOTA){
    do {
        xPosObjetivo = random(106);
        yPosObjetivo = random(71);
        enemigo.mover(random(111), random(71));
    } while ((jugador1.getX() < xPosObjetivo + BORDE_PELOTA && jugador1.getY() < yPosObjetivo + BORDE_PELOTA && jugador1.getX() > xPosObjetivo - BORDE_PELOTA && jugador1.getY() > yPosObjetivo - BORDE_PELOTA) ||
             (jugador1.getX() < enemigo.getX() + BORDE_PELOTA && jugador1.getY() < enemigo.getY() + BORDE_PELOTA && jugador1.getX() > enemigo.getX() - BORDE_PELOTA && jugador1.getY() > enemigo.getY() - BORDE_PELOTA));
    puntaje++;
  }
}

void Enemigos(){
  // Spawn / colisiones
  if (jugador1.getX() < enemigo.getX() + BORDE_PELOTA && jugador1.getY() < enemigo.getY() + BORDE_PELOTA && jugador1.getX() > enemigo.getX() - BORDE_PELOTA && jugador1.getY() > enemigo.getY() - BORDE_PELOTA){
  do {
      enemigo.mover(random(111), random(71));
    } while (jugador1.getX() < enemigo.getX() + BORDE_PELOTA && jugador1.getY() < enemigo.getY() + BORDE_PELOTA && jugador1.getX() > enemigo.getX() - BORDE_PELOTA && jugador1.getY() > enemigo.getY() - BORDE_PELOTA);
    puntaje--;
  }
  // Movimiento
  enemigo.mover(enemigo.getVelX(), enemigo.getVelY());
  // limites de pantalla
  if (enemigo.getX() > 110){ // Limite derecha
    enemigo.setVel(-enemigo.getVelX(),enemigo.getVelY());
  }
  // Limite izquierda
  if (enemigo.getX() < 5){
    enemigo.setVel(-enemigo.getVelX(),enemigo.getVelY());
  } 
  // Limite arriba
  if ( enemigo.getY() > 90){
    enemigo.setVel(enemigo.getVelX(),-enemigo.getVelY());
  }
  // Limite izquierda
  if ( enemigo.getY() < 5){
    enemigo.setVel(enemigo.getVelX(),-enemigo.getVelY());
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