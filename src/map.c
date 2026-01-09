#include <stdio.h>
#include <stdlib.h>

#include "map.h"

Map* LoadMap(char* file)
{
    int w, h;
    Map* map = NULL;

    FILE* in = fopen(file,"r");

    if(in != NULL)
    {
        fscanf(in, "%d %d", &w, &h);
        map = CreateMap(w, h);

        if(map != NULL)
        {
            int i, j;
            for(i = 0; i < h; i++)
                for(j = 0; j < w; j++)
                    if( fscanf(in, "%lf", &map->data[i][j])!=1)
                    {
                        fprintf(stderr, "Wystopil blad przy implementacji danych do mapy. [%d %d] \n", i, j);
                        fclose(in);
                        FreeMap(map);
                        return NULL;
                    }

        }
        else{
            fprintf(stderr, "Wystopil blad przy tworzeniu mapy.\n");
            fclose(in);
            return NULL;
        }
        
    }
    else{
        fprintf(stderr, "Nie udalo sie otworzyc pliku %s\n", file);
        return NULL;
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
    int i,j;
    i = (int) x;
    j = (int) y;
    return map->data[i][j];
}

void FreeMap(Map* map){
    int i;
    for(i = 0; i < map->h; i++)
        free(map->data[i]);
    free(map->data);
    free(map);
}