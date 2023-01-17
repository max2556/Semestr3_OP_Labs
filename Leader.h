#pragma once
#include <SDL.h>
#include <vector>
#include "Figure.h"

class Leader : public Object
{
public:
	explicit Leader(Figure& figure);
	explicit Leader(Figure& figure, const std::vector<SDL_FPoint>& points);

	void draw(SDL_Renderer* renderer) override {
		moveable.draw(renderer);
	}
	void update() override;

public:
	void setSpeed(const double newSpeed);
	void appendPoint(const SDL_FPoint& newPoint);

public:
	std::vector<SDL_FPoint> trajectoryPoints;
	double movementSpeed;
	SDL_FPoint direction;
	Figure& moveable;		//<---- управляет вот этим

private:
	size_t currentTrajectoryPointIndex = 0;
	size_t nextTrajectoryPointIndex = 0;
	double arrivingAccuracy = 0.001;

private:
	void chooseNextPoint();
	void changeDirection();
	void changeMoveableColor();
};

