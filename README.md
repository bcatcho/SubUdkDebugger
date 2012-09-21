
## Here writhers a prototype UDK Debugger Interface for Sublime Text 2

There are three main parts to this project:

1. A Debugger interface that conforms to the [http://udn.epicgames.com/Three/DebuggerInterface.html](Udk Debugger Interface)
   - It is written in C# but is wrapped by CLR enabled c++
   - Other than logging, the main responsibility of this DLL is to connect UDK.exe to any other ZeroMQ subscriber on the same machine (local for now).
2. A test client
   - To test the ZeroMQ server
3. A Sublime Text 2 pluggin
   - TODO