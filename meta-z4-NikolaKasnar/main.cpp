#include <fmt/format.h>
#include <type_traits>
#include <array>
#include <cassert>
#include <cstdint> // za (u)intptr_t
#include <vector>
#include <unordered_set>

// 1. dio zadatka
template <typename T>
struct RemoveReference {
    using type = T;
};

template <typename T>
struct RemoveReference<T&> {
    using type = T;
};

template <typename T>
struct RemoveReference<T&&> {
    using type = T;
};

// Alias template
template <typename T>
using RemoveReference_t = typename RemoveReference<T>::type;

// 2. dio zadatka
template <typename T>
struct AddLValueReference {
    using type = T&;
};

template <>
struct AddLValueReference<void> {
    using type = void; // Vraca void za tip void
};

// Alias template
template <typename T>
using AddLValueReference_t = typename AddLValueReference<T>::type;

// 3. dio zadatka
// Obicni template za IsArray
template <typename T>
struct IsArray {
    static constexpr bool value = false;
};

// Specijalizacija za ogranicena polja(tip T[N])
template <typename T, std::size_t N>
struct IsArray<T[N]> {
    static constexpr bool value = true;
};

// Specijaliziacija za polja bez odredene velicine(prethodna specijalizacija mi iz nekog razloga nije radila)
template <typename T>
struct IsArray<T[]> {
    static constexpr bool value = true;
};

// Alias template
template <typename T>
constexpr bool IsArray_v = IsArray<T>::value;

// 4. dio zadatka
template <typename T, typename S, std::size_t N>
auto operator+(const std::array<T, N>& a, const std::array<S, N>& b) ->
    std::array<decltype(std::declval<T>() + std::declval<S>()), N> {
    std::array<decltype(std::declval<T>() + std::declval<S>()), N> result;

    for (std::size_t i = 0; i < N; ++i) {
        result[i] = a[i] + b[i];
    }

    return result;
}

// 5. dio zadatka
// Pomocna funkcija
template <typename B, typename D>
struct IsBaseOfHelper {
private:
    template <typename T>
    static std::true_type test(const volatile T*);
    
    template <typename>
    static std::false_type test(...);

    static D* makeD();

public:
    static constexpr bool value = decltype(test<B>(makeD()))::value;
};

// Posebni slucajevi kada je jedan ili oba pointera pokazuju na void
template <typename B>
struct IsBaseOfHelper<B, void> {
    static constexpr bool value = false;
};

template <typename D>
struct IsBaseOfHelper<void, D> {
    static constexpr bool value = false;
};

template <>
struct IsBaseOfHelper<void, void> {
    static constexpr bool value = false;
};

template <typename B, typename D>
struct IsBaseOf : IsBaseOfHelper<B, D> {};

// 6. dio zadatka
// Primarni template za hasConstReverseIterator_v
template <typename Container, typename = void>
struct hasConstReverseIterator : std::false_type {};

// Specijalizacija za hasConstReverseIterator_v
template <typename Container>
struct hasConstReverseIterator<Container,
    std::void_t<typename Container::const_reverse_iterator>> : std::true_type {};

// Varijabilni template hasConstReverseIterator_v
template <typename Container>
constexpr bool hasConstReverseIterator_v = hasConstReverseIterator<Container>::value;

// Metafunkcija ConstReverseIteratorType
template <typename Container, typename = void>
struct ConstReverseIteratorType {};

// Specijalizacija za ConstReverseIteratorType
template <typename Container>
struct ConstReverseIteratorType<Container,
    std::enable_if_t<hasConstReverseIterator_v<Container>>> {
    using type = typename Container::const_reverse_iterator;
};

// 7. dio zadatka

// Pomocni template za SFINAE
template <typename...>
using void_t = void;

// Template za hasMember
template <typename T, typename = void>
struct hasMember : std::false_type {};

// Specijalizacija za hasMember_x
template <typename T>
struct hasMember<T, void_t<decltype(std::declval<T>().x)>> : std::true_type {};

// Specijalizacija za funkcije imena x
template <typename T, typename R, typename... Args>
struct hasMember<T(R(Args...)), void> : std::false_type {};

// Alias template
template <typename T>
inline constexpr bool hasMember_x = hasMember<T>::value;


// Klase za testiranje
class B {};
class D : public B {};
class C{};

class E : public B, public C {};

class Base{
    public:
    virtual ~Base() = default;
};
class Derived : public Base {};


class AAA{
    public:
        int x;
};
class BBB{
    public:
        void x() const {}
};
class CCC{
    int y;
};


// Ne mijenjati main!
int main(){
    // 1. 
    static_assert(std::is_same_v<RemoveReference_t<int &>, int>);
    static_assert(std::is_same_v<RemoveReference_t<int &&>, int>);
    static_assert(std::is_same_v<RemoveReference_t<int const &>, int const>);

    // 2.
    static_assert(std::is_same_v<AddLValueReference_t<int>, int&>);
    static_assert(std::is_same_v<AddLValueReference_t<int&>, int&>);
    static_assert(std::is_same_v<AddLValueReference_t<int&&>, int&>);
    static_assert(std::is_same_v<AddLValueReference_t<void>, void>);

    // 3. 
    static_assert(IsArray_v<int> == false);
    static_assert(IsArray_v<int[]> == true);
    static_assert(IsArray_v<int[3]> == true);

    // 4.
    std::array<int,3> a{1,2,3};
    std::array<float,3> b{1.0f, 2.0f, 3.0f};
    auto c = a+b;
    assert(c[0] == 2);
    assert(c[1] == 4);
    assert(c[2] == 6);
    static_assert(std::is_same_v<std::decay_t<decltype(c[0])>, float>); 
    
    // 5. 
    static_assert( IsBaseOf<B,D>::value );
    static_assert( !IsBaseOf<B,C>::value );
    static_assert( IsBaseOf<B,B>::value );
    static_assert( !IsBaseOf<int,long>::value );
    static_assert( !IsBaseOf<void,void>::value );
    static_assert( !IsBaseOf<void,B>::value );

    static_assert( IsBaseOf<const B,D>::value );
    static_assert( IsBaseOf<B, volatile D>::value );
    
    static_assert( IsBaseOf<B,E>::value );
    static_assert( IsBaseOf<C,E>::value );

    // 6. 
    static_assert(hasConstReverseIterator_v<std::vector<int>>);
    static_assert(!hasConstReverseIterator_v<std::unordered_set<int>>);

    ConstReverseIteratorType<std::vector<int>>::type it;
//    ConstReverseIteratorType<std::unordered_set<int>>::type it1;  // ne kompilira se
   
    // 7. 
    static_assert(hasMember_x<AAA>);
    static_assert(!hasMember_x<BBB>);
    static_assert(!hasMember_x<CCC>);


   
    return 0;
}
