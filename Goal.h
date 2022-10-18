#pragma once
#include "Actor.h"

class AGoal : public AActor
{
public:
	AGoal();
	AGoal(int NewX, int NewY);
	~AGoal();

	bool isComplete;
	Uint64 ElapsedTime;
	Uint64 ExecuteTime;

	virtual void Tick() override;
};