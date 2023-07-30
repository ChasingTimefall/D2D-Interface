#pragma once

#include "../instance.h"
#include "../../tools/vector.h"

#define MAX_FONTS 50
#define MAX_RENDEROBJECTS 50000

template<class Interface>
inline void SafeRelease(
	Interface** ppInterfaceToRelease)
{
	if (*ppInterfaceToRelease != NULL)
	{
		(*ppInterfaceToRelease)->Release();
		(*ppInterfaceToRelease) = NULL;
	}
}

enum EFontIndex {
	FONTINDEX_DEFAULT = 0,
	FONTINDEX_ELEMENTTITLE,
	FONTINDEX_MAX
};

struct TFont {
	IDWriteTextFormat* Format = nullptr;
	DWORD FontSize;
};

enum ERenderObject {
	RENDER_OBJECT_RECTANGLE = 0,
	RENDER_OBJECT_RECTANGLE_FILLED,
	RENDER_OBJECT_TEXT,
	RENDER_OBJECT_LINE,
	RENDER_OBJECT_MAX
};
struct TRenderObject {
	ERenderObject ObjectType;
	float flRed = 0.0f;
	float flGreen = 0.0f;
	float flBlue = 0.0f;
	float flAlpha = 0.0f;
	float flThickness = 0.0f;
	TVector2D vecPosition;
	TVector2D vecPositionOrSize;
	TFont* Font = nullptr;
	std::string szText;
};

class CDrawList {
public:
	CDrawList(CD2D1Render* _OwningRenderer);

	void DrawLine(const TVector2D& vecMin, const TVector2D& vecMax, int r, int g, int b, int a, float flThickness);
	void DrawRectangle(const TVector2D& vecMin, const TVector2D& vecSize, int r, int g, int b, int a, float flThickness);
	void DrawRectangleFilled(const TVector2D& vecMin, const TVector2D& vecMax, int r, int g, int b, int a);
	void RenderText(TFont* pText, std::string szString, TVector2D vecPos, int r, int g, int b, int a, bool bAlignCenter = false);

	void Render();
private:
	CD2D1Render* OwningRenderer = nullptr;
	TArray<TRenderObject, MAX_RENDEROBJECTS> DrawList;
};

class CD2D1Render {
public:

	CD2D1Render() {
		hWindow = nullptr;
		Factory = nullptr;
		RenderTarget = nullptr;
		Brush = nullptr;
		WriteFactory = nullptr;
	}

	void Construct(HWND hWindow , bool bEnableVsync);
	~CD2D1Render();

	void BeginScene();
	void EndScene();
	TFont* GetFont(EFontIndex Index = FONTINDEX_DEFAULT);
	int GetMaxTextLength(const TVector2D& vecRegionSize, TFont* Font, const std::string& szText);
	TVector2D GetTextSize(TFont* Font, const std::string& szText ,int iMaxWidth = -1,int iMaxHeight = -1);
public:
	void DrawLine(const TVector2D& vecMin, const TVector2D& vecMax, float r, float g, float b, float a, float flThickness);
	void DrawRectangle(const TVector2D& vecMin, const TVector2D& vecSize, float r, float g, float b, float a, float flThickness);
	void DrawRectangleFilled(const TVector2D& vecMin, const TVector2D& vecMax, float r, float g, float b, float a);
	void RenderText(IDWriteTextFormat* pTextFormat, std::string szString, TVector2D vecPos, float r, float g, float b, float a);
public:
	TArray<TFont, MAX_FONTS> Fonts;
	CDrawList* BackgroundList = nullptr;
	CDrawList* ForegroundList = nullptr;
public:
	HWND hWindow;
	ID2D1Factory* Factory;
	ID2D1HwndRenderTarget* RenderTarget;
	ID2D1SolidColorBrush* Brush;
	IDWriteFactory* WriteFactory = nullptr;

};
