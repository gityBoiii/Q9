#include "Floor.h"

AFloor::AFloor()
{
	Shape = ' ';
	ZOrder = 10;
	MyColor = { 100, 0, 0, 0 };
	LoadBMP("data/floor.bmp");

}

AFloor::AFloor(int NewX, int NewY)
	: AFloor()
{
	X = NewX;
	Y = NewY;
}

AFloor::~AFloor()
{
}