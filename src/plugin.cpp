#include <spdlog/sinks/basic_file_sink.h>
#include "RE/Skyrim.h"
#include "SKSE/SKSE.h"
#include "logging.h"
#include "hooks.h"
#include "versionlibdb.h"

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

//bool DumpSpecificVersion() {
//    // 1.6.640.0.8
//    VersionDb db;
//
//    // Try to load database regardless of running executable version.
//
//    if (!db.Load(1, 6, 640, 0)) {
//        logger::debug("Failed to load database!");
//        return false;
//    }
//
//    // Write out a file where each line is the ID and offset.
//    db.Dump("offsets.txt");
//    logger::debug("Dumped offsets ");
//    return true;
//}


SKSEPluginLoad(const SKSE::LoadInterface *skse) {
    
    SetupLog();
    
    SKSE::Init(skse);
    InitializeMessaging();
    DumpSpecificVersion();

    logger::info("Initialized info");

    return true;
}