projekt3: main.o interakcje.o menu.o pliki.o struktura.o walidacja.o wyswietlanie.o
	gcc $^ -o $@
main.o: main.c
	gcc -c -Wall $^
wyswietlanie.o: wyswietlanie.c
	gcc -c -Wall $^
interakcje.o: interakcje.c
	gcc -c -Wall $^
struktura.o: struktura.c
	gcc -c -Wall $^
walidacja.o: walidacja.c
	gcc -c -Wall $^
pliki.o: pliki.c
	gcc -c -Wall $^
menu.o: menu.c
	gcc -c -Wall $^
