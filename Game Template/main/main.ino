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
// Resoluciones de la pantalla
#define HRES 120
#define VRES 96

TVout TV;
Joystick joystick(PINJOY_X, PINJOY_Y, PINJOYBUTTON);
Obstaculo cubo;

void Limpiar() {
  // Limpia pantalla y datos
  TV.delay_frame(1);
  TV.clear_screen();
}

void Actualizar() {
  // Actualizar valores de los controladores
  joystick.update();
}

void Gameplay() {
  Dibujo();
}

void Dibujo() {
  // Dibujo del puntaje
  TV.select_font(font6x8);
  TV.print("Template");
}


void setup() {
  TV.begin(PAL, HRES, VRES);
  joystick.setup();  //Inicializar joystick
}

void loop() {
  // Liampia pantalla
  Limpiar();

  // Update controladores
  Actualizar();

  // CMD - Joy
  Gameplay();
}