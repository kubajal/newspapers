#include "bazadanych.h"

char interakcje()
{
	while(!walidacjaInterakcji(stdin))
		printf("Wybierz prawidlowa interakcje jeszcze raz.\n");

	return bufor[0];
}
