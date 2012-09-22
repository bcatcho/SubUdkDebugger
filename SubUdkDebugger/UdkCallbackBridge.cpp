#include "stdafx.h"
#include <vcclr.h>
#include "UdkCallbackBridge.h"


UdkCallbackBridge::UdkCallbackBridge(CallbackPointer callbackPointerParam) :
	callbackPointer(callbackPointerParam)
{ 

}void UdkCallbackBridge::Send(System::String^ command)
{
	cli::pin_ptr<const System::Char> pCommandChar = PtrToStringChars( command );
	const wchar_t *pszpCommandChar = pCommandChar;


	if (this->callbackPointer == NULL)
	{
		return;
	}

	try
	{
		this->callbackPointer(ATL::CW2A(pszpCommandChar));
	}
	catch(System::AccessViolationException^)
	{
		System::Diagnostics::Debug::WriteLine(
			System::String::Concat(
				L"debug::(callbackPointer) callbackPointer is not accessable (AccessViolationException)", 
				command));
	}
}

void UdkCallbackBridge::Close()
{
	this->callbackPointer = NULL;
}
