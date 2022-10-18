//#include <conio.h> //_getch()
#include <fstream>
#include <algorithm>

#include "Engine.h"
#include "World.h"
#include "Player.h"
#include "Floor.h"
#include "Wall.h"
#include "Goal.h"
#include "Monster.h"
#include "Text.h"


using namespace std;

int Engine::KeyCode = 0;

Engine::Engine()
{
	MyWorld = new FWorld();
	bIsRunning = true;

	SDLInit();
	TTF_Init();
	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
}

void Engine::SDLInit()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		SDL_Log("SDL_Init_Error");
		exit(-1);
	}

	MyWindow = SDL_CreateWindow("MyGame", 100, 100, 600, 600, SDL_WINDOW_VULKAN);
	MyRenderer = SDL_CreateRenderer(MyWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE);
	//MyRenderer = SDL_CreateRenderer(MyWindow, -1, SDL_RENDERER_SOFTWARE | SDL_RENDERER_TARGETTEXTURE);
}

void Engine::SDLTerm()
{
	TTF_Quit();
	SDL_DestroyRenderer(MyRenderer);
	SDL_DestroyWindow(MyWindow);

	SDL_Quit();
}

Engine::~Engine()
{
	delete MyWorld;

	SDLTerm();
}

void Engine::BeginPlay()
{
	MyWorld->BeginPlay();
}

void Engine::EndPlay()
{
	MyWorld->EndPlay();
}

void Engine::Run()
{
	BeginPlay();

	while (bIsRunning)
	{
		DeltaSeconds = SDL_GetTicks64() - LastTick;
		Input();
		Tick();
		LastTick = SDL_GetTicks64();
		Render();
	}

	EndPlay();
}

void Engine::QuitGame()
{
	bIsRunning = false;
}

void Engine::LoadLevel(string MapFilename)
{
	UnloadLevel();

	char Data[100];
	ifstream MapFile(MapFilename);

	int Y = 0;
	while (MapFile.getline(Data, 100))
	{
		for (int X = 0; X < strlen(Data); ++X)
		{
			if (Data[X] == '*')
			{
				MyWorld->SpawnActor(new AWall(X, Y));
				MyWorld->SpawnActor(new AFloor(X, Y));
			}
			else if (Data[X] == 'P')
			{
				MyWorld->SpawnActor(new APlayer(X, Y));
				MyWorld->SpawnActor(new AFloor(X, Y));
			}
			else if (Data[X] == 'M')
			{
				MyWorld->SpawnActor(new AMonster(X, Y));
				MyWorld->SpawnActor(new AFloor(X, Y));
			}
			else if (Data[X] == 'G')
			{
				MyWorld->SpawnActor(new AGoal(X, Y));
				MyWorld->SpawnActor(new AFloor(X, Y));
			}
			else if (Data[X] == ' ')
			{
				MyWorld->SpawnActor(new AFloor(X, Y));
			}
		}
		Y++;
	}
	MapFile.close();

	//Sort
	SortActor();
}

void Engine::UnloadLevel()
{
	MyWorld->Terminate();
}

void Engine::SortActor()
{
	sort(MyWorld->ActorList.begin(), MyWorld->ActorList.end(), AActor::Compare);
	//for (int i = 0; i < MyWorld->ActorList.size(); ++i)
	//{
	//	for (int j = i; j < MyWorld->ActorList.size(); ++j)
	//	{
	//		if (MyWorld->ActorList[i]->ZOrder > MyWorld->ActorList[j]->ZOrder)
	//		{
	//			AActor* Temp = MyWorld->ActorList[i];
	//			MyWorld->ActorList[i] = MyWorld->ActorList[j];
	//			MyWorld->ActorList[j] = Temp;
	//		}
	//	}
	//}
}

vector<AActor*>& Engine::GetAllActors()
{
	return MyWorld->ActorList;
}

void Engine::SpawnActor(AActor* NewActor)
{
	MyWorld->SpawnActor(NewActor);
}

void Engine::Input()
{
	SDL_PollEvent(&MyEvent);
//	Engine::KeyCode = _getch();
}

void Engine::Tick()
{
	if (MyEvent.type == SDL_QUIT)
	{
		bIsRunning = false;
	}

	MyWorld->Tick();

	//SDL_Log("%f",  (double)1000 / (double)DeltaSeconds);
}

void Engine::Render()
{
	//system("cls");
	SDL_Color BackgroundColor = { 0, 0, 0 ,0 };

	SDL_SetRenderDrawColor(MyRenderer, BackgroundColor.r, BackgroundColor.g, BackgroundColor.b, BackgroundColor.a);
	SDL_RenderClear(MyRenderer);


	MyWorld->Render();


	SDL_RenderPresent(MyRenderer);


}
