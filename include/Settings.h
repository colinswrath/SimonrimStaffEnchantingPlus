#pragma once

class Settings
{
public:
    inline static std::vector<RE::BGSListForm*> staffFormLists{};
    inline static RE::BGSListForm*              fakeConcStaffList{};

    static void LoadSettings() noexcept;

    inline static bool debug_logging{};
};
