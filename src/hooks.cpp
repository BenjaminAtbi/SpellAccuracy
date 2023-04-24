#include "hooks.h"


/*
create trampoline space and write call to new function
*/
//void ProjectileHook::InitializeHook() {
//    logger::trace("Initializing trampoline...");
//    auto &trampoline = SKSE::GetTrampoline();
//    //trampoline.create(64);
//    logger::trace("Trampoline initialized.");
//
//    //oldfunc = trampoline.write_call<5>(GetHookAddress(), newfunc);
//}
//
//uintptr_t ProjectileHook::GetHookAddress() {
//    static REL::Relocation<decltype(newfunc)> relvalue(/* dummy id */  RELOCATION_ID(42832, 44001), 0);
//    return relvalue.address();
//}