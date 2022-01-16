#include "menu.h"


Menu::Menu(sf::View* adres_kamery, int* aktualny_ekran)
{
	liczba_przyciskow = 3;
	menu = new sf::Text[liczba_przyciskow];

	this->aktualny_ekran = aktualny_ekran;

	float width = 800.f;
	float height = 600.f;

	pole_glowne.setPosition({ 0.f,0.f });
	pole_glowne.setSize({ width,height });
	pole_glowne.setFillColor(sf::Color( 49, 165, 80 ));

	naglowek.setPosition({ 0.f,0.f });
	naglowek.setSize({ 800.f,100.f });
	naglowek.setFillColor(sf::Color(105, 196, 215));

	tytul.setFont(font);
	tytul.setString("Flappy Pet");
	tytul.setCharacterSize(40);
	tytul.setPosition({ (naglowek.getSize().x / 2) - 100.f , 25.f });

	//adres_kamery->
	if (!font.loadFromFile("arial.ttf"))
	{
		return;
	}

	for (int i = 0; i < liczba_przyciskow; i++)
	{
		menu[i].setFont(font);
		menu[1].setFillColor(sf::Color::White);
		menu[i].setPosition(sf::Vector2f(width / 3, height / (liczba_przyciskow + 1) * (i + 1)));
	}

	menu[0].setFillColor(sf::Color(105, 196, 215));
	menu[0].setString("Nowa gra");
	menu[1].setString(L"Historia wyników");
	menu[2].setString(L"Wyjœcie");

	inicjalizacja_animacji();
	
}


Menu::~Menu()
{
	delete []menu;
}


void Menu::draw(sf::RenderWindow* window)
{
	klatka_timer += 1.0 / 60.0;
	window->draw(pole_glowne);
	window->draw(naglowek);
	window->draw(tytul);
	for (int i = 0; i < liczba_przyciskow; i++)
	{
		window->draw(menu[i]);
	}

	for (int i = 0; i < 2; i++)
	{
		window->draw(pet_menu[i]);
		pet_animacja[i].aktualizacja(ktora_klatka);
		pet_menu[i].setTextureRect(pet_animacja[i].klatka_zwroc());
	}
	
	animuj();
}


void Menu::przesunG()
{
	if (selectedItem >= 0 && selectedItem < liczba_przyciskow)
	{
		menu[selectedItem].setFillColor(sf::Color::White);
		menu[selectedItem].setStyle(sf::Text::Regular);
		selectedItem--;
		if (selectedItem < 0)
			selectedItem = liczba_przyciskow - 1;
		menu[selectedItem].setFillColor(sf::Color(105, 196, 215));
		menu[selectedItem].setStyle(sf::Text::Bold);
	}


}

void Menu::przesunD()
{
	if (selectedItem >= 0 && selectedItem < liczba_przyciskow)
	{
		menu[selectedItem].setFillColor(sf::Color::White);
		menu[selectedItem].setStyle(sf::Text::Regular);
		selectedItem++;
		if (selectedItem >= liczba_przyciskow)
			selectedItem = 0;
		menu[selectedItem].setFillColor(sf::Color(105, 196, 215));
		menu[selectedItem].setStyle(sf::Text::Bold);
	}

}

void Menu::sterowanie(sf::RenderWindow* window, sf::Event* event)
{
	if (event->type == sf::Event::KeyReleased)
	{
		if (event->key.code == sf::Keyboard::Up)
		{
			przesunG();
		}

		if (event->key.code == sf::Keyboard::Down)
		{
			przesunD();
		}

		
		if (event->key.code == sf::Keyboard::Enter && getSelectedItem() == 0)
		{
			*aktualny_ekran = 2;
		}

		if (event->key.code == sf::Keyboard::Enter && getSelectedItem() == 1)
		{
			*aktualny_ekran = 3;
		}

		if (event->key.code == sf::Keyboard::Enter && getSelectedItem() == 2)
		{
			exit(0);
		}
		
	}
}

void Menu::animuj()
{
	if (klatka_timer >= 0.25)
	{
		if (ktora_klatka == 1)
		{
			ktora_klatka = 0;
			klatka_timer = 0.0;
		}
		else
		{
			ktora_klatka = 1;
			klatka_timer = 0.0;
		}
	}
}

void Menu::inicjalizacja_animacji()
{
	pet_menu = new sf::RectangleShape[2];
	pet_tekstura = new sf::Texture[2];
	pet_animacja = new animacja[2];

	pet_menu[0].setSize({ 76,46 });
	pet_menu[1].setSize({ 76,46 });
	pet_menu[0].setPosition({ naglowek.getPosition().x + 100.f, naglowek.getPosition().y + 20.f });
	pet_menu[1].setPosition({ naglowek.getPosition().x + naglowek.getSize().x - 100.f - pet_menu[1].getSize().x,naglowek.getPosition().y + 20.f });

	pet_tekstura[0].loadFromFile("pet_menu.png");
	pet_tekstura[1].loadFromFile("pet_menu2.png");
	pet_animacja[0] = { &pet_tekstura[0],2 };
	pet_animacja[1] = { &pet_tekstura[1],2 };

	pet_menu[0].setTexture(&pet_tekstura[0]);
	pet_menu[1].setTexture(&pet_tekstura[1]);
	pet_menu[0].setTextureRect(pet_animacja[0].klatka_zwroc());
	pet_menu[1].setTextureRect(pet_animacja[1].klatka_zwroc());
}

Koniec_gry::Koniec_gry(float x, float y, sf::View* adres_kamery, int* aktualny_ekran, unsigned int* ekran)
{
	liczba_przyciskow = 3;
	menu = new sf::Text[liczba_przyciskow];
	std::cout << "inicjalizowanie pamieci -> koniec gry" << std::endl;

	this->aktualny_ekran = aktualny_ekran;
	this->ekran = ekran;

	float width = 600.f;
	float height = 300.f;

	pole_glowne.setPosition({ x,y });
	pole_glowne.setSize({ width,height });
	pole_glowne.setFillColor(sf::Color(49, 165, 80));

	naglowek.setPosition(pole_glowne.getPosition());
	naglowek.setSize({ width,100.f });
	naglowek.setFillColor(sf::Color(105, 196, 215));

	tytul.setFont(font);
	if (*ekran == 1) { tytul.setString("Koniec Gry"); }
	else if(*ekran == 3) { tytul.setString(L"    Opcje"); }
	tytul.setCharacterSize(40);
	tytul.setPosition({ (naglowek.getPosition().x + naglowek.getSize().x / 2) - 100.f , naglowek.getPosition().y + 25.f });

	if (!font.loadFromFile("arial.ttf"))
	{
		return;
	}

	for (int i = 0; i < liczba_przyciskow; i++)
	{
		menu[i].setFont(font);
		menu[1].setFillColor(sf::Color::White);
		menu[i].setPosition(sf::Vector2f(pole_glowne.getPosition().x + width / 3, pole_glowne.getPosition().y + naglowek.getSize().y + height / (liczba_przyciskow + 1) * i));
	}
	
	menu[0].setFillColor(sf::Color(105, 196, 215));
	menu[0].setString("Resetuj gre");
	menu[1].setString(L"Wróæ do menu");
	menu[2].setString("Wyjscie z gry");
	
	inicjalizacja_animacji();

}

void Koniec_gry::sterowanie(sf::RenderWindow* window, sf::Event* event)
{
	if (event->type == sf::Event::KeyReleased)
	{
		if (event->key.code == sf::Keyboard::Escape && *ekran == 3)
		{
			*ekran = 0;
		}

		if (event->key.code == sf::Keyboard::Up)
		{
			przesunG();
		}

		if (event->key.code == sf::Keyboard::Down)
		{
			przesunD();
		}

		
		if (event->key.code == sf::Keyboard::Enter && getSelectedItem() == 0)
		{
			*aktualny_ekran = 112;
		}

		if (event->key.code == sf::Keyboard::Enter && getSelectedItem() == 1)
		{
			*aktualny_ekran = 0;
		}

		if (event->key.code == sf::Keyboard::Enter && getSelectedItem() == 2)
		{
			exit(0);
		}
		
	}
}

Menu_Poziom_Wybor::Menu_Poziom_Wybor(sf::View* adres_kamery, int* aktualny_ekran, unsigned int* poziom_gry)
{
	liczba_przyciskow = 4;
	menu = new sf::Text[liczba_przyciskow];
	std::cout << "inicjalizowanie pamieci -> menu_poziom_wybor" << std::endl;

	this->aktualny_ekran = aktualny_ekran;
	this->poziom_gry = poziom_gry;

	float width = 800.f;
	float height = 600.f;

	pole_glowne.setPosition({ 0.f,0.f });
	pole_glowne.setSize({ width,height });
	pole_glowne.setFillColor(sf::Color(49, 165, 80));

	naglowek.setPosition({ 0.f,0.f });
	naglowek.setSize({ 800.f,100.f });
	naglowek.setFillColor(sf::Color(105, 196, 215));

	tytul.setFont(font);
	tytul.setString(L"Wybór Poziomu");
	tytul.setCharacterSize(40);
	tytul.setPosition({ (naglowek.getSize().x / 2) - 100.f , 25.f });

	if (!font.loadFromFile("arial.ttf"))
	{
		return;
	}
	for (int i = 0; i < liczba_przyciskow; i++)
	{
		menu[i].setFont(font);
		menu[1].setFillColor(sf::Color::White);
		menu[i].setPosition(sf::Vector2f(width / 3, height / (liczba_przyciskow + 1) * (i + 1)));
	}

	menu[0].setFillColor(sf::Color(105, 196, 215));
	menu[0].setString("Heaven");
	menu[1].setString("Midnight");
	menu[2].setString("Gates of hell");
	menu[3].setString("Menu");

	inicjalizacja_animacji();

}

void Menu_Poziom_Wybor::sterowanie(sf::RenderWindow* window, sf::Event* event)
{
	if (event->type == sf::Event::KeyReleased)
	{
		if (event->key.code == sf::Keyboard::Up)
		{
			przesunG();
		}

		if (event->key.code == sf::Keyboard::Down)
		{
			przesunD();
		}


		if (event->key.code == sf::Keyboard::Enter && getSelectedItem() == 0)
		{
			*aktualny_ekran = 1;
			*poziom_gry = 1;
		}

		if (event->key.code == sf::Keyboard::Enter && getSelectedItem() == 1)
		{
			*aktualny_ekran = 1;
			*poziom_gry = 2;
		}

		if (event->key.code == sf::Keyboard::Enter && getSelectedItem() == 2)
		{
			*aktualny_ekran = 1;
			*poziom_gry = 3;
		}

		if (event->key.code == sf::Keyboard::Enter && getSelectedItem() == 3)
		{
			*aktualny_ekran = 0;
		}

	}
}

Historia_Wynikow::Historia_Wynikow(sf::View* adres_kamery, int* aktualny_ekran)
{
	liczba_przyciskow = 2;
	menu = new sf::Text[liczba_przyciskow];

	this->aktualny_ekran = aktualny_ekran;

	float width = 800.f;
	float height = 600.f;

	pole_glowne.setPosition({ 0.f,0.f });
	pole_glowne.setSize({ width,height });
	pole_glowne.setFillColor(sf::Color(49, 165, 80));

	naglowek.setPosition({ 0.f,0.f });
	naglowek.setSize({ 800.f,100.f });
	naglowek.setFillColor(sf::Color(105, 196, 215));

	tytul.setFont(font);
	tytul.setString(L"Historia wyników");
	tytul.setCharacterSize(40);
	tytul.setPosition({ (naglowek.getSize().x / 2) - 150.f , 25.f });

	if (!font.loadFromFile("arial.ttf"))
	{
		return;
	}

	for (int i = 0; i < liczba_przyciskow; i++)
	{
		menu[i].setFont(font);
		menu[1].setFillColor(sf::Color::White);
	}

	menu[0].setPosition({600.f,200.f});
	menu[1].setPosition({600.f,400.f});

	menu[0].setFillColor(sf::Color(105, 196, 215));
	menu[0].setString("Menu");
	menu[1].setString("Resetuj");

	odczyt_statystyk_z_pliku();

	for (int i = 0; i < 10; i++)
	{
		wyniki[i].setFont(font);
		wyniki[i].setPosition({ 30.f, 100.f + i * 50.f });
		wyniki[i].setFillColor(sf::Color::Blue);
		wyniki[i].setString("Wynik: " + std::to_string(staty_menu[i].wynik) + "	Poziom: " + std::to_string(staty_menu[i].numer_poziomu));
		wyniki[i].setCharacterSize(30);
	}

}

void Historia_Wynikow::sterowanie(sf::RenderWindow* window, sf::Event* event)
{
	if (event->type == sf::Event::KeyReleased)
	{
		if (event->key.code == sf::Keyboard::Up)
		{
			przesunG();
		}

		if (event->key.code == sf::Keyboard::Down)
		{
			przesunD();
		}


		if (event->key.code == sf::Keyboard::Enter && getSelectedItem() == 0)
		{
			*aktualny_ekran = 0;
		}

		if (event->key.code == sf::Keyboard::Enter && getSelectedItem() == 1)
		{
			resetuj_statystyki();
			for (int i = 0; i < 10; i++)
			{
				wyniki[i].setString("Wynik: " + std::to_string(0) + "	Poziom: " + std::to_string(0));
			}

		}
	}
}

void Historia_Wynikow::resetuj_statystyki()
{
	std::fstream plik;
	plik.open("staty.txt", std::ios::out);
	if (plik.good() == true) 
	{

	}
	else { std::cout << "Problem" << std::endl; }
	plik.close();
}

void Historia_Wynikow::draw(sf::RenderWindow* window)
{
	window->draw(pole_glowne);
	window->draw(naglowek);
	window->draw(tytul);

	for (int i = 0; i < liczba_przyciskow; i++)
	{
		window->draw(menu[i]);
	}

	for (int i = 0; i < 10; i++)
	{
		window->draw(wyniki[i]);
	}
}

void Historia_Wynikow::odczyt_statystyk_z_pliku()
{
	std::fstream plik;
	plik.open("staty.txt", std::ios::in | std::ios::binary);
	plik.seekg(0, std::ios::end); // 0 pozycja od koñca pliku
	unsigned int f = plik.tellg(); // pozycja koñcowa
	if (plik.good() == true)
	{
		for(unsigned int i = 0; i<10;i++)
		{
			f -= sizeof(Staty);
			plik.seekg(f);
			std::cout << plik.tellg()<<std::endl;
			plik.read((char*)&staty_menu[i], sizeof(*staty_menu));
		}
	}
	else
	{
		std::cout << "Problem z plikiem" << std::endl;
		plik.close();
		return;
	}
	

	plik.close();
}

