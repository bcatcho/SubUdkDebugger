using System;
using System.Text;
using ZMQ;
using Exception = System.Exception;

namespace IpcTestClient
{
   class Program
   {
      static void Main()
      {
         using ( var context = new Context( 1 ) )
         using ( var subscriber = context.Socket( SocketType.DEALER ) )
         {
            subscriber.Connect( "tcp://localhost:5556" );

            var keepGoing = true;
            Console.CancelKeyPress += ( sender, eventArgs ) =>
                                         {
                                            keepGoing = false;
                                         };

            // todo poll in a background task.
            // TODO how does one know if still connected?
            // BUG Events stack up an are sent the next time the server comes online

            Console.WriteLine( "[Connected to tcp://localhost:5556]" );
            Console.WriteLine( "[Write a message and hit enter to communicate with the server]" );
            while ( keepGoing )
            {
               var outMsg = Console.ReadLine();
               try
               {
                  SendStatus sendStatus = subscriber.Send( outMsg, Encoding.Unicode );
                  Console.WriteLine( Enum.GetName( typeof( SendStatus ), sendStatus ) );
               }
               catch ( Exception e )
               {

                  Console.WriteLine( e.Message );
               }
            }
         }
      }
   }
}
