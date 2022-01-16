#include <SFML/Graphics.hpp>
#include <iostream>
#include <ctime>
#include <cstdlib>
#include "menu.h"
#include "pet.h"
#include "Gra.h"



int main()
{
	srand(time(NULL)); // inicjalizowanie maszyny losuj¹cej
	int aktualny_ekran = 0;  // zmienna pokazuj¹ca na jaki ekran teraz patrzysz  // 0 - Menu ; 1 - Gra ; 2 - Menu_Poziom_Wybor; 3 - Historia_Wynikow ; 112 - resetowanie ekranu
	int poprzedni_ekran = 0; // zmienna pokazuj¹ca na jaki ekran teraz patrzy³aœ w poprzedniej klatce obrazu (zanim wcisnê³aœ jakiœ przycisk)
	unsigned int poziom_gry; // zmienna do przekazywania numeru poziomu gry pomiêdzy Menu_Poziom_Wybor a Gr¹
	sf::RenderWindow window(sf::VideoMode(800, 600), "Flappy pet"); // Okienko 800x600
	sf::View kamera({ 0.f,0.f,800.f,600.f }); // Kamera 800x600 ze startow¹ pozycj¹ 0,0
	Menu* menu = new Menu(&kamera, &aktualny_ekran); // Dynamicznie alokowane Menu po wskaŸniku

	window.setFramerateLimit(60); // Górny limit FPS'ów: 60 (ile maksymalnie klatek karta graficzna mo¿e (ma pozwolenie) wygenerowaæ w ci¹gu jednej sekundy)
	gra* program = 0; // Inicjalizacja i ustawienie wskaŸnika klasy Gra na 0 (czyli sama gra jeszcze nie istnieje -> roboczo wskaŸnik wskazany na 0 to taki którego nie u¿ywamy)
	sf::Event event; // Inicjalizacja obs³ugi zdarzeñ (np. przycisków z klawiatury) 
	while (window.isOpen()) // Petla wykonywana dopóki okno jest otwarte
	{

		while (window.pollEvent(event)) // Pêtla obs³ugi zdarzeñ
		{
			if (event.type == sf::Event::Closed) { exit(0); } // Klikasz X w prawym górnym rogu i wychodzisz z gry;

			switch (aktualny_ekran) // Zmiana trybu obs³ugi zdarzeñ (trybu sterowania po klasie sf::Event)
			{//w zale¿noœci od aktualnego ekranu
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

		if (aktualny_ekran != poprzedni_ekran) // Wykrycie zmiany ekranu i obs³uga takiej sytuacji
		{
			if (poprzedni_ekran == 1) // Usuwanie danych zwi¹zanych z obiektem klasy Gra (zwalnianie pamiêci)
			{
				delete program;
				program = 0; // Robocze ustawienie wskaŸnika na 0
			}
			else // Usuwanie danych zwi¹zanych z obiektem klasy Menu lub dziedziczonych (zwalnianie pamiêci)
			{
				delete menu;
				menu = 0; // Robocze ustawienie wskaŸnika na 0
			}

			if (aktualny_ekran == 112) // 112 to kod resetu okna czyli je¿eli poprzedni_ekran = 1 to po tej procedurze aktualny_ekran = 1
			{
				aktualny_ekran = poprzedni_ekran;
			}
			else // Innym wypadku poprzedni_ekran przyjmie wartoœæ aktualny_ekran (dziêki temu przy kolejnej zmianie ekranu bêdzie wiadomo dla którego wskaŸnika zawartoœæ trzeba usun¹æ i wyzerowaæ)
			{
				poprzedni_ekran = aktualny_ekran;
			}

			switch (aktualny_ekran) // Generowanie nowego obiektu (tego co bêdziemy widzieæ i czym bêdziemy sterowaæ) na podstawie zmiennej aktualny_ekran
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

		window.clear(); // czyszczenie obrazu pomiêdzy klatkami obrazu

		switch (aktualny_ekran) // Renderowanie obrazu dla konkretnego obiektu danej klasy (np. aktualny_ekran == 1 -> Grasz w grê to widzisz s³upki,t³o,ptaka bo jesteœ w trakcie rozgrywki)
		{
		case 0:
		case 2:
		case 3:
			kamera.setCenter(400.f, 300.f); // Ustawienie pozycji kamery dla wszelkiego rodzaju Menu
			menu->draw(&window); // Renderowanie obrazu dla wszelkiego rodzaju Menu
			break;
		case 1:
			program->aktualizuj(); // Aktualizacja ró¿nych procedur zwi¹zanych z Gr¹ (w tym sterowanie p³ynne po samej klasie Sf::Keyboard bez bufora Sf::Event)
			break;
		}
		window.setView(kamera); // Okno pobiera ci¹gle widok kamery
		window.display(); // Wyœwietlanie ca³ego okna (z zawartoœci¹)
	}

	return 0;
}