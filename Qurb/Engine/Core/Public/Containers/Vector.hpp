/// \file Vector.hpp

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
    template <typename T>
    class QURB_API Vector
    {
    public:
        using ElementType = T;

    public:
        //--------------------------------------------------------------------------------------------------------------
        // Constructors
        //--------------------------------------------------------------------------------------------------------------

        constexpr Vector() noexcept;
        constexpr explicit Vector(usize count) noexcept;
        constexpr Vector(usize count, const T& value) noexcept;
        constexpr Vector(std::initializer_list<T> init) noexcept;

        constexpr Vector(const Vector& other) noexcept;
        constexpr Vector(Vector&& other) noexcept;

        constexpr ~Vector() noexcept;

    public:
        constexpr auto operator=(const Vector& other) noexcept -> Vector&;
        constexpr auto operator=(Vector&& other) noexcept -> Vector&;

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
        [[nodiscard]] constexpr auto capacity() const noexcept -> usize;

        constexpr auto reserve(usize size) noexcept -> void;

        //--------------------------------------------------------------------------------------------------------------
        // Modifiers
        //--------------------------------------------------------------------------------------------------------------

        constexpr auto clear() noexcept -> void;

        constexpr auto erase(const T* first, const T* last) noexcept -> T*;
        constexpr auto erase(const T* pos) noexcept -> T*;

        constexpr auto pushBack(const T& value) noexcept -> void;
        constexpr auto pushBack(T&& value) noexcept -> void;

        template <typename... Args>
        constexpr auto emplaceBack(Args&&... args) noexcept -> T&;

        constexpr auto popBack() noexcept -> void;

        constexpr auto resize(usize size) noexcept -> void;
        constexpr auto resize(usize size, const T& value) noexcept -> void;

    private:
        static constexpr auto growthFactor = 1.5f;

        auto realloc(usize capacity) -> void;

    private:
        T*    _data;
        usize _size;
        usize _capacity;
    };

    template <typename T>
    struct IsVector : FalseType
    {};

    template <typename T>
    struct IsVector<Vector<T>> : TrueType
    {};

    template <typename T>
    inline constexpr bool isVectorV = IsVector<T>::value;

    template <typename T>
    constexpr Vector<T>::Vector() noexcept
        : _data(nullptr)
        , _size(0)
        , _capacity(0)
    {}

    template <typename T>
    constexpr Vector<T>::Vector(usize count) noexcept
        : Vector(count, T())
    {}

    template <typename T>
    constexpr Vector<T>::Vector(usize count, const T& value) noexcept
        : _data(nullptr)
        , _size(0)
        , _capacity(0)
    {
        realloc(count);
        _size = count;
        for (usize i = 0; i < _size; ++i)
        {
            new (&_data[i]) T(value);
        }
    }

    template <typename T>
    constexpr Vector<T>::Vector(std::initializer_list<T> init) noexcept
        : _data(nullptr)
        , _size(0)
        , _capacity(0)
    {
        realloc(init.size());
        for (const T& elem : init)
        {
            new (&_data[_size]) T(elem);
            ++_size;
        }
    }

    template <typename T>
    constexpr Vector<T>::Vector(const Vector& other) noexcept
        : _data(nullptr)
        , _size(0)
        , _capacity(0)
    {
        realloc(other._capacity);

        for (usize i = 0; i < other._size; ++i)
        {
            new (&_data[i]) T(other._data[i]);
        }
        _size = other._size;
    }

    template <typename T>
    constexpr Vector<T>::Vector(Vector&& other) noexcept
        : _data(std::move(other._data))
        , _size(other._size)
        , _capacity(other._capacity)
    {
        other._data     = nullptr;
        other._size     = 0;
        other._capacity = 0;
    }

    template <typename T>
    constexpr Vector<T>::~Vector() noexcept
    {
        clear();
        operator delete(_data, _capacity * sizeof(T));
    }

    template <typename T>
    constexpr auto Vector<T>::operator=(const Vector& other) noexcept -> Vector&
    {
        if (this != &other)
        {
            clear();
            reserve(other._capacity);

            for (usize i = 0; i < other._size; ++i)
            {
                new (&_data[i]) T(other._data[i]);
            }
            _size = other._size;
        }
        return *this;
    }

    template <typename T>
    constexpr auto Vector<T>::operator=(Vector&& other) noexcept -> Vector&
    {
        if (this != &other)
        {
            clear();
            ::operator delete(_data, _capacity * sizeof(T));

            _data     = other._data;
            _size     = other._size;
            _capacity = other._capacity;

            other._data     = nullptr;
            other._size     = 0;
            other._capacity = 0;
        }
        return *this;
    }

    template <typename T>
    constexpr auto Vector<T>::at(usize index) -> T&
    {
        if (index >= _size)
        {
            throw std::out_of_range("Vector::at() index out of range");
        }
        return _data[index];
    }

    template <typename T>
    constexpr auto Vector<T>::at(usize index) const -> const T&
    {
        if (index >= _size)
        {
            throw std::out_of_range("Vector::at() index out of range");
        }
        return _data[index];
    }

    template <typename T>
    constexpr auto Vector<T>::operator[](usize index) noexcept -> T&
    {
        return _data[index];
    }

    template <typename T>
    constexpr auto Vector<T>::operator[](usize index) const noexcept -> const T&
    {
        return _data[index];
    }

    template <typename T>
    constexpr auto Vector<T>::front() noexcept -> T&
    {
        return _data[0];
    }

    template <typename T>
    constexpr auto Vector<T>::front() const noexcept -> const T&
    {
        return _data[0];
    }

    template <typename T>
    constexpr auto Vector<T>::back() noexcept -> T&
    {
        return _data[_size - 1];
    }

    template <typename T>
    constexpr auto Vector<T>::back() const noexcept -> const T&
    {
        return _data[_size - 1];
    }

    template <typename T>
    constexpr auto Vector<T>::data() noexcept -> T*
    {
        return _data;
    }

    template <typename T>
    constexpr auto Vector<T>::data() const noexcept -> const T*
    {
        return _data;
    }

    template <typename T>
    constexpr auto Vector<T>::begin() noexcept -> T*
    {
        return _data;
    }

    template <typename T>
    constexpr auto Vector<T>::begin() const noexcept -> const T*
    {
        return _data;
    }

    template <typename T>
    constexpr auto Vector<T>::cbegin() const noexcept -> const T*
    {
        return _data;
    }

    template <typename T>
    constexpr auto Vector<T>::end() noexcept -> T*
    {
        return _data + _size;
    }

    template <typename T>
    constexpr auto Vector<T>::end() const noexcept -> const T*
    {
        return _data + _size;
    }

    template <typename T>
    constexpr auto Vector<T>::cend() const noexcept -> const T*
    {
        return _data + _size;
    }

    template <typename T>
    constexpr auto Vector<T>::empty() const noexcept -> bool
    {
        return _size == 0;
    }

    template <typename T>
    constexpr auto Vector<T>::size() const noexcept -> usize
    {
        return _size;
    }

    template <typename T>
    constexpr auto Vector<T>::capacity() const noexcept -> usize
    {
        return _capacity;
    }

    template <typename T>
    constexpr auto Vector<T>::reserve(usize size) noexcept -> void
    {
        if (size > _capacity)
        {
            realloc(size);
        }
    }

    template <typename T>
    constexpr auto Vector<T>::clear() noexcept -> void
    {
        for (usize i = 0; i < _size; ++i)
        {
            _data[i].~T();
        }

        _size = 0;
    }

    template <typename T>
    constexpr auto Vector<T>::erase(const T* first, const T* last) noexcept -> T*
    {
        // Compute iterators into our buffer.
        auto write = begin() + (first - _data);
        auto read  = begin() + (last - _data);
        auto itEnd = end();

        // Shift the elements after [first,last) down to `write`.
        for (; read != itEnd; ++read, ++write)
        {
            *write = std::move(*read);
        }

        // Destroy the now-unused tail elements.
        auto newSize = write - begin();
        for (auto destroyIt = begin() + newSize; destroyIt != itEnd; ++destroyIt)
        {
            destroyIt->~T();
        }

        _size = newSize;
        return begin() + (first - _data);
    }

    template <typename T>
    constexpr auto Vector<T>::erase(const T* pos) noexcept -> T*
    {
        auto idx = pos - _data;
        return erase(begin() + idx, begin() + idx + 1);
    }

    template <typename T>
    constexpr auto Vector<T>::pushBack(const T& value) noexcept -> void
    {
        if (_size >= _capacity)
        {
            realloc(_capacity * growthFactor);
        }

        new (&_data[_size]) T(value);
        ++_size;
    }

    template <typename T>
    constexpr auto Vector<T>::pushBack(T&& value) noexcept -> void
    {
        if (_size >= _capacity)
        {
            realloc(_capacity * growthFactor);
        }

        new (&_data[_size]) T(std::move(value));
        ++_size;
    }

    template <typename T>
    template <typename... Args>
    constexpr auto Vector<T>::emplaceBack(Args&&... args) noexcept -> T&
    {
        if (_size >= _capacity)
        {
            realloc(_capacity * growthFactor);
        }

        new (&_data[_size]) T(std::forward<Args>(args)...);
        return _data[_size++];
    }

    template <typename T>
    constexpr auto Vector<T>::popBack() noexcept -> void
    {
        if (_size > 0)
        {
            _data[--_size].~T();
        }
    }

    template <typename T>
    constexpr auto Vector<T>::resize(usize size) noexcept -> void
    {
        resize(size, T());
    }

    template <typename T>
    constexpr auto Vector<T>::resize(usize size, const T& value) noexcept -> void
    {
        if (size < _size)
        {
            for (usize i = size; i < _size; ++i)
            {
                _data[i].~T();
            }
        }
        else if (size > _size)
        {
            if (size > _capacity)
            {
                realloc(size);
            }
            for (usize i = _size; i < size; ++i)
            {
                new (&_data[i]) T(value);
            }
        }
        _size = size;
    }

    template <typename T>
    auto Vector<T>::realloc(usize capacity) -> void
    {
        if (capacity == 0)
        {
            capacity = 2;
        }

        T* newData = static_cast<T*>(::operator new(capacity * sizeof(T)));

        const usize elementsToCopy = (_size < capacity) ? _size : capacity;
        for (usize i = 0; i < elementsToCopy; ++i)
        {
            new (&newData[i]) T(std::move(_data[i]));
        }

        for (usize i = 0; i < _size; ++i)
        {
            _data[i].~T();
        }
        ::operator delete(_data, _capacity * sizeof(T));

        _data     = newData;
        _capacity = capacity;
        _size     = (_size > capacity) ? capacity : _size;
    }
}

template <typename T>
struct std::formatter<qurb::Vector<T>>
{
    constexpr auto parse(std::format_parse_context& ctx) { return ctx.begin(); }

    template <typename FormatContext>
    auto format(const qurb::Vector<T>& vector, FormatContext& ctx) const
    {
        auto out = ctx.out();
        out      = std::format_to(ctx.out(), "[");
        if (vector.size() > 0)
        {
            auto it = vector.begin();
            out     = std::format_to(out, "{}", *it);
            for (++it; it != vector.end(); ++it)
            {
                out = std::format_to(out, ", {}", *it);
            }
        }
        return std::format_to(out, "]");
    }
};
