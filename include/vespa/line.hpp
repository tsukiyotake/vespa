#ifndef __VESPA_LINE__
#define __VESPA_LINE__

#include "coord.hpp"

namespace vespa {

    template<class type, size_t dim>
    class line {
    public:
        using coord_type = coord<type, dim>;
    public:
        constexpr line(coord_type const& begin, coord_type end)noexcept: start_(begin), stop_(end) {}

        constexpr coord_type const& start() const noexcept { return start_; }
        constexpr coord_type& start() noexcept { return start_; }
        constexpr coord_type const& stop() const noexcept { return stop_; }
        constexpr coord_type& stop() noexcept { return stop_; }

    private:
        coord_type start_, stop_;

    };

}

#endif
