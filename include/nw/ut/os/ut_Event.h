#ifndef NW_UT_EVENT_H_
#define NW_UT_EVENT_H_

#include <cafe/os.h>

namespace nw { namespace ut {

class Event
{
public:
    Event(bool manualReset, bool initialState);
    ~Event();

    void Signal();
    void Reset();
    void Wait();
    bool TryWait();

  private:
    OSEvent m_Event;
};
static_assert(sizeof(Event) == 0x24);

} } // namespace nw::ut

#endif // NW_UT_EVENT_H_
