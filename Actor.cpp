#include "Actor.h"
#include <iostream>
#include <Windows.h>
#include "MyEngine.h"

using namespace std;

AActor::AActor() :
	X(1), Y(1), Shape(' '), CollisionType(ECollisionType::NoCollision), ZOrder(10),
	MyColor(SDL_Color{ 255, 255, 255, 0 }), TileSize(60), MySurface(nullptr), MyTexture(nullptr), MyColorKey(SDL_Color{255, 255, 255, 0})
{
	//X = 1;
	//Y = 1;
	//Shape = ' ';
}

AActor::AActor(int NewX, int NewY)
	: AActor()
{
	X = NewX;
	Y = NewY;
}

AActor::~AActor()
{
	SDL_FreeSurface(MySurface);
	SDL_DestroyTexture(MyTexture);
}

void AActor::Render()
{
	//Text
	//COORD Currrent;
	//Currrent.X = X;
	//Currrent.Y = Y;
	//SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Currrent);
	//cout << Shape;

	//2D
	SDL_Rect MyRect = SDL_Rect({ X * TileSize, Y * TileSize, TileSize, TileSize });
	if (MyTexture == nullptr)
	{
		SDL_SetRenderDrawColor(GEngine->MyRenderer, MyColor.r,
			MyColor.g, MyColor.b, MyColor.a);
		SDL_RenderFillRect(GEngine->MyRenderer, &MyRect);
		//SDL_RenderDrawPoint(GEngine->MyRenderer, X * TileSize, Y * TileSize);
	}
	else
	{
		SDL_RenderCopy(GEngine->MyRenderer, MyTexture, nullptr, &MyRect);
	}


}

void AActor::Tick()
{
}

void AActor::BeginPlay()
{
}

void AActor::EndPlay()
{
}

bool AActor::CheckHit(AActor* Other)
{
	if ((int)Other->CollisionType & (int)ECollisionType::PhysicsOnly)
	{
		if (Other->X == X && Other->Y == Y)
		{
			return true;
		}
	}

	return false;
}

void AActor::LoadBMP(string Filename)
{
	MySurface = SDL_LoadBMP(Filename.c_str());

	SDL_SetColorKey(MySurface, SDL_TRUE,
		SDL_MapRGB(MySurface->format, MyColorKey.r, MyColorKey.g, MyColorKey.b));

	MyTexture = SDL_CreateTextureFromSurface(GEngine->MyRenderer, MySurface);
}
