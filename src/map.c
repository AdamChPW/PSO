#include <stdio.h>
#include <stdlib.h>

#include "map.h"
#include "utilis.h"

#define BUFSIZE 8192

Map* LoadMap(char* file)
{
    int w, h;
    char buf[BUFSIZE];
    Map* map = NULL;

    FILE* in = fopen(file,"r");

    if(in != NULL)
    {
        fscanf(in, "%d %d", &w, &h);
        map = CreateMap(w, h);

        if(map != NULL)
        {
            fgets(buf, BUFSIZE, in);
            int i;
            for(i = 0; i < h; i++){

                if(fgets(buf, BUFSIZE, in) != NULL)
                    if(ReadRow(buf, w, map->data[i]) == w)
                        continue;
                    
                fprintf(stderr, "[src/map.c] Wystopil blad przy implementacji danych do mapy. (rzat %d) \n", i);
                fclose(in);
                FreeMap(map);
                return NULL;
            }

        }
        else{
            fprintf(stderr, "[src/map.c] Wystopil blad przy tworzeniu mapy.\n");
        }
        
    }
    else{
        fprintf(stderr, "[src/map.c] Nie udalo sie otworzyc pliku %s\n", file);
    }

    fclose(in);
    return map;
}

Map* CreateMap(int w, int h){
    int i;
    Map* map = (Map*) malloc(sizeof(Map));
    
    if(map!=NULL)
    {
        map->w = w;
        map->h = h;
        map->data = (double**) malloc(h * sizeof(double*));
        
        for(i = 0; i< h; i++){
            map->data[i] = (double*) malloc(w * sizeof(double)); 
        }
    }
    return map;
}

double GetValue(Map* map, double x, double y){
    int c,r;
    r = (int) x;
    c = (int) y;

    if(r >= map->h || c >= map->h){
        fprintf(stderr, "[src/map.c] GetValue: Wspolrzedne poza mapa: (%d %d)\n",r,c);
        exit(-1);
    }

    return map->data[r][c];
}

void FreeMap(Map* map){
    int i;
    for(i = 0; i < map->h; i++)
        free(map->data[i]);
    free(map->data);
    free(map);
}