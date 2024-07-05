class Joystick {
    private:
        int pinX, pinY, pinButton;
        int Xvalue, Yvalue, buttonValue;
    public:
        /* //////////////
          -Declaracion del objeto joystick-
            -pinX - Pin donde se encuentra los valores X del Stick
            -pinY - Pin donde se encuentra los valores Y del Stick
            -pinButton - Pin donde se encuentra el PULSADOR del Stick
        */ //////////////
        Joystick(int, int, int);
        /* //////////////
          -Inicializacion del joystick
        */ //////////////
        void setup();
        /* //////////////
          -Actualizacion de los valores X,Y y PULSADOR del Joystick
        */ //////////////
        void update();
        /* //////////////
          -Retorna valor X
        */ //////////////
        int getX();
        /* //////////////
          -Retorna valor Y
        */ //////////////
        int getY();
        /* //////////////
          -Retorna valor PULSADOR
        */ //////////////
        int getButton();
};

class Player {
    private:
        int x, y;
    public:
    /* //////////////
      -Declaracion del objeto Player
        -Por defecto los valores de X e Y inician en 0
    */ //////////////
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