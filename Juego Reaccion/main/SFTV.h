class Joystick {
    private:
        int pinX, pinY, pinButton;
        int Xvalue, Yvalue, buttonValue;
    public:
        Joystick(int, int, int);
        void setup();
        void update();
        int getX();
        int getY();
        int getButton();
};

class Player {
    private:
        int x, y;
    public:
        Player();
        void mover(int, int);
        int getX();
        int getY();
};

class Entidad : public Player {
  private:
  int velocidad,velocidadX,velocidadY;
  public:
  Entidad();
  void caida();
  void barrido();
  void setVel(int);
  void setVel(int, int);
  int getVel();
  int getVelX();
  int getVelY();
};