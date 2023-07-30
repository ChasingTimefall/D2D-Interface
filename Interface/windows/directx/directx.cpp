#include "directx.h"
#include "../../tools/vector.h"
#include "../../tools/util.h"
#include "../../tools/xorstr.h"

CDrawList::CDrawList(CD2D1Render* _OwningRenderer) {
	OwningRenderer = _OwningRenderer;
}

void CDrawList::DrawLine(const TVector2D& vecMin, const TVector2D& vecMax, int r, int g, int b, int a, float flThickness) {
	DrawList.AddBack(TRenderObject{ RENDER_OBJECT_LINE,(float)r / 255.f, (float)g / 255.f, (float)b / 255.f, (float)a / 255.f
	,flThickness  ,vecMin,vecMax , nullptr });
}
void CDrawList::DrawRectangle(const TVector2D& vecMin, const TVector2D& vecSize, int r, int g, int b, int a, float flThickness) {
	DrawList.AddBack(TRenderObject{ RENDER_OBJECT_RECTANGLE,(float)r / 255.f, (float)g / 255.f, (float)b / 255.f, (float)a / 255.f
,flThickness  ,vecMin,vecSize , nullptr });
}
void CDrawList::DrawRectangleFilled(const TVector2D& vecMin, const TVector2D& vecMax, int r, int g, int b, int a) {
	DrawList.AddBack(TRenderObject{ RENDER_OBJECT_RECTANGLE_FILLED,(float)r / 255.f, (float)g / 255.f, (float)b / 255.f, (float)a / 255.f
,0.0f  ,vecMin,vecMax , nullptr });
}

void CDrawList::RenderText(TFont* pText, std::string szString, TVector2D vecPos, int r, int g, int b, int a, bool bAlignCenter) {
	
	TVector2D vecPosition = vecPos;

	if (bAlignCenter)
	{
		TVector2D vecAlignment = OwningRenderer->GetTextSize(pText,szString);
		vecPosition -= vecAlignment / 2.f;
	}

	auto Object = DrawList.AddBack(TRenderObject{ RENDER_OBJECT_TEXT,(float)r / 255.f, (float)g / 255.f, (float)b / 255.f, (float)a / 255.f
,0.0f  ,vecPosition,TVector2D(), pText });

	if (Object)
		Object->szText = szString;

}

void CDrawList::Render() {

	if (DrawList.IsEmpty())
		return;

	for (int iCurrent = 0; iCurrent < DrawList.ArraySize(); iCurrent++)
	{
		auto Object = DrawList[iCurrent];

		switch (Object->ObjectType)
		{
		    case RENDER_OBJECT_RECTANGLE:
			{
				OwningRenderer->DrawRectangle(Object->vecPosition, Object->vecPositionOrSize, Object->flRed, Object->flGreen, Object->flBlue, Object->flAlpha, Object->flThickness);
				break;
			}
			case RENDER_OBJECT_RECTANGLE_FILLED:
			{
				OwningRenderer->DrawRectangleFilled(Object->vecPosition, Object->vecPositionOrSize, Object->flRed, Object->flGreen, Object->flBlue, Object->flAlpha);
				break;
			}
			case RENDER_OBJECT_TEXT:
			{
				OwningRenderer->RenderText(Object->Font->Format, Object->szText, Object->vecPosition, Object->flRed, Object->flGreen, Object->flBlue, Object->flAlpha);
				Object->szText.clear();
				break;
			}
			case RENDER_OBJECT_LINE:
			{
				OwningRenderer->DrawLine(Object->vecPosition, Object->vecPositionOrSize, Object->flRed, Object->flGreen, Object->flBlue, Object->flAlpha, Object->flThickness);
				break;
			}
			default:
				break;
		}
	}

	DrawList.Clear();
}



void CD2D1Render::DrawLine(const TVector2D& vecMin, const TVector2D& vecMax, float r, float g, float b, float a, float flThickness) {
	const auto rectangle = D2D1::RectF(vecMin.x, vecMin.y, vecMax.x, vecMax.y);
	Brush->SetColor(D2D1::ColorF(r, g, b, a));
	RenderTarget->DrawLine(D2D1::Point2F(vecMin.x, vecMin.y), D2D1::Point2F(vecMax.x, vecMax.y),Brush, flThickness);
}

void CD2D1Render::DrawRectangle( const TVector2D& vecMin, const TVector2D& vecSize, float r, float g, float b, float a, float flThickness) {
	const auto rectangle = D2D1::RectF(vecMin.x, vecMin.y, vecMin.x + vecSize.x, vecMin.y + vecSize.y);
	Brush->SetColor(D2D1::ColorF(r, g, b, a));
	RenderTarget->DrawRectangle(rectangle, Brush, flThickness);
}

void CD2D1Render::DrawRectangleFilled( const TVector2D& vecMin, const TVector2D& vecSize, float r, float g, float b, float a) {
	const auto rectangle = D2D1::RectF(vecMin.x, vecMin.y, vecMin.x + vecSize.x, vecMin.y + vecSize.y);
	Brush->SetColor(D2D1::ColorF(r, g, b, a));
	RenderTarget->FillRectangle(rectangle, Brush);
}

void CD2D1Render::RenderText( IDWriteTextFormat* pTextFormat, std::string szString, TVector2D vecPos, float r, float g, float b, float a)
{
	vecPos.x = floor(vecPos.x);
	vecPos.y = floor(vecPos.y);

	std::wstring wString = TUtilities::MultiByteToWide(szString);

	D2D1_SIZE_F renderTargetSize = RenderTarget->GetSize();

	Brush->SetColor(D2D1::ColorF(r, g, b, a));
	RenderTarget->SetTextAntialiasMode(D2D1_TEXT_ANTIALIAS_MODE_CLEARTYPE);

	RenderTarget->DrawText(wString.c_str(), wString.size(), pTextFormat, D2D1::RectF((int)vecPos.x, (int)vecPos.y, (int)renderTargetSize.width, (int)renderTargetSize.height),Brush , D2D1_DRAW_TEXT_OPTIONS_NONE, DWRITE_MEASURING_MODE_NATURAL);
}

void CD2D1Render::BeginScene()
{
	RenderTarget->BeginDraw();
	RenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());
	RenderTarget->Clear(D2D1::ColorF(0, 0, 0, 0));
}
TFont* CD2D1Render::GetFont(EFontIndex Index) {
	return Fonts[Index];
}

void CD2D1Render::EndScene()
{
	RenderTarget->EndDraw();
}

int CD2D1Render::GetMaxTextLength(const TVector2D& vecRegionSize, TFont* Font, const std::string& szText) {

	int iMaxCharacterLength = 0;

	std::string szString;

	for (auto Current : szText)
	{
		    szString.append(1,(char)Current);

		TVector2D vecAlignment = GetTextSize(Font, szString);
		
		if (vecAlignment.x >= vecRegionSize.x)
			break;

		iMaxCharacterLength += 1;
    }

	return iMaxCharacterLength;
}

TVector2D CD2D1Render::GetTextSize(TFont* Font, const std::string& szText, int iMaxWidth, int iMaxHeight) {

	IDWriteTextLayout* Layout;

	std::wstring szWideText = TUtilities::MultiByteToWide(szText);

	if (WriteFactory->CreateTextLayout(szWideText.c_str(), szWideText.size() , Font->Format, iMaxWidth == -1 ? 1000 : iMaxWidth, iMaxHeight == -1 ? Font->FontSize : iMaxHeight, &Layout) == S_OK) {
		DWRITE_TEXT_METRICS Metrics;
		Layout->GetMetrics(&Metrics);
		SafeRelease(&Layout);
		return TVector2D(Metrics.widthIncludingTrailingWhitespace, Metrics.height);
	}

	return TVector2D();

}

void CD2D1Render::Construct(HWND hWindow, bool bEnableVsync) {

	BackgroundList = new CDrawList(this);
    ForegroundList = new CDrawList(this);

	HRESULT hr = S_OK;
	hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &Factory);

	if (SUCCEEDED(hr))
	{
		DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(IDWriteFactory), reinterpret_cast<IUnknown**>((&WriteFactory)));

		auto pDefaultFont = Fonts.AddBack(TFont());
		pDefaultFont->FontSize = 9;

		WriteFactory->CreateTextFormat(
			skCrypt(L"Verdana"), NULL, DWRITE_FONT_WEIGHT_SEMI_LIGHT, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_ULTRA_CONDENSED, pDefaultFont->FontSize, (skCrypt(L"")), &pDefaultFont->Format);
	
		auto pElementTitleFont = Fonts.AddBack(TFont());
		pElementTitleFont->FontSize = 10;

		WriteFactory->CreateTextFormat(
			skCrypt(L"Verdana"), NULL, DWRITE_FONT_WEIGHT_SEMI_LIGHT, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_ULTRA_CONDENSED, pElementTitleFont->FontSize, (skCrypt(L"")), &pElementTitleFont->Format);

		RECT rc;
		GetClientRect(hWindow, &rc);

		D2D1_SIZE_U size = D2D1::SizeU(
			rc.right - rc.left,
			rc.bottom - rc.top);

		HRESULT hr = Factory->CreateHwndRenderTarget(
			D2D1::RenderTargetProperties(D2D1_RENDER_TARGET_TYPE_HARDWARE, D2D1::PixelFormat(DXGI_FORMAT_UNKNOWN, D2D1_ALPHA_MODE_PREMULTIPLIED)),
			D2D1::HwndRenderTargetProperties(hWindow, size, bEnableVsync ? D2D1_PRESENT_OPTIONS_NONE : D2D1_PRESENT_OPTIONS_IMMEDIATELY),
			&RenderTarget);
	
		if (SUCCEEDED(hr))
		{
			hr = RenderTarget->CreateSolidColorBrush(
				D2D1::ColorF(D2D1::ColorF::White),
				&Brush
			);
		}

	}
}

CD2D1Render::~CD2D1Render() {
	SafeRelease(&Factory);
	SafeRelease(&RenderTarget);
	SafeRelease(&Brush);
	SafeRelease(&WriteFactory);

	delete ForegroundList;
	delete BackgroundList;

	for (int iCurrent = 0; iCurrent < Fonts.ArraySize(); iCurrent++)
	{
		TFont* Font = Fonts[iCurrent];
		SafeRelease(&Font->Format);
	}
}

