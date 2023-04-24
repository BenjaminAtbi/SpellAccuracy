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

    spdlog::info("Initialized info");
    spdlog::error("Initialized error {}", 69);
    spdlog::trace("Initialized trace");


    SKSE::log::info("Initialized info");
    SKSE::log::error("Initialized error {}", 69);
    SKSE::log::trace("Initialized trace");

    logger::info("Initialized info");
    logger::error("Initialized error {}", 69);
    logger::trace("Initialized trace");

    return true;
}