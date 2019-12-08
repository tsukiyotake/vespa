#ifndef __VESPA_OPERATION_ABS__
#define __VESPA_OPERATION_ABS__

#include "abs.hpp"

namespace vespa {

    template<class type, type threshold=static_cast<type>(0.001)>
    constexpr type sqrt(type const& rhs) {
        auto result =  rhs / static_cast<type>(2);
        auto previous, next;
        do  {
            previous = result;
            next = (rhs / previous + previous) / static_cast<type>(2);
            result = next;
        } while(abs(next - previous) > threshold);

        return result;
    }

}

#endif