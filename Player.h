#pragma once
#include "Actor.h"


class APlayer : public AActor
{
public:
	APlayer();
	APlayer(int NewX, int NewY);

	~APlayer();

	virtual void Tick() override;
	bool PredictCanMove();

	virtual void Render() override;

	int SpriteXIndex = 0;
	int SpriteYIndex = 0;

	Uint64 ElapsedTime = 0;
	Uint64 ExecuteTime = 0;
};

