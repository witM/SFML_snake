#include "Assets.h"


Snake::Snake()
{
	// begin of snake's head
	float _posX = 500.f;
	float _posY = 100.f;
	tailCount = 3;
	// set head snakeArray[0]
	snakeArray[0].color = sf::Color::Red;
	snakeArray[0].x = _posX;
	snakeArray[0].y = _posY;
	snakeArray[0].size = SIZE_RECT;
	// set rest of snake's tail
	for (int i = 1; i < snakeArray.size(); i++)
	{
		_posX -= (SIZE_RECT + PADD);
		auto& _tail = snakeArray[i];
		_tail.size = SIZE_RECT;
		_tail.color = sf::Color::Green;
		_tail.x = _posX;
		_tail.y = _posY;
		//item.setOutlineThickness(0.5f);
		//item.setOutlineColor(sf::Color::Red);
	}
	//
}

/* make snake moving per frame */

void Snake::tick(EDirection Dir)
{
	dir = Dir;
	// SET HEAD DIRECTION
	float _xSpeed;
	float _ySpeed;
	if (dir == EDirection::LEFT)
	{
		_xSpeed = -20.f - PADD;
		_ySpeed = 0.f;
	}
	else if (dir == EDirection::UP)
	{
		_xSpeed = 0.f;
		_ySpeed = -20.f - PADD;
	}
	else if (dir == EDirection::RIGHT)
	{
		_xSpeed = 20.f + PADD;
		_ySpeed = 0.f;
	}
	else if (dir == EDirection::DOWN)
	{
		_xSpeed = 0.f;
		_ySpeed = 20.f + PADD;
	}
	// MAKE TAILS MOVE BY FOLLOWING HEAD
	float _headX = snakeArray[0].x;
	float _headY = snakeArray[0].y;
	snakeArray[0].x += _xSpeed;
	snakeArray[0].y += _ySpeed;
	for (int i = 1; i < snakeArray.size(); i++)
	{
		float _secX = snakeArray[i].x;
		float _secY = snakeArray[i].y;
		snakeArray[i].x = _headX;
		snakeArray[i].y = _headY;
		_headX = _secX;
		_headY = _secY;
	}

	//Sleep(200);
}

/* draw snake */

void Snake::draw(sf::RenderWindow & Wnd)
{
	sf::RectangleShape _s;
	_s.setSize(sf::Vector2f(SIZE_RECT, SIZE_RECT));
	for (int i = 0; i < tailCount; i++)
	{
		_s.setFillColor(snakeArray[i].color);
		_s.setPosition(snakeArray[i].x, snakeArray[i].y);
		Wnd.draw(_s);
	}
}

/* add tail to back snake */

void Snake::addTail()
{
	/*NOTE: adding tail to snake is just increment tailCount and by that next tail in snakeArray begin following snake (Tick)*/
	
	//snakeArray[tailCount].color = sf::Color::Green;
	/*if (dir == EDirection::LEFT)
	{
	snakeArray[tailCount].x = snakeArray[tailCount - 1].x + SIZE_RECT + PADD;
	snakeArray[tailCount].y = snakeArray[tailCount - 1].y;
	}
	else if (dir == EDirection::UP)
	{
	snakeArray[tailCount].x = snakeArray[tailCount - 1].x;
	snakeArray[tailCount].y = snakeArray[tailCount - 1].y + SIZE_RECT + PADD;
	}
	else if (dir == EDirection::RIGHT)
	{
	snakeArray[tailCount].x = snakeArray[tailCount - 1].x - SIZE_RECT - PADD;
	snakeArray[tailCount].y = snakeArray[tailCount - 1].y;
	}
	else if (dir == EDirection::DOWN)
	{
	snakeArray[tailCount].x = snakeArray[tailCount - 1].x;
	snakeArray[tailCount].y = snakeArray[tailCount - 1].y - SIZE_RECT - PADD;
	}*/
	tailCount++;
}
