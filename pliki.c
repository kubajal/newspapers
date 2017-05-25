#include "bazadanych.h"

void odczytTxt(char *nazwaPliku, char *haslo)
{
	char dzial[21], nazwa[21], numer[6], czestosc[21], x;
	FILE *plik;

    plik = fopen(nazwaPliku, "rt");
	if(plik == NULL){
		printf("Nie znaleziono podanego pliku. Anulowanie.\n");
		return;
	}
	if(haslo[0]){														// jesli uzytkownik podal haslo to sprawdzamy czy jest poprawne (o ile w ogole plik jest zabezpieczony haslem)
		zapelnijBufor(plik);
		if(strcmp(bufor, haslo)){
			printf("Podane haslo jest nieprawidlowe dla pliku %s.\n", nazwaPliku);
			fclose(plik);
			return;
		}
	}
	while(walidacjaInterakcji(plik))									// 1 - dodanie dzialu, 2 - dodanie gazety, 3 - wyjscie
	{
		x = bufor[0];
		if(!(x == '1' || x == '2' || x == '3')){
			printf("Tylko czesc pliku zostala wczytana lub nie zostal wczytany wcale (dane w pliku sa w zlym formacie).\n");	// zly format pliku, ale program mogl otworzyc to co do tej pory bylo w dobrym formacie
			fclose(plik);
			return;
		}
		switch(x)
		{
			case '1':
				if(!walidacjaDzialu(plik)){								// sprawdzenie formatu danych
					printf("Tylko czesc pliku zostala wczytana lub nie zostal wczytany wcale (dane w pliku sa w zlym formacie).\n");
					fclose(plik);
					return;
				}
				if(!czyIstniejeDzial(bufor))
					utworzDzial(bufor);										// utworzenie dzialu wczytanego z pliku
				break;
			case '2':
				if(!(walidacjaGazetyZPliku(plik, dzial, nazwa, numer, czestosc))){	// sprawdzenie poprawnosci formatu danych
					printf("Tylko czesc pliku zostala wczytana lub nie zostal wczytany wcale (dane w pliku sa w zlym formacie).\n");
					fclose(plik);
					return;
				}
				if(!ID[atoi(numer)]){
					utworzGazete(poczatek, dzial, nazwa, numer, czestosc);	// utworzenie gazety wczytanej z pliku
					ID[atoi(numer)] = 1;
				}
				break;
			case '3':													// koniec pliku z danymi
				fclose(plik);
				printf("Odczyt zakonczyl sie sukcesem.\n");
				return;
		}
	}
	printf("Tylko czesc pliku zostala wczytana lub nie zostal wczytany wcale (prawdopodobnie plik zabezpieczony haslem).\n");	// uzytkownik nie podal hasla
	fclose(plik);
	return;
}

void wczytajBin(FILE *plik)
{
    zerujBufor();
    fread(bufor, sizeof(char), 20, plik);
}

void odczytBin(char *nazwaPliku, char *haslo)
{
	char dzial[21], nazwa[21], numer[6], czestosc[21], x;
	FILE *plik;

    plik = fopen(nazwaPliku, "rb");
	if(plik == NULL){
		printf("Nie znaleziono podanego pliku. Anulowanie.\n");
		return;
	}
	wczytajBin(plik);
	if(strcmp(bufor, haslo)){
        printf("Zle haslo.\n");
        fclose(plik);
        return;
	}
	while(!feof(plik))
	{
        wczytajBin(plik);
        switch(bufor[0])
        {
            case '1':
                wczytajBin(plik);
                if(!znajdzDzial(bufor))
                    utworzDzial(bufor);
                break;
            case '2':
                wczytajBin(plik);
                strcpy(dzial, bufor);
                wczytajBin(plik);
                strcpy(nazwa, bufor);
                wczytajBin(plik);
                strcpy(numer, bufor);
                wczytajBin(plik);
                strcpy(czestosc, bufor);
                utworzGazete(poczatek, dzial, nazwa, numer, czestosc);
                ID[atoi(numer)] = 1;
                break;
            case '3':
                fclose(plik);
                return;
        }
	}
	fclose(plik);
	return;
}

void zapisTxt(char *nazwaPliku, char *haslo)
{
	if(poczatek == NULL){
		printf("Lista jest pusta. Nie ma nic do zapisania.\n");
		return;
	}

	FILE *plik;
	struct Dzial *y = poczatek;
	struct Gazeta *x = poczatek->pierwsza;

    plik = fopen(nazwaPliku, "wt");							// zapisywanie w trybie tekstowym
	if(haslo[0] != 0)
		fprintf(plik, "%s\n", haslo);							// zabezpieczenie pliku haslem podanym przez uzytkownika
	while(y != NULL){											// zrzucenie do pliku informacji o istniejacych dzialach i gazetach
		fprintf(plik, "1\n%s\n", y->nazwa);
		x = y->pierwsza;
		while(x != NULL){
			fprintf(plik, "2\n%s\n%s\n%s\n%s\n", y->nazwa, x->nazwa, x->numer, x->czestosc);
			x = x->nastepna;
			}
		y = y->nastepny;
	}
	fprintf(plik, "3\n");										// 3 - koniec pliku
	fclose(plik);
}

void zapiszBin(FILE *plik, char *v)
{
    zerujBufor();
    strcpy(bufor, v);
    fwrite(bufor, sizeof(char), 20, plik);
}

void zapisBin(char *nazwaPliku, char *haslo)
{
	if(poczatek == NULL){
		printf("Lista jest pusta. Nie ma nic do zapisania.\n");
		return;
	}

	FILE *plik;
	struct Dzial *y = poczatek;
	struct Gazeta *x = poczatek->pierwsza;

    plik = fopen(nazwaPliku, "wb");
	if(haslo[0] != 0){
        zapiszBin(plik, haslo);
    }
	while(y != NULL){											// zrzucenie do pliku informacji o istniejacych dzialach i gazetach
        zapiszBin(plik, "1");
        zapiszBin(plik, y->nazwa);
		x = y->pierwsza;
		while(x != NULL){
            zapiszBin(plik, "2");
            zapiszBin(plik, y->nazwa);
            zapiszBin(plik, x->nazwa);
            zapiszBin(plik, x->numer);
            zapiszBin(plik, x->czestosc);

			x = x->nastepna;
        }
		y = y->nastepny;
	}
    zapiszBin(plik, "3");
	fclose(plik);
}

void zapisLubOdczyt()
{
	int i = 0;
	char oz[21], nazwaPliku[21], haslo[21];

	for(i = 0; i < 20; i++)
		oz[i] = nazwaPliku[i] = haslo[i] = 0;

	printf("Podaj komende lub wpisz 'K' by wrocic. Komenda musi miec nastepujacy format:\n");
	printf("odczyt/zapis nazwapliku.rozszerzenie (haslo).\n");
	printf("Nalezy wybrac: odczyt lub zapis pliku, podac nazwe pliku z rozszerzeniem ('.txt' lub '.ula', lacznie max. 20 znakow) oraz opcjonalnie podac haslo (jesli rozszerzeniem jest '.ula', max. 20 znakow).\n");

	while(!walidacjaPliku(oz, nazwaPliku, haslo))
		printf("Podaj wlasciwa komende jeszcze raz lub wpisz 'K'.\n");

	if(bufor[0] == 'K' && bufor[1] == 0)			// uzytkownik wpisuje 'K' - powrot do menu
		return;

	if(!strcmp("odczyt", oz) && !strcmp(".ula", nazwaPliku + strlen(nazwaPliku) - 4))	// odczyt
		odczytBin(nazwaPliku, haslo);

	if(!strcmp("odczyt", oz) && !strcmp(".txt", nazwaPliku + strlen(nazwaPliku) - 4))	// odczyt
		odczytTxt(nazwaPliku, haslo);

	if(!strcmp("zapis", oz) && !strcmp(".txt", nazwaPliku + strlen(nazwaPliku) - 4))	// zapis
		zapisTxt(nazwaPliku, haslo);

	if(!strcmp("zapis", oz) && !strcmp(".ula", nazwaPliku + strlen(nazwaPliku) - 4))	// zapis
		zapisBin(nazwaPliku, haslo);

	return;
}
