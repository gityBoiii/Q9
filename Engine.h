#pragma once
#include <string>
#include <vector>
#include "SDL.h"
#include "SDL_ttf.h"
#include "SDL_mixer.h"

#pragma comment(lib, "SDL2main.lib")
#pragma comment(lib, "SDL2.lib")
#pragma comment(lib, "SDL2_ttf.lib")
#pragma comment(lib, "SDL2_mixer.lib")

using namespace std;

class FWorld;
//class AActor;

//추상 클래스
class Engine
{
public:
	Engine();
	virtual ~Engine();

	virtual void BeginPlay();

	virtual void EndPlay();

	//순수 가상 함수
	virtual void Initialize() = 0;
	virtual void Terminalize() = 0;

	void Run();
	void QuitGame();


	inline static int GetKeyCode()
	{
		return KeyCode;
	}

	vector<class AActor*>& GetAllActors();

	void SDLInit();
	void SDLTerm();

	SDL_Window* MyWindow;
	SDL_Renderer* MyRenderer;
	SDL_Event MyEvent;

	inline const Uint64 GetWorldDeltaSeconds()
	{
		return DeltaSeconds;
	}

	void SpawnActor(AActor* NewActor);
	void LoadLevel(string MapFilename);
	void UnloadLevel();

protected:

	virtual void Input();
	virtual void Tick();
	virtual void Render();

	

	void SortActor();

	FWorld* MyWorld;

	static int KeyCode;

	bool bIsRunning = true;

	Uint64 LastTick;
	Uint64 DeltaSeconds;


};