#pragma once 

#include <coroutine>
#include <cstddef>  // za std::byte
#include <string>
#include <utility> // za std::exchange()
#include <optional>
#include <cassert>


class Parser{

    // Moram ga ranije deklarirati zbog koristenja u Awaiter(neznam jel to smijem u ovom zadatku)
    struct Promise;

    // Čekanje na sljedeći oktet.
    struct Awaiter{
        std::coroutine_handle<Promise> cHandle;

        // Kodirati Awaiter koji čeka na sljedeći oktet i vraća
        // ga u korutinu kad ga dočeka. Ako oktet još nije spreman 
        // suspendira korutinu.
        bool await_ready() const noexcept {
            return false;
        }

        void await_suspend(std::coroutine_handle<Promise> coroutine) noexcept {
            // Zaustavi korutinu i spremi handle od korutine za nastavak kasnije
            cHandle = coroutine;
        }

        std::byte await_resume() const noexcept {
            // Vrati dobiveni byte korutini
            return cHandle.promise().current_byte.value();
        }      
    };

     struct Promise
     {
         std::optional<std::byte> current_byte;
         std::string current_frame;

         // Detalji Promise objekta 
        auto initial_suspend() const noexcept {
            return std::suspend_never{};
        }

        auto final_suspend() const noexcept {
            return std::suspend_never{};
        }

        Awaiter await_transform(std::byte b) {
            current_byte = b;
            return Awaiter{std::coroutine_handle<Promise>::from_promise(*this)};
        }

        void unhandled_exception() {
            std::terminate();
        }

        std::suspend_always yield_value(std::string frame) {
            current_frame = std::move(frame);
            return {};
        }

        void return_void() {}

        // Funkcija potrebna za povratnu vrijednost korutine
        Parser get_return_object() noexcept;
        
     };
     std::coroutine_handle<Promise> cHandle;
public:
    using promise_type = Promise;
    // Javne metode klase Parser.
    void set_byte(std::byte b) {
        // Postavi current_byte u promisu i nastavi korutinu
        cHandle.promise().current_byte = b;
        cHandle.resume();
    }

    std::string get_frame() {
        // Vrati current_frame od promisa
        return std::exchange(cHandle.promise().current_frame, {});
    }
};