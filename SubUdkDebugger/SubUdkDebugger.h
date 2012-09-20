// SubUdkDebugger.h
//

#pragma once

#define UDK_DECLSPEC    __declspec(dllexport)

extern "C"
{
	UDK_DECLSPEC void SetCallback(void* CallbackFunc);
	UDK_DECLSPEC void ShowDllForm();
	UDK_DECLSPEC void BuildHierarchy();
	UDK_DECLSPEC void ClearHierarchy();
	UDK_DECLSPEC void AddClassToHierarchy(const char* ClassName);
	UDK_DECLSPEC void ClearWatch(int WatchType);
	UDK_DECLSPEC void ClearAWatch(int WatchType);
	UDK_DECLSPEC int  AddAWatch(int WatchType, int ParentIndex, const char* VarName, const char* VarValue);
	UDK_DECLSPEC void LockList(int WatchList);
	UDK_DECLSPEC void UnlockList(int WatchList);
	UDK_DECLSPEC void AddBreakpoint(const char* ClassName, int LineNo);
	UDK_DECLSPEC void RemoveBreakpoint(const char* ClassName, int LineNo);
	UDK_DECLSPEC void EditorLoadClass(const char* ClassName);
	UDK_DECLSPEC void EditorGotoLine(int LineNo, int bHighlight);
	UDK_DECLSPEC void AddLineToLog(const char* Text);
	UDK_DECLSPEC void CallStackClear();
	UDK_DECLSPEC void CallStackAdd(const char* CallStackEntry);
	UDK_DECLSPEC void SetCurrentObjectName(const char* ObjectName);
	UDK_DECLSPEC void DebugWindowState(int StateCode);
}
