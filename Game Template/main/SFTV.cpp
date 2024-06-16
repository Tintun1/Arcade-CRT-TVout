#include "SFTV.h"
#include "Arduino.h"
Joystick::Joystick(int _pinX, int _pinY, int _pinButton) {
    pinX = _pinX;
    pinY = _pinY;
    pinButton = _pinButton;
}

void Joystick::setup() {
    pinMode(pinX, INPUT);
    pinMode(pinY, INPUT);
    pinMode(pinButton, INPUT_PULLUP);
}

void Joystick::update() {
    Xvalue = analogRead(pinX);
    Yvalue = analogRead(pinY);
    buttonValue = digitalRead(pinButton);
}

int Joystick::getX() {
    return Xvalue;
}

int Joystick::getY() {
    return Yvalue;
}

int Joystick::getButton() {
    return buttonValue;
}

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

Obstaculo::Obstaculo() {
  velocidad = 1;
}

void Obstaculo::caida(){
  mover(getX(), getY() + velocidad );
}

void Obstaculo::barrido(){
  mover(getX() - velocidad, getY());
}

void Obstaculo::setVel(int _velocidad){
  velocidad = _velocidad;
}