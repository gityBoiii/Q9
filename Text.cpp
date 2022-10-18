#include "Text.h"
#include "MyEngine.h"
#include <Windows.h>

AText::AText()
{
	Content = "";
}

AText::AText(int NewX, int NewY, string NewContent, int NewFontSize)
{
	X = NewX;
	Y = NewY;
	Content = NewContent;
	FontSize = NewFontSize;
	MyColor = { 255, 255, 255, 0 };
	ZOrder = 100;

	Font = TTF_OpenFont("./Data/NGULIM.TTF", FontSize);

	wstring UniCode(Content.length(), 0);
	MultiByteToWideChar(CP_ACP, 0, Content.c_str(), (int)Content.length(),
		(LPWSTR)UniCode.c_str(), (int)Content.length() + 1);

//	MySurface = TTF_RenderText_Solid(Font, Content.c_str(), MyColor);
	SDL_Color BackgroudColor = { 255, 0, 0, 0 };

	MySurface = TTF_RenderUNICODE_LCD(Font, (Uint16*)UniCode.c_str(),
		MyColor, BackgroudColor);

	//MySurface = TTF_RenderUNICODE_Shaded(Font, (Uint16*)UniCode.c_str(), 
	//	MyColor, BackgroudColor);

	MyTexture = SDL_CreateTextureFromSurface(GEngine->MyRenderer,
		MySurface);
}

AText::~AText()
{
	TTF_CloseFont(Font);
}

void AText::Render()
{
	SDL_Rect RenderRect = { X, Y, MySurface->w, MySurface->h };
	SDL_RenderCopy(GEngine->MyRenderer, MyTexture, nullptr, &RenderRect);
}
