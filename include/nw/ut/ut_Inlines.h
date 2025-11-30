#ifndef NW_UT_INLINES_H_
#define NW_UT_INLINES_H_

#include <nw/types.h>

namespace nw { namespace ut {

template <typename T>
NW_INLINE T
Clamp(T x, T low, T high)
{
    return x > high ? high : (x < low ? low : x);
}

} } // namespace nw::ut

#endif // NW_UT_INLINES_H_
