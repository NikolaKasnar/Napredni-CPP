#include <iostream>
#include <cassert>
#include <type_traits>

// Zadatak 1.
// a. prva verzija koja koristi rekurziju i specijalizaciju predloška.

// Koristim Pascalovu formulu za rekurzivno racunanje binomnog koeficijenta
template <unsigned d, unsigned k>
struct Binomni{
    static constexpr int value = (k == 0 || k == d) ? 1 : Binomni<d - 1, k - 1>::value + Binomni<d - 1, k>::value;
};

// Zavrsetci rekurzije
template <unsigned k>
struct Binomni<0, k> {
    static constexpr int value = 0; // Ako je d=0 vraca vrijednost 0 po definiciji binomnog koeficijenta
};

template <unsigned int d, unsigned int k>
struct Dim{
    static constexpr unsigned int value = Binomni<d+k,k>::value;
};


// b. druga verzija koja koristi c++11 constexpr funkciju. 
//    Funkcija se sastoji od samo jedne return naredbe, 

// Pomocna funkcija za racunanje binomnog koeficijenta
constexpr unsigned int dimPomocni(unsigned int d, unsigned int k){
    return (d == 0) ? 0 : ((k == 0 || k == d) ? 1 : dimPomocni(d - 1, k - 1) + dimPomocni(d - 1, k));
}
constexpr unsigned int dim(unsigned int d, unsigned int k){
    return (k == 0 || k == d+k) ? 1 : dimPomocni(d+k, k); // Provjerava odmah uvjet ako je k=d+k, moglo se i bez toga, kasnije sam tek otkrio za ternari operator sa ugnijezdenim pozivom koji je koristen u pomocnoj funkciji
}


// c. treća verzija koja koristi c++14 constexpr funkciju i ne koristi
//  rekurziju. 
constexpr unsigned int dim14(unsigned int d, unsigned int k){
    unsigned int result = 1;
    for (unsigned int i = 1; i <= k; i++) {
        result = result * (d + k - i + 1) / i;
    }
    return result;
}

// Zadatak 2. 
// a. C++11 verzija 

// Pomocna funkcija za racunanje rekurzije; provjerava je li sljedeći znak null te ako je vraca 0, inace opet poziva funkciju  rekurzivno
constexpr int64_t hash_recursive(const char *s, int64_t p, int64_t m, std::size_t index) {
    return (s[index] != '\0') ? ((hash_recursive(s, p, m, index + 1) * p + (s[index] - 'a' + 1)) % m) : 0;
}
constexpr int64_t hash11(const char * s) 
{
    const int64_t p = 31;
    const int64_t m = 1e9+9;
    return hash_recursive(s, p, m, 0); // U pomocnu funkciju saljemo string s, p, m i index pocetnog znaka od kojeg krecemo racunat hash funkciju
}

// b. C++14 verzija 
// Racuna hash vrijednost bez rekurzije
constexpr int64_t hash14(const char * s) 
{
    const int64_t p = 31;
    const int64_t m = 1e9+9;

    int64_t hashValue = 0;
    int64_t pPow = 1;// p^i; na pocetku je 1 jer racunamo 31^0

    for (int i = 0; s[i] != '\0'; ++i) {
        hashValue = (hashValue + (s[i] - 'a' + 1) * pPow) % m;
        pPow = (pPow * p) % m;
    }

    return hashValue;
}



int main(){
        // Ovaj kod ne brisati! Možete dodavati svoje testove.
        // Zadatak 1.
        // 1. 
        static_assert(Dim<0,3>::value == 1);
        static_assert(Dim<3,0>::value == 1);
        static_assert(Dim<3,1>::value == 4);
        static_assert(Dim<3,2>::value == 10);
        static_assert(Dim<3,3>::value == 20);
        static_assert(Dim<5,3>::value == 56);
        //std::cout<< "test"; //Ispis za test
        // 2.
        static_assert(dim(0,3) == 1);
        static_assert(dim(3,0) == 1);
        static_assert(dim(3,1) == 4);
        static_assert(dim(3,2) == 10);
        static_assert(dim(3,3) == 20);
        static_assert(dim(5,3) == 56);    
        //3.
        static_assert(dim14(0,3) == 1);
        static_assert(dim14(3,0) == 1);
        static_assert(dim14(3,1) == 4);
        static_assert(dim14(3,2) == 10);
        static_assert(dim14(3,3) == 20);
        static_assert(dim14(5,3) == 56);  
        
        // Zadatak 2.
        constexpr const char * s1="abcder";
        constexpr const char * s2="ertamabcdernn";
        constexpr const char * s3="afgtbbnjiocbfrewqdeloikjuhbvcr";
        constexpr const char * s4="utdtbbnjiocbzrewddegoimjeh";
        constexpr const char * s5="abcder";
        /*std::cout << hash11(s1) << "\n";
        std::cout << hash11(s2) << "\n";
        std::cout << hash11(s3) << "\n";
        std::cout << hash11(s4) << "\n";
        std::cout << hash11(s5) << "\n";*/
        /*// Neki moji testovi za testiranje hash funkcije
        std::cout << ((((((s5[0]-'a'+1)*10+(s5[1]-'a'+1))*10+(s5[2]-'a'+1))*10+(s5[3]-'a'+1))*10+(s5[4]-'a'+1))*10+(s5[5]-'a'+1)) << "\n";
        std::cout << s5[5] << s5[5]-'a'+1 << "\n";*/
        static_assert(hash11(s1) == 520064433);
        static_assert(hash11(s2) == 202527068);
        static_assert(hash11(s3) == 615720090);
        static_assert(hash11(s4) == 814096530);


        // std::cout << hash14(s5) << "\n";
        static_assert(hash14(s1)==hash11(s1));
        static_assert(hash14("ertamabcdernn")==hash11("ertamabcdernn"));
        static_assert(hash14(s3)==hash11(s3));
        static_assert(hash14(s4)==hash11(s4));

        return 0;
}
