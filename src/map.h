#ifndef _MAP_H_
#define _MAP_H_

// Obsługa wczytywania mapy, zwalniania pamięci mapy, pobierania wartości z danego punktu.
// data[r][c] (x = row, y = column)

typedef struct Map {
    int w;
    int h;
    double** data;
} Map;

Map* LoadMap(char* file);

Map* CreateMap(int w, int h);

double GetValue(Map* map, double x, double y);

// Zwraca wektor z [MaxValue, xMax, yMax];
double* GetMax(Map* map);

void FreeMap(Map* map);

#endif