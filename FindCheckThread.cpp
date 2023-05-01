//---------------------------------------------------------------------------
#include <System.hpp>
#pragma hdrstop

#include "SSearch.h"
#include "FindCheckThread.h"
#pragma package(smart_init)
//---------------------------------------------------------------------------
bool IsJPG(BYTE *Sign)
{
	BYTE JPG[10]{0xFF, 0xD8, 0xFF, 0xE0, 0x00, 0x10, 0x4A, 0x46, 0x49, 0x46};
	for (int i = 0; i < sizeof(JPG); i++)
	{
		if (Sign[i] != JPG[i])
			return false;
	}
	return true;
}

bool IsPNG(BYTE *Sign)
{
	BYTE PNG[4]{0x89, 0x50, 0x4E, 0x47};
	for (int i = 0; i < sizeof(PNG); i++)
	{
		if (Sign[i] != PNG[i])
			return false;
	}
	return true;	
}

bool IsBMP(BYTE *Sign)
{
	BYTE BMP[2]{0x42, 0x4D};
	for (int i = 0; i < sizeof(BMP); i++)
	{
		if (Sign[i] != BMP[i])
			return false;
	}
	return true;		
}

bool IsGIF(BYTE * Sign)
{
	BYTE GIF[3]{0x47, 0x49, 0x46};
	for (int i = 0; i < sizeof(GIF); i++)
	{
		if (Sign[i] != GIF[i])
			return false;
	}
	return true;
}
//---------------------------------------------------------------------------
__fastcall FindCheckThread::FindCheckThread(bool CreateSuspended)
	: TThread(CreateSuspended)
{
	wstring path = L"\\\\.\\" + Form1->Path + L":";
	Disk = CreateFileW(path.c_str(), GENERIC_READ, FILE_SHARE_READ |
		FILE_SHARE_WRITE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (Disk == INVALID_HANDLE_VALUE)
		Terminate();
	DWORD SecPerClus, BytesPerSec, NumOfFrClus;
	path = Form1->Path + L":\\";
	GetDiskFreeSpaceW(path.c_str(), &SecPerClus, &BytesPerSec, &NumOfFrClus,
		&NumOfClus);
	ClusSize = SecPerClus * BytesPerSec;
	Timer = CreateWaitableTimer(NULL, false, NULL);
	WFT = new WriteFillThread(true);
}
//---------------------------------------------------------------------------
void __fastcall FindCheckThread::Execute()
{
	FreeOnTerminate = true;
	LARGE_INTEGER FirstResponse = { 0 };
	LONG ResponsePeriod = 1000;
	SetWaitableTimer(Timer, &FirstResponse, ResponsePeriod, NULL, NULL, false);
	DWORD Read;
	int BlockSize = ClusSize * 32;
	Block = new BYTE[BlockSize];
	BYTE Sign[10];
	for (ClusNum = 0; ClusNum < NumOfClus;)
	{
		bool ReadRes = ReadFile(Disk, Block, BlockSize, &Read, NULL);
        if (!ReadRes || Read != BlockSize)
			Terminate();
		for (int i = 0; i < BlockSize; i += ClusSize, ClusNum++)
		{
            if (WaitForSingleObject(Timer, 0) == WAIT_OBJECT_0)
				Synchronize(&PB);
			FileType = NULL;
			for (int j = 0; j < sizeof(Sign); j++)
				Sign[j] = Block[i + j];
			if (IsJPG(Sign))
				FileType = ".jpg/.jpeg";
			if (IsPNG(Sign))
				FileType = ".png";
			if (IsBMP(Sign))
				FileType = ".bmp";
			if (IsGIF(Sign))
				FileType = ".gif";
			if (FileType != NULL)
			{
				WFT->Resume();
				Suspend();
			}
        }
	}
	Synchronize(&End);
}
//---------------------------------------------------------------------------
void __fastcall FindCheckThread::PB()
{
	Form1->ProgressBar->Position = int((ClusNum / NumOfClus) * 100);
}
//---------------------------------------------------------------------------
void __fastcall FindCheckThread::End()
{
    Form1->VolumeBox->Enabled = 1;
	Form1->ProgressBar->Position = 100;
	Form1->SearchButton->Visible = 1;
	Form1->SearchButton->Enabled = 1;
	Form1->StopButton->Enabled = 0;
}
//---------------------------------------------------------------------------
__fastcall FindCheckThread::~FindCheckThread()
{
    CloseHandle(Timer);
	CloseHandle(Disk);
	delete[] Block;
}
//---------------------------------------------------------------------------
