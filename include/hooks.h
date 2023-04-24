#pragma once
#include "logging.h"
#include "RE/Skyrim.h"
#include "SKSE/SKSE.h"

class ProjectileHook 
{
    public:
        void InitializeHook();
        uintptr_t GetHookAddress();

    private:
        void newfunc();
        static REL::Relocation<decltype(newfunc)> oldfunc;
        
};