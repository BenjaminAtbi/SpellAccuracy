#include <spdlog/sinks/basic_file_sink.h>
#include "RE/Skyrim.h"
#include "SKSE/SKSE.h"
#include "logging.h"
#include "hooks.h"

using namespace SKSE;

void InitializeMessaging() {
    if (!GetMessagingInterface()->RegisterListener([](MessagingInterface::Message *message) {
            if (message->type == MessagingInterface::kDataLoaded) InitializeHooking();
        })) {
        stl::report_and_fail("Unable to register message listener.");
    }
}

/*
create trampoline space and write call to new function
*/
void InitializeHooking() {
    logger::trace("Initializing trampoline...");
    auto &trampoline = SKSE::GetTrampoline();
    trampoline.create(64);
    logger::trace("Trampoline initialized.");

    ProjectileHook::InitializeHook(trampoline);

    // oldfunc = trampoline.write_call<5>(GetHookAddress(), newfunc);
}

SKSEPluginLoad(const SKSE::LoadInterface *skse) {
    
    SetupLog();
    
    SKSE::Init(skse);
    InitializeMessaging();

    logger::info("Initialized info");

    return true;
}