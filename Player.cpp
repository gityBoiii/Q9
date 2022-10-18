#include "Player.h"
#include <iostream>
#include "MyEngine.h"

using namespace std;

APlayer::APlayer()
{
	Shape = 'P';
	ZOrder = 40;
	CollisionType = ECollisionType::CollisionEnable;
	MyColor = { 0, 255, 0, 0 };
	MyColorKey = { 255, 0, 255, 0 };
	ElapsedTime = 0;
	ExecuteTime = 200;
	SpriteXIndex = 0;
	SpriteYIndex = 0;

	LoadBMP("data/player.bmp");
}

APlayer::APlayer(int NewX, int NewY)
	: APlayer()
{
	X = NewX;
	Y = NewY;
}

APlayer::~APlayer()
{
}

void APlayer::Tick()
{
	ElapsedTime += GEngine->GetWorldDeltaSeconds();
	if (ExecuteTime <= ElapsedTime)
	{
		ElapsedTime = 0;
		SpriteXIndex++;
		SpriteXIndex %= 5;
	}

	if (GEngine->MyEvent.type != SDL_KEYDOWN)
	{
		return;
	}

	switch (GEngine->MyEvent.key.keysym.sym)
	{
	case SDLK_w:
		SpriteYIndex = 2;
		Y--;
		if (!PredictCanMove())
		{
			Y++;
		}
		break;

	case SDLK_a:
		SpriteYIndex = 0;
		X--;
		if (!PredictCanMove())
		{
			X++;
		}
		break;

	case SDLK_s:
		SpriteYIndex = 3;
		Y++;
		if (!PredictCanMove())
		{
			Y--;
		}
		break;

	case SDLK_d:
		SpriteYIndex = 1;
		X++;
		if (!PredictCanMove())
		{
			X--;
		}
		break;

	case SDLK_ESCAPE:
		GEngine->QuitGame();

		break;
	}
}

bool APlayer::PredictCanMove()
{
	for (AActor* Actor : GEngine->GetAllActors())
	{
		if (X == Actor->X && Y == Actor->Y &&
			dynamic_cast<APlayer*>(Actor) == nullptr)
		{
			if (CheckHit(Actor))
			{
				return false;
			}
		}
	}

	return true;
}

void APlayer::Render()
{
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
		int SpriteSize = MySurface->w / 5;
		SDL_Rect SourceRect = { SpriteSize * SpriteXIndex,
			SpriteSize * SpriteYIndex,
			SpriteSize, SpriteSize };
		SDL_RenderCopy(GEngine->MyRenderer, MyTexture, &SourceRect, &MyRect);
	}

}
