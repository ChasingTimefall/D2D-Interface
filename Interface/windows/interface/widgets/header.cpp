#include "../widgets.h"

void CWgtHeader::SetRelativePosition(const TVector2D& vecRelativePosition) 
{
	vecObjectPosition = vecRelativePosition;
}

void CWgtHeader::SetSize(const TVector2D& vecSize) 
{
	vecObjectSize = vecSize;
}

void CWgtHeader::SetIdentifier(std::string _szIdentifier) {
	szIdentifier = _szIdentifier;
}