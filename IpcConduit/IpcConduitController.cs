
using System.Threading;
using System.Threading.Tasks;

namespace IpcConduit
{
   using System;
    using System.IO;
   using ZMQ;

   public class IpcConduitController : IDisposable
   {
      private StreamWriter _log;
      private Task _zmqServer;
      private bool runServer;

      public static IpcConduitController Create()
      {
         return new IpcConduitController();
      }

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
         runServer = true;
         var svr = new Action(delegate
         {
            using ( var context = new Context( 1 ) )
            {
               using (var router = context.Socket(SocketType.ROUTER))
               {
                  router.Bind("tcp://*:5556");

                  router.PollInHandler += (socket, revents) =>
                                             {
                                                var zmsg = new ZMessage(socket);
                                                WriteLog(zmsg.BodyToString());
                                             };

                  while ( runServer )
                  {
                     Context.Poller(router);
                  }
               }
            }
         });

         WriteLog("Starting ZeroMQ server");
         _zmqServer = new Task(svr);
         _zmqServer.Start();
      }

      public void WriteLog( String text )
      {
         var logText = String.Format( "[{0}] {1}", DateTime.Now.ToString( "MM/dd/yyyy h:mm tt" ), text );
         _log.WriteLine( logText );
         _log.Flush();
      }

      public void StopDebugger()
      {
         runServer = false;
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
   }
}
