#include <SFML/Graphics.hpp>
#include <iostream>
#include <ctime>
#include <cstdlib>
#include "menu.h"
#include "pet.h"
#include "Gra.h"
#include "pomoc.h"
#define MAX_LICZBA_POZIOMOW 3



int main()
{
	Pomoc pomoc;
	int menu_selected_flag = 0; // problematyczna zmienna 
	sf::RenderWindow window(sf::VideoMode(800, 600), "Flappy pet");
	sf::View kamera({ 0.f,0.f,800.f,600.f });
	Menu menu(&kamera);
	window.setFramerateLimit(60);
	//gra program(&window, &kamera);
	gra* program = 0;
	sf::Event event;
	while (window.isOpen())
	{
		
		while (window.pollEvent(event))
		{
			switch (menu_selected_flag)
			{
			case 0:
			case 2:
				menu.sterowanie(&window, &event, menu_selected_flag);
				break;
			case 1:
				program->sterowanie_event();
				break;
			}
		}
		window.clear();
		if (menu_selected_flag == 0)
		{
			menu.draw(&window);
		}
		if ((menu_selected_flag == 1) && (program == 0))
		{
			program = new gra(&window, &kamera, &event);
		}
		if ((menu_selected_flag == 1)&&(program!=0))
		{
			program->aktualizuj();
		}
		if (menu_selected_flag == 2)
		{
			pomoc.draw(window);
		}
		window.setView(kamera);
		window.display();
	}

	return 0;
}