#pragma once

#include <nw/ut/ut_HeapBase.h>

namespace nw { namespace ut {

// TODO
class FrameHeap : public HeapBase
{
private:
    struct HeapState
    {
        u32 tagName;
        void* headAllocator;
        void* tailAllocator;
        HeapState* pPrevState;

        HeapState()
            : tagName(0)
            , headAllocator(nullptr)
            , tailAllocator(nullptr)
            , pPrevState(nullptr)
        {
        }
    };

public:
    u32 GetAllocatableSize(int alignment = DEFAULT_ALIGNMENT);

private:
    void* mHeadAllocator;
    void* mTailAllocator;
    HeapState* mpState;
};
static_assert(sizeof(FrameHeap) == 0x34, "nw::ut::FrameHeap size mismatch");

} }
