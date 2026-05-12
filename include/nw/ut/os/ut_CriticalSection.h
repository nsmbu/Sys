#pragma once

#include <nw/ut/ut_ScopedLock.h>
#include <nw/ut/os/ut_Mutex.h>

namespace nw { namespace ut {

class CriticalSection
{
public:
    CriticalSection()
    {
        m_Mutex.Initialize();
    }

    ~CriticalSection()
    {
        m_Mutex.Finalize();
    }

    void Enter()
    {
        m_Mutex.Lock();
    }

    bool TryEnter()
    {
        return m_Mutex.TryLock();
    }

    void Leave()
    {
        m_Mutex.Unlock();
    }

    void Lock()
    {
        Enter();
    }

    bool TryLock()
    {
        return TryEnter();
    }

    void Unlock()
    {
        Leave();
    }

private:
    ut::Mutex m_Mutex;
};
static_assert(sizeof(CriticalSection) == 0x30, "nw::ut::CriticalSection size mismatch");

template <>
class ScopedLock<CriticalSection>
{
private:
    // NW_DISALLOW_COPY_AND_ASSIGN(ScopedLock); // TODO

public:
    explicit ScopedLock(CriticalSection& lockObj)
        : m_LockObj(lockObj)
    {
        m_LockObj.Enter();
    }

    ~ScopedLock()
    {
        m_LockObj.Leave();
    }

private:
    CriticalSection& m_LockObj;
};

} }
