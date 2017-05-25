#include "bazadanych.h"

void wyswietlWybranyDzial()
{
	struct Dzial *y = NULL;

	sortuj();
	printf("Podaj nazwe dzialu, ktory chcesz wyswietlic.\n");

	while(!walidacjaDzialu(stdin))
		printf("Podaj nazwe dzialu do wyswietlenia jeszcze raz.\n");

	y = znajdzDzial(bufor);

	if(y == NULL){
		printf("Nie znaleziono dzialu o podanej nazwie.\n");
		return;
	}

	if(y->pierwsza == NULL){
		printf("Ten dzial jest pusty.\n");
		return;
	}

	formatowanieWyswietlania(y);
}

void wyswietlListe()
{
	struct Dzial *y = poczatek;

	if(y == NULL){
		printf("Lista gazet jest pusta. Nie ma nic do wyswietlenia.\n\n");
		return;
	}

	sortuj();

    printf("Dzial                    Nazwa gazety             numer    czestotliwosc wydania\n\n");

	while(y != NULL){
		formatowanieWyswietlania(y);
		y = y->nastepny;
	}

	printf("\n\n");
}

void wyswietlListeDzialow()
{
	struct Dzial *pom = poczatek;

	if(pom == NULL){
		printf("Lista jest pusta. Nie ma nic do wyswietlenia.\n");
		return;
	}

	printf("Lista dzialow w kolejnosci alfabetycznej:\n");

	sortuj();

	while(pom != NULL){
		printf("%s\n", pom->nazwa);
		pom = pom->nastepny;
	}
}

void modyfikujDzial()
{
	struct Dzial *pom = NULL;
	if(poczatek == NULL){
		printf("Lista jest pusta. Nie ma co zmienic.\n");
		return;
	}
	printf("Podaj nazwe dzialu, ktorego nazwe chcesz zmienic:\n");
	wyswietlListeDzialow();
	while(!walidacjaDzialu(stdin))
		printf("Podaj poprawna nazwe dzialu.\n");

	pom = znajdzDzial(bufor);
	if(pom == NULL){
		printf("Nie znaleziono podanego dzialu.\n");
		return;
	}
	printf("Podaj nowa nazwe dla dzialu %s.\n", bufor);
	while(!walidacjaDzialu(stdin))
		printf("Podaj poprawna nazwe dzialu.\n");

	if(poczatek != NULL){
		struct Dzial *it = poczatek;
		while(it != NULL)
		{
			if(!strcmp(it->nazwa, bufor)){
				printf("Dzial o podanej nazwie juz istnieje.\n");
				return;
			}
			it = it->nastepny;
		}
	}

	strcpy(pom->nazwa, bufor);
}

void usunWybranyDzial()
{
	struct Dzial *c = NULL;

	if(poczatek == NULL){
		printf("Lista jest pusta. Nie ma nic do usuniecia.\n");
		return;
	}

	printf("Podaj nazwe dzialu, ktory chcesz usunac.\n");
	wyswietlListeDzialow();
	while(!walidacjaDzialu(stdin))
		printf("Podaj poprawna nazwe dzialu.\n");

	c = znajdzDzial(bufor);

	if(c == NULL){
		printf("Podany dzial nie istnieje.\n");
		return;
	}

	if(c == poczatek){
		poczatek = poczatek->nastepny;
		usun(c);
		return;
	}
	usunDzial(c, poczatek);
}

void modyfikacjaRekordu()
{
	struct Gazeta *pom = NULL;

	if(poczatek == NULL){
		printf("Lista jest pusta. Nie ma nic do wyswietlenia.\n");
		return;
	}
	sortuj();
    wyswietlListe();
    printf("Podaj numer ID rekordu, ktory chcesz poprawic.\n");
    while(!walidacjaNumeru(stdin))
    	printf("Podaj poprawny numer.\n");

	pom = znajdzGazete(bufor);
	if(pom == NULL){
		printf("Nie ma rekordu o podanym numerze ID.\n");
		return;
	}

	printf("Podaj ktore pole chcesz zmodyfikowac:\n");
	printf("1 - nazwe,\n2 - numer,\n3 - czestosc wydawania.\n");
	while(!walidacjaModyfikacji(stdin))
		printf("Podaj 1, 2 lub 3.\n");
	switch(bufor[0])
	{
		case '1':
			printf("Podaj nowa nazwe gazety.\n");
			while(!walidacjaNazwy(stdin))
				printf("Podaj nazwe jeszcze raz.");
			strcpy(pom->nazwa, bufor);
			return;
		case '2':
			printf("Podaj nowy numer gazety.\n");
			while(!walidacjaNumeru(stdin) || ID[atoi(bufor)])
				printf("Podaj nowy numer jeszcze raz.\n");
			ID[atoi(pom->numer)] = 0;
			ID[atoi(bufor)] = 1;
			strcpy(pom->numer, bufor);
			break;
		case '3':
			printf("Podaj nowa czestosc wydawania.\n");
			while(!walidacjaCzestosci(stdin))
				printf("Podaj nowa czestosc wydawania gazety jeszcze raz.\n");
			strcpy(pom->czestosc, bufor);
			break;
	}
}

void przeniesRekordy()
{
	char skad[MAXDZIAL], dokad[MAXDZIAL];
	struct Dzial *pomz = NULL, *pomdo = NULL;
	struct Gazeta *y = NULL;

	wyswietlListe();

	printf("Podaj nazwe dzialu z ktorego chcesz przenosic rekordy.\n");
	while(!walidacjaDzialu(stdin))
		printf("Podaj nazwe dzialu jeszcze raz.\n");
	pomz = znajdzDzial(bufor);

	if(pomz == NULL){
		printf("Taki dzial nie istnieje.\n");
		return;
	}

	strcpy(skad, bufor);

	printf("Podaj nazwe dzialu do ktorego chcesz prznosic rekordy.\n");
	while(!walidacjaDzialu(stdin))
		printf("Podaj nazwe dzialu jeszcze raz.\n");
	pomdo = znajdzDzial(bufor);

	if(pomdo == NULL){
		printf("Taki dzial nie istnieje.\n");
		return;
	}

	strcpy(dokad, bufor);

    printf("Dzial                    Nazwa gazety             numer     czestotliwosc wydania\n\n");
	formatowanieWyswietlania(pomz);

	printf("Podaj numery ID rekordow, ktore chcesz przeniesc do dzialu %s. Aby zakonczyc wpisywanie numerow wpisz 'K'.\n", dokad);
	while(1)
	{
		while(!walidacjaNumeru(stdin) && !(bufor[0] == 'K' && bufor[1] == 0))
			printf("Podaj numer jeszcze raz.\n");
		if(bufor[0] != 'K')
		{
			struct Gazeta *it = pomz->pierwsza;
			while(it != NULL){
				if(!strcmp(it->numer, bufor))
					break;
				it = it->nastepna;
			}
			if(it == NULL){
				printf("Nie znaleziono gazety o podanym numerze ID w dziale %s. Podaj kolejny numer lub wpisz 'K'.\n", skad);
				continue;
			}

			y = pomz->pierwsza;

			if(it == pomz->pierwsza)
				pomz->pierwsza = it->nastepna;
			else{
				while(y->nastepna != it && y != NULL)
					y = y->nastepna;
				y->nastepna = it->nastepna;
			}
			utworzGazete(poczatek, dokad, it->nazwa, it->numer, it->czestosc);
			zerujGazete(it);
			free(it);
		}
		else
			break;
	}
	sortuj();
}

void dodajNowyDzial()
{
	printf("Podaj nazwe nowego dzialu.\n");

	while(!walidacjaDzialu(stdin))
		printf("Podaj nazwe nowego dzialu jeszcze raz.\n");

	if(znajdzDzial(bufor) != NULL){
		printf("Podany dzial juz istnieje.\n");
		return;
	}

	utworzDzial(bufor);

}

void dodajNowaGazete()
{
	char dzial[MAXDZIAL];
	char nazwa[MAXNAZWA];
	char numer[MAXNUMER];
	char czestosc[MAXCZESTOSC];

	if(poczatek == NULL){
		printf("Nie istnieje zaden dzial. Prosze najpierw utworzyc przynajmniej jeden dzial.\n");
		return;
	}

	printf("Podaj nazwe dzialu.\n");
	while(!walidacjaDzialu(stdin))
		printf("Podaj poprawna nazwe dzialu.\n");
	if(znajdzDzial(bufor) == NULL){
		printf("Podany dzial nie istnieje.\n");
		return;
	}
	strcpy(dzial, bufor);

	printf("Podaj nazwe gazety.\n");
	while(!walidacjaNazwy(stdin))
		printf("Podaj poprawna nazwe gazety.\n");
	strcpy(nazwa, bufor);

	printf("Podaj numer gazety.\n");
	while(!walidacjaNumeru(stdin) || ID[atoi(bufor)]){
		printf("Podaj numer jeszcze raz.\n");
	}
	strcpy(numer, bufor);

	printf("Podaj czestosc wydawania gazety.\n");
	while(!walidacjaCzestosci(stdin))
		printf("Podaj czestosc wydawania gazety jeszcze raz %s.\n", nazwa);
	strcpy(czestosc, bufor);

	utworzGazete(poczatek, dzial, nazwa, numer, czestosc);
	ID[atoi(numer)] = 1;
}

void wyswietlWgParametru()
{
	if(poczatek == NULL){
		printf("Lista jest pusta. Nie ma nic do wyswietlenia.\n");
		return;
	}
	printf("Podaj wg ktorego parametru chcesz wyswietlic rekordy:\n");
	printf("1 - nazwa,\n2 - numer,\n3 - czestosc wydawania.\n");

	while(!walidacjaModyfikacji(stdin))
		printf("Podaj 1, 2 lub 3 jeszcze raz.\n");

	switch(bufor[0])
	{
		case '1':
			printf("Podaj nazwe gazety:\n");
			while(!walidacjaNazwy(stdin))
				printf("Podaj nazwe gazety jeszcze raz.\n");
			char nazwa[MAXNAZWA];
			strcpy(nazwa, bufor);
			wyswietlWgNazwy(nazwa, poczatek);
			return;
		case '2':
			printf("Podaj numer ID gazety:\n");
			while(!walidacjaNumeru(stdin))
				printf("Podaj numer ID gazety jeszcze raz.\n");
			wyswietlWgNumeru(bufor, poczatek);
			return;
		case '3':
			printf("Podaj czestosc wydawania:\n");
			while(!walidacjaCzestosci(stdin))
				printf("Podaj czestosc wydawania jeszcze raz.\n");
			char czestosc[MAXCZESTOSC];
			strcpy(czestosc, bufor);
			wyswietlWgCzestosci(czestosc, poczatek);
			return;
	}
}

int wyjscie()
{
	printf("Czy na pewno chcesz wyjsc? T/N\n");

	while(!walidacjaWyjscia(stdin))
		printf("Podaj 'T' lub 'N' jeszcze raz.\n");

	if(bufor[0] == 'T'){
		posprzataj();
		return 1;
	}

	return 0;
}

int menu()
{
	dostepneAkcje();

	while(!walidacjaInterakcji(stdin))
		printf("Wybierz prawidlowa interakcje jeszcze raz.\n");

	switch(bufor[0])
	{
		case '1':
			dodajNowyDzial();
			return 1;
		case '2':
			modyfikujDzial();
			return 1;
		case '3':
			usunWybranyDzial();
			return 1;
		case '4':
			dodajNowaGazete();
			return 1;
		case '5':
			modyfikacjaRekordu();
			return 1;
		case '6':
			wyswietlListe();
			return 1;
		case '7':
			wyswietlListeDzialow();
			return 1;
		case '8':
			wyswietlWybranyDzial();
			return 1;
		case '9':
			przeniesRekordy();
			return 1;
		case 'a':
			wyswietlWgParametru();
			return 1;
		case 'b':
			zapisLubOdczyt();
			return 1;
		case 'c':
			if(wyjscie())
				return 0;
			return 1;
	}

	return 0;
}
