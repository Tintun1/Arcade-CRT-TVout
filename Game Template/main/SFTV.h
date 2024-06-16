class Joystick {
    private:
        int pinX, pinY, pinButton;
        int Xvalue, Yvalue, buttonValue;
    public:
        Joystick(int, int , int);
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

class Obstaculo : public Player {
  private:
  int velocidad;
  public:
  Obstaculo();
  void caida();
  void barrido();
  void setVel(int);
};