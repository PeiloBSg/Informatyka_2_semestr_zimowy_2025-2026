

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

struct Pomiar
{
    char czas[40];
    float temperatura;
    float cisnienie;
    float wilgotnosc;
};

struct Stacja{
    int id;
    char nazwa[40];
    char lokalizacja[60];
};

struct Rekord{
    struct Stacja stacja;
    struct Pomiar pomiar;
};


struct ProbaMocy{
    char czas[30];
    float moc_kw;
};



int main()
{
                            //A
    /*
    const int N=10;
    float T_sr=0, P_sr=0;
    time_t currentTime;
    struct Rekord dane[10]; //tablica danych pomiarowych
    struct Stacja s1={100, "Stacja PG", "Gdansk-Wrzeszcz"};
    struct Stacja s2={200, "Aniolki", "Gdansk-Aniolki"};

    //printf(" %d %s %s\n", s1.id, s1.nazwa, s1.lokalizacja);       //przyk³¹d odczytu danych ze struktury

    //generator danych pomiar
    srand(time(NULL));
    for(int i=0;i<N;i++)
    {
        dane[i].pomiar.temperatura = rand()%45-10;
        dane[i].pomiar.cisnienie = 980 + rand()%55;
        dane[i].pomiar.wilgotnosc = 30 + rand()%70;

        time(&currentTime);

        strcpy(dane[i].pomiar.czas, ctime(&currentTime));
        dane[i].pomiar.czas[24]='\0';
    }




    //generator danych wydruk
    for(int i=0;i<N;i++)
    {
        if(i%2==0)
            dane[i].stacja = s1;
        else
            dane[i].stacja = s2;
    }

    //Odczyt danych, wydruk
    printf(" ID    NAZWA_STACJI    LOKALIZACJA_STACJI    CZAS    TEMP    CIS    WILG\n");
    for(int i=0;i<N;i++)
        {
        printf(" %d    %s    %s", dane[i].stacja.id, dane[i].stacja.nazwa, dane[i].stacja.lokalizacja);
        printf(    "    %s", dane[i].pomiar.czas);
        printf("    %.2f    ", dane[i].pomiar.temperatura);
        printf("%.2f    ", dane[i].pomiar.cisnienie);
        printf("%.2f\n ", dane[i].pomiar.wilgotnosc);
    }
//Przetwarzanie danych
    //Policz œrednie
    for(int i=0;i<N;i++)
    {
        T_sr+=dane[i].pomiar.temperatura;
        P_sr+=dane[i].pomiar.cisnienie;
    }
    T_sr=T_sr/N;
    P_sr=P_sr/N;

    printf("T_sr=%.2f, P_sr=%.2f\n", T_sr, P_sr);


    */



                            //B




    float Ez=0;
    time_t currentTime;
    struct ProbaMocy p[20]; //dane pomiarowe
    float D_t_h = 15/60; //15 min w godzinach


    //generator danych
    for(int i=0;i<20;i++)
    {
        time(&currentTime);

        strcpy(p[i].czas, ctime(&currentTime));
        int ind = strcspn(p[i].czas,"\n");
        p[i].czas[ind]='\0';
        p[i].moc_kw = (1000 + rand()%1000)/1000.0; //moc w kW
    }

    //odczyt danych

    for(int i=0;i<20;i++)
    {
        printf(" %s  %.2f\n", p[i].czas, p[i].moc_kw);
    }


    //przetwarzanie danych
    //liczê zu¿yt¹ energiê

    for(int i=0;i<20-1;i++){
        Ez=Ez+D_t_h*(p[i].moc_kw+p[i+1].moc_kw)/2;
    }

    printf("Zuzycie energii: Ez=%.2f\n",Ez);
}













