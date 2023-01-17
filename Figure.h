#pragma once
#include "Object.h"

constexpr SDL_Color DEFAULT_FILL_COLOR{ 70, 94, 140 };		 //Dark blue
constexpr SDL_Color DEFAULT_OUTLINE_COLOR{ 115, 148, 191 };  //Light blue

class Figure : public Object
{
public:
	Figure();
	~Figure() {};

	virtual void draw(SDL_Renderer* renderer) override{};
	virtual void update() override {};

	void setPosition(float x, float y);
	void setFillColor(SDL_Color& newColor);
	void setOutlineColor(SDL_Color& newColor);


	SDL_Color fillColor = DEFAULT_FILL_COLOR;
	SDL_Color outlineColor = DEFAULT_OUTLINE_COLOR;

	SDL_FPoint currentPosition;
};

