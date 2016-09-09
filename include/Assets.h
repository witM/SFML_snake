#pragma once

#include <array>
#include "SFML\Graphics.hpp"

/* SNAKE CLASS */
class Snake
{

public:
	enum EDirection { LEFT, UP, RIGHT, DOWN, NONE };
	//
	struct TAIL
	{
		float x, y;
		float size;
		sf::Color color;
	};
public:
	Snake();
	// GETTERS // 
	/* get head position */
	const sf::Vector2f getHeadPosition() const { return sf::Vector2f(snakeArray[0].x, snakeArray[0].y); }
	/* get tail size */
	const float& getTailSize() const { return snakeArray[0].size; }
	/* get tail count in snake */
	const int& getTailCount() const { return tailCount; }
	/* get tail by index */
	const Snake::TAIL& operator[](int index) const { return snakeArray[index]; }
	/* make snake moving per frame */
	void tick(EDirection Dir);
	/* draw snake */
	void draw(sf::RenderWindow& Wnd);
	/* add tail to back snake */
	void addTail();

private:
	const float SIZE_RECT = 20.f;
	const float PADD = 5.f;
	int tailCount;
	std::array<Snake::TAIL, 100> snakeArray;
	EDirection dir;
};
/* CAP STRUCT */
struct CAP
{
	/*const float left() const { return cap.getPosition().x - cap.getRadius(); }
	const float up() const { return cap.getPosition().y - cap.getRadius(); }
	const float right() const { return cap.getPosition().x + cap.getRadius(); }
	const float down() const { return cap.getPosition().y + cap.getRadius(); }*/
	sf::Vector2f pos;
	const float RADIUS = 10.f;
	bool isCatch;
	sf::Color color;
};