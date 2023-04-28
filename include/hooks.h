#pragma once
#include "logging.h"
#include "RE/Skyrim.h"
#include "SKSE/SKSE.h"

class ProjectileHook 
{
    public:
        static void InitializeHook(SKSE::Trampoline& trampoline);
};