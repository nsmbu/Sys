#ifndef NW_UT_BINARYFILEFORMAT_H_
#define NW_UT_BINARYFILEFORMAT_H_

#include <nw/types.h>

#define NW_UT_MAKE_SIGWORD(a, b, c, d)  \
    static_cast<nw::ut::SigWord>(       \
        (static_cast<u8>(a) << 24) |    \
        (static_cast<u8>(b) << 16) |    \
        (static_cast<u8>(c) <<  8) |    \
        (static_cast<u8>(d) <<  0)      \
    )

namespace nw { namespace ut {

typedef u32 SigWord;

} } // namespace nw::ut

#endif // NW_UT_BINARYFILEFORMAT_H_
