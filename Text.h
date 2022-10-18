#pragma once
#include "Actor.h"
#include "SDL_ttf.h"
#include <string>

using namespace std;

class AText : public AActor
{
public:
	AText();
	AText(int X, int Y, string NewContent, int NewFontSize);
	~AText();

	string Content;
	int FontSize;

	TTF_Font* Font;

	virtual void Render() override;
};

