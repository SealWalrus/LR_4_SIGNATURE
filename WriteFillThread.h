//---------------------------------------------------------------------------
#ifndef WriteFillThreadH
#define WriteFillThreadH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include "sqlite3.h"
//---------------------------------------------------------------------------
class WriteFillThread : public TThread
{
private:
	sqlite3 *DB;
	sqlite3_stmt *Stmt;
    char *ErrMsg;
protected:
	void __fastcall Execute();
public:
	__fastcall WriteFillThread(bool CreateSuspended);
    void __fastcall VST();
    __fastcall ~WriteFillThread();
};
//---------------------------------------------------------------------------
#endif
