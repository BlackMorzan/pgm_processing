#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct /*inicjacja struktury zawierającej odcienie, wymiary i adres tablicy*/
{ 
	int wym_x, wym_y, odcieni, typ;
	int *obraz; 
	int *RED; 
	int *GREEN; 
	int *BLUE;
	int r, g, b;

}  obrazek;


int czytaj(FILE *plik_we, obrazek *ob);

void wyswietl(char *n_pliku);

void negatyw(obrazek *ob);

void progowanie (int prog, obrazek *ob);

void konturowanie (obrazek *ob);

void rozciaganie (obrazek *ob);

void zmiana (int cze, int bi, obrazek *ob);

void zapisz(FILE *plik_wy, obrazek *ob);

void konwersja (obrazek *ob);
