#include "Settings.h"

void Settings::LoadSettings() noexcept
{
    logger::info("Loading settings");

    CSimpleIniA ini;

    ini.SetUnicode();
    ini.LoadFile(R"(.\Data\SKSE\Plugins\SimonrimStaffEnchantingPlus.ini)");

    debug_logging = ini.GetBoolValue("Log", "Debug");

    if (debug_logging) {
        spdlog::set_level(spdlog::level::debug);
        logger::debug("Debug logging enabled");
    }

    auto dataHandler = RE::TESDataHandler::GetSingleton();

    logger::info("Loading Adamant staff list");
    auto adamantStaffList = dataHandler->LookupForm(RE::FormID(0x56BCB1), "Adamant.esp")->As<RE::BGSListForm>();

    if (adamantStaffList) {
        staffFormLists.push_back(adamantStaffList);
    }

    logger::info("Loading Pilgrim staff list");
    auto pilgrimStaffList = dataHandler->LookupForm(RE::FormID(0x362BF1), "Pilgrim.esp")->As<RE::BGSListForm>();

    if (pilgrimStaffList) {
        staffFormLists.push_back(pilgrimStaffList);
    }

    logger::info("Loading dragon hunting staff list");
    auto dhStaffList = dataHandler->LookupForm(RE::FormID(0xC2A), "DragonHunting.esp")->As<RE::BGSListForm>();

    if (dhStaffList) {
        staffFormLists.push_back(dhStaffList);
    }

    logger::info("Loading formlist from patch");
    auto patchConcList = dataHandler->LookupForm(RE::FormID(0x800), "SimonrimStaffEnchantingPlusPerkPatch.esp")->As<RE::BGSListForm>();

    if (patchConcList) {
        fakeConcStaffList = patchConcList;
    }

    logger::info("Loaded settings");
    logger::info("");
}
