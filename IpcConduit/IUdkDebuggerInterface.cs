using System.Collections.Generic;

namespace IpcConduit
{
   interface IUdkDebuggerInterface
   {
      void ShowDllForm();

      void BuildHierarchy();

      void ClearHierarchy();

      void AddClassToHierarchy( string className );

      void ClearWatch( int watchType );

      void ClearAWatch( int watchType );

      int AddAWatch( int watchType, int parentIndex, string varName, string varValue );

      void LockList( int watchList );

      void UnlockList( int watchList );

      void AddBreakpoint( string className, int lineNo );

      void RemoveBreakpoint( string className, int lineNo );

      void EditorLoadClass( string className );

      void EditorGotoLine( int lineNo, int highlight );

      void AddLineToLog( string text );

      void CallStackClear();

      void CallStackAdd( string callStackEntry );

      void SetCurrentObjectName( string objectName );

      void DebugWindowState( int stateCode );

      void AddWatches( int watchList, IList<string> iList );

      void ShutDown();
   }
}
