#pragma once

namespace nw { namespace ut {

template <typename TLockObject>
class ScopedLock
{
private:
    // NW_DISALLOW_COPY_AND_ASSIGN(ScopedLock); // TODO

public:
    explicit ScopedLock(TLockObject& lockObj)
        : m_LockObj(lockObj)
    {
        m_LockObj.Lock();
    }

    ~ScopedLock()
    {
        m_LockObj.Unlock();
    }

private:
    TLockObject& m_LockObj;
};

} }
