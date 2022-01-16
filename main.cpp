#include <SFML/Graphics.hpp>
#include <iostream>
#include <ctime>
#include <cstdlib>
#include "menu.h"
#include "pet.h"
#include "Gra.h"



int main()
{
	srand(time(NULL)); // inicjalizowanie maszyny losuj�cej
	int aktualny_ekran = 0;  // zmienna pokazuj�ca na jaki ekran teraz patrzysz  // 0 - Menu ; 1 - Gra ; 2 - Menu_Poziom_Wybor; 3 - Historia_Wynikow ; 112 - resetowanie ekranu
	int poprzedni_ekran = 0; // zmienna pokazuj�ca na jaki ekran teraz patrzy�a� w poprzedniej klatce obrazu (zanim wcisn�a� jaki� przycisk)
	unsigned int poziom_gry; // zmienna do przekazywania numeru poziomu gry pomi�dzy Menu_Poziom_Wybor a Gr�
	sf::RenderWindow window(sf::VideoMode(800, 600), "Flappy pet"); // Okienko 800x600
	sf::View kamera({ 0.f,0.f,800.f,600.f }); // Kamera 800x600 ze startow� pozycj� 0,0
	Menu* menu = new Menu(&kamera, &aktualny_ekran); // Dynamicznie alokowane Menu po wska�niku

	window.setFramerateLimit(60); // G�rny limit FPS'�w: 60 (ile maksymalnie klatek karta graficzna mo�e (ma pozwolenie) wygenerowa� w ci�gu jednej sekundy)
	gra* program = 0; // Inicjalizacja i ustawienie wska�nika klasy Gra na 0 (czyli sama gra jeszcze nie istnieje -> roboczo wska�nik wskazany na 0 to taki kt�rego nie u�ywamy)
	sf::Event event; // Inicjalizacja obs�ugi zdarze� (np. przycisk�w z klawiatury) 
	while (window.isOpen()) // Petla wykonywana dop�ki okno jest otwarte
	{

		while (window.pollEvent(event)) // P�tla obs�ugi zdarze�
		{
			if (event.type == sf::Event::Closed) { exit(0); } // Klikasz X w prawym g�rnym rogu i wychodzisz z gry;

			switch (aktualny_ekran) // Zmiana trybu obs�ugi zdarze� (trybu sterowania po klasie sf::Event)
			{//w zale�no�ci od aktualnego ekranu
			case 0:
			case 2:
			case 3:
				menu->sterowanie(&window, &event); // sterowanie dla klasy Menu lub dziedziczonych 
				break;
			case 1:
				program->sterowanie_event(); // sterowanie dla klasy Gra
				break;
			}
		}

		if (aktualny_ekran != poprzedni_ekran) // Wykrycie zmiany ekranu i obs�uga takiej sytuacji
		{
			if (poprzedni_ekran == 1) // Usuwanie danych zwi�zanych z obiektem klasy Gra (zwalnianie pami�ci)
			{
				delete program;
				program = 0; // Robocze ustawienie wska�nika na 0
			}
			else // Usuwanie danych zwi�zanych z obiektem klasy Menu lub dziedziczonych (zwalnianie pami�ci)
			{
				delete menu;
				menu = 0; // Robocze ustawienie wska�nika na 0
			}

			if (aktualny_ekran == 112) // 112 to kod resetu okna czyli je�eli poprzedni_ekran = 1 to po tej procedurze aktualny_ekran = 1
			{
				aktualny_ekran = poprzedni_ekran;
			}
			else // Innym wypadku poprzedni_ekran przyjmie warto�� aktualny_ekran (dzi�ki temu przy kolejnej zmianie ekranu b�dzie wiadomo dla kt�rego wska�nika zawarto�� trzeba usun�� i wyzerowa�)
			{
				poprzedni_ekran = aktualny_ekran;
			}

			switch (aktualny_ekran) // Generowanie nowego obiektu (tego co b�dziemy widzie� i czym b�dziemy sterowa�) na podstawie zmiennej aktualny_ekran
			{
			case 0: if (menu == 0) { menu = new Menu(&kamera, &aktualny_ekran); }
				  break;
			case 1: if (program == 0) { program = new gra(&window, &kamera, &event, &aktualny_ekran, &poziom_gry); }
				  break;
			case 2: if (menu == 0) { menu = new Menu_Poziom_Wybor(&kamera, &aktualny_ekran, &poziom_gry); }
				  break;
			case 3: if (menu == 0) { menu = new Historia_Wynikow(&kamera, &aktualny_ekran); }
				  break;
			}
		}

		window.clear(); // czyszczenie obrazu pomi�dzy klatkami obrazu

		switch (aktualny_ekran) // Renderowanie obrazu dla konkretnego obiektu danej klasy (np. aktualny_ekran == 1 -> Grasz w gr� to widzisz s�upki,t�o,ptaka bo jeste� w trakcie rozgrywki)
		{
		case 0:
		case 2:
		case 3:
			kamera.setCenter(400.f, 300.f); // Ustawienie pozycji kamery dla wszelkiego rodzaju Menu
			menu->draw(&window); // Renderowanie obrazu dla wszelkiego rodzaju Menu
			break;
		case 1:
			program->aktualizuj(); // Aktualizacja r�nych procedur zwi�zanych z Gr� (w tym sterowanie p�ynne po samej klasie Sf::Keyboard bez bufora Sf::Event)
			break;
		}
		window.setView(kamera); // Okno pobiera ci�gle widok kamery
		window.display(); // Wy�wietlanie ca�ego okna (z zawarto�ci�)
	}

	return 0;
}