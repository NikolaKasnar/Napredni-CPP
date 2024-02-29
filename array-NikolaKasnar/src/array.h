#include <utility> 
#include <initializer_list>
#include <stdexcept>
#include <iostream>
#include <iterator>

/* Klasa koja implementira statički alocirani vektor.
 */
template <typename T, std::size_t N>
class Array{
    T  data[N];
public:
    
    // Konstruktor koji ne uzima parametre
    Array(){
        for (std::size_t i = 0; i < N; ++i) {
            data[i] = T();
        }
    }

    // Konstruktor koji prima parametar te svaki element inicijalizira sa tom vrijednosti
    Array(const T& initialValue) {
        for (std::size_t i = 0; i < N; ++i) {
            data[i] = initialValue;
        }
    }

    // Konstruktor inicijalizacijskom listom
    Array(std::initializer_list<T> initList) {
        std::size_t i = 0;
        for (const T& value : initList) {
            if (i >= N) {
                throw std::runtime_error("Broj elemenata u listi je prevelik.");
            }
            data[i] = value;
            ++i;
        }
    }

    // Konstruktor kopiranja
    Array(const Array& other) {
        for (std::size_t i = 0; i < N; ++i) {
            data[i] = other.data[i];
        }
    }

    // Operator pridruživanja kopiranjem
    Array& operator=(const Array& other) {
        if (this != &other) { // Provjeri jel dodaje sam na sebe
            for (std::size_t i = 0; i < N; ++i) {
                data[i] = other.data[i];
            }
        }
        return *this;
    } 

    // Operator indeksiranja
    T& operator[](std::size_t index) {
        if (index < N) {
            return data[index];
        } else {
            throw std::out_of_range("Index out of range.");
        }
    }

    // Const verzija operatora indeksiranja(read only)
    const T& operator[](std::size_t index) const {
        if (index < N) {
            return data[index];
        } else {
            throw std::out_of_range("Index out of range.");
        }
    }

    // moj iterator za range-for petlju(koristi se za vracanje pocetka i kraja polja)
    class Iterator {
    public:
        Iterator(T* ptr) : ptr(ptr) {}
        T& operator*() { return *ptr; }
        Iterator& operator++() { ++ptr; return *this; }
        bool operator!=(const Iterator& other) const { return ptr != other.ptr; }
    private:
        T* ptr;
    };

    Iterator begin() { return Iterator(data); }
    Iterator end() { return Iterator(data + N); }

    // Const verzija od begin() i end() za const elemente
    class ConstIterator {
    public:
        ConstIterator(const T* ptr) : ptr(ptr) {}
        const T& operator*() const { return *ptr; }
        ConstIterator& operator++() { ++ptr; return *this; }
        bool operator!=(const ConstIterator& other) const { return ptr != other.ptr; }
    private:
        const T* ptr;
    };

    ConstIterator begin() const { return ConstIterator(data); }
    ConstIterator end() const { return ConstIterator(data + N); }


    //opteretim operator << tako da mogu testirati ispisivanje moje klase
    friend std::ostream& operator<<(std::ostream& os, const Array& arr) {
        os << '[';
        for (std::size_t i = 0; i < N; ++i) {
            os << arr.data[i];
            if (i < N - 1) {
                os << ", ";
            }
        }
        os << ']';
        return os;
    }

};


template <typename T, typename S, std::size_t N>
bool operator==(Array<T,N> const & lhs, Array<S,N> const & rhs){
    for (std::size_t i = 0; i < N; ++i) {
        if (lhs[i] != rhs[i]) {
            return false; // Neki ili svi elementi nisu jednaki
        }
    }
    return true; // Svi elementi su jednaki
}
