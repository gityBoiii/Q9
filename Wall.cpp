#include "Wall.h"

AWall::AWall()
{
	Shape = '*';
	ZOrder = 20;
	CollisionType = ECollisionType::PhysicsOnly;
	MyColor = { 0, 0, 0, 0 };
	LoadBMP("data/wall.bmp");
}

AWall::AWall(int NewX, int NewY)
	: AWall()
{
	X = NewX;
	Y = NewY;
}

AWall::~AWall()
{
}

