#pragma once
#include "logging.h"
#include "RE/Skyrim.h"
#include "SKSE/SKSE.h"


class ProjectileHook {
public:
    static void InitializeHook(SKSE::Trampoline& trampoline) {
        _InitProjectile =
            trampoline.write_call<5>(GetHookedFunction().address(), reinterpret_cast<uintptr_t>(InitProjectile));
        logger::debug("Projectile hook written.");
    }

private:
    static void InitProjectile(RE::Projectile* a_this);
    static inline REL::Relocation<decltype(InitProjectile)> _InitProjectile;
    
    static REL::Relocation<decltype(InitProjectile)>& GetHookedFunction() noexcept {
        // Relocation of a call instruction 0x42 bytes past start of the ID'd function
        static REL::Relocation<decltype(InitProjectile)> value(RELOCATION_ID(43030, 44222),
                                                               REL::VariantOffset(0x3B8, 0x78A, 0).offset());
        return value;
    }
};

void InitializeHooks(SKSE::Trampoline& trampoline);