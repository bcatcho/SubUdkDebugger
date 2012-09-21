#pragma once

using namespace System;
using namespace IpcConduit;

namespace IpcConduitCpp {

    public ref class ManagedIpcConduit
    {
    public:
        bool Yar()
        {
                IpcConduitController^ c = gcnew IpcConduitController();
                return c->Yar();
        }
    };
}