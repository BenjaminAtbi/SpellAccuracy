#include <spdlog/sinks/basic_file_sink.h>
#include "RE/Skyrim.h"
#include "SKSE/SKSE.h"
#include "logging.h"
#include "hooks.h"

using namespace SKSE;



/*
create trampoline space and write call to new function
*/
void InitializeTrampoline() {
    logger::trace("Initializing trampoline...");
    auto &trampoline = SKSE::GetTrampoline();
    trampoline.create(64);
    logger::trace("Trampoline initialized.");

    InitializeHooks(trampoline);
}

void InitializeMessaging() {
    if (!GetMessagingInterface()->RegisterListener([](MessagingInterface::Message *message) {
            //load hooks after data is loaded
            if (message->type == MessagingInterface::kDataLoaded) InitializeTrampoline();
        })) {
        stl::report_and_fail("Unable to register message listener.");
    }
}



SKSEPluginLoad(const SKSE::LoadInterface *skse) {
    
    SetupLog();
    
    SKSE::Init(skse);
    InitializeMessaging();

    logger::info("Initialized info");

    return true;
}