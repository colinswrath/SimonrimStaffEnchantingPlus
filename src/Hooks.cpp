#include "Hooks.h"
#include "Settings.h"

namespace Hooks
{
    void Install() noexcept
    {
        IsInListPatch::Install();
        logger::info("Installed list condition hook");
        logger::info("");
    }

    void IsInListPatch::Install()
    {
        auto hook = REL::Relocation<std::uintptr_t>(IsInListConditionFunction, 0x46);
        REL::make_pattern<"E8">().match_or_fail(hook.address());

        auto& trampoline = SKSE::GetTrampoline();
        _GetItemIndex    = trampoline.write_call<5>(hook.address(), &GetItemIndex);
    }

    std::int32_t IsInListPatch::GetItemIndex(const RE::BGSListForm* a_list, const RE::TESForm* a_item)
    {
        //Get formlists to check
        //Pilgrim
        //Mysticism
        //Dragon hunting staff list

        if (a_list && std::ranges::find(Settings::staffFormLists, a_list) != Settings::staffFormLists.end()) {
            if (const auto enchantment = a_item->As<RE::EnchantmentItem>()) {
                if (enchantment->data.spellType == RE::MagicSystem::SpellType::kStaffEnchantment) {
                    logger::debug("Is general staff enchant");

                    return 0;
                }
            }
            return -1;
        }
        else if (a_list && a_list == Settings::fakeConcStaffList) {
            if (const auto enchantment = a_item->As<RE::EnchantmentItem>()) {
                if (enchantment->data.castingType == RE::MagicSystem::CastingType::kConcentration)
                {
                    logger::debug("Item is conc staff enchant list check");
                    return 0;
                }
            }
            return -1;
        }
        else {
            return _GetItemIndex(a_list, a_item);
        }
    }
} // namespace Hooks
