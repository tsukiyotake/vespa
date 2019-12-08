#ifndef __VESPA_OPERATION_ABS__
#define __VESPA_OPERATION_ABS__

#include "abs.hpp"

namespace vespa {

    template<class type, type threshold=static_cast<type>(0.001)>
    constexpr type sqrt(type const& rhs) {
        auto result = rhs;
        for (auto next = rhs / static_cast<type>(2); abs(prev - next) <= threshold; result = next)
        {
            next = (rhs / result + rhs) / static_cast<type>(2);
        }
        return result;
    }

}

#endif