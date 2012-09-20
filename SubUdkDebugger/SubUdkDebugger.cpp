// This is the main DLL file.

#include "stdafx.h"

// This is the main DLL file.

#include "stdafx.h"
#include <vcclr.h>
#include <gcroot.h>
#include "SubUdkDebugger.h"

using namespace System;
using namespace System::IO;


#define _LOG


typedef void (*CallbackPointer)(const char*);
gcroot<StreamWriter^> _log;
CallbackPointer callbackPointer = nullptr;
bool debugging = false;
int g_WatchId[3];
int eventNum = 0;


void WriteLog(String^ text)
{
#ifdef _LOG
	if (_log)
	{
		String^ logText = String::Format("[{0}] {1}", DateTime::Now.ToString("MM/dd/yyyy h:mm tt"), text);
		_log->WriteLine(logText);
		_log->Flush();
	}
#endif
}


void SendCommand(String^ text)
{
	if (!callbackPointer)
	{
		WriteLog("Warning! Callback Pointer is empty!");
		return;
	}
	char* szCommand = (char*)(System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(text)).ToPointer();

	WriteLog(String::Format("Command: {0}", text));
	if (callbackPointer) {
		callbackPointer(szCommand); 
	}

	System::Runtime::InteropServices::Marshal::FreeHGlobal(IntPtr((void*)szCommand));
}

void SetupLog()
{
	_log = gcnew StreamWriter("debugger.log", true);
	_log->WriteLine("\nDebugger started [{0}]", DateTime::Now.ToString("MM/dd/yyyy h:mm tt"));
	_log->WriteLine("==================================================================");
}


void UnhandledExceptionHandler(Object^ sender, UnhandledExceptionEventArgs^ e)
{
        try
        {
			WriteLog( e->ExceptionObject->ToString() );
        }
        finally
        {
            throw (Exception^) e->ExceptionObject;
        }
}

[STAThread]
void WorkerThreadFunction()
{
        AppDomain::CurrentDomain->UnhandledException += gcnew UnhandledExceptionEventHandler(&UnhandledExceptionHandler);
}

extern "C"
{
	void SetCallback(void* callbackFunc)
	{
		if (!debugging)
		{
			SetupLog();
			debugging = true;
		}
		callbackPointer = (CallbackPointer)callbackFunc;
		WriteLog("SetCallback");
	}

	void ShowDllForm()
	{
		WriteLog("ShowDllForm");
		SendCommand("go");
	}

	void BuildHierarchy()
	{
		//WriteLog("BuildHierarchy");
	}

	void ClearHierarchy()
	{
		//WriteLog("ClearHierarchy");
	}

	void AddClassToHierarchy(const char* className)
	{
		//WriteLog("AddClassToHierarchy");
	}

	void ClearWatch(int watchType)
	{
		g_WatchId[watchType] = 0;
		//WriteLog("ClearWatch");
	}

	void ClearAWatch(int watchType)
	{
		g_WatchId[watchType] = 0;
		//WriteLog("ClearAWatch");
	}

	int AddAWatch(int watchType, int parentIndex, const char* varName, const char* varValue)
	{
		int nResult = 0;
		nResult = ++g_WatchId[watchType];
		//WriteLog("AddAWatch");
		return nResult;
	}

	void LockList(int watchList)
	{
		//WriteLog("LockList");
	}

	void UnlockList(int watchList)
	{
		//WriteLog("UnlockList");
	}

	void AddBreakpoint(const char* className, int lineNo)
	{
		//WriteLog("AddBreakpoint");
	}

	void RemoveBreakpoint(const char* className, int lineNo)
	{
		//WriteLog("RemoveBreakpoint");
	}

	void EditorLoadClass(const char* className)
	{
		//WriteLog("EditorLoadClass");
	}

	void EditorGotoLine(int lineNo, int highlight)
	{
		//WriteLog("EditorGotoLine");
	}

	void AddLineToLog(const char* text)
	{
		String^ logString = gcnew String(text);

		WriteLog(String::Format("AddLineToLog {0}", logString));
		if (String::Compare(logString, "Log: Detaching UnrealScript Debugger (currently detached)") == 0)
		{
			WriteLog("Shutting Down Debugger Interface!");
			_log->Close();
			_log = nullptr;
			callbackPointer = NULL;
			debugging = false;
		}
	}

	void CallStackClear()
	{
		//WriteLog("CallStackClear");
	}

	void CallStackAdd(const char* callStackEntry)
	{
		//WriteLog("CallStackAdd");
	}

	void SetCurrentObjectName(const char* objectName)
	{
		//WriteLog("SetCurrentObjectName");
	}

	void DebugWindowState(int stateCode)
	{
		//WriteLog("DebugWindowState");
	}
}