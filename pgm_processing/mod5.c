#include <stdio.h>
#include "mod5.h"
#include <string.h>
#include <stdlib.h>

#define MAX 512            /* Maksymalny rozmiar wczytywanego obrazu */
#define DL_LINII 1024      /* Dlugosc buforow pomocniczych */


/****************************zapisywanie******************************/

void zapisz (FILE *plik_wy, obrazek *ob)
{
  int i, j;
  
  int (*obraz)[ob->wym_x];
	obraz=(int(*)[ob->wym_x]) ob->obraz;
	int (*RED)[ob->wym_x];
	RED=(int(*)[ob->wym_x]) ob->RED;
	int (*GREEN)[ob->wym_x];
	GREEN=(int(*)[ob->wym_x]) ob->GREEN;
	int (*BLUE)[ob->wym_x];
	BLUE=(int(*)[ob->wym_x]) ob->BLUE;
  
	if(ob->typ==2)
	{
		void tabs (obrazek *ob);
	  fprintf(plik_wy,"P2\n");    /*wpisanie numeru magicznego, wymiarow i szarosci zamiast P2 P3*/
	  fprintf(plik_wy,"%d %d %d\n",ob->wym_x,ob->wym_y,ob->odcieni);
   
		for (i=0;i<ob->wym_y;i++)       /*wpisanie tablicy fprintf(plik_wy, "%d %d %d ", RED[i][j],GREEN[i][j],BLUE[i][j])*/
    {
			for (j=0;j<ob->wym_x;j++)
				fprintf(plik_wy,"%d ",obraz[i][j]);
			fprintf(plik_wy,"\n");
    }			
	}
	else
	{
  
   	fprintf(plik_wy,"P3\n");    /*wpisanie numeru magicznego, wymiarow i szarosci zamiast P2 P3*/
	 	fprintf(plik_wy,"%d %d %d\n",ob->wym_x,ob->wym_y,ob->odcieni);
   
	  for (i=0;i<ob->wym_y;i++)       /*wpisanie tablicy*/
	  {
	    for (j=0;j<ob->wym_x;j++) 
		   	fprintf(plik_wy, "%d %d %d ", RED[i][j],GREEN[i][j],BLUE[i][j]);
		}
	}
}

/*******************************wyszarzanie*******************************/

void konwersja (obrazek *ob)
{
	if (ob->typ==2)
		fprintf(stderr,"niewlasciwy typ");
	else
	{
	int (*obraz)[ob->wym_x];
  obraz=(int(*)[ob->wym_x]) ob->obraz;
	int (*RED)[ob->wym_x];
	RED=(int(*)[ob->wym_x]) ob->RED;
	int (*GREEN)[ob->wym_x];
	GREEN=(int(*)[ob->wym_x]) ob->GREEN;
	int (*BLUE)[ob->wym_x];
	BLUE=(int(*)[ob->wym_x]) ob->BLUE;  
  int i,j;
  ob->odcieni=ob->odcieni*3;
  ob->typ=2;
	for (i=0; i<ob->wym_y;++i)
  {
    for (j=0; j<ob->wym_x;++j)
    {
    	obraz[i][j]=((GREEN[i][j])*(RED[i][j])*(BLUE[i][j]))/3;
    }
	}
	}
}	



/*****************************zmiana poziomow*****************************/

void zmiana (int cze, int bi, obrazek *ob)
{
  int (*obraz)[ob->wym_x];
  obraz=(int(*)[ob->wym_x]) ob->obraz;
	int (*RED)[ob->wym_x];
	RED=(int(*)[ob->wym_x]) ob->RED;
	int (*GREEN)[ob->wym_x];
	GREEN=(int(*)[ob->wym_x]) ob->GREEN;
	int (*BLUE)[ob->wym_x];
	BLUE=(int(*)[ob->wym_x]) ob->BLUE;  
  int i,j;                 /*funkcja nadaje nowe wartosci czerni i bieli*/
    
  for (i=0; i<ob->wym_y;++i)
  {
    for (j=0; j<ob->wym_x;++j)
    {
		  if (obraz[i][j]<=cze*ob->odcieni/100)
		    obraz[i][j]=0;     /*wszystko mniejsze od cze jest = 0*/
      if (obraz[i][j]>cze*ob->odcieni/100)
      {                      /* wartosci pomiedzy zostaja dostosowane */
        if (obraz[i][j]<bi*ob->odcieni/100)
				  obraz[i][j]=(((obraz[i][j]-cze*ob->odcieni/100)*ob->odcieni)/((bi*ob->odcieni/100)-(cze*ob->odcieni/100)));
      }
      if (obraz[i][j])       /*wszystko wieksze od bi jest = szar*/
	      obraz[i][j]=ob->odcieni;
    }
  }
  /**************/
  if (ob->typ==2)
	{
  	for (i=0; i<ob->wym_y;++i)
  	{
    	for (j=0; j<ob->wym_x;++j)
    	{
			  if (obraz[i][j]<=cze*ob->odcieni/100)
			    obraz[i][j]=0;     /*wszystko mniejsze od cze jest = 0*/
    	  if (obraz[i][j]>cze*ob->odcieni/100)
    	  {                      /* wartosci pomiedzy zostaja dostosowane */
    	    if (obraz[i][j]<bi*ob->odcieni/100)
					  obraz[i][j]=(((obraz[i][j]-cze*ob->odcieni/100)*ob->odcieni)/((bi*ob->odcieni/100)-(cze*ob->odcieni/100)));
    	  }
    	  if (obraz[i][j])       /*wszystko wieksze od bi jest = szar*/
	  	    obraz[i][j]=ob->odcieni;
    	}
		}
	}
	else
	{
		if (ob->r==1)
		{
			for (i=0; i<ob->wym_y;++i)
  		{
    		for (j=0; j<ob->wym_x;++j)
    		{
				  if (RED[i][j]<=cze*ob->odcieni/100)
				    RED[i][j]=0;     /*wszystko mniejsze od cze jest = 0*/
    		  if (RED[i][j]>cze*ob->odcieni/100)
    		  {                      /* wartosci pomiedzy zostaja dostosowane */
    		    if (RED[i][j]<bi*ob->odcieni/100)
						  RED[i][j]=(((RED[i][j]-cze*ob->odcieni/100)*ob->odcieni)/((bi*ob->odcieni/100)-(cze*ob->odcieni/100)));
    		  }
    		  if (RED[i][j])       /*wszystko wieksze od bi jest = szar*/
	  		    RED[i][j]=ob->odcieni;
    		}
  		}
  	}	
  	if (ob->g==1)
  	{
			for (i=0; i<ob->wym_y;++i)
		  {
    		for (j=0; j<ob->wym_x;++j)
    		{
				  if (GREEN[i][j]<=cze*ob->odcieni/100)
				    GREEN[i][j]=0;     /*wszystko mniejsze od cze jest = 0*/
    		  if (GREEN[i][j]>cze*ob->odcieni/100)
    		  {                      /* wartosci pomiedzy zostaja dostosowane */
    		    if (GREEN[i][j]<bi*ob->odcieni/100)
						  GREEN[i][j]=(((GREEN[i][j]-cze*ob->odcieni/100)*ob->odcieni)/((bi*ob->odcieni/100)-(cze*ob->odcieni/100)));
    		  }
    		  if (GREEN[i][j])       /*wszystko wieksze od bi jest = szar*/
	  		    GREEN[i][j]=ob->odcieni;
	  		}
    	}
		}
  	if (ob->b==1)
  	{
			for (i=0; i<ob->wym_y;++i)
		  {
		  	for (j=0; j<ob->wym_x;++j)
   			{
	  			if (BLUE[i][j]<=cze*ob->odcieni/100)
	    			BLUE[i][j]=0;     /*wszystko mniejsze od cze jest = 0*/
     			if (BLUE[i][j]>cze*ob->odcieni/100)
   				{                      /* wartosci pomiedzy zostaja dostosowane */
       			if (BLUE[i][j]<bi*ob->odcieni/100)
			  			BLUE[i][j]=(((BLUE[i][j]-cze*ob->odcieni/100)*ob->odcieni)/((bi*ob->odcieni/100)-(cze*ob->odcieni/100)));
     			}
     			if (BLUE[i][j])       /*wszystko wieksze od bi jest = szar*/
      			BLUE[i][j]=ob->odcieni;
   			}
 			}
		}		
	}
}
/*****************************rozciaganie histogramu*****************************/

void rozciaganie (obrazek *ob)
{
  int (*obraz)[ob->wym_x];
  obraz=(int(*)[ob->wym_x]) ob->obraz;
	int (*RED)[ob->wym_x];
	RED=(int(*)[ob->wym_x]) ob->RED;
	int (*GREEN)[ob->wym_x];
	GREEN=(int(*)[ob->wym_x]) ob->GREEN;
	int (*BLUE)[ob->wym_x];
	BLUE=(int(*)[ob->wym_x]) ob->BLUE;
  int i,j,min, max;

	if (ob->typ==2)
	{
		for (i=0; i<ob->wym_y;++i)
  	{
  	  for (j=0; j<ob->wym_x;++j)
  	  {
  		  if (obraz[i][j]>0)
  	      min=obraz[i][j];
  	    if (obraz[i][j]<ob->odcieni)
  	      max=obraz[i][j];
  	  }
  	}
  	for (i=0; i<ob->wym_y;++i)
 		{
   		for (j=0; j<ob->wym_x;++j)
				obraz[i][j]=(obraz[i][j]-max)*(ob->odcieni/(min-max));
  	}
  }
	else
	{
		if (ob->r==1)
		{
			for (i=0; i<ob->wym_y;++i)
  		{
  	  	for (j=0; j<ob->wym_x;++j)
  	  	{
  		  	if (RED[i][j]>0)
  	    	  min=RED[i][j];
  	    	if (RED[i][j]<ob->odcieni)
  	    	  max=RED[i][j];
  	  	}
  		}
  		for (i=0; i<ob->wym_y;++i)
 			{
   			for (j=0; j<ob->wym_x;++j)
					RED[i][j]=(RED[i][j]-max)*(ob->odcieni/(min-max));
  		}
  	}	
  	if (ob->g==1)
  	{
			for (i=0; i<ob->wym_y;++i)
  		{
  	  	for (j=0; j<ob->wym_x;++j)
  	  	{
  			  if (GREEN[i][j]>0)
  	  	    min=GREEN[i][j];
  	  	  if (GREEN[i][j]<ob->odcieni)
  	  	    max=GREEN[i][j];
  	  	}
  		}
  		for (i=0; i<ob->wym_y;++i)
 			{
   			for (j=0; j<ob->wym_x;++j)
					GREEN[i][j]=(GREEN[i][j]-max)*(ob->odcieni/(min-max));
  		}
  	}
  	if (ob->b==1)
  	{
			for (i=0; i<ob->wym_y;++i)
  		{
  		  for (j=0; j<ob->wym_x;++j)
  		  {
  			  if (BLUE[i][j]>0)
  		      min=BLUE[i][j];
  		    if (BLUE[i][j]<ob->odcieni)
  		      max=BLUE[i][j];
  		  }
  		}
  		for (i=0; i<ob->wym_y;++i)
 			{
   			for (j=0; j<ob->wym_x;++j)
					BLUE[i][j]=(BLUE[i][j]-max)*(ob->odcieni/(min-max));
  		}
  	}
	}
}

/****************************konturowanie******************************/

void konturowanie (obrazek *ob)
{
  int (*obraz)[ob->wym_x];
  obraz=(int(*)[ob->wym_x]) ob->obraz;
	int (*RED)[ob->wym_x];
	RED=(int(*)[ob->wym_x]) ob->RED;
	int (*GREEN)[ob->wym_x];
	GREEN=(int(*)[ob->wym_x]) ob->GREEN;
	int (*BLUE)[ob->wym_x];
	BLUE=(int(*)[ob->wym_x]) ob->BLUE;
  int i,j;                  /*ta funkcja przyciemnia piksel, jesli mocno sie rozni od reszty*/

	if (ob->typ==2)
	{
  	for (i=0; i<ob->wym_y;++i)
  	{
	  	for (j=0; j<ob->wym_x;++j)
      	obraz[i][j]=(abs(obraz[i+1][j]-obraz[i][j])+abs(obraz[i][j+1]-obraz[i][j]))/2;
  	}
	}
	else
	{
		if (ob->r==1)
		{
			for (i=0; i<ob->wym_y;++i)
  		{
		  	for (j=0; j<ob->wym_x;++j)
  	    RED[i][j]=(abs(RED[i+1][j]-RED[i][j])+abs(RED[i][j+1]-RED[i][j]))/2;
  		}
  	}	
  	if (ob->g==1)
  	{
			for (i=0; i<ob->wym_y;++i)
  		{
		  	for (j=0; j<ob->wym_x;++j)
  	    GREEN[i][j]=(abs(GREEN[i+1][j]-GREEN[i][j])+abs(GREEN[i][j+1]-GREEN[i][j]))/2;
  		}
  	}
  	if (ob->b==1)
  	{
			for (i=0; i<ob->wym_y;++i)
  		{
		  	for (j=0; j<ob->wym_x;++j)
  	    BLUE[i][j]=(abs(BLUE[i+1][j]-BLUE[i][j])+abs(BLUE[i][j+1]-BLUE[i][j]))/2;
  		}
  	}
	}
}

/****************************progowanie******************************/

void progowanie (int prog, obrazek *ob)
{

  int (*obraz)[ob->wym_x];
  obraz=(int(*)[ob->wym_x]) ob->obraz;
	int (*RED)[ob->wym_x];
	RED=(int(*)[ob->wym_x]) ob->RED;
	int (*GREEN)[ob->wym_x];
	GREEN=(int(*)[ob->wym_x]) ob->GREEN;
	int (*BLUE)[ob->wym_x];
	BLUE=(int(*)[ob->wym_x]) ob->BLUE;
  int i,j;                  /*wyszukuje prog i wszystko co jest nizsze bedzie mialo wartosc 0*/

  if (ob->typ==2)
	{
  	for (i=0; i<ob->wym_y;++i)
  	{
	  	for (j=0; j<ob->wym_x;++j)
      if (obraz[i][j]<=(ob->odcieni*prog/100))
	    	obraz[i][j]=0;
      else
        obraz[i][j]=ob->odcieni;
  	}
	}
	else
	{
		if (ob->r==1)
		{
			for (i=0; i<ob->wym_y;++i)
  		{
		  	for (j=0; j<ob->wym_x;++j)
  	    if (RED[i][j]<=(ob->odcieni*prog/100))
	        RED[i][j]=0;
        else
          RED[i][j]=ob->odcieni;
  		}
  	}	
  	if (ob->g==1)
  	{
			for (i=0; i<ob->wym_y;++i)
  		{
		  	for (j=0; j<ob->wym_x;++j)
  	    if (GREEN[i][j]<=(ob->odcieni*prog/100))
	        GREEN[i][j]=0;
        else
          GREEN[i][j]=ob->odcieni;
  		}
  	}
  	if (ob->b==1)
  	{
			for (i=0; i<ob->wym_y;++i)
  		{
		  	for (j=0; j<ob->wym_x;++j)
  	    if (BLUE[i][j]<=(ob->odcieni*prog/100))
	        BLUE[i][j]=0;
        else
          BLUE[i][j]=ob->odcieni;
  		}
  	}
	}
}

/***************************negatyw*******************************/

void negatyw (obrazek *ob)
{
  int (*obraz)[ob->wym_x];
  obraz=(int(*)[ob->wym_x]) ob->obraz;
	int (*RED)[ob->wym_x];
	RED=(int(*)[ob->wym_x]) ob->RED;
	int (*GREEN)[ob->wym_x];
	GREEN=(int(*)[ob->wym_x]) ob->GREEN;
	int (*BLUE)[ob->wym_x];
	BLUE=(int(*)[ob->wym_x]) ob->BLUE;
	int i,j;               /*od maksymalnej wartsci szarosci odejmuje kazdy element tablicy*/
	
	if (ob->typ==2)
	{
  	for (i=0; i<ob->wym_y;++i)
  	{
	  	for (j=0; j<ob->wym_x;++j)
      obraz[i][j]=ob->odcieni-obraz[i][j];
  	}
	}
	else
	{
		if (ob->r==1)
		{
			for (i=0; i<ob->wym_y;++i)
  		{
		  	for (j=0; j<ob->wym_x;++j)
  	    RED[i][j]=ob->odcieni-RED[i][j];
  		}
  	}	
  	if (ob->g==1)
  	{
			for (i=0; i<ob->wym_y;++i)
  		{
		  	for (j=0; j<ob->wym_x;++j)
  	    GREEN[i][j]=ob->odcieni-GREEN[i][j];
  		}
  	}
  	if (ob->b==1)
  	{
			for (i=0; i<ob->wym_y;++i)
  		{
		  	for (j=0; j<ob->wym_x;++j)
  	    BLUE[i][j]=ob->odcieni-BLUE[i][j];
  		}
  	}
	}
}

/**************************wczytywanie***************************/

int czytaj(FILE *plik_we, obrazek *ob) 
{
  char buf[DL_LINII];      /* bufor pomocniczy do czytania naglowka i komentarzy */
  int znak;                /* zmienna pomocnicza do czytania komentarzy */
  int koniec=0;            /* czy napotkano koniec danych w pliku */
  int i, j, ty;
	ob->typ=0;
	
  /*Sprawdzenie czy podano prawidÂłowy uchwyt pliku */
  if (plik_we==NULL) 
  {
    fprintf(stderr,"Blad: Nie podano uchwytu do pliku\n");
    return(0);
  }

  /* Sprawdzenie "numeru magicznego" - powinien byĂŚ P2 */
  if (fgets(buf,DL_LINII,plik_we)==NULL)   /* Wczytanie pierwszej linii pliku do bufora */
    koniec=1;  
                            /* Nie udalo sie? Koniec danych! */
	if (buf[0]=='P' || koniec)
	{
		if (buf[1]=='2')
			ob->typ=2;
		if (buf[1]=='3')
			ob->typ=3;
	}
	else
	{
		fprintf(stderr,"Blad: To nie jest plik PGM\n");
    return(0);
	}
	
  /* Pominiecie komentarzy */
  do 
  {
    if ((znak=fgetc(plik_we))=='#') 
    {         /* Czy linia rozpoczyna sie od znaku '#'? */
      if (fgets(buf,DL_LINII,plik_we)==NULL)  /* Przeczytaj ja do bufora                */
				koniec=1;                   /* Zapamietaj ewentualny koniec danych */
    }  
    else 
    {
      ungetc(znak,plik_we);                   /* Gdy przeczytany znak z poczatku linii */
    }                                         /* nie jest '#' zwroc go                 */
  } 
  while (znak=='#' && !koniec);   /* Powtarzaj dopoki sa linie komentarza */
                                    /* i nie nastapil koniec danych         */

  /* Pobranie wymiarow obrazu i liczby odcieni szarosci */


  fscanf(plik_we,"%d", &(ob->wym_x));
  fscanf(plik_we,"%d", &(ob->wym_y));
  fscanf(plik_we,"%d", &(ob->odcieni));
  

	if (ob->typ==3)
	{
		ob->RED = malloc(ob->wym_x*ob->wym_y*sizeof(int));
		int (*RED)[ob->wym_x];  
		RED=(int(*)[ob->wym_x]) ob->RED; 

		ob->GREEN = malloc(ob->wym_x*ob->wym_y*sizeof(int));
		int (*GREEN)[ob->wym_x];
 		GREEN=(int(*)[ob->wym_x]) ob->GREEN; 

		ob->BLUE = malloc(ob->wym_x*ob->wym_y*sizeof(int));
		int (*BLUE)[ob->wym_x];
 		BLUE=(int(*)[ob->wym_x]) ob->BLUE; 

		for(i = 0; i < ob->wym_y; i++)
		{    
			for(j = 0; j < ob->wym_x; j++)
			{
				if (ob->typ==3)
				fscanf(plik_we, "%d %d %d", &(RED[i][j]),&(GREEN[i][j]),&(BLUE[i][j]));
			}
		}
	}
	else
	{
		ob->obraz = malloc(ob->wym_x*ob->wym_y*sizeof(int));
  	int (*obraz)[ob->wym_x];
  	obraz=(int(*)[ob->wym_x]) ob->obraz;
	
  	for(i = 0; i < ob->wym_y; i++)
		{    
			for(j = 0; j < ob->wym_x; j++)
			{
      	fscanf(plik_we, "%d", &(obraz[i][j]));
			}
		}
	}
	
	if (ob->typ==3)
		printf("Praca w trybie PPM\n");
	else
		printf("Praca w trybie PGM\n");

  return 1;   /* Czytanie zakonczone sukcesem    */
}                       /* Zwroc liczbe wczytanych pikseli */

/******************************Wyswietlenie************************/

void wyswietl(char *n_pliku) 
{printf("pomoc wy");
  char polecenie[DL_LINII];      /* bufor pomocniczy do zestawienia polecenia */
  strcpy(polecenie,"display ");  /* konstrukcja polecenia postaci */
  strcat(polecenie,n_pliku);     /* display "nazwa_pliku" &       */
  strcat(polecenie," &");
  printf("%s\n",polecenie);      /* wydruk kontrolny polecenia */
  system(polecenie);             /* wykonanie polecenia        */
}

