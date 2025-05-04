/// \file Delegate.hpp
/// \brief A lightweight 0-overhead wrapper for binding function objects.
///        Largely inspired by 'bitwizeshift' see https://github.com/bitwizeshift/Delegate.

#pragma once

#include "CoreUtility.hpp"

#include <optional>
#include <stdexcept>
#include <type_traits>
#include <utility>

namespace qurb
{
    namespace detail
    {
        template <typename Type>
        struct EffectiveSignatureImpl;

        template <typename R, typename... Args>
        struct EffectiveSignatureImpl<R (*)(Args...)>
        {
            using type = R(Args...);
        };

        template <typename R, typename... Args>
        struct EffectiveSignatureImpl<R (*)(Args..., ...)>
        {
            using type = R(Args..., ...);
        };

        template <typename R, typename... Args>
        struct EffectiveSignatureImpl<R (*)(Args...) noexcept>
        {
            using type = R(Args...);
        };

        template <typename R, typename... Args>
        struct EffectiveSignatureImpl<R (*)(Args..., ...) noexcept>
        {
            using type = R(Args..., ...);
        };

        template <typename R, typename C, typename... Args>
        struct EffectiveSignatureImpl<R (C::*)(Args...)>
        {
            using type = R(Args...);
        };

        template <typename R, typename C, typename... Args>
        struct EffectiveSignatureImpl<R (C::*)(Args..., ...)>
        {
            using type = R(Args..., ...);
        };

        template <typename R, typename C, typename... Args>
        struct EffectiveSignatureImpl<R (C::*)(Args...) noexcept>
        {
            using type = R(Args...);
        };

        template <typename R, typename C, typename... Args>
        struct EffectiveSignatureImpl<R (C::*)(Args..., ...) noexcept>
        {
            using type = R(Args..., ...);
        };

        //----------------------------------------------------------------------------

        template <typename R, typename C, typename... Args>
        struct EffectiveSignatureImpl<R (C::*)(Args...) const>
        {
            using type = R(Args...);
        };

        template <typename R, typename C, typename... Args>
        struct EffectiveSignatureImpl<R (C::*)(Args..., ...) const>
        {
            using type = R(Args..., ...);
        };

        template <typename R, typename C, typename... Args>
        struct EffectiveSignatureImpl<R (C::*)(Args...) const noexcept>
        {
            using type = R(Args...);
        };

        template <typename R, typename C, typename... Args>
        struct EffectiveSignatureImpl<R (C::*)(Args..., ...) const noexcept>
        {
            using type = R(Args..., ...);
        };

        //----------------------------------------------------------------------------

        template <typename T>
        using EffectiveSignature = typename EffectiveSignatureImpl<T>::type;
    }

    //==================================================================================================================
    // Class : BadDelegateCall
    //==================================================================================================================

    /// \brief An exception thrown when a `delegate` is invoked without a bound function
    class BadDelegateCall final : public std::runtime_error
    {
    public:
        BadDelegateCall();
    };

    //==================================================================================================================
    // Binding
    //==================================================================================================================

    inline namespace target
    {
        /// \brief
        ///
        /// \tparam Function The function to bind
        template <auto Function>
        struct FunctionBindTarget
        {};

        /// \brief
        ///
        /// \tparam MemberFunction The function to bind
        /// \tparam T
        template <auto MemberFunction, typename T>
        struct MemberBindTarget
        {
            T* instance;
        };
    }

    /// \brief Binds a function pointer to create a function bind target
    ///
    /// \tparam Function The function to bind
    ///
    /// \return The created target
    template <auto Function>
    constexpr auto bind() noexcept -> FunctionBindTarget<Function>;

    /// \brief Binds a member pointer to create a function bind target
    ///
    /// \pre `p != nullptr`
    ///
    /// \tparam MemberFunction The member function
    /// \tparam T The type
    ///
    /// \param p The instance pointer
    ///
    /// \return The created target
    template <auto MemberFunction, typename T>
    constexpr auto bind(T* p) noexcept -> MemberBindTarget<MemberFunction, T>;

    //==================================================================================================================
    // Class : Delegate
    //==================================================================================================================

    template <typename Signature>
    class Delegate;

    /// \brief A lightweight 0-overhead wrapper for binding function objects.
    ///
    /// \tparam R The return type
    /// \tparam Args The arguments of the function
    template <typename R, typename... Args>
    class Delegate<R(Args...)> final
    {
    public:
        /// \brief Default constructs this delegate without a bound target
        constexpr Delegate() noexcept;

        template <auto Function, typename = std::enable_if_t<std::is_invocable_r_v<R, decltype(Function), Args...>>>
        constexpr Delegate(FunctionBindTarget<Function> target) noexcept;

        template <
            auto MemberFunction,
            typename T,
            typename = std::enable_if_t<std::is_invocable_r_v<R, decltype(MemberFunction), T&, Args...>>>
        constexpr Delegate(MemberBindTarget<MemberFunction, T> target) noexcept;

        template <
            auto MemberFunction,
            typename T,
            typename = std::enable_if_t<std::is_invocable_r_v<R, decltype(MemberFunction), const T&, Args...>>>
        constexpr Delegate(MemberBindTarget<MemberFunction, const T> target) noexcept;

        Delegate(const Delegate& other) = default;

        auto operator=(const Delegate& other) -> Delegate& = default;

        constexpr auto operator==(const Delegate& other) const noexcept -> bool;
        constexpr auto operator!=(const Delegate& other) const noexcept -> bool;

    public:
        template <
            auto Function,
            typename = std::enable_if_t<std::is_invocable_r_v<R, decltype(Function), Args...>>>
        constexpr auto bind() noexcept -> Delegate&;

        template <
            auto MemberFunction,
            typename T,
            typename = std::enable_if_t<std::is_invocable_r_v<R, decltype(MemberFunction), T&, Args...>>>
        constexpr auto bind(T* instance) noexcept -> Delegate&;

        template <
            auto MemberFunction,
            typename T,
            typename = std::enable_if_t<std::is_invocable_r_v<R, decltype(MemberFunction), const T&, Args...>>>
        constexpr auto bind(const T* instance) noexcept -> Delegate&;

        constexpr auto reset() noexcept -> void;

        constexpr explicit operator bool() const noexcept;

        template <
            typename... UArgs,
            typename = std::enable_if_t<std::is_invocable_v<R (*)(Args...), UArgs...>>>
        constexpr auto operator()(UArgs&&... args) const -> R;

        template <
            typename... UArgs,
            typename = std::enable_if_t<std::is_invocable_v<R (*)(Args...), UArgs...> and std::is_void_v<R>>>
        constexpr auto invoke(UArgs&&... args) const -> void;

        template <
            typename... UArgs,
            typename = std::enable_if_t<std::is_invocable_v<R (*)(Args...), UArgs...> and not std::is_void_v<R>>>
        constexpr auto invoke(UArgs&&... args) const -> std::optional<R>;

        [[nodiscard]] constexpr auto isBound() const noexcept -> bool;

        template <
            auto Function,
            typename = std::enable_if_t<std::is_invocable_r_v<R, decltype(Function), Args...>>>
        [[nodiscard]] constexpr auto isBound() const noexcept -> bool;

        template <
            auto MemberFunction,
            typename T,
            typename = std::enable_if_t<std::is_invocable_r_v<R, decltype(MemberFunction), T&, Args...>>>
        [[nodiscard]] constexpr auto isBound(T* instance) const noexcept -> bool;

        template <
            auto MemberFunction,
            typename T,
            typename = std::enable_if_t<std::is_invocable_r_v<R, decltype(MemberFunction), const T&, Args...>>>
        [[nodiscard]] constexpr auto isBound(const T* instance) const noexcept -> bool;

    private:
        using StubFunction = R (*)(const Delegate*, Args...);

        friend struct std::hash<Delegate>;

    private:
        [[noreturn]] static auto nullStub(const Delegate*, Args...) -> R;

        template <auto Function>
        static auto functionStub(const Delegate*, Args... args) -> R;

        template <auto MemberFunction, typename T>
        static auto memberFunctionStub(const Delegate* self, Args... args) -> R;

    private:
        struct Empty
        {};

        union
        {
            Empty       _empty;
            void*       _instance;
            const void* _const_instance;
        };

        StubFunction _stub;
    };

    template <auto Function>
    Delegate(FunctionBindTarget<Function>) -> Delegate<detail::EffectiveSignature<decltype(Function)>>;

    template <auto MemberFunction, typename T>
    Delegate(MemberBindTarget<MemberFunction, T>) -> Delegate<detail::EffectiveSignature<decltype(MemberFunction)>>;

    //==================================================================================================================
    // Class : BadDelegateCall
    //==================================================================================================================

    inline BadDelegateCall::BadDelegateCall()
        : std::runtime_error("Delegate called without being bound")
    {}

    //==================================================================================================================
    // Binding
    //==================================================================================================================

    template <auto Function>
    constexpr auto bind() noexcept -> FunctionBindTarget<Function>
    {
        return {};
    }

    template <auto MemberFunction, typename T>
    constexpr auto bind(T* p) noexcept -> MemberBindTarget<MemberFunction, T>
    {
        return {p};
    }

    //==================================================================================================================
    // Class : Delegate
    //==================================================================================================================

    template <typename R, typename... Args>
    constexpr Delegate<R(Args...)>::Delegate() noexcept
        : _empty()
        , _stub(&nullStub)
    {}

    template <typename R, typename... Args>
    template <auto Function, typename>
    constexpr Delegate<R(Args...)>::Delegate(FunctionBindTarget<Function>) noexcept
        : _empty()
        , _stub(&functionStub<Function>)
    {}

    template <typename R, typename... Args>
    template <auto MemberFunction, typename T, typename>
    constexpr Delegate<R(Args...)>::Delegate(MemberBindTarget<MemberFunction, T> target) noexcept
        : _instance(target.instance)
        , _stub(&memberFunctionStub<MemberFunction, T>)
    {}

    template <typename R, typename... Args>
    template <auto MemberFunction, typename T, typename>
    constexpr Delegate<R(Args...)>::Delegate(MemberBindTarget<MemberFunction, const T> target) noexcept
        : _const_instance(target.instance)
        , _stub(&memberFunctionStub<MemberFunction, const T>)
    {}

    template <typename R, typename... Args>
    constexpr auto Delegate<R(Args...)>::operator==(const Delegate& other) const noexcept -> bool
    {
        return _instance == other._instance and _stub == other._stub;
    }

    template <typename R, typename... Args>
    constexpr auto Delegate<R(Args...)>::operator!=(const Delegate& other) const noexcept -> bool
    {
        return !operator==(other);
    }

    template <typename R, typename... Args>
    template <auto Function, typename>
    constexpr auto Delegate<R(Args...)>::bind() noexcept -> Delegate&
    {
        return *this = Delegate(FunctionBindTarget<Function>());
    }

    template <typename R, typename... Args>
    template <auto MemberFunction, typename T, typename>
    constexpr auto Delegate<R(Args...)>::bind(T* instance) noexcept -> Delegate&
    {
        return *this = Delegate(MemberBindTarget<MemberFunction, T>(instance));
    }

    template <typename R, typename... Args>
    template <auto MemberFunction, typename T, typename>
    constexpr auto Delegate<R(Args...)>::bind(const T* instance) noexcept -> Delegate&
    {
        return *this = Delegate(MemberBindTarget<MemberFunction, const T>(instance));
    }

    template <typename R, typename... Args>
    constexpr auto Delegate<R(Args...)>::reset() noexcept -> void
    {
        _stub = &nullStub;
    }

    template <typename R, typename... Args>
    constexpr Delegate<R(Args...)>::operator bool() const noexcept
    {
        return isBound();
    }

    template <typename R, typename... Args>
    template <typename... UArgs, typename>
    constexpr auto Delegate<R(Args...)>::operator()(UArgs&&... args) const -> R
    {
        return std::invoke(_stub, this, std::forward<UArgs>(args)...);
    }

    template <typename R, typename... Args>
    template <typename... UArgs, typename>
    constexpr auto Delegate<R(Args...)>::invoke(UArgs&&... args) const -> void
    {
        try
        {
            return std::invoke(_stub, this, std::forward<UArgs>(args)...);
        }
        catch (const BadDelegateCall&)
        {
            return;
        }
    }

    template <typename R, typename... Args>
    template <typename... UArgs, typename>
    constexpr auto Delegate<R(Args...)>::invoke(UArgs&&... args) const -> std::optional<R>
    {
        try
        {
            return std::invoke(_stub, this, std::forward<UArgs>(args)...);
        }
        catch (const BadDelegateCall&)
        {
            return std::nullopt;
        }
    }

    template <typename R, typename... Args>
    constexpr auto Delegate<R(Args...)>::isBound() const noexcept -> bool
    {
        return _stub != &nullStub;
    }

    template <typename R, typename... Args>
    template <auto Function, typename>
    constexpr auto Delegate<R(Args...)>::isBound() const noexcept -> bool
    {
        return _stub == &functionStub<Function>;
    }

    template <typename R, typename... Args>
    template <auto MemberFunction, typename T, typename>
    constexpr auto Delegate<R(Args...)>::isBound(T* instance) const noexcept -> bool
    {
        return _stub == &memberFunctionStub<MemberFunction, T> and _instance == instance;
    }

    template <typename R, typename... Args>
    template <auto MemberFunction, typename T, typename>
    constexpr auto Delegate<R(Args...)>::isBound(const T* instance) const noexcept -> bool
    {
        return _stub == &memberFunctionStub<MemberFunction, const T> and _const_instance == instance;
    }

    template <typename R, typename... Args>
    auto Delegate<R(Args...)>::nullStub(const Delegate*, Args...) -> R
    {
        throw BadDelegateCall();
    }

    template <typename R, typename... Args>
    template <auto Function>
    auto Delegate<R(Args...)>::functionStub(const Delegate*, Args... args) -> R
    {
        return std::invoke(Function, std::forward<Args>(args)...);
    }

    template <typename R, typename... Args>
    template <auto MemberFunction, typename T>
    auto Delegate<R(Args...)>::memberFunctionStub(const Delegate* self, Args... args) -> R
    {
        auto* const c = [&self] {
            if constexpr (std::is_const_v<T>)
            {
                return static_cast<T*>(self->_const_instance);
            }
            else
            {
                return static_cast<T*>(self->_instance);
            }
        }();

        return std::invoke(MemberFunction, *c, std::forward<Args>(args)...);
    }

    using Action = Delegate<void()>;
}

template <typename R, typename... Args>
struct std::hash<qurb::Delegate<R(Args...)>>
{
    auto operator()(const qurb::Delegate<R(Args...)>& delegate) const noexcept -> size_t
    {
        size_t hash = 0;
        qurb::hashCombine(hash, delegate._instance, delegate._stub);
        return hash;
    }
};
