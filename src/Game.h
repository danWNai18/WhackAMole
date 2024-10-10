
#ifndef PLATFORMER_GAME_H
#define PLATFORMER_GAME_H

#include <SFML/Graphics.hpp>

class Game
{
 public:
  Game(sf::RenderWindow& window);
  ~Game();
  bool init();
  void update(float dt);
  void render();
  void mouseClicked(sf::Event event);
  void keyPressed(sf::Event event);

 private:
	
	bool in_menu;
	bool play_selected = true;
	bool collisionCheck(sf::Vector2i click, sf::Sprite sprite);
	void spawn();

  sf::RenderWindow& window;
  sf::Sprite bird;
  sf::Texture bird_texture;
  sf::Sprite background;
  sf::Texture background_texture;

  sf::Font font;
  sf::Text menu_text;
  sf::Text play_option;
  sf::Text quit_option;

  bool reverse = false;

  int speed = 500;

  int score = 0;
  std::string score_string;
  sf::Text score_text;

};

#endif // PLATFORMER_GAME_H
