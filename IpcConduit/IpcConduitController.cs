
namespace IpcConduit
{
   using System;
    using System.IO;

   public class IpcConduitController : IDisposable
   {
      private StreamWriter _log;

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
      }

      public void WriteLog( String text )
      {
         String logText = String.Format( "[{0}] {1}", DateTime.Now.ToString( "MM/dd/yyyy h:mm tt" ), text );
         _log.WriteLine( logText );
         _log.Flush();

      }

      public bool Yar()
      {
         _log.WriteLine( "ohhhh buddy" );
         _log.Flush();
         return true;
      }

      public void Dispose()
      {
         _log.Dispose();
      }
   }
}
