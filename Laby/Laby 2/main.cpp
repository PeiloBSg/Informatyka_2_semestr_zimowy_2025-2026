#include <iostream>
#include "Pilka.h"
#include "paletka.h"

int main()
{
   /* Pilka p1(100,100,10,10,4);
        for(int i=0;i<20;i++)
        {
            p1.przesun();
            p1.drukuj();
        }
        */


        Paletka pal1(100,10,10,0,10);
            for(int i=0;i<70;i++)
            {
                pal1.przesun();
                pal1.drukuj();
                pal1.kolizjaSciana();
            }

    return 0;
}
