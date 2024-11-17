#pragma once

namespace Hooks
{
    void Install() noexcept;
    constexpr auto  IsInListConditionFunction = REL::ID(21539);

    class IsInListPatch
    {
    public:
        static void                                            Install();
        static std::int32_t                                    GetItemIndex(const RE::BGSListForm* a_list, const RE::TESForm* a_item);
        inline static REL::Relocation<decltype(&GetItemIndex)> _GetItemIndex;
    };
} // namespace Hooks
