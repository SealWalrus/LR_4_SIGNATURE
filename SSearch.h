//---------------------------------------------------------------------------
#ifndef SSearchH
#define SSearchH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include "VirtualTrees.hpp"
#include <Vcl.ComCtrls.hpp>

#include <windows.h>
#include "FindCheckThread.h"
//---------------------------------------------------------------------------
using namespace std;
//---------------------------------------------------------------------------
typedef struct
{
	ULONGLONG ClusterNumber;
	String FileType;
} Data;
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
	TVirtualStringTree *VirtualStringTree;
	TProgressBar *ProgressBar;
	TButton *SearchButton;
	TButton *StopButton;
	TComboBox *VolumeBox;
	void __fastcall SearchButtonClick(TObject *Sender);
	void __fastcall VolumeBoxSelect(TObject *Sender);
	void __fastcall StopButtonClick(TObject *Sender);
	void __fastcall VirtualStringTreeGetText(TBaseVirtualTree *Sender, PVirtualNode Node,
          TColumnIndex Column, TVSTTextType TextType, UnicodeString &CellText);

private:	// User declarations
public:		// User declarations
	wstring Path;
    FindCheckThread *FCT;
	__fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
