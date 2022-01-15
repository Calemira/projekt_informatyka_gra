#include <SFML/Graphics.hpp>
#include <iostream>
#include <ctime>
#include <cstdlib>
#include "menu.h"
#include "pet.h"
#include "Gra.h"



int main()
{
	srand(time(NULL));
	int aktualny_ekran = 0; // 0 - Menu ; 1 - Gra ; 2 - Menu_Poziom_Wybor; 3 - Historia_Wynikow ; 112 - resetowanie ekranu
	int poprzedni_ekran = 0;
	unsigned int poziom_gry;
	sf::RenderWindow window(sf::VideoMode(800, 600), "Flappy pet");
	sf::View kamera({ 0.f,0.f,800.f,600.f });
	Menu *menu = new Menu(&kamera,&aktualny_ekran);

	window.setFramerateLimit(60);
	gra* program = 0;
	sf::Event event;
	while (window.isOpen())
	{
		
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed) { exit(0); }

			switch (aktualny_ekran)
			{
			case 0:
			case 2:
			case 3:
				menu->sterowanie(&window, &event);
				break;
			case 1:
				program->sterowanie_event();
				break;
			}
		}

		if (aktualny_ekran != poprzedni_ekran)
		{
			if (poprzedni_ekran == 1)
			{
				delete program;
				program = 0;
			}
			else
			{
				delete menu;
				menu = 0;
			}

			if (aktualny_ekran == 112)
			{
				aktualny_ekran = poprzedni_ekran;
			}
			else
			{
				poprzedni_ekran = aktualny_ekran;
			}

			switch (aktualny_ekran)
			{
			case 0: if (menu == 0) { menu = new Menu(&kamera, &aktualny_ekran); }
				break;
			case 1: if (program == 0) {program = new gra(&window, &kamera, &event, &aktualny_ekran, &poziom_gry); }
				break;
			case 2: if (menu == 0) { menu = new Menu_Poziom_Wybor(&kamera, &aktualny_ekran, &poziom_gry); }
				break;
			case 3: if (menu == 0) { menu = new Historia_Wynikow(&kamera, &aktualny_ekran); }
				break;
			}
		}

		window.clear();

		switch (aktualny_ekran)
		{
		case 0:
		case 2:
		case 3:
			kamera.setCenter(400.f, 300.f);
			menu->draw(&window);
			break;
		case 1:
			program->aktualizuj();
			break;
		}
		window.setView(kamera);
		window.display();
	}

	return 0;
}