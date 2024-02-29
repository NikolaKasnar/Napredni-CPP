#include "demengle.h"

#include <iostream>
#include <concepts>
#include <type_traits>
#include <span>

/* Zadatak 1. Napisati koncept FPCont koji ispituje da li tip T 
 *            ima metode begin() i end(), da li se povratna vrijednost od 
 *            begin() dade dereferncirati te da li daje nešto konvertibilno u 
 *            tip double. 
 */

template <typename T>
concept FPCont = requires(T t) {
    // Provjerimo jel T ima begin() i end() funkcije
    { t.begin() } -> std::same_as<decltype(t.end())>;

    // Provjerimo jel se povratna vrijednost od begin() moze dereferencirati u nesto konvertibilno u tip double
    requires std::convertible_to<decltype(*t.begin()), double>;
};

// Klase X,Y i Z služe za testiranje Zadatka 1.
class X{};

struct Y{
    void begin(){}
    void end(){}
};

struct Z{
    float * begin(){ return nullptr;}
    float * end(){ return nullptr; }
};

// Zadatak 2.  Napraviti koncept Same<T,S> koji je istina ako su 
//             tipovi T i S jednaki nakon zanemarivanja dekoracija const i
//             volatile. 

template <typename T, typename S>
// Maknem const i volatile sa std::remove_cv_t i onda ih usporedim sa std::is_same_v
concept Same = std::is_same_v<std::remove_cv_t<T>, std::remove_cv_t<S>>;


// Zadatak 3. Napisati koncept Number koji je istinit za sve cjelobrojne 
//          tipove i sve tipove s pokretnim zarezom, osim za tip bool
//          i sve moguće char tipove. (bool i char-ovi su cjelobrojni tipovi).
//          Ograničeni predložak mult() služi za testiranje koncepta.
//

// Neograničeni predložak funkcije mult() - samo kako ne bi imali grešku pri kompilaciji.
// UPUTA: Ako demengle_type_name(x) ne radi na vašem sustavu, zamijenite 
//        ga s typeid(x).name(). Isto za y.
auto mult(auto x, auto y){
    std::cerr << "Greška. Tip od x = " << demengle_type_name(x)
              << ". Tip od y = " << demengle_type_name(y) << "\n";
    return -1;
}

// Koncept Number
template <typename T>
concept Number = (std::is_integral_v<T> || std::is_floating_point_v<T>) && !std::is_same_v<T, bool> && !std::is_same_v<T, char>; // Istinito samo ako je T bilo koji int ili double tip

// Ograničeni predložak funkcije mult()
template <Number T, Number U>
auto mult(T x, U y) {
    // Provjeravamo jesu li x i y bilo koji od ovih tipova chara ili boola te u tom slucaju vraca -1 i prikladnu poruku
    if constexpr (std::is_same_v<T, bool> || std::is_same_v<U, bool> ||
                  std::is_same_v<T, char> || std::is_same_v<U, char> ||
                  std::is_same_v<T, unsigned char> || std::is_same_v<U, unsigned char> ||
                  std::is_same_v<T, char8_t> || std::is_same_v<U, char8_t> ||
                  std::is_same_v<T, char16_t> || std::is_same_v<U, char16_t> ||
                  std::is_same_v<T, char32_t> || std::is_same_v<U, char32_t> ||
                  std::is_same_v<T, wchar_t> || std::is_same_v<U, wchar_t>) {
        std::cerr << "Greška. Tip od x = " << demengle_type_name(x)
                  << ". Tip od y = " << demengle_type_name(y) << "\n";
        return -1;
    } else {
        return x * y;
    }
}


// ZADATAK 4. Napraviti koncept Pointer koji predstavlja pointer. Pri tome je pointer (po
//          našoj definiciji)  "void *" ili nešto što se dade dereferencirati. 
//          Napravite predložak "print(auto const & val)" koji ispisuje vrijednost val 
//          te napravite preopterećenje predloška print() koje uzima pokazivač val i ispisuje *val. 
//          Ispravno preopterećenje postići koristeći koncept Pointer. 

// Koncept Pointer
template <typename T>
concept Pointer = std::is_pointer_v<T> || std::is_same_v<T, std::nullptr_t>;

// Template funkcije print
template <typename T>
void print(const T& val) {
    std::cout << val << "\n";
}

// Preopterecenje funkcije print za koncept Pointer
template <Pointer T>
void print(const T& val) {
    std::cout << *val << "\n";
}

// ZADATAK 5.
// Treba napisati koncept Two koji proizvoljan niz argumenata zadovoljava ako svi argumenti 
// pripadaju zadanom skupu od dva tipa int i char.
// 

//Koncept Two
// Provjerimo jel sadzi barem jedan argument i onda jesu li svi ti tipovi int ili char
template <typename... Args>
concept Two = (sizeof...(Args) > 0) && (... && (std::is_same_v<Args, int> || std::is_same_v<Args, char>));

// Funkcija koja može uzeti proizvoljan broj parametara ali samo 
// tipa int i char (u bilo kojem poretku).
template<typename... Args>
requires Two<int, char, Args...>
void f1(Args... args){
	std::cout << "OK\n";
}

/* Zadatak 6. Napisati koncept InPlaceEngine koji provjerava da tip
 *          ima metodu process() koja kao argument uzima std::span<double>.
 *          Klasa Wrapper je parametrizirana s tipom koji mora imati 
 *          metodu process(). Zamijenite opći predložak Wrapper s 
 *          predloškom ograničenim na tipove koji zadovoljavaju 
 *          koncept InPlaceEngine. Implementirajte metodu Wrapper::reset()
 *          tako da poziva Engine::reset() ako takva metoda postoji,
 *          a ne radi ništa ako ne postoji. Pri tome koristiti
 *          samo if constexpr i requires!
 */

// Koncept InPlaceEngine
template <typename Engine>
concept InPlaceEngine = requires(Engine e, std::span<double> sp) {
    { e.process(sp) } -> std::same_as<void>;
};

// Polazni kod klase Wrapper - neograničeni predložak
/*template <typename Engine>
class Wrapper{
    public:
        Wrapper(Engine e) : engine_(std::move(e)) {}
        void process(std::span<double> buf){
            engine_.process(buf);
        }
        void reset(){
            // Ako Engine::reset() postoji, pozovi ga. 
            // Ako ne postoji ispiši "reset ne postoji".
            // Koristiti if constexpr i requires!
            if constexpr (requires(const Engine& e) { e.reset(); }) {
            engine_.reset();
            } 
            else{
            std::cout << "reset does not exist\n";
            }
        }
    private:
        Engine engine_;
};*/

// Ograničeni predložak klase Wrapper
template <InPlaceEngine Engine>
class Wrapper {
    public:
        Wrapper(Engine e) : engine_(std::move(e)) {}

        void process(std::span<double> buf) {
            engine_.process(buf);
        }

        void reset() {
            // Ako Engine::reset() postoji, pozovi ga. 
            // Ako ne postoji ispiši "reset ne postoji".
            // Koristiti if constexpr i requires!
            if constexpr (requires(const Engine& e) { e.reset(); }){
                engine_.reset();
            } 
            else{
                std::cout << "reset does not exist\n";
            }
        }

    private:
        Engine engine_;
};


// Engine klase za testiranje.
struct Engine1{
    void process(std::span<double> sp){ std::cout << "process\n"; }
};
struct Engine2{
    void process(std::span<double> sp){ std::cout << "process\n"; }
    void reset() const { std::cout << "resret\n"; }
};
struct Engine3{
};


