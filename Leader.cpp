#include "Leader.h"
#include "Utils.h"
#include "Application.h"
#include "CircleFigure.h"

Leader::Leader(Figure& figure) :
	moveable(figure)
{}

Leader::Leader(Figure& figure, const std::vector<SDL_FPoint>& points)
	:moveable(figure)
{
	trajectoryPoints = points;
	chooseNextPoint();
	moveable.currentPosition = trajectoryPoints[currentTrajectoryPointIndex];
}

void Leader::update()
{
	SDL_FPoint deltaPos = direction * movementSpeed * Statics::getInstance()->getDeltaTime();
	moveable.currentPosition += deltaPos;

	SDL_FPoint vectorToDest = trajectoryPoints[nextTrajectoryPointIndex] - moveable.currentPosition;

	long double dot = dotProduct(vectorToDest, direction);
	if (dot <= 0)
	{
		chooseNextPoint();
		moveable.currentPosition = trajectoryPoints[currentTrajectoryPointIndex];
	}
}

void Leader::appendPoint(const SDL_FPoint& newPoint)
{
	trajectoryPoints.push_back(newPoint);
}

void Leader::setSpeed(const double newSpeed)
{
	movementSpeed = newSpeed;
}

void Leader::chooseNextPoint()
{
	if (currentTrajectoryPointIndex == 0 && nextTrajectoryPointIndex == 0)
	{
		currentTrajectoryPointIndex = 0;
		nextTrajectoryPointIndex = currentTrajectoryPointIndex + 1;
	}

	currentTrajectoryPointIndex = nextTrajectoryPointIndex;
	nextTrajectoryPointIndex = (nextTrajectoryPointIndex + 1) % trajectoryPoints.size();

	changeDirection();
	changeMoveableColor();  //< Выбивается из концепции смешного обобщения ради исполнения цели
}

void Leader::changeDirection()
{
	direction = (trajectoryPoints[nextTrajectoryPointIndex] - trajectoryPoints[currentTrajectoryPointIndex]);
	//direction = moveable.currentPosition - trajectoryPoints[nextTrajectoryPointIndex];
}

void Leader::changeMoveableColor()
{
	moveable.fillColor.r = (moveable.fillColor.r + 10) % 255;
	moveable.fillColor.g = (moveable.fillColor.g + 17) % 255;
	moveable.fillColor.b = (moveable.fillColor.b + 26) % 255;
}
