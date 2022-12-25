#include "Leader.h"
#include "Utils.h"
#include "Application.h"

Leader::Leader(Figure* figure)
{
	moveable = figure;
}

void Leader::update()
{
	SDL_FPoint deltaPos = direction * movementSpeed * Application::Statics::getDeltaTime();
	moveable->currentPosition += deltaPos;
}

void Leader::appendPoint(SDL_FPoint& newPoint)
{
	trajectoryPoints.push_back(newPoint);
}

void Leader::setSpeed(double newSpeed)
{
	movementSpeed = newSpeed;
}

void Leader::chooseNextPoint()
{
	if (currentTrajectoryPointIndex == -1)
	{
		currentTrajectoryPointIndex = 0;
		nextTrajectoryPointIndex = currentTrajectoryPointIndex + 1;
	}

	currentTrajectoryPointIndex = nextTrajectoryPointIndex;
	nextTrajectoryPointIndex = (nextTrajectoryPointIndex + 1) % trajectoryPoints.size();

	changeDirection();
}

void Leader::changeDirection()
{
	direction = (trajectoryPoints[nextTrajectoryPointIndex] - trajectoryPoints[currentTrajectoryPointIndex]);
}

