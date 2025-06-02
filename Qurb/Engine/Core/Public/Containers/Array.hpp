/// \file Array.hpp

#pragma once

#include "CoreDefines.hpp"
#include "CoreTraits.hpp"
#include "CoreTypes.hpp"

#include <algorithm>
#include <format>
#include <initializer_list>
#include <stdexcept>

namespace qurb
{
    template <typename T, usize N>
    class QURB_API Array
    {
    public:
        constexpr Array() noexcept = default;
        constexpr Array(std::initializer_list<T> init) noexcept;

    public:
        //--------------------------------------------------------------------------------------------------------------
        // Element access
        //--------------------------------------------------------------------------------------------------------------

        constexpr auto               at(usize index) -> T&;
        [[nodiscard]] constexpr auto at(usize index) const -> const T&;

        constexpr auto operator[](usize index) noexcept -> T&;
        constexpr auto operator[](usize index) const noexcept -> const T&;

        constexpr auto               front() noexcept -> T&;
        [[nodiscard]] constexpr auto front() const noexcept -> const T&;

        constexpr auto               back() noexcept -> T&;
        [[nodiscard]] constexpr auto back() const noexcept -> const T&;

        constexpr auto               data() noexcept -> T*;
        [[nodiscard]] constexpr auto data() const noexcept -> const T*;

        //--------------------------------------------------------------------------------------------------------------
        // Iterators
        //--------------------------------------------------------------------------------------------------------------

        constexpr auto               begin() noexcept -> T*;
        [[nodiscard]] constexpr auto begin() const noexcept -> const T*;
        [[nodiscard]] constexpr auto cbegin() const noexcept -> const T*;

        constexpr auto               end() noexcept -> T*;
        [[nodiscard]] constexpr auto end() const noexcept -> const T*;
        [[nodiscard]] constexpr auto cend() const noexcept -> const T*;

        //--------------------------------------------------------------------------------------------------------------
        // Capacity
        //--------------------------------------------------------------------------------------------------------------

        [[nodiscard]] constexpr auto empty() const noexcept -> bool;
        [[nodiscard]] constexpr auto size() const noexcept -> usize;

        //--------------------------------------------------------------------------------------------------------------
        // Operations
        //--------------------------------------------------------------------------------------------------------------

        constexpr auto fill(const T& value) noexcept -> void;

    private:
        T _data[N];
    };

    template <typename T, typename... Args>
    Array(T, Args...) -> Array<T, 1 + sizeof...(Args)>;

    template <typename T>
    struct IsArray : FalseType
    {};

    template <typename T, usize N>
    struct IsArray<Array<T, N>> : TrueType
    {};

    template <typename T>
    inline constexpr bool isArrayV = IsArray<T>::value;

    //--------------------------------------------------------------------------------------------------------------
    // Constructors
    //--------------------------------------------------------------------------------------------------------------

    template <typename T, usize N>
    constexpr Array<T, N>::Array(std::initializer_list<T> init) noexcept
    {
        std::ranges::copy_n(init.begin(), N, std::ranges::begin(_data));
    }

    //------------------------------------------------------------------------------------------------------------------
    // Element access
    //------------------------------------------------------------------------------------------------------------------

    template <typename T, usize N>
    constexpr auto Array<T, N>::at(usize index) -> T&
    {
        if (index >= N)
        {
            throw std::out_of_range("Array::at() index out of range");
        }

        return _data[index];
    }

    template <typename T, usize N>
    constexpr auto Array<T, N>::at(usize index) const -> const T&
    {
        if (index >= N)
        {
            throw std::out_of_range("Array::at() index out of range");
        }

        return _data[index];
    }

    template <typename T, usize N>
    constexpr auto Array<T, N>::operator[](usize index) noexcept -> T&
    {
        return _data[index];
    }

    template <typename T, usize N>
    constexpr auto Array<T, N>::operator[](usize index) const noexcept -> const T&
    {
        return _data[index];
    }

    template <typename T, usize N>
    constexpr auto Array<T, N>::front() noexcept -> T&
    {
        return _data[0];
    }

    template <typename T, usize N>
    constexpr auto Array<T, N>::front() const noexcept -> const T&
    {
        return _data[0];
    }

    template <typename T, usize N>
    constexpr auto Array<T, N>::back() noexcept -> T&
    {
        return _data[N - 1];
    }

    template <typename T, usize N>
    constexpr auto Array<T, N>::back() const noexcept -> const T&
    {
        return _data[N - 1];
    }

    template <typename T, usize N>
    constexpr auto Array<T, N>::data() noexcept -> T*
    {
        return _data;
    }

    template <typename T, usize N>
    constexpr auto Array<T, N>::data() const noexcept -> const T*
    {
        return _data;
    }

    //------------------------------------------------------------------------------------------------------------------
    // Iterators
    //------------------------------------------------------------------------------------------------------------------

    template <typename T, usize N>
    constexpr auto Array<T, N>::begin() noexcept -> T*
    {
        return _data;
    }

    template <typename T, usize N>
    constexpr auto Array<T, N>::begin() const noexcept -> const T*
    {
        return _data;
    }

    template <typename T, usize N>
    constexpr auto Array<T, N>::cbegin() const noexcept -> const T*
    {
        return _data;
    }

    template <typename T, usize N>
    constexpr auto Array<T, N>::end() noexcept -> T*
    {
        return _data + N;
    }

    template <typename T, usize N>
    constexpr auto Array<T, N>::end() const noexcept -> const T*
    {
        return _data + N;
    }

    template <typename T, usize N>
    constexpr auto Array<T, N>::cend() const noexcept -> const T*
    {
        return _data + N;
    }

    //------------------------------------------------------------------------------------------------------------------
    // Capacity
    //------------------------------------------------------------------------------------------------------------------

    template <typename T, usize N>
    constexpr auto Array<T, N>::empty() const noexcept -> bool
    {
        return false;
    }

    template <typename T, usize N>
    constexpr auto Array<T, N>::size() const noexcept -> usize
    {
        return N;
    }

    //------------------------------------------------------------------------------------------------------------------
    // Operations
    //------------------------------------------------------------------------------------------------------------------

    template <typename T, usize N>
    constexpr auto Array<T, N>::fill(const T& value) noexcept -> void
    {
        std::ranges::fill(_data, value);
    }

    template <typename T>
    class Array<T, 0>
    {};
}

template <typename T, qurb::usize N>
struct std::formatter<qurb::Array<T, N>>
{
    constexpr auto parse(std::format_parse_context& ctx) { return ctx.begin(); }

    template <typename FormatContext>
    auto format(const qurb::Array<T, N>& array, FormatContext& ctx) const
    {
        auto out = ctx.out();
        out      = std::format_to(out, "[");

        if constexpr (N > 0)
        {
            const auto it = array.begin();
            out           = std::format_to(out, "{}", *it);

            for (++it; it != array.end(); ++it)
            {
                out = std::format_to(out, ", {}", *it);
            }
        }
        return std::format_to(out, "]");
    }
};
