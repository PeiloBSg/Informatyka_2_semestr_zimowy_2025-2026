#include <iostream>


class Pilka
{
public:
    Pilka(int x_in, int y_in, int vx_in, int vy_in, int r_in);
    void przesun();
    void odbijX();
    void odbijY();
    void kolizjaSciana(int w, int h);
    void drukuj();
    //--metody do odczytu danych
    int getX(){return x;}
    int getY(){return y;}
    int getVX(){return vx;}
    int getVY(){return vy;}
private:
    int x;
    int y;
    int vx;
    int vy;
    int r;

};


Pilka::Pilka(int x_in, int y_in, int vx_in, int vy_in, int r_in){
    if(x_in <=0)
        x_in = 0;
    if(x_in>=640)
        x_in =640;
    x = x_in;
    y = y_in;
    vx = vx_in;
    vy = vy_in;
    r = r_in;
}

void Pilka::przesun()
{
    //std::cout<<"Przesuwam pilke\n";
    x+=vx;
    y+=vy;

}

void Pilka::odbijX()
{
    vx=-vx;
}

void Pilka::odbijY()
{
    vy=-vy;
}

void Pilka::kolizjaSciana(int w, int h)
{
   if(getX()>=640||getX()<=0){
        odbijX();
        std::cout<<"HIT-x\n";
   }
}
void Pilka::drukuj()
{
    std::cout<<" x="<<getX()<<" y="<<getY()<<" vx="<<getVX()<<" vy="<<getVY()<<"\n";
}

