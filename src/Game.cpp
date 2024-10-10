
#include "Game.h"
#include <iostream>

Game::Game(sf::RenderWindow& game_window)
  : window(game_window)
{
  srand(time(NULL));
}

Game::~Game()
{

}

bool Game::init()
{

	in_menu = true;
	if (!background_texture.loadFromFile("../Data/WhackaMole Worksheet/background.png"))
	{
		std::cout << "background texture did not load \n";
	}
	background.setTexture(background_texture);
	
	//bird texture
	if (!bird_texture.loadFromFile("../Data/WhackaMole Worksheet/bird.png"))
	{
		std::cout << "Error loading player texture \n";
		return false;
	}
	bird.setTexture(bird_texture);
	bird.setScale(0.5, 0.5);
	bird.setPosition(window.getSize().x / 2 - bird.getGlobalBounds().width / 2, 525);

	if (!font.loadFromFile("../Data/Fonts/OpenSans-Bold.ttf"))
	{
		std::cout << "Error loading font\n";
		return false;
	}

	//menu text options
	menu_text.setFont(font);
	menu_text.setString("Whack-a-mole");
	menu_text.setCharacterSize(72);
	menu_text.setFillColor(sf::Color::White);
	menu_text.setPosition(65, 200);

	//play button options
	play_option.setFont(font);
	play_option.setString(">Play<");
	play_option.setCharacterSize(60);
	play_option.setFillColor(sf::Color::White);
	play_option.setPosition(250, 400);

	//quit button options
	quit_option.setFont(font);
	quit_option.setString("Quit");
	quit_option.setCharacterSize(60);
	quit_option.setFillColor(sf::Color::White);
	quit_option.setPosition(650, 400);

	//score text
	score_text.setFont(font);
	score_text.setString("Score: 0");
	score_text.setCharacterSize(50);
	score_text.setFillColor(sf::Color::Black);
	score_text.setPosition(window.getSize().x / 2 - score_text.getGlobalBounds().width, 100);


  return true;
}

void Game::update(float dt)
{
	if (reverse == true)
	{
		(bird.move(-0.5 * speed * dt, 0.0f * speed * dt));
		bird.setTextureRect(sf::IntRect(
			bird.getLocalBounds().width,
			0,
			-bird.getLocalBounds().width,
			bird.getLocalBounds().height));
	}
	else
	{
		bird.move(0.5 * speed * dt, 0);
		bird.setTextureRect(sf::IntRect(0, 0, bird.getLocalBounds().width, bird.getLocalBounds().height));
	}

	if ((bird.getPosition().x > (window.getSize().x - bird.getGlobalBounds().width)) ||
		(bird.getPosition().x < 0))
	{
		reverse = !reverse;
	}
}

void Game::render()
{
	if (!in_menu)
	{
		window.draw(background);
		window.draw(bird);
		window.draw(score_text);

	}
	else
	{
		window.draw(menu_text);
		window.draw(play_option);
		window.draw(quit_option);
	}
	
}

void Game::mouseClicked(sf::Event event)
{
  //get the click position
  sf::Vector2i click = sf::Mouse::getPosition(window);
  collisionCheck(click, bird);
  std::cout << "hit";
}

void Game::keyPressed(sf::Event event)
{
	if (event.key.code == sf::Keyboard::Escape)
	{
		window.close();
	}

	if (
		(event.key.code == sf::Keyboard::Left) ||
		(event.key.code == sf::Keyboard::Right))
	{
		play_selected = !play_selected;
		if (play_selected)
		{
			play_option.setString(">Play<");
			quit_option.setString("Quit");
		}
		else
		{
			play_option.setString("Play");
			quit_option.setString(">Quit<");
		}
	}
	else if (event.key.code == sf::Keyboard::Enter)
	{
		if (play_selected)
		{
			in_menu = false;
		}
		else
		{
			window.close();
		}
	}
}

bool Game::collisionCheck(sf::Vector2i click, sf::Sprite sprite)
{
	if ((click.x > sprite.getPosition().x) &&
		(click.x < sprite.getPosition().x + sprite.getGlobalBounds().width) &&
		(click.y > sprite.getPosition().y) &&
		(click.y < sprite.getPosition().y + sprite.getGlobalBounds().height))
	{
		score++;
		score_string = std::to_string(score);
		score_text.setString("Score: " + score_string);
		spawn();
		return true;
	}
	else
		return false;

}

void Game::spawn()
{
	float x = rand() % (1000);
	float y = rand() % (620);
}


