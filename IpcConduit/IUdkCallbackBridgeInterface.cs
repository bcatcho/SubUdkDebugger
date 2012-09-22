namespace IpcConduit
{
   public interface IUdkCallbackBridgeInterface
   {
      void Send( string command );
      void Close();
   }
}
