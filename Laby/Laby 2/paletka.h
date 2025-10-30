#include <iostream>


class Paletka
{
public:
    Paletka(int x_in, int y_in, int vx_in, int vy_in, int r_in);
    void przesun();
    void zatrzymajX();
    void kolizjaSciana();
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


Paletka::Paletka(int x_in, int y_in, int vx_in, int vy_in, int r_in){
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

void Paletka::przesun()
{
    //std::cout<<"Przesuwam paletke\n";
    x+=vx;

}

void Paletka::zatrzymajX()
{
    vx=0;
    if(x>=635)
        std::cout<<"Prawa\n";
    else
        std::cout<<"Lewa\n";
}


void Paletka::kolizjaSciana()
{
   if(getX()>=635||getX()<=5){
        zatrzymajX();
   }
}
void Paletka::drukuj()
{
    std::cout<<" x="<<getX()<<" y="<<getY()<<" vx="<<getVX()<<" vy="<<getVY()<<"\n";
}
