#ifndef BAZADANYCH_H_INCLUDED
#define BAZADANYCH_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXBUFOR 1024				// maxymalny rozmiar tablicy, w ktorej buforowane sa dane wprowadzane przez uzytkownika w celu walidacji
#define MAXNUMER 6					// maxymalna dlugosc numeru ID - 5 + znak '\0'
#define MAXCZESTOSC 21				// maxymalna dlugosc czestosci - 20 + znak '\0'
#define MAXNAZWA 21					// maxymalna dlugosc nazwy gazety - 20 + znak '\0'
#define MAXDZIAL 21					// maxymalna dlugosc nazwy dzialu - 20 + znak '\0'
#define GRAFIKA ----------------------------------------

struct Gazeta									// podstawowa struktura - gazeta
{
	char nazwa[MAXNAZWA];
	char numer[MAXNUMER];
	char czestosc[MAXCZESTOSC];
	struct Gazeta *nastepna;
};

struct Dzial									// podstawowa struktura - dzial
{
	char nazwa[MAXDZIAL];
	struct Dzial *nastepny;
	struct Gazeta *pierwsza;
};

struct Dzial *poczatek;							// korzen struktury drzewiastej bazy danych
char bufor[MAXBUFOR];							// bufor dla lancuchow znakow (walidacja)
char ID[1000000];								// tablica zajetych numerow ID

void wiadomoscPowitalna();
void dostepneAkcje();							// wyswietlenie dostepnych akcji w menu glownym
struct Dzial *znajdzDzial(char *nazwa);			// zwraca wskaznik na zadany nazwa dzial
void formatowanieWyswietlania(struct Dzial *y);	// wyswietlenie zadanego dzialu w odpowiedniej formie
struct Gazeta *znajdzGazete(char *numer);		// zwraca wskaznik na szukana gazete
void wyswietlWybranyDzial();					// wywoluje uzytkownik w menu glownym, wyswietla dzial o nazwie podanej przez uzytkownika
void wyswietlListe();							// wywoluje uzytkownik w menu glownym, wyswietla cala liste dzialow i gazety
void wyswietlListeDzialow();					// wywoluje uzytkownik w menu glownym, wyswietla liste dzialow
void modyfikujDzial();							// wywoluje uzytkownik w menu glownym, zmienia nazwe wybranego dzialu
void usunWybranyDzial();						// wywoluje uzytkownik w menu glownym, usuwa caly wybrany dzial
void modyfikacjaRekordu();						// wywoluje uzytkownik w menu glownym, modyfikuje wybrana gazete
void zamienGazety(struct Gazeta *a, struct Gazeta *b);	// swap Gazet
void zamienDzialy(struct Dzial *a, struct Dzial *b);	// swap Dzialow
void sortuj();											// sortowanie alfabetyczne najpierw po dziale, a potem po nazwie gazety
void przeniesRekordy();							// wywoluje uzytkownik w menu glownym, przenosi wybrane po ID gazety z jednego dzialu do drugiego
void wyswietlWgNazwy(char *nazwa, struct Dzial *poczatek);	// jedna z mozliwosci wyswietlaniaWgParametru
void wyswietlWgNumeru(char *numer, struct Dzial *poczatek);	// jedna z mozliwosci wyswietlaniaWgParametru
void wyswietlWgCzestosci(char *czestosc, struct Dzial *poczatek);	// jedna z mozliwosci wyswietlaniaWgParametru
void dodajNowyDzial();							// wywoluje uzytkownik w menu glownym, dodaje nowy dzial
void dodajNowaGazete();							// wywoluje uzytkownik w menu glownym, dodaje nowa gazete
void wyswietlWgParametru();						// wywoluje uzytkownik w menu glownym, wyswietla wg nazwy, ID lub czestosci wydawania
void posprzataj();								// zwalnia zaalokowana pamiec przed wyjsciem z programu
int wyjscie();									// wywoluje uzytkownik w menu glownym, upewnia sie ze uzytkownik na pewno chce wyjsc z programu
int menu();										// glowna petla programu
void usun(struct Dzial *y);
void utworzGazete(struct Dzial *pocz, char *dzial, char *nazwa, char *numer, char *czestosc);
void zerujGazete(struct Gazeta *x);

void odczyt(char *nazwaPliku, char *haslo);		// odczyt z pliku zewnetrzenego
void zapis(char *nazwaPliku, char *haslo);		// zapis do pliku
void zapisLubOdczyt();							// wywoluje uzytkownik w menu glownym, obsluga zapisu lub odczytu plikow

void zerujBufor();								// wypelnia zerami
void zapelnijBufor(FILE *plik);					// zapelnia danymi z pliku, wyrzuca '\n' z konca
int walidacjaNazwy(FILE *plik);					// sprawdza czy podana nazwa jest prawidlowa
int walidacjaNumeru(FILE *plik);				// sprawdza czy podany numer jest prawidlowy
int walidacjaCzestosci(FILE *plik);				// sprawdza czy podana czestosc jest prawidlowa
int walidacjaDzialu(FILE *plik);				// sprawdza czy podana nazwa dzialu jest prawidlwoa
int walidacjaInterakcji(FILE *plik);			// sprawdza czy w menu uzytkownik podal jeden z numerow interakcji
int walidacjaModyfikacji(FILE *plik);			// sprawdza czy uzytkownik podal odpowiednia komende przy modyfikacji
int walidacjaWyjscia(FILE *plik);				// sprawdza czy uzytkownik na pewno chce wyjsc z programu
int walidacjaDzialuZPliku(FILE *plik, char *dzial);	// sprawdza czy dzial wczytany z pliku jest poprawnym lancuchem znakowym
int walidacjaGazetyZPliku(FILE *plik, char *dzial, char *nazwa, char *numer, char *czestosc);	// sprawdza czy dzial, nazwa, ID, czestosc wydawania danej gazety sa poprawnym lancuchami znakowymi
int walidacjaPliku(char *oz, char *nazwaPliku, char *haslo);	// sprawdza czy uzytkownik wpisal poprawna komede przy odczycie lub zapisie do pliku

#endif // BAZADANYCH_H_INCLUDED
