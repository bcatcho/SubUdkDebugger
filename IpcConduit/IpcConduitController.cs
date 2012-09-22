using System.Collections.Generic;
using System.Threading.Tasks;
using System;
using System.IO;
using ZMQ;

namespace IpcConduit
{

   public class IpcConduitController : IDisposable, IUdkDebuggerInterface
   {
      private StreamWriter _log;
      private Task _zmqServer;
      private bool _runServer;
      private IUdkCallbackBridgeInterface _callbackBridge;

      public IpcConduitController()
      {

         _log = new StreamWriter( "Debugger.log", true );
         _log.WriteLine( "\nManaged Debugger started [{0}]", DateTime.Now.ToString( "MM/dd/yyyy h:mm tt" ) );
         _log.WriteLine( "==================================================================" );
         _log.Flush();

         StartZmqServer();
      }

      private void StartZmqServer()
      {
         _runServer = true;
         var svr = new Action( delegate
         {
            using ( var context = new Context( 1 ) )
            {
               using ( var router = context.Socket( SocketType.ROUTER ) )
               {
                  router.Bind( "tcp://*:5556" );

                  router.PollInHandler += ( socket, revents ) =>
                                             {
                                                var zmsg = new ZMessage( socket );
                                                WriteLog( zmsg.BodyToString() );
                                             };

                  while ( _runServer )
                  {
                     Context.Poller( router );
                  }
               }
            }
         } );

         WriteLog( "Starting ZeroMQ server" );
         _zmqServer = new Task( svr );
         _zmqServer.Start();
      }

      public void WriteLog( String text )
      {
         var logText = String.Format( "[{0}] {1}", DateTime.Now.ToString( "MM/dd/yyyy h:mm tt" ), text );
         _log.WriteLine( logText );
         _log.Flush();
      }

      public void SetCallbackBridge( IUdkCallbackBridgeInterface callbackBridge )
      {
         _callbackBridge = callbackBridge;
      }

      public void SendCommand( string command )
      {
         if (_callbackBridge != null)
             _callbackBridge.Send(command);
      }

      public void StopDebugger()
      {
         _runServer = false;
         //_zmqServer.Wait();
      }

      public void Dispose()
      {
         _log.Dispose();

         if ( _zmqServer.Status == TaskStatus.Running )
         {
            StopDebugger();
         }
         _zmqServer.Dispose();
      }

      public void AddLineToLog( string text )
      {
         WriteLog(text);

         if ( text == "Log: Detaching UnrealScript Debugger (currently detached)" )
         {
             WriteLog("Shutting Down Debugger Interface");
             StopDebugger();
         }
      }

      public void ShowDllForm()
      {
         SendCommand("go");
      }

      public void EditorGotoLine(int lineNo, int highlight)
      {
         WriteLog("EditorGotoLine");
      }

      public void CallStackClear()
      {
         WriteLog( "CallStackClear" );
      }

      public void CallStackAdd(string callStackEntry)
      {
         WriteLog("EditorGotoLine");
      }

      public void SetCurrentObjectName(string objectName)
      {
         WriteLog( "SetCurrentObjectName" );
      }

      public void DebugWindowState(int stateCode)
      {
         WriteLog( "DebugWindowState" );
      }

      public void AddWatches(int watchList, IList<string> iList)
      {
         WriteLog( "AddWatches" );
      }

      public void ShutDown()
      {
         WriteLog( "ShutDown" );
      }

      public void BuildHierarchy()
      {
         WriteLog( "BuildHierarchy" );
      }

      public void ClearHierarchy()
      {
         WriteLog( "ClearHierarchy" );
      }

      public void AddClassToHierarchy(string className)
      {
         WriteLog( "AddClassToHierarchy" );
      }

      public void ClearWatch(int watchType)
      {
         WriteLog( "ClearWatch" );
      }

      public void ClearAWatch(int watchType)
      {
         WriteLog( "ClearAWatch" );
      }

      public int AddAWatch(int watchType, int parentIndex, string varName, string varValue)
      {
         WriteLog( "AddAWatch" );
         return 0;
      }

      public void LockList(int watchList)
      {
         WriteLog( "LockList" );
      }

      public void UnlockList(int watchList)
      {
         WriteLog( "UnlockList" );
      }

      public void AddBreakpoint(string className, int lineNo)
      {
         WriteLog( "AddBreakpoint" );
      }

      public void RemoveBreakpoint(string className, int lineNo)
      {
         WriteLog( "RemoveBreakpoint" );
      }

      public void EditorLoadClass(string className)
      {
         WriteLog( "EditorLoadClass" );
      }
   }
}
