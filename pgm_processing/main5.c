#include <stdio.h>
#include "mod5.h"
#include <stdlib.h>
#include <string.h>

#define MAX 512            /* Maksymalny rozmiar wczytywanego obrazu */
#define DL_LINII 1024      /* Dlugosc buforow pomocniczych */
/****************************MAIN*************************/

int main(int argc, char *argh[])
{
    int wybor=1, prog, czern, biel;  /*wprowadzenie wartosci wpisywanych przez uzytkownika*/
    FILE *plik;
    int odczytano=0;        /*wprowadzenie wartosci sprawdzajacej, czy plik zostal wczytany*/      
    char *nazwaws;
    obrazek ob;
    
    int i, wczytaj=0, wyswietlanie=0, zapisywanie=0, negoj=0, progoj=0, konturoj=0, rozciagaj=0, zmien=0, szarz=0, red=0, green=0, blue=0;
    
    for (i=1; i<argc; i++)  /*obraz musi być napierw wczytany*/
      switch (argh[i][1])
    	{
      case 'i':/*wczytaj*/
        wczytaj=1;
	fprintf(stdout,"wczytaj");
        if (++i<argc)
        {
          nazwaws=argh[i];
          plik=fopen(nazwaws,"r");
          if (plik != NULL)
          {
          	odczytano = czytaj(plik, &ob);
          	fclose(plik);
          }
  			}
          else
           	fprintf(stderr,"brak pliku");
          break;
      }
      if (wczytaj!=1)
      {
      	fprintf(stderr,"brak polecenia wczytaj\n");
      	return 10;
      }
    
    for (i=1; i<argc; i++)  /*na jakim kolorze bedziesz pracowac?*/
    {
    	switch (argh[i][1])
    	{
    		case 'r': /*czerwony*/
    			if (wczytaj==0) 
          	fprintf(stderr,"brak pliku!\n");
          if (ob.typ!=3)
          {
          	printf("nie ma kolorow\n");
          	break;
          }
          else
          	ob.r=1;
          	break;
          	
      	case 'g': /*green*/
    			if (wczytaj==0) 
          	fprintf(stderr,"brak pliku!\n");
          if (ob.typ!=3)
          {
          	printf("nie ma kolorow\n");
          	break;
          }
          else
          	ob.g=1;
          	break;
          	
        case 'b': /*blue*/
    			if (wczytaj==0) 
          	fprintf(stderr,"brak pliku!\n");
          if (ob.typ!=3)
          {
          	printf("nie ma kolorow\n");
          	break;
          }
          else
          	ob.b=1;
          	break;
          	
 				case 'l': /*Wyszarzanie*/
        		if (green==1 || blue==1 || red==1)
        			fprintf(stderr,"czy na pewno chcesz pracowac na szarym?");
        		if (ob.typ!=3)
          	{
          		printf("nie ma kolorow\n");
          		break;
          	}
        		if (odczytano!=0)
        		{
        			konwersja(&ob);
         	    printf("wykonano\n");
         	  }
         	  else
         	    fprintf(stderr,"brak pliku\n");
         	  break;
    	}	
    }
          
    for (i=1; i<argc; i++)
    {
    	switch (argh[i][1])
    	{
               
        case 'n':/*Negatyw*/
          negoj=1;
          if (wczytaj==0) 
          	fprintf(stderr,"brak pliku!\n");
          else 
          	negatyw(&ob);
          break;
           
         case 'p':/*Progowanie*/
           progoj=1;
           if (wczytaj==0) 
           	fprintf(stderr,"brak pliku!\n");
          else
          {
            if (++i<argc)
            {
              prog=atoi(argh[i]);
              progowanie(prog, &ob);
             }
					}
					break;
               
            case 'h':  /*rozciaganie histogramu*/
            	if (wczytaj!=0)
                rozciaganie(&ob);
            	else
                fprintf(stderr,"brak pliku\n");
            	break;
               
           case 'z': /*zmiana poziomów*/
            printf("zmiana poziomow...\n");
            if (wczytaj!=0)
            {
              czern=atoi(argh[i]);
              biel=atoi(argh[i]);
              if (biel<=0 || biel>=100)
								fprintf(stderr,"niewlasciwa wartosc bieli");
							else
							{
								if (czern<=0 || czern>=100)
									fprintf(stderr,"niewlasciwa wartosc czerni");
								else
								{
                	zmiana(czern, biel, &ob);
                }
              }
            }
            else
                fprintf(stderr,"brak pliku\n");
            break;
               
            case 'k':/*Konturowanie*/
                konturoj=1;
                if (wczytaj==0) 
                	printf("Najpierw podaj plik do wczytania!\n");
                else 
                	konturowanie(&ob);
                break;

        }                                                                                  
    }
    
    
    for (i=1; i<argc; i++)
    {
    	switch (argh[i][1])
    	{
    	case 'o':/*Zapisz*/
        if (wczytaj==0) 
        	fprintf(stderr,"brak pliku!\n");
        zapisywanie=1;
        if (++i<argc)
        {
          nazwaws=argh[i];
          plik=fopen(nazwaws,"w");
          zapisz(plik, &ob);
          fclose(plik);
        }
        break;
  		}
    }
    
    if (zapisywanie!=1)
    	{
    		fprintf(stderr,"brak polecenia zapisz\n");
    		return 10;
			}
		
		for (i=1; i<argc; i++)
    {
    	switch (argh[i][1])
    	{
    		case 'd':/*Wyswietlanie*/
          wyswietlanie=1;
          if (wczytaj==0) 
	        	printf("Najpierw podaj plik do wczytania!\n");
          wyswietl(nazwaws);
          break;
    	}
    }
return 0;
}
