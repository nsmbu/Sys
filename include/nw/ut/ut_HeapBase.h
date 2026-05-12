#pragma once

#include <nw/ut/ut_LinkList.h>

namespace nw { namespace ut {

class HeapNode
{
public:
    HeapNode()
    {
    }

    virtual ~HeapNode()
    {
    }

public:
    LinkListNode mLinkNode;
};
static_assert(sizeof(HeapNode) == 0xC, "");

// TODO
class HeapBase : public HeapNode
{
public:
    typedef ut::LinkList<HeapBase, offsetof(HeapNode, mLinkNode)> HeapList;

    static const int DEFAULT_ALIGNMENT = 4;

    void* GetHeapStartAddress() { return this; }
    void* GetHeapEndAddress()   { return mHeapEnd; }

    s32 GetTotalSize()          { return ((s32)(mHeapEnd) - (s32)(this)); }
    s32 GetTotalUsableSize()    { return ((s32)(mHeapEnd) - (s32)(mHeapStart)); }

protected:
    void* mHeapStart;
    void* mHeapEnd;

private:
    u32 mSignature;
    HeapList mChildList;
    u32 mAttribute;
};
static_assert(sizeof(HeapBase) == 0x28, "");

} }
