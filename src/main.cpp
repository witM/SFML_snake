
#include <iostream>
#include <array>
#include <ctime>
#include <cstdlib>
#include <Windows.h>
using namespace std;

#include <SFML\Graphics.hpp>
//
#include "Assets.h"


#define SCREEN_WIDTH		800
#define SCREEN_HEIGHT		600
#define BITS				32
sf::String g_Title = "sfml app";
sf::Font g_font;
const float g_FPS_TARGET = 10.f;
const float g_DT_TARGET = 1.f / g_FPS_TARGET;



/* GAME ASSETS */
// 0 - run, 1 - game over, 2 - player won
int g_gameOver;
Snake g_snake;
Snake::EDirection g_dir;
const int g_CAP_MAX = 20;
CAP g_capArray[g_CAP_MAX];
int g_catchCaps;
sf::Text g_text;

/* GAME FUNCTIONS */
int IsGameOver();
bool IsSnakeCatchCap();
void DrawTiles(sf::RenderWindow& Wnd);

/* BASE GAME FUNCTIONS*/
void InitGame();
void HandleInput(sf::Event& Event);
void Update();
void Draw(sf::RenderWindow& Wnd);

int main()
{
	if (!g_font.loadFromFile(string("font.ttf")))
		cout << "font not loaded, error" << endl;

	sf::RenderWindow _window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, BITS), g_Title);
	sf::Text _txt(sf::String("hello"), g_font, 20);
	/* game */
	srand(time(nullptr));
	InitGame();

	sf::Event _event;
	sf::Clock _clock;
	while (1)
	{
		_clock.restart();
		// event process
		while (_window.pollEvent(_event))
		{
			if ((_event.type == sf::Event::Closed) || (_event.type == sf::Event::KeyPressed && _event.key.code == sf::Keyboard::Escape))
				exit(0);
			HandleInput(_event);
		}
		// logic and renderic
		//else
		{
			Update();
			_window.clear();
			Draw(_window);
			_window.display();
		}
		float _dt = _clock.getElapsedTime().asSeconds();
		//cout << _dt << endl;
		if (_dt < g_DT_TARGET)
		{
			float _s = (g_DT_TARGET - _dt) * 1000.f;
			Sleep(_s);
		}
	
	}

	
	//std::cin.get();0
}
/* Game handle input */
void HandleInput(sf::Event& Event)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		g_dir = Snake::EDirection::LEFT;
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		g_dir = Snake::EDirection::UP;
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		g_dir = Snake::EDirection::RIGHT;
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		g_dir = Snake::EDirection::DOWN;
}
/* Game update */
void Update()
{
	if (g_gameOver == 0)
	{
		g_snake.tick(g_dir);
		if (IsGameOver() != 0)
			return;
		// check if snake catch cap
		IsSnakeCatchCap();
	}
}
/* Game Draw */
void Draw(sf::RenderWindow& Wnd)
{
	if (g_gameOver == 0)
	{
		// draw caps to catch
		for (auto& item : g_capArray)
		{
			if (item.isCatch == false)
			{
				sf::CircleShape _c;
				_c.setRadius(item.RADIUS);
				_c.setOrigin(item.RADIUS, item.RADIUS);
				_c.setPosition(item.pos);
				_c.setFillColor(item.color);
				Wnd.draw(_c);
			}
		}
		// draw snake
		g_snake.draw(Wnd);
	}
	else
	{
		Wnd.draw(g_text);
	}


}
/* Init game */
void InitGame()
{
	g_gameOver = 0;
	g_catchCaps = 0;
	// setup text game
	g_text.setFont(g_font);
	g_text.setCharacterSize(30);
	g_text.setPosition(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
	g_text.setColor(sf::Color::Red);
	g_text.setString(sf::String("Game is over!"));
	// snake direction at beginning
	g_dir = Snake::EDirection::RIGHT;
	// setup caps
	for (int i = 0; i < g_CAP_MAX; i++)
	{
		auto& capItem = g_capArray[i];
		float _posX = rand() % (SCREEN_WIDTH - 10) + 5.f;
		float _posY = rand() % (SCREEN_HEIGHT - 10) + 5.f;
		//min = 5.f;
		//max = SCREEN - 5.f;
		capItem.pos.x = _posX;
		capItem.pos.y = _posY;
		capItem.color =	sf::Color::Blue;
		capItem.isCatch = false;
	}
}
/* Check if snake go out of screen or collision itself - game over */
int IsGameOver()
{
	// CHECK OUT OF SCREEN (HEAD)
	const sf::Vector2f& _headPos = g_snake.getHeadPosition() ;
	const float& _TAIL_SIZE = g_snake.getTailSize();
	if (_headPos.x < 0 ||
		_headPos.x + _TAIL_SIZE > SCREEN_WIDTH ||
		_headPos.y < 0 ||
		_headPos.y + _TAIL_SIZE > SCREEN_HEIGHT)
	{
		g_gameOver = 1;
	}
	// CHECK IF SNAKE COLLISON ITSELF
	for (int i = 1; i < g_snake.getTailCount(); i++)
	{
		const auto& _snakeTail = g_snake[i];
		if (_headPos.x == _snakeTail.x && _headPos.y == _snakeTail.y)
			g_gameOver = 1;
	}
	// CHECK IF PLAYER CATCH ALL CAPS
	if (g_catchCaps == g_CAP_MAX)
		g_gameOver = 2;

	if (g_gameOver == 0)
		return 0;
	else if (g_gameOver == 1)
		g_text.setString(sf::String("Game is Over"));
	else if (g_gameOver == 2)
		g_text.setString(sf::String("You won!"));
	return g_gameOver;

		
}
/* Check if snake catch cap - yes then add tail to snake */
bool IsSnakeCatchCap()
{
	const auto& _headPos = g_snake.getHeadPosition();
	const float& _TAIL_SIZE = g_snake.getTailSize();
	for (int i = 0; i < g_CAP_MAX; i++)
	{
		if (g_capArray[i].isCatch == false)
		{
			auto& _cap = g_capArray[i];
			// check collision cap and head snake
			if (_headPos.x + _TAIL_SIZE > _cap.pos.x - _cap.RADIUS &&
				_headPos.x < _cap.pos.x + _cap.RADIUS &&
				_headPos.y + _TAIL_SIZE > _cap.pos.y - _cap.RADIUS &&
				_headPos.y < _cap.pos.y + _cap.RADIUS)
			{
				_cap.isCatch = true;
				g_snake.addTail();
				g_catchCaps++;
				return true;
			}
		}
	}
	return false;
}

////////////////////////////////////////////////////////////////////////////////

/* Draw tiles background*/
void DrawTiles(sf::RenderWindow& Wnd)
{
	const float SIZE_PADD = 20.f;
	const int COUNT_VERTICLE   = (SCREEN_WIDTH / SIZE_PADD);
	const int COUNT_HORIZONTAL = SCREEN_HEIGHT / SIZE_PADD;
	// draw verticle
	sf::Vertex _points[2]
	{

		sf::Vertex(sf::Vector2f(0.f, 0.f), sf::Color::White),
		sf::Vertex(sf::Vector2f(0.f, SCREEN_HEIGHT-1), sf::Color::White)
	};
	//_points[0].position += sf::Vector2f(SIZE_PADD, 0.f);
	//_points[1].position += sf::Vector2f(SIZE_PADD, 0.f);
	Wnd.draw(_points, 2, sf::PrimitiveType::Lines);
	for (int i = 0; i < COUNT_VERTICLE; i++)
	{
		_points[0].position += sf::Vector2f(SIZE_PADD, 0.f);
		_points[1].position += sf::Vector2f(SIZE_PADD, SCREEN_HEIGHT);
		Wnd.draw(_points, 2, sf::PrimitiveType::Lines);
	}

	// draw horizontal
	_points[0].position = sf::Vector2f(0.f, 0.f + SIZE_PADD);
	_points[1].position = sf::Vector2f(SCREEN_WIDTH - 1, 0.f + SIZE_PADD);
	/*for (int i = 0; i < COUNT_HORIZONTAL; i++)
	{
		Wnd.draw(_points, 2, sf::PrimitiveType::Lines);
		_points[0].position += sf::Vector2f(0.f, SIZE_PADD);
		_points[1].position += sf::Vector2f(0.f, SIZE_PADD);

	}*/
}
















