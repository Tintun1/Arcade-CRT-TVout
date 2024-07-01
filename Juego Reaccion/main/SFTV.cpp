#include "SFTV.h"
#include "Arduino.h"
/* //////////////
  -Declaracion del objeto joystick-
    -pinX - Pin donde se encuentra los valores X del Stick
    -pinY - Pin donde se encuentra los valores Y del Stick
    -pinButton - Pin donde se encuentra el PULSADOR del Stick
*/ //////////////
Joystick::Joystick(int _pinX, int _pinY, int _pinButton) {
    pinX = _pinX;
    pinY = _pinY;
    pinButton = _pinButton;
}

/* //////////////
  -Inicializacion del joystick
*/ //////////////
void Joystick::setup() {
    pinMode(pinX, INPUT);
    pinMode(pinY, INPUT);
    pinMode(pinButton, INPUT_PULLUP);
}

/* //////////////
  -Actualizacion de los valores X,Y y PULSADOR del Joystick
*/ //////////////
void Joystick::update() {
    Xvalue = analogRead(pinX);
    Yvalue = analogRead(pinY);
    buttonValue = digitalRead(pinButton);
}

/* //////////////
  -Retorna valor X
*/ //////////////
int Joystick::getX() {
    return Xvalue;
}

/* //////////////
  -Retorna valor Y
*/ //////////////
int Joystick::getY() {
    return Yvalue;
}

/* //////////////
  -Retorna valor PULSADOR
*/ //////////////
int Joystick::getButton() {
    return buttonValue;
}

/* //////////////
  -Declaracion del objeto Player
    -Por defecto los valores de X e Y inician en 0
*/ //////////////
Player::Player() {
    x = 0;
    y = 0;
}

void Player::mover(int _x, int _y) {
    x = _x;
    y = _y;
}

int Player::getX() {
    return x;
}

int Player::getY() {
    return y;
}

Entidad::Entidad() {
  velocidad = 0;
}

void Entidad::caida(){
  mover(getX(), getY() + velocidad );
}

void Entidad::barrido(){
  mover(getX() - velocidad, getY());
}

void Entidad::setVel(int _velocidad){
  velocidad = _velocidad;
}

void Entidad::setVel(int _velocidadX, int _velocidadY){
  velocidadX = _velocidadX;
  velocidadY = _velocidadY;
}

int Entidad::getVel(){
  return velocidad;
}

int Entidad::getVelX(){
  return velocidadX;
}

int Entidad::getVelY(){
  return velocidadY;
}