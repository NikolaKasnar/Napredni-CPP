#pragma once
#include <utility>
#include <memory>

template <typename Sgn>
class MyFunction;

template <typename Ret, typename... Args>
class MyFunction<Ret(Args...)>
{
private:
     // WrapperBase je abstrakna bazna klasa sa virtualnom funkcijom invoke(); Ova klasa ce se koristiti kao baza za type-erased wrapper
    struct WrapperBase
    {
        virtual Ret invoke(Args...) = 0;
        virtual std::unique_ptr<WrapperBase> clone() const = 0; // Dodana clone metoda
        virtual ~WrapperBase() = default;
    };

    template <typename Functor>
    // Klasa koja nasljeduje funkcije of WrapperBase te sadrzi funktor za odredini tip koji koristimo u testu
    struct Wrapper : public WrapperBase
    {
        Functor functor;

        template <typename F>
        Wrapper(F&& f) : functor(std::forward<F>(f)) {}

        Ret invoke(Args... args) override
        {
            return functor(std::forward<Args>(args)...);
        }

          // Implementacija clone metode
        std::unique_ptr<WrapperBase> clone() const override
        {
            return std::make_unique<Wrapper<Functor>>(functor);
        }
    };

    std::unique_ptr<WrapperBase> wrapper;

public:
    template <typename F>
    // Konstruktor
    MyFunction(F&& f) : wrapper(new Wrapper<F>(std::forward<F>(f))) {}

    // Konstruktor za funkcijske objekte
    MyFunction(Ret (*functionPointer)(Args...)) : wrapper(new Wrapper<decltype(functionPointer)>(functionPointer)) {}

    // Konstruktor kopije
    MyFunction(const MyFunction& other) : wrapper(other.wrapper->clone()) {}

    // Konstruktor kopije premjestanjem
    MyFunction(MyFunction&& other) noexcept : wrapper(std::move(other.wrapper)) {}

    // Operator pridruzivanja
    MyFunction& operator=(const MyFunction& other)
    {
        if (this != &other)
        {
            wrapper = other.wrapper->clone();
        }
        return *this;
    }

    // Operator pridruživanja premjestanjem
    MyFunction& operator=(MyFunction&& other) noexcept
    {
        if (this != &other)
        {
            wrapper = std::move(other.wrapper);
        }
        return *this;
    }

     // Koristi se za pozivanje spremljenih argumenata
    Ret operator()(Args... args) const
    {
        return wrapper->invoke(std::forward<Args>(args)...);
    }
};


