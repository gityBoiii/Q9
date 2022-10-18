#include "Goal.h"
#include "MyEngine.h"
#include "Player.h"
#include <iostream>
#include "Text.h"

using namespace std;

AGoal::AGoal()
{
	Shape = 'G';
	ZOrder = 30;
	CollisionType = ECollisionType::QueryOnly;
	MyColor = { 255, 255, 0, 0 };
	LoadBMP("data/coin.bmp");

	isComplete = false;
	ElapsedTime = 0;
	ExecuteTime = 3000;

}

AGoal::AGoal(int NewX, int NewY)
	: AGoal()
{
	X = NewX;
	Y = NewY;
}

AGoal::~AGoal()
{
}

void AGoal::Tick()
{
	if (isComplete == false)
	{
		for (AActor* Actor : GEngine->GetAllActors())
		{
			if (X == Actor->X && Y == Actor->Y &&
				dynamic_cast<APlayer*>(Actor))
			{
				GEngine->SpawnActor(new AText(200, 200, "스테이지 클리어", 40));
				//GEngine->QuitGame();
				isComplete = true;
				break;
			}
		} 
	}
	else
	{
		ElapsedTime += GEngine->GetWorldDeltaSeconds();
		if (ExecuteTime <= ElapsedTime)
		{
			GEngine->LoadLevel("Level2.txt");
			//GEngine->QuitGame();
		}
	}
}
