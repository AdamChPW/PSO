#include <stdio.h>

#include "map.h"

/*
Puki co odpalanie i obsluga bledow

Zwraca 0 - Gdy program zakonczyl dzialanie sukcesem
Zwraca 1 - Gdy nie podano zadnych argumentow wywolania
Zwraca 2 - Gdy podano nieparzysta liczbe argumentow
Zwraca 3 - Nie udalo sie wczytac mapy
*/

int main(int argc, char** argv)
{
    if(argc == 1){
        fprintf(stderr,"[%s] Error 1: Nie podano zadnych argumentow.\nProgram wymaga podania przynajmniej sciezki do pliku z mapa.\n",argv[0]);
        return 1;
    }

    if(argc%2 == 1){
        fprintf(stderr,"[%s] Error 2: Niewlasciwa strukrura argumentow.\n",argv[0]);
        return 2;
    }

    Map *map = LoadMap(argv[1]);

    if(map == NULL){
        fprintf(stderr,"[%s] Error 3: Nieudalo sie wczytac mapy.\n",argv[0]);
        return 3;
    }

    return 0;
}