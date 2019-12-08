#ifndef __VESPA_OPERATION_ABS__
#define __VESPA_OPERATION_ABS__

namespace vespa {

    template<class type>
    constexpr type abs(type const& rhs)noexcept {
        return rhs >= 0 ? rhs : -rhs;
    }

}

#endif