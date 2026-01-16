#ifndef _UTILIS_H_
#define _UTILIS_H

// (Opcjonalnie) Generatory liczb losowych, funkcje pomocnicze.

/*
Czyta w doublow z string s i zapisuje w tablicy target.
Zwraca liczbe wprowadzonych doubli.
Uwaga: Rozmiar tablicy target nie moze byc mniejszy od w!
*/
int ReadRow(char *s, int w, double *target);


double RandDouble(double min, double max);

#endif