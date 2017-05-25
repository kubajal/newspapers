#include "bazadanych.h"

void wiadomoscPowitalna()
{
	printf("\nJakub Jalowiec, 2015, WEiTI PW\n");
	printf("Program do ewidencji gazet.\n\n");
}

void dostepneAkcje()
{
	printf("\nPodaj numer interakcji:\n");
	printf("1 - dodanie nowego dzialu,\n");
	printf("2 - modyfikacja wybranego dzialu,\n");
	printf("3 - usuniecie wybranego dzialu,\n");
	printf("4 - dodanie rekordu,\n");
	printf("5 - modyfikacja wybranego rekordu,\n");
	printf("6 - wyswietlenie calej listy,\n");
	printf("7 - wyswietlenie listy dzialow,\n");
	printf("8 - wyswietlenie wybranego dzialu,\n");
	printf("9 - przeniesienie rekordow z wybranego dzialu do wybranego dzialu,\n");
	printf("a - wyswietlenie wg wybranego parametru,\n");
	printf("b - zapisanie aktualnej bazy gazet do pliku lub odczyt bazy z pliku,\n");
	printf("c - wyjscie.\n\n");
}

void wyswietlWgNazwy(char *nazwa, struct Dzial *poczatek)
{
	struct Dzial *y = poczatek, *pomy = NULL;
	struct Gazeta *x = NULL;

	while(y != NULL){
		pomy = malloc(sizeof(struct Dzial));
		zerujDzial(pomy);
		strcpy(pomy->nazwa, y->nazwa);
		x = y->pierwsza;
		while(x != NULL){
			if(!strcmp(x->nazwa, nazwa))
				utworzGazete(pomy, pomy->nazwa, x->nazwa, x->numer, x->czestosc);
			x = x->nastepna;
		}
		formatowanieWyswietlania(pomy);
		usun(pomy);
		y = y->nastepny;
	}
}

void wyswietlWgNumeru(char *numer, struct Dzial *poczatek)
{
	struct Dzial *y = poczatek;
	struct Gazeta *x = NULL;

	while(y != NULL){
		x = y->pierwsza;
		while(x != NULL){
			if(!strcmp(numer, x->numer)){
				printf("%-20s     %-20s     %-5s     %-20s", y->nazwa, x->nazwa, x->numer, x->czestosc);
				return;
			}
			x = x->nastepna;
		}
		y = y->nastepny;
	}
	printf("Nie znaleziono rekordu o podanym numerze.\n");
	return;
}

void wyswietlWgCzestosci(char *czestosc, struct Dzial *poczatek)
{
	struct Dzial *y = poczatek, *pomy;
	struct Gazeta *x = NULL;

	while(y != NULL){
		pomy = malloc(sizeof(struct Dzial));
		zerujDzial(pomy);
		strcpy(pomy->nazwa, y->nazwa);
		x = y->pierwsza;
		while(x != NULL){
			if(!strcmp(x->czestosc, czestosc))
				utworzGazete(pomy, pomy->nazwa, x->nazwa, x->numer, x->czestosc);
			x = x->nastepna;
		}
		formatowanieWyswietlania(pomy);
		usun(pomy);
		y = y->nastepny;
	}
}

void formatowanieWyswietlania(struct Dzial *y)
{
	struct Gazeta *x = NULL;

	x = y->pierwsza;
	if(x == NULL){
		printf("%s\n\n", y->nazwa);
	}
	else{
		printf("%-20s     %-20s     %-5s    %-20s\n", y->nazwa, x->nazwa, x->numer, x->czestosc);
		x = x->nastepna;
		while(x != NULL){
			printf("                         %-20s     %-5s    %-20s\n", x->nazwa, x->numer, x->czestosc);
			x = x->nastepna;
		}
		printf("\n");
	}
	y = y->nastepny;
}
