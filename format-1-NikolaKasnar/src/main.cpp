#include <fmt/format.h>
#include <array> // Za niz
#include <cstdlib> // Za rand() funkciju
#include <fstream>
#include <fmt/ostream.h>

int main () {

    int i;

    std::array<int, 10> a; // Inicijaliziram polje sa 10 mjesta

    // Unosim random brojeve izmedu 0 i 20 u polje a
    for (i=0; i<10; i++){
        a[i]=rand()%20; // rand() daje neki broj veci od nule, ja zatim uzmem njegov cjelobrojni ostatak pri dijeljenju sa 20
    }

    // Ispisujem te brojeve onako kako to trazi zadatak
    fmt::print("Ispis za a) dio zadatka:\n");
    for(i=0;i<10;i++){
        fmt::print("{}:", i); 
        fmt::print("{:.>10}", a[i]); // Pomak desno
        fmt::print(" ** ");
        fmt::print("{:.<10}", a[i]); // Pomak lijevo
        fmt::print(" ** ");
        fmt::print("{:.^10}", a[i]); // Pomak u sredinu
        fmt::print(" ** ");
        fmt::print("{:.^#10x}\n", a[i]); // Pomak u sredinu uz hex zapis
    }

    // Ispis za b) dio zadatka
    
    double pi = 3.141592653590;
    int j=3;

    fmt::print("\nIspis za b) dio zadatka:\n");
    for(i=0; i<10; i++){
        // Ako je i djeljiv sa 2 onda ispred ne pisem +, a ako nije onda ga pisem
        if(i%2==0){
            fmt::print("{}: {:15.{}f}\n", i, pi, j++);
        }
        else{
            fmt::print("{}: {:+15.{}f}\n", i, pi, j++);
        }
    }
    


    // Ispis u datoteku adrese.txt za c) dio zadatka
    int x=1;
    int y=2;
    int z=3;

    std::ofstream out("adrese.txt");
    fmt::print(out, "Adresa varijable x: {}\n", static_cast<void*>(&x)); // Moram castat adresu kao sto je navedeno u materijalima sa predavanja o fmt biblioteci jer inace dobivam gresku
    fmt::print(out, "Adresa varijable y: {}\n", static_cast<void*>(&y));
    fmt::print(out, "Adresa varijable z: {}\n", static_cast<void*>(&z));
    out.close();
    
    return 0;
}
