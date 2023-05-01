//---------------------------------------------------------------------------
#ifndef FindCheckThreadH
#define FindCheckThreadH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>

#include "WriteFillThread.h"
//---------------------------------------------------------------------------
class FindCheckThread : public TThread
{
private:
	HANDLE Disk;
    HANDLE Timer;
	ULONG NumOfClus;
	int ClusSize;
    BYTE *Block;
protected:
	void __fastcall Execute();
public:
	WriteFillThread *WFT;
	ULONG ClusNum;
    const char *FileType;
	__fastcall FindCheckThread(bool CreateSuspended);
    void __fastcall PB();
    void __fastcall End();
    __fastcall ~FindCheckThread();
};
//---------------------------------------------------------------------------
#endif
