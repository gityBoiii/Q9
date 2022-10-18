#pragma once
#include <vector>
using namespace std;

class AActor;

class FWorld
{
public:
	FWorld();
	~FWorld();

	void Terminate();

	vector<AActor*> ActorList;
	void SpawnActor(AActor* NewActor);
	void DestroyActor(AActor* DeleteActor);

	void Render();
	void Tick();

	void BeginPlay();
	void EndPlay();

};

