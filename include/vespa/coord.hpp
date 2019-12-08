#ifndef __VESPA_COORD__
#define __VESPA_COORD__

#include "vector.hpp"

namespace vespa {

    template<class type, size_t dim>
    class coord : public vector<type, dim> {};

    template<class type>
    class coord<type, 2> : public vector<type, 2> {
    public:
        constexpr value_type const& x()const noexcept { return (*this)[0]; }
        constexpr value_type & x()noexcept { return (*this)[0]; }
        constexpr value_type const& y()const noexcept { return (*this)[1]; }
        constexpr value_type & y()noexcept { return (*this)[1]; }

    };

    template<class type>
    class coord<type, 3> : public vector<type, 3> {
    public:
        constexpr value_type const& x()const noexcept { return (*this)[0]; }
        constexpr value_type & x()noexcept { return (*this)[0]; }
        constexpr value_type const& y()const noexcept { return (*this)[1]; }
        constexpr value_type & y()noexcept { return (*this)[1]; }
        constexpr value_type const& z()const noexcept { return (*this)[2]; }
        constexpr value_type & z()noexcept { return (*this)[2]; }

    };

    template<class type>
    class coord<type, 4> : public vector<type, 4> {
    public:
        constexpr value_type const& x()const noexcept { return (*this)[0]; }
        constexpr value_type & x()noexcept { return (*this)[0]; }
        constexpr value_type const& y()const noexcept { return (*this)[1]; }
        constexpr value_type & y()noexcept { return (*this)[1]; }
        constexpr value_type const& z()const noexcept { return (*this)[2]; }
        constexpr value_type & z()noexcept { return (*this)[2]; }
        constexpr value_type const& w()const noexcept { return (*this)[3]; }
        constexpr value_type & w()noexcept { return (*this)[3]; }
    };

}

#endif