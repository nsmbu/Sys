#pragma once

#include <cafe/os/OSMutex.h>

namespace nw { namespace ut {

class Mutex
{
public:
    Mutex()
        : m_IsIntialized(false)
    {
    }

    ~Mutex()
    {
    }

    void Initialize()
    {
        if (!m_IsIntialized)
        {
            m_IsIntialized = true;
            OSInitMutex(&m_Lock);
        }
    }

    void Finalize()
    {
        m_IsIntialized = false;
    }

    void Lock()
    {
        // NW_ASSERT(m_IsIntialized);
        OSLockMutex(&m_Lock);
    }

    bool TryLock()
    {
        // NW_ASSERT(m_IsIntialized);
        return OSTryLockMutex(&m_Lock) != false;
    }

    void Unlock()
    {
        // NW_ASSERT(m_IsIntialized);
        OSUnlockMutex(&m_Lock);
    }

    // TODO
    // void WaitCond(OSCond& cond)
    // {
    //     // NW_ASSERT(m_IsIntialized);
    //     OSWaitCond(&cond, &m_Lock);
    // }

private:
    OSMutex m_Lock;
    bool m_IsIntialized;
};
static_assert(sizeof(Mutex) == 0x30, "nw::ut::Mutex size mismatch");

} }
