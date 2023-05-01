//---------------------------------------------------------------------------
#include <System.hpp>
#pragma hdrstop

#include "SSearch.h"
#include "FindCheckThread.h"
#include "WriteFillThread.h"
#pragma package(smart_init)
//---------------------------------------------------------------------------
__fastcall WriteFillThread::WriteFillThread(bool CreateSuspended)
	: TThread(CreateSuspended)
{
	sqlite3_open("files", &DB);
	int Res = sqlite3_prepare_v2(DB, "CREATE TABLE IF NOT EXISTS list\
		(clusternumber integer,	filetype varchar(10))", -1, &Stmt, NULL);
	if (Res != SQLITE_OK)
		Terminate();
	Res = sqlite3_step(Stmt);
	if (Res != SQLITE_DONE)
		Terminate();
	Res = sqlite3_exec(DB,"DELETE FROM list", NULL, NULL, &ErrMsg);
	if (Res != SQLITE_OK)
		Terminate();
}
//---------------------------------------------------------------------------
void __fastcall WriteFillThread::Execute()
{
	FreeOnTerminate = true;
	int Res = sqlite3_prepare_v2(DB,"INSERT INTO list(clusternumber,\
		filetype) values(?,?)", -1, &Stmt, NULL);
	if (Res != SQLITE_OK)
		Terminate();
	while (!Form1->FCT->Finished)
	{
		sqlite3_bind_int(Stmt, 1, Form1->FCT->ClusNum);
		sqlite3_bind_text(Stmt, 2, Form1->FCT->FileType,
			strlen(Form1->FCT->FileType), NULL);
		sqlite3_step(Stmt);
		sqlite3_reset(Stmt);
		Synchronize(&VST);
		Form1->FCT->Resume();
		Suspend();
	}
}
//---------------------------------------------------------------------------
void __fastcall WriteFillThread::VST()
{
	Form1->VirtualStringTree->BeginUpdate();
	PVirtualNode Node = Form1->VirtualStringTree->AddChild(NULL);
	Data* data = (Data*)Form1->VirtualStringTree->GetNodeData(Node);
	data->ClusterNumber = Form1->FCT->ClusNum;
	data->FileType = Form1->FCT->FileType;
	Form1->VirtualStringTree->EndUpdate();
}
//---------------------------------------------------------------------------
__fastcall WriteFillThread::~WriteFillThread()
{
    sqlite3_finalize(Stmt);
	sqlite3_close(DB);
}
//---------------------------------------------------------------------------
