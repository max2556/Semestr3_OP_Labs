#pragma once
#include <SDL.h>
#include <vector>
#include "Figure.h"

class Leader : public Object
{
public:
	Leader(Figure* figure);

	void update();

public:
	void setSpeed(double newSpeed);
	void appendPoint(SDL_FPoint& newPoint);

public:
	std::vector<SDL_FPoint> trajectoryPoints;
	double movementSpeed;
	SDL_FPoint direction;

private:
	Figure* moveable;
	size_t currentTrajectoryPointIndex;
	size_t nextTrajectoryPointIndex;
	double arrivingAccuracy = 0.001;

private:
	void chooseNextPoint();
	void changeDirection();

};

