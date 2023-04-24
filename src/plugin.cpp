#include <spdlog/sinks/basic_file_sink.h>
#include "RE/Skyrim.h"
#include "SKSE/SKSE.h"
#include "logging.h"
#include "hooks.h"

using namespace SKSE;

void InitializeMessaging() {
    if (!GetMessagingInterface()->RegisterListener([](MessagingInterface::Message *message) {
            if (message->type == MessagingInterface::kDataLoaded) {
                logger::info("hello world");
            }
            //ProjectileHook::InitializeHook();
        })) {
        stl::report_and_fail("Unable to register message listener.");
    }
}

SKSEPluginLoad(const SKSE::LoadInterface *skse) {
    
    SKSE::Init(skse);
    SetupLog();
    InitializeMessaging();

    logger::info("Initialized info");

    return true;
}