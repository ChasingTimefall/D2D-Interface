#include "../widgets.h"

CWgtFrame::CWgtFrame(const std::string& _szIdentifier, const TVector2D& vecRelativePosition, const TVector2D& vecSize)
{
	vecObjectPosition = vecRelativePosition;
	vecObjectSize = vecSize;
	WgtIndex = WGT_FRAME;
	szIdentifier = _szIdentifier;
}

void CWgtFrame::OnPostRenderCallback(TWinInstance* Instance)
{
	if (Objects.IsEmpty())
		return;

	vecCurrentPosition = vecObjectPosition;

	for (int iCurrentObject = 0; iCurrentObject < Objects.ArraySize(); iCurrentObject++)
	{
		auto Object = *Objects[iCurrentObject];

		switch (Object->WgtIndex)
		{
		   case WGT_CHECKBOX:
		   {
			   CCheckboxWgt* Checkbox = (CCheckboxWgt*)Object;
			   Checkbox->OnPostRenderCallback(Instance , this);
			   break;
		   }
		   case WGT_INPUTTEXT:
		   {		  
			   CInputTextWgt* InputText = (CInputTextWgt*)Object;
			   InputText->OnPostRenderCallback(Instance, this);
			   break;
		   }
		   case WGT_SLIDER:
		   {
			   CSliderWgt* Slider = (CSliderWgt*)Object;
			   Slider->OnPostRenderCallback(Instance, this);
			   break;
		   }
		   case WGT_SINGLESELECT:
		   {			  
			   CSingleSelectWgt* SingleSelect = (CSingleSelectWgt*)Object;
			   SingleSelect->OnPostRenderCallback(Instance, this);
			   break;
		   }
		   case WGT_MULTISELECT:
		   {		   
			   CMultiSelectWgt* MultiSelect = (CMultiSelectWgt*)Object;
			   MultiSelect->OnPostRenderCallback(Instance, this);
			   break;
		   }
		   case WGT_BUTTON:
		   {			
			   CButtonWgt* Button = (CButtonWgt*)Object;
			   Button->OnPostRenderCallback(Instance, this);
			   break;
		   }
		   case WGT_LOADINGBAR:
		   {
			   CLoadingBarWgt* LoadingBar = (CLoadingBarWgt*)Object;
			   LoadingBar->OnPostRenderCallback(Instance, this);
			   break;
		   }
		   default:
			   break;
		}
	}
}

void CWgtFrame::ClearFrame() {
	Objects.Clear();
}

bool CWgtFrame::AddObjectToFrame(CWgtHeader* Header) {
	return Objects.AddBack(Header) != nullptr;
}

