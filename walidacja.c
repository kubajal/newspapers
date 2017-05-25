#include "bazadanych.h"

void zerujBufor()
{
	int i = 0;

	for(i = 0; i < MAXBUFOR; i++)
		bufor[i] = 0;
}

void zapelnijBufor(FILE *plik)
{
	zerujBufor();
	fgets(bufor, 1024, plik);
	bufor[strlen(bufor) - 1] = 0;		// usuniecie znaku '\n' z konca bufora
	if(bufor[strlen(bufor) - 1] == 13)	// usuniecie z bufora znaku carriage return gdy wczytujemy tekst z pliku
		bufor[strlen(bufor) - 1] = 0;
}

int walidacjaNazwy(FILE *plik)
{
	int i = 0;

	zapelnijBufor(plik);

	if(bufor[0] <= 'z' && bufor[0] >= 'a')
		bufor[0] = bufor[0] - 'a' + 'A';
	if(!(bufor[0] <= 'Z' && bufor[0] >= 'A'))
		return 0;

	for(i = 1; i < MAXNAZWA; i++)
		if(!(bufor[i] >= 'a' && bufor[i] <= 'z' || bufor[i] >= 'A' && bufor[i] <= 'Z' || bufor[i] == ' ' || bufor[i] == 0))
			return 0;

	bufor[MAXNAZWA - 1] = 0;

	return 1;
}

int walidacjaNumeru(FILE *plik)
{
	int i = 0;

	zapelnijBufor(plik);

	if(strlen(bufor) != 5)
		return 0;

	for(i = 0; i < MAXNUMER; i++)
		if(!(bufor[i] >= '0' && bufor[i] <= '9' || bufor[i] == 0))
			return 0;

	if(bufor[MAXNUMER - 1] != 0 || !bufor[0])
		return 0;

	bufor[MAXNUMER - 1] = 0;

	return 1;
}

int walidacjaCzestosci(FILE *plik)
{
	int i = 0;

	zapelnijBufor(plik);

	for(i = 0; i < MAXCZESTOSC; i++)
		if(!((bufor[i] <= 'z' && bufor[i] >= 'a') || bufor[i] == 0))
			return 0;

	if(bufor[MAXCZESTOSC - 1] != 0 || bufor[0] == 0)
		return 0;

	bufor[MAXCZESTOSC - 1] = 0;

	return 1;
}

int walidacjaDzialu(FILE *plik)
{
	int i = 0;

	zapelnijBufor(plik);

	if(bufor[0] <= 'z' && bufor[0] >= 'a')
		bufor[0] = bufor[0] - 'a' + 'A';

	if(bufor[0] == 0 || bufor[MAXDZIAL - 1] != 0 || !(bufor[0] <= 'Z' && bufor[0] >= 'A'))
		return 0;

	for(i = 1; i < MAXDZIAL; i++)
		if(!((bufor[i] <= 'z' && bufor[i] >= 'a') || bufor[i] == 0))
			return 0;

	bufor[MAXDZIAL - 1] = 0;

	return 1;
}

int walidacjaInterakcji(FILE *plik)
{
	zapelnijBufor(plik);

	if(!(bufor[0] == '1' || bufor[0] == '2' || bufor[0] == '3' || bufor[0] == '4' || bufor[0] == '5' || bufor[0] == '6' || bufor[0] == '7' || bufor[0] == '8' || bufor[0] == '9' || bufor[0] == 'a' || bufor[0] == 'b' || bufor[0] == 'c') || bufor[1] != 0)
		return 0;

	return 1;
}

int walidacjaModyfikacji(FILE *plik)
{
	zapelnijBufor(plik);

	if(!(bufor[0] == '1' || bufor[0] == '2' || bufor[0] == '3') || bufor[1] != 0)
		return 0;

	return 1;
}

int walidacjaWyjscia(FILE *plik)
{
	zapelnijBufor(plik);

	if(bufor[1] != 0 || !(bufor[0] == 'T' || bufor[0] == 'N'))
		return 0;

	return 1;
}

int walidacjaDzialuZPliku(FILE *plik, char *dzial)
{
	if(!walidacjaDzialu(plik));
		return 0;
	strcpy(dzial, bufor);
	return 1;
}

int walidacjaGazetyZPliku(FILE *plik, char *dzial, char *nazwa, char *numer, char *czestosc)
{
	if(!walidacjaDzialu(plik))
		return 0;
	strcpy(dzial, bufor);

	if(!walidacjaNazwy(plik))
		return 0;
	strcpy(nazwa, bufor);

	if(!walidacjaNumeru(plik))
		return 0;
	strcpy(numer, bufor);

	if(!walidacjaCzestosci(plik))
		return 0;
	strcpy(czestosc, bufor);

	return 1;
}

int walidacjaPliku(char *oz, char *nazwaPliku, char *haslo)
{
	int i = 0;
	char tab[1024];

	zapelnijBufor(stdin);

	if(bufor[0] == 'K' && bufor[1] == 0)
		return 1;

	if(sscanf(bufor, "%s %s %s %s", oz, nazwaPliku, haslo, tab) > 3)
		return 0;

    oz[20] = 0;
    nazwaPliku[20] = 0;
    haslo[20] = 0;

	if(!(!strcmp("odczyt", oz) || !strcmp("zapis", oz))){
		return 0;
	}

	if(strlen(nazwaPliku) < 5 ||!(!strcmp(".txt", nazwaPliku + strlen(nazwaPliku) - 4) || !strcmp(".ula", nazwaPliku + strlen(nazwaPliku) - 4)))
		return 0;

	if(strlen(haslo) > 20)
		return 0;

	for(i = 0; i < strlen(nazwaPliku) - 4; i++)
		if(!(nazwaPliku[i] <= 'z' && nazwaPliku[i] >= 'a' || nazwaPliku[i] <= 'Z' && nazwaPliku[i] >= 'A'))
			return 0;

	return 1;
}
