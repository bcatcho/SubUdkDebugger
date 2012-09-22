#include "stdafx.h"
#include <gcroot.h>
#include "SubUdkDebugger.h"
#include "UdkCallbackBridge.h"

using namespace System;
using namespace IpcConduit;


typedef void (*CallbackPointer)(const char*);
gcroot<IpcConduitController ^> ipcController;

extern "C"
{
	IpcConduitController^ ipcConduit()
	{
		auto testIpcForNull = (IpcConduitController^)ipcController;
		if ( testIpcForNull == nullptr )
			ipcController = gcnew IpcConduitController();

		return ipcController;
	}

	void WriteLog(String^ text)
	{
		ipcConduit()->WriteLog(text);
	}

	void SetCallback(void* callbackFunc)
	{
		UdkCallbackBridge^ bridge = gcnew UdkCallbackBridge((CallbackPointer)callbackFunc);
		ipcConduit()->SetCallbackBridge(bridge);
	}

	void ShowDllForm()
	{
		ipcConduit()->ShowDllForm();
	}

	void BuildHierarchy()
	{
		ipcConduit()->BuildHierarchy();
	}

	void ClearHierarchy()
	{
		ipcConduit()->ClearHierarchy();
	}

	void AddClassToHierarchy(const char* className)
	{
		String^ name = gcnew String(className);
		ipcConduit()->AddClassToHierarchy(name);
	}

	void ClearWatch(int watchType)
	{
		ipcConduit()->ClearWatch(watchType);
	}

	void ClearAWatch(int watchType)
	{
		ipcConduit()->ClearAWatch( watchType );
	}

	int AddAWatch(int watchType, int parentIndex, const char* varName, const char* varValue)
	{
		String^ name = gcnew String(varName);
		String^ val = gcnew String(varName);
		return ipcConduit()->AddAWatch(watchType, parentIndex, name, val);
	}

	void LockList(int watchList)
	{
		ipcConduit()->LockList(watchList);
	}

	void UnlockList(int watchList)
	{
		ipcConduit()->UnlockList(watchList);
	}

	void AddBreakpoint(const char* className, int lineNo)
	{
		String^ name = gcnew String(className);
		ipcConduit()->AddBreakpoint(name, lineNo);
	}

	void RemoveBreakpoint(const char* className, int lineNo)
	{
		String^ name = gcnew String(className);
		ipcConduit()->RemoveBreakpoint(name, lineNo);
	}

	void EditorLoadClass(const char* className)
	{
		String^ name = gcnew String(className);
		ipcConduit()->EditorLoadClass(name);
	}

	void EditorGotoLine(int lineNo, int highlight)
	{
		ipcConduit()->EditorGotoLine( lineNo, highlight );
	}

	void AddLineToLog(const char* text)
	{
		String^ managedText = gcnew String(text);
		ipcConduit()->AddLineToLog( managedText );
	}

	void CallStackClear()
	{
		ipcConduit()->CallStackClear();
	}

	void CallStackAdd(const char* callStackEntry)
	{
		String^ callStackEntryString = gcnew String(callStackEntry);
		ipcConduit()->CallStackAdd(callStackEntryString);
	}

	void SetCurrentObjectName(const char* objectName)
	{
		String^ name = gcnew String(objectName);
		ipcConduit()->SetCurrentObjectName(name);
	}

	void DebugWindowState(int stateCode)
	{
		ipcConduit()->DebugWindowState(stateCode);
	}
}