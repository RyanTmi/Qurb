#pragma once

#include "CoreTypes.hpp"

#include <type_traits>

namespace qurb::rhi
{
    /// \brief The `Object` class.
    class Object
    {
    public:
        Object() noexcept;
        virtual ~Object() = default;

        Object(const Object&) = delete;
        Object(Object&&)      = delete;

        Object& operator=(const Object&) = delete;
        Object& operator=(Object&&)      = delete;

    public:
        auto release() -> void;
        auto retain() -> void;

        [[nodiscard]] auto retainCount() const -> uint64;

    private:
        uint64 _retainCount;
    };

    /// \brief The `Ref` class.
    template <typename T>
    class Ref final
    {
    public:
        constexpr Ref() noexcept;
        constexpr explicit Ref(std::nullptr_t) noexcept;
        constexpr explicit Ref(T* ptr) noexcept;

        // template <typename U>
        // constexpr explicit Ref(U* ptr) noexcept;

        ~Ref() noexcept;

        constexpr Ref(const Ref& other) noexcept;
        constexpr Ref(Ref&& other) noexcept;


        template <typename U>
        constexpr Ref(const Ref<U>& other) noexcept;

        template <typename U>
        constexpr Ref(Ref<U>&& other) noexcept;

        auto operator=(const Ref& other) noexcept -> Ref&;
        auto operator=(Ref&& other) noexcept -> Ref&;

    public:
        auto get() const noexcept -> T*;
        auto operator*() const noexcept -> T&;
        auto operator->() const noexcept -> T*;
        operator bool() const noexcept;

        auto reset(T* ptr = nullptr) noexcept -> void;
        auto swap(Ref& o) noexcept -> void;

        template <typename U>
        auto as() const noexcept -> Ref<U>;

    private:
        template <typename U>
        friend class Ref;

        auto retain() noexcept -> void;
        auto release() noexcept -> void;

    private:
        T* _ptr;
    };

    //-----------------------------------------------------------------------------------------------------------------
    // class Object
    //-----------------------------------------------------------------------------------------------------------------

    inline Object::Object() noexcept
        : _retainCount(1)
    {}

    inline auto Object::release() -> void
    {
        if (--_retainCount == 0)
        {
            delete this;
        }
    }

    inline auto Object::retain() -> void
    {
        ++_retainCount;
    }

    inline auto Object::retainCount() const -> uint64
    {
        return _retainCount;
    }

    //-----------------------------------------------------------------------------------------------------------------
    // class Ref
    //-----------------------------------------------------------------------------------------------------------------

    template <typename T>
    constexpr Ref<T>::Ref() noexcept
        : _ptr(nullptr)
    {}

    template <typename T>
    constexpr Ref<T>::Ref(std::nullptr_t) noexcept
        : _ptr(nullptr)
    {}

    template <typename T>
    constexpr Ref<T>::Ref(T* ptr) noexcept
        : _ptr(ptr)
    {}

    template <typename T>
    Ref<T>::~Ref() noexcept
    {
        release();
    }

    template <typename T>
    constexpr Ref<T>::Ref(const Ref& other) noexcept
        : _ptr(other._ptr)
    {
        retain();
    }

    template <typename T>
    constexpr Ref<T>::Ref(Ref&& other) noexcept
        : _ptr(other._ptr)
    {
        other._ptr = nullptr;
    }

    template <typename T>
    template <typename U>
    constexpr Ref<T>::Ref(const Ref<U>& other) noexcept
        : _ptr(other._ptr)
    {
        retain();
    }

    template <typename T>
    template <typename U>
    constexpr Ref<T>::Ref(Ref<U>&& other) noexcept
        : _ptr(other._ptr)
    {
        other._ptr = nullptr;
    }

    template <typename T>
    auto Ref<T>::operator=(const Ref& other) noexcept -> Ref&
    {
        if (this != &other)
        {
            // retain new first in case it's the same as current
            if (other._ptr)
            {
                other._ptr->retain();
            }
            release();
            _ptr = other._ptr;
        }
        return *this;
    }

    template <typename T>
    auto Ref<T>::operator=(Ref&& other) noexcept -> Ref&
    {
        if (this != &other)
        {
            release();
            _ptr       = other._ptr;
            other._ptr = nullptr;
        }
        return *this;
    }

    template <typename T>
    auto Ref<T>::get() const noexcept -> T*
    {
        return _ptr;
    }

    template <typename T>
    auto Ref<T>::operator*() const noexcept -> T&
    {
        return *_ptr;
    }

    template <typename T>
    auto Ref<T>::operator->() const noexcept -> T*
    {
        return _ptr;
    }

    template <typename T>
    Ref<T>::operator bool() const noexcept
    {
        return _ptr != nullptr;
    }

    template <typename T>
    auto Ref<T>::reset(T* ptr) noexcept -> void
    {
        release();
        _ptr = ptr;
    }

    template <typename T>
    auto Ref<T>::swap(Ref& other) noexcept -> void
    {
        std::swap(_ptr, other._ptr);
    }

    template <typename T>
    template <typename U>
    auto Ref<T>::as() const noexcept -> Ref<U>
    {
        return Ref<U>(static_cast<U*>(_ptr));
    }

    template <typename T>
    auto Ref<T>::retain() noexcept -> void
    {
        if (_ptr)
        {
            _ptr->retain();
        }
    }

    template <typename T>
    auto Ref<T>::release() noexcept -> void
    {
        if (_ptr)
        {
            _ptr->release();
            _ptr = nullptr;
        }
    }

    template <typename T, typename... Args>
    auto makeRef(Args&&... args) -> Ref<T>
    {
        return Ref<T>(new T(std::forward<Args>(args)...));
    }
}
