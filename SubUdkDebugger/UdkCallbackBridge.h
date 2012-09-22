#pragma once

ref class UdkCallbackBridge : public IpcConduit::IUdkCallbackBridgeInterface
{
	typedef void (*CallbackPointer)(const char*);

private:
	CallbackPointer callbackPointer;	

public:
	UdkCallbackBridge(CallbackPointer);
	virtual void Send(System::String ^);
	virtual void Close();
};

