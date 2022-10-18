#pragma once
#include "Actor.h"
class AMonster : public AActor
{
public:
	AMonster();
	AMonster(int NewX, int NewY);
	~AMonster();

	virtual void Tick() override;
	bool PredictCanMove();

	Uint64 ElapsedTime = 0;
	Uint64 ExecuteTime = 0;
};

