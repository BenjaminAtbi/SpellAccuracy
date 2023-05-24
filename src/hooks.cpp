#include "hooks.h"



namespace SampleHook {
    // signature of the function being called (and the one that will replace it)
    int32_t* PopulateHitData(RE::Actor* target, char* unk0);

    // relocation of trampoline function that essentially makes original function call
    REL::Relocation<decltype(PopulateHitData)> OriginalPopulateHitData;

    REL::Relocation<decltype(PopulateHitData)>& GetHookedFunction() noexcept {
        // Relocation of a call instruction 0x42 bytes past start of the ID'd function
        static REL::Relocation<decltype(PopulateHitData)> value(RELOCATION_ID(42832, 44001), 0x42);
        return value;
    }

    static void InitializeHook(SKSE::Trampoline& trampoline) {
        // The trampoline can be used to write a new call instruction at a given address (here the start of the function
        // for
        // HitData::Populate). We use write_code<5> to indicate this is a 5-byte call instruction (rather than the much
        // rarer 6-byte call). We pass in the address of our function that will be called, and a pointer to the
        // trampoline function is returned.
        //
        // The trampoline pointed to contains any instructions from the original function we overwrote and a call to the
        // instruction that comes after, so that if we call that address as a function, we are in effect calling the
        // original code.
        OriginalPopulateHitData =
            trampoline.write_call<5>(GetHookedFunction().address(), reinterpret_cast<uintptr_t>(PopulateHitData));
        logger::debug("Hit data hook written.");
    }

    int32_t* PopulateHitData(RE::Actor* target, char* unk0) {
        logger::debug("hit register");
        return OriginalPopulateHitData(target, unk0);
    }
};

void ProjectileHook::InitProjectile(RE::Projectile* a_this) {
    logger::debug("projectile Init");
    _InitProjectile(a_this);
}



void InitializeHooks(SKSE::Trampoline& trampoline) { 
    SampleHook::InitializeHook(trampoline); 
    ProjectileHook::InitializeHook(trampoline);
}




/* Projectile manipulation examples */

//class NormLightingsHook {
//public:
//    static void Hook() {
//        _BeamProjectile__ctor =
//            SKSE::GetTrampoline().write_call<5>(REL::ID(42928).address() + 0x185, Ctor);  // SkyrimSE.exe+74B2F5
//    }
//
//private:
//    static RE::BeamProjectile* Ctor(RE::BeamProjectile* proj, void* LaunchData) {
//        proj = _BeamProjectile__ctor(proj, LaunchData);
//        if (auto spell = proj->spell;
//            spell && spell->GetCastingType() == RE::MagicSystem::CastingType::kFireAndForget) {
//            proj->flags.set(RE::Projectile::Flags::kUseOrigin);
//            proj->flags.reset(RE::Projectile::Flags::kAutoAim);
//        }
//        return proj;
//    }
//
//    static inline REL::Relocation<decltype(Ctor)> _BeamProjectile__ctor;
//};

//namespace Hooks {
//    // Spawn many projectiles
//    class ManyProjsHook {
//    public:
//        static void Hook() {
//            _castProjectile = SKSE::GetTrampoline().write_call<5>(REL::ID(33670).address() + 0x575,
//                                                                  castProjectile);  // SkyrimSE.exe+5504F5
//        }
//
//    private:
//        static bool castProjectile(RE::MagicCaster* a, RE::BGSProjectile* bproj, RE::Actor* a_char,
//                                   RE::CombatController* a4, RE::NiPoint3* startPos, float rotationZ, float rotationX,
//                                   uint32_t area, void* a9) {
//            auto found = Casting::get_ManyCasted(bproj->formID);
//            if (!found.first) return _castProjectile(a, bproj, a_char, a4, startPos, rotationZ, rotationX, area, a9);
//
//            Casting::onManyCasted(a, a_char, startPos, {rotationX, rotationZ});
//
//            return true;
//        }
//
//        static inline REL::Relocation<decltype(castProjectile)> _castProjectile;
//    };
//
//    struct Projectile__LaunchData {
//        void* vftable_LaunchData_0;
//        RE::NiPoint3 startPos;
//        RE::NiPoint3 Point_14;
//        RE::BGSProjectile* projectile;
//        RE::TESObjectREFR* source;
//        RE::CombatController* combatController;
//        RE::TESObjectWEAP* weap;
//        RE::TESAmmo* overwriteAmmo;
//        float rotationZ;
//        float rotationX;
//        void* field_50;
//        RE::TESObjectREFR* target;
//        std::pair<float, float> drawn_time;
//        RE::TESObjectCELL* cell;
//        RE::MagicItem* CastItem;
//        RE::MagicSystem::CastingSource castingSource;
//        RE::EnchantmentItem* ammoEnchantment;
//        RE::AlchemyItem* poison;
//        uint32_t area;
//        float Effectiveness;
//        float scale;
//        char field_9C;
//        char field_9D;
//        char field_9E;
//        char field_9F;
//        char field_A0;
//        char field_A1;
//        char field_A2;
//        char field_A3;
//        char gapA4[4];
//    };

//		class SetNewTypeHook {
//public:
//    static void Hook() {
//        FenixUtils::writebytes<17693, 0xefa>("\x0F\x1F\x80\x00\x00\x00\x00"sv);
//
//        _CreateProjectile = SKSE::GetTrampoline().write_call<5>(
//            REL::ID(17693).address() + 0xe82,
//            CreateProjectile);  // SkyrimSE.exe+2360C2 -- TESObjectWEAP::Fire_140235240
//    }
//
//private:
//    static uint32_t* CreateProjectile(uint32_t* handle, Projectile__LaunchData* ldata) {
//        auto bproj = ldata->projectile;
//
//        auto found = Casting::get_ManyCasted(bproj->formID);
//        if (!found.first) return _CreateProjectile(handle, ldata);
//
//        Casting::onManyCasted(ldata->source->As<RE::Actor>(), &ldata->startPos,
//                              ProjectileRot{ldata->rotationX, ldata->rotationZ}, ldata->weap, ldata->overwriteAmmo);
//
//        *handle = 0;
//
//        return handle;
//    }
//
//    static inline REL::Relocation<decltype(CreateProjectile)> _CreateProjectile;
//};
//}
