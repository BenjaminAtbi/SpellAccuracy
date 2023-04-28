#include "hooks.h"



namespace ProjectileHook {

    int32_t* PopulateHitData(RE::Actor* target, char* unk0);

    REL::Relocation<decltype(PopulateHitData)> OriginalPopulateHitData;


    /* get relocation of PopulateHitData function at address specified by given ID */
    REL::Relocation<decltype(PopulateHitData)>& GetHookedFunction() noexcept {
        static REL::Relocation<decltype(PopulateHitData)> value(RELOCATION_ID(42832, 44001), 0x42);
        return value;
    }

    void InitializeHook(SKSE::Trampoline& trampoline) {
        // The trampoline can be used to write a new call instruction at a given address (here the start of the function
        // for
        // HitData::Populate). We use write_code<5> to indicate this is a 5-byte call instruction (rather than the much
        // rarer 6-byte call). We pass in the address of our function that will be called, and a pointer to the
        // trampoline function is returned.
        //
        // The trampoline pointed to contains any instructions from the original function we overwrote and a call to the
        // instruction that comes after, so that if we call that address as a function, we are in effect calling the
        // original code.
        OriginalPopulateHitData = trampoline.write_call<5>(GetHookedFunction().address(), reinterpret_cast<uintptr_t>(PopulateHitData));
        logger::debug("Hit data hook written.");
    }
}





