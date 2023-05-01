//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "SSearch.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "VirtualTrees"
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
	VirtualStringTree->NodeDataSize = sizeof(Data);
	DWORD Mask = GetLogicalDrives();
	for (int i = 0; i < 26; i++)
	{
		bool V = ((Mask >> i) & 1);
		if (V)
		{
			VolumeBox->AddItem((char)(65 + i), NULL);
		}
	}
}
//---------------------------------------------------------------------------
void __fastcall TForm1::VolumeBoxSelect(TObject *Sender)
{
	Path = VolumeBox->Items->Strings[VolumeBox->ItemIndex];
	SearchButton->Enabled = 1;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::SearchButtonClick(TObject *Sender)
{
    VirtualStringTree->Clear();
	VolumeBox->Enabled = 0;
	SearchButton->Enabled = 0;
	SearchButton->Visible = 0;
	ProgressBar->Visible = 1;
	StopButton->Enabled = 1;
    FCT = new FindCheckThread(false);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::StopButtonClick(TObject *Sender)
{
	if (!FCT->WFT->Finished)
		FCT->WFT->Free();
	if (!FCT->Finished)
		FCT->Free();
	VolumeBox->Enabled = 1;
	SearchButton->Visible = 1;
	ProgressBar->Visible = 0;
    StopButton->Enabled = 0;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::VirtualStringTreeGetText(TBaseVirtualTree *Sender, PVirtualNode Node,
          TColumnIndex Column, TVSTTextType TextType, UnicodeString &CellText)
{
	Data *data = (Data*)Sender->GetNodeData(Node);
	switch (Column) {
		case 0:
			CellText = data->ClusterNumber;
			break;
		case 1:
			CellText = data->FileType;
			break;
	}
}
//---------------------------------------------------------------------------
