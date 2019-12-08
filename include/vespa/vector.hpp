#ifndef __VESPA_vector__
#define __VESPA_vector__

#include <array>

namespace vespa {

    template<class type, size_t dim>
    class vector {
    public:
        constexpr static size_t dimension = dim;
        using value_type = type;

    private:
        template<class other, size_t ... index>
        constexpr vector& iadd(vector<other> const& rhs, std::index_sequence<index...>)noexcept
        {
            return ((values_[index] += rhs[index]), ..., *this);
        }

        template<class other, size_t ... index>
        constexpr vector& iadd(other const& rhs, std::index_sequence<index...>)noexcept
        {
            return ((values_[index] += rhs), ..., *this);
        }

        template<class other, size_t ... index>
        constexpr vector& isub(vector<other> const& rhs, std::index_sequence<index...>)noexcept
        {
            return ((values_[index] -= rhs[index]), ..., *this);
        }

        template<class other, size_t ... index>
        constexpr vector& isub(other const& rhs, std::index_sequence<index...>)noexcept
        {
            return ((values_[index] -= rhs), ..., *this);
        }

        template<class other, size_t ... index>
        constexpr vector& imul(vector<other> const& rhs, std::index_sequence<index...>)noexcept
        {
            return ((values_[index] *= rhs[index]), ..., *this);
        }

        template<class other, size_t ... index>
        constexpr vector& imul(other const& rhs, std::index_sequence<index...>)noexcept
        {
            return ((values_[index] *= rhs), ..., *this);
        }

        template<class other, size_t ... index>
        constexpr vector& idiv(vector<other> const& rhs, std::index_sequence<index...>)noexcept
        {
            return ((values_[index] /= rhs[index]), ..., *this);
        }

        template<class other, size_t ... index>
        constexpr vector& idiv(other const& rhs, std::index_sequence<index...>)noexcept
        {
            return ((values_[index] /= rhs), ..., *this);
        }

        template<size_t ... index>
        constexpr vector inv(std::index_sequence<index...> seq)const noexcept { return vector(-values_[index]..., seq) }

        template<size_t ... index>
        constexpr vector square(std::index_sequence<index...>)const noexcept { return (values_[index] * values_[index]) + ...; }

    public:
        constexpr vector(): values_{} {}

        template<size_t ... index>
        constexpr vector(std::initializer_list<value_type> list, std::index_sequence<index...>)noexcept:
            values_{ list.begin()[index]... } {}

        constexpr vector(std::initializer_list<value_type> list)noexcept: vector(list, std::make_index_sequence<dimension>) {}

        constexpr value_type const& operator[](size_t index)const noexcept { return values_[index]; }
        constexpr value_type& operator[](size_t index)noexcept { return values_[index]; }

        constexpr vector operator-()const noexcept {
            return inv(std::make_index_sequence<dimension>());
        }

        constexpr vector const& operator+()const noexcept { return *this; }

    public:
        template<class other_type>
        constexpr vector& operator+=(vector<other_type, dimension>const& rhs)noexcept {
            return iadd(rhs, std::make_index_sequence<dimension>());
        }

        template<class other_type>
        constexpr vector& operator+=(other_type const& rhs)noexcept {
            return iadd(rhs, std::make_index_sequence<dimension>());
        }

        template<class other_type>
        constexpr vector& operator-=(vector<other_type, dimension>const& rhs)noexcept {
            return isub(rhs, std::make_index_sequence<dimension>());
        }

        template<class other_type>
        constexpr vector& operator-=(other_type const& rhs)noexcept {
            return isub(rhs, std::make_index_sequence<dimension>());
        }

                template<class other_type>
        constexpr vector& operator*=(vector<other_type, dimension>const& rhs)noexcept {
            return imul(rhs, std::make_index_sequence<dimension>());
        }

        template<class other_type>
        constexpr vector& operator*=(other_type const& rhs)noexcept {
            return imul(rhs, std::make_index_sequence<dimension>());
        }

                template<class other_type>
        constexpr vector& operator/=(vector<other_type, dimension>const& rhs)noexcept {
            return idiv(rhs, std::make_index_sequence<dimension>());
        }

        template<class other_type>
        constexpr vector& operator/=(other_type const& rhs)noexcept {
            return idiv(rhs, std::make_index_sequence<dimension>());
        }

    public:
        constexpr value_type square()const noexcept {
            return square(std::make_index_sequence<dimension>());
        }

    private:
        std::array<value_type, dimension> values_;

    };

    namespace {

        template<class ltype, class rtype, size_t ... index>
        inline constexpr auto add(vector<ltype, sizeof...(index)> const& lhs, vector<rtype, sizeof...(index)> const& rhs, std::index_sequence<index...> seq)noexcept {
            using reult_type = decltype(std::declval<ltype>() + std::declval<rtype>());
            return vector<reult_type, sizeof...(index)>((lhs[index] + rhs[index])..., seq);
        }

        template<class ltype, class rtype, size_t ... index>
        inline constexpr auto add(vector<ltype, sizeof...(index)> const& lhs, rtype const& rhs, std::index_sequence<index...> seq)noexcept {
            using reult_type = decltype(std::declval<ltype>() + std::declval<rtype>());
            return vector<reult_type, sizeof...(index)>((lhs[index] + rhs)..., seq);
        }

        template<class ltype, class rtype, size_t ... index>
        inline constexpr auto add(ltype const& lhs, vector<rtype, sizeof...(index)> const& rhs, std::index_sequence<index...> seq)noexcept {
            using reult_type = decltype(std::declval<ltype>() + std::declval<rtype>());
            return vector<reult_type, sizeof...(index)>((lhs + rhs[index])..., seq);
        }

        template<class ltype, class rtype, size_t ... index>
        inline constexpr auto sub(vector<ltype, sizeof...(index)> const& lhs, vector<rtype, sizeof...(index)> const& rhs, std::index_sequence<index...> seq)noexcept {
            using reult_type = decltype(std::declval<ltype>() - std::declval<rtype>());
            return vector<reult_type, sizeof...(index)>((lhs[index] - rhs[index])..., seq);
        }

        template<class ltype, class rtype, size_t ... index>
        inline constexpr auto sub(vector<ltype, sizeof...(index)> const& lhs, rtype const& rhs, std::index_sequence<index...> seq)noexcept {
            using reult_type = decltype(std::declval<ltype>() - std::declval<rtype>());
            return vector<reult_type, sizeof...(index)>((lhs[index] - rhs)..., seq);
        }

        template<class ltype, class rtype, size_t ... index>
        inline constexpr auto sub(ltype const& lhs, vector<rtype, sizeof...(index)> const& rhs, std::index_sequence<index...> seq)noexcept {
            using reult_type = decltype(std::declval<ltype>() - std::declval<rtype>());
            return vector<reult_type, sizeof...(index)>((lhs - rhs[index])..., seq);
        }

        template<class ltype, class rtype, size_t ... index>
        inline constexpr auto mul(vector<ltype, sizeof...(index)> const& lhs, vector<rtype, sizeof...(index)> const& rhs, std::index_sequence<index...> seq)noexcept {
            using reult_type = decltype(std::declval<ltype>() * std::declval<rtype>());
            return vector<reult_type, sizeof...(index)>((lhs[index] * rhs[index])..., seq);
        }

        template<class ltype, class rtype, size_t ... index>
        inline constexpr auto mul(vector<ltype, sizeof...(index)> const& lhs, rtype const& rhs, std::index_sequence<index...> seq)noexcept {
            using reult_type = decltype(std::declval<ltype>() * std::declval<rtype>());
            return vector<reult_type, sizeof...(index)>((lhs[index] * rhs)..., seq);
        }

        template<class ltype, class rtype, size_t ... index>
        inline constexpr auto mul(ltype const& lhs, vector<rtype, sizeof...(index)> const& rhs, std::index_sequence<index...> seq)noexcept {
            using reult_type = decltype(std::declval<ltype>() * std::declval<rtype>());
            return vector<reult_type, sizeof...(index)>((lhs * rhs[index])..., seq);
        }

        template<class ltype, class rtype, size_t ... index>
        inline constexpr auto div(vector<ltype, sizeof...(index)> const& lhs, vector<rtype, sizeof...(index)> const& rhs, std::index_sequence<index...> seq)noexcept {
            using reult_type = decltype(std::declval<ltype>() / std::declval<rtype>());
            return vector<reult_type, sizeof...(index)>((lhs[index] / rhs[index])..., seq);
        }

        template<class ltype, class rtype, size_t ... index>
        inline constexpr auto div(vector<ltype, sizeof...(index)> const& lhs, rtype const& rhs, std::index_sequence<index...> seq)noexcept {
            using reult_type = decltype(std::declval<ltype>() / std::declval<rtype>());
            return vector<reult_type, sizeof...(index)>((lhs[index] / rhs)..., seq);
        }

        template<class ltype, class rtype, size_t ... index>
        inline constexpr auto div(ltype const& lhs, vector<rtype, sizeof...(index)> const& rhs, std::index_sequence<index...> seq)noexcept {
            using reult_type = decltype(std::declval<ltype>() / std::declval<rtype>());
            return vector<reult_type, sizeof...(index)>((lhs / rhs[index])..., seq);
        }

        template<class ltype, class rtype, size_t ... index>
        inline constexpr auto dot(vector<ltype, sizeof...(index)> const& lhs, vector<ltype, sizeof...(index)> const& rhs)noexcept {
            return (lhs[index] * rhs[index]) + ...;
        }

    }

    template<class ltype, class rtype, size_t dim>
    inline constexpr auto operator+(vector<ltype, dim> const& lhs, vector<rtype, dim> const& rhs)noexcept {
        return add(lhs, rhs, std::make_index_sequence<dim>());
    }

    template<class ltype, class rtype, size_t dim>
    inline constexpr auto operator+(vector<ltype, dim> const& lhs, rtype const& rhs)noexcept {
        return add(lhs, rhs, std::make_index_sequence<dim>());
    }

    template<class ltype, class rtype, size_t dim>
    inline constexpr auto operator+(ltype const& lhs, vector<rtype, dim> const& rhs)noexcept {
        return add(lhs, rhs, std::make_index_sequence<dim>());
    }

    template<class ltype, class rtype, size_t dim>
    inline constexpr auto operator-(vector<ltype, dim> const& lhs, vector<rtype, dim> const& rhs)noexcept {
        return sub(lhs, rhs, std::make_index_sequence<dim>());
    }

    template<class ltype, class rtype, size_t dim>
    inline constexpr auto operator-(vector<ltype, dim> const& lhs, rtype const& rhs)noexcept {
        return sub(lhs, rhs, std::make_index_sequence<dim>());
    }

    template<class ltype, class rtype, size_t dim>
    inline constexpr auto operator-(ltype const& lhs, vector<rtype, dim> const& rhs)noexcept {
        return sub(lhs, rhs, std::make_index_sequence<dim>());
    }

    template<class ltype, class rtype, size_t dim>
    inline constexpr auto operator*(vector<ltype, dim> const& lhs, vector<rtype, dim> const& rhs)noexcept {
        return mul(lhs, rhs, std::make_index_sequence<dim>());
    }

    template<class ltype, class rtype, size_t dim>
    inline constexpr auto operator*(vector<ltype, dim> const& lhs, rtype const& rhs)noexcept {
        return mul(lhs, rhs, std::make_index_sequence<dim>());
    }

    template<class ltype, class rtype, size_t dim>
    inline constexpr auto operator*(ltype const& lhs, vector<rtype, dim> const& rhs)noexcept {
        return mul(lhs, rhs, std::make_index_sequence<dim>());
    }

    template<class ltype, class rtype, size_t dim>
    inline constexpr auto operator/(vector<ltype, dim> const& lhs, vector<rtype, dim> const& rhs)noexcept {
        return div(lhs, rhs, std::make_index_sequence<dim>());
    }

    template<class ltype, class rtype, size_t dim>
    inline constexpr auto operator/(vector<ltype, dim> const& lhs, rtype const& rhs)noexcept {
        return div(lhs, rhs, std::make_index_sequence<dim>());
    }

    template<class ltype, class rtype, size_t dim>
    inline constexpr auto operator/(ltype const& lhs, vector<rtype, dim> const& rhs)noexcept {
        return div(lhs, rhs, std::make_index_sequence<dim>());
    }

    template<class ltype, class rtype, size_t dim>
    inline constexpr auto dot(vector<ltype, dim> const& lhs, vector<rtype, dim> const& rhs)noexcept {
        return dot(lhs, rhs, std::make_index_sequence<dim>());
    }

}

#endif
