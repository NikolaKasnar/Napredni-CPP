#include "range/v3/all.hpp"  // to je dovoljno za range-v3.
                             // Pojedini elementi se mogu "includati" i pojedinačno. 
#include "fmt/format.h"
#include <iostream>
#include <string>
#include <optional>

using namespace ranges; // Nikako ne uključivati std!

struct Planet {
    std::string name;
    double gravity;
};


int main(){
    {
     //1. Generirajte niz 1,2,2,3,3,3.......9,9,9,9,9,9,9,9,9.

     // Koristim views::ints za stvaranje raspona brojeva od 1 do 9, views::trasform koristim za ponevljanje svakog broja n puta
     // i na kraju koristim views::join za spajanje svih brojeva u jedan raspon
      auto numbers = views::ints(1, 10) | views::transform([](int n) { return views::repeat_n(n, n); }) | views::join;

      fmt::print("{}\n", fmt::join(numbers, ", "));
    }

    {
    // 2. Nađi planet s gravitacijom 11.15 m²/s. Rezultat vratiti (i ispisati)
    //    kao std::optional<std::string>.
      Planet const v[] = {{"Venus",8.87}, {"Mars",3.711}, {"Jupiter", 24.92},{"Neptun", 11.15},
                          {"Saturn", 10.44}, {"Uran",8.69}};

      // Koristim views::filter za filtriranje planeta sa gravitacijom 11.15, views::transform za izvuci imena planeta sa tom gravitacijom,
      // i views::take(1) koristim za izvaditi prvi od tih planeta( u ovom slučaju Neptun). 
      auto result = v | views::filter([](const Planet& p) { return p.gravity == 11.15; })
                  | views::transform(&Planet::name)
                  | views::take(1);

      // Ako ne pronađem planet vraćam std::nullopt
      std::optional<std::string> optionalResult = !result.empty() ? std::optional<std::string>(*result.begin()) : std::nullopt;

      fmt::print("{}\n", optionalResult.value_or("Planet nije pronaden"));// Ako napisem gravitaciju npr. 1.15, ispisat ce se da planet nije pronaden
    }

    {
      // 3. Aproksimirajte broj  π koristeći Gregory - Leibnizovu formulu 
      // π ≈ 4 * ( 1 - 1/3 + 1/5 - 1/7 + 1/9 - ...). Ispišite rezultat s 30 članova.

      const int terms = 30;

      // Sa views:iota() stvorim raspon od 0 do terms-1, views::transform() mi racuna clanove Gregory-Leibnitzove formule
      // Na kraju ih spremim u vector
      auto pi_approximation = views::iota(0, terms)
                            | views::transform([](int i) {
                                double term = 1.0 / (2 * i + 1);
                                return (i % 2 == 0) ? term : -term;
                            })
                            | to_vector;

      // Sa accumulate izracunam sumu clanova i zatim ih pomnozim sa 4
      double sum = accumulate(pi_approximation, 0.0, std::plus<>());
      double result = sum * 4;

      fmt::print("Aproksimacija od pi sa {} članova: {}\n", terms, result);
    }

    {
      // 4. Selektirati domenu u web adresi i konverirati ju u string. Ispisati. 
      auto const str = std::string{"https://en.test.org"}; // -> org

      // Sa views:reverse obrnem adresu, sa views::take_while uzimam znakove sve do prve tocke
      // Sa views::reverse ga opet obrnem i na kraju ga spremim kao string
      auto domain = str | views::reverse
                      | views::take_while([](char c) { return c != '.'; })
                      | views::reverse
                      | to<std::string>;

      fmt::print("Domain: {}\n", domain);
    }

    
    {
      //5.  Pretvoriti CAMELCASE string u SNAKE_CASE.
      std::string str{"ovoJeMojaCamelCaseVarijabla"};

      // Iz nekog razloga mi ovo ne ispisuje dobro, za ispis dobijem upitnike, nesto ga muci std::tolower()
      /*// Provjerim koje je slovo veliko pa umjesto njega stavim '_' i malo slovo, a ako je malo slovo spremim malo slovo
      auto snake_case = str | views::transform([](char c) {
                          return std::isupper(c) ? '_' + std::tolower(c) : c;
                      })
                      | to<std::string>;
    
      fmt::print("snake case: {}\n", snake_case); // ovo_je_moja_camel_case_varijabla*/

      // Provjerim koje je slovo veliko pa umjesto njega stavim '_' i malo slovo, a ako je malo slovo spremim malo slovo
      // Iz nekog razloga mi std::tolower() vraca ASCII kod pa ga moram castat natrag u char
      auto snake_case = str 
                        | views::transform([](char c) { return std::isupper(c) ? (fmt::format("_{}", static_cast<char>(std::tolower(c)))) : std::string(1, c); })
                        | views::join
                        | to<std::string>();

      fmt::print("snake case: {}\n", snake_case); // ovo_je_moja_camel_case_varijabla
    }
    {
      //6.  Izračunati euklidsku udaljenost između dvije točke zadana tipom std::array<double,n>. 
      std::array<double,4> a{1,2,3,4}, b{4,3,2,1};

      // Koristim views::tip_with za izracun udaljenosti izmedu svaka dva clana brojeva, a1 i a2, b1 i b2 i c1 i c2
      // Sa accumulate() ih sve zbrojim i sa sqrt jos nadodam korijen
      auto squared_diff = views::zip_with([](double x, double y) { return (x - y) * (x - y); }, a, b);
      double sum_of_squares = accumulate(squared_diff, 0.0, std::plus<>());
      double euclidean_distance = sqrt(sum_of_squares);

      fmt::print("Euclidska udaljenost: {}\n", euclidean_distance);
    }
    {
      //7.  Provjeriti korektnost ISBN-13 broja (na primjer 9780306406157).
      //    Polazeći s lijeva na desno treba naizmjenično množiti znamenke s 1 odnosno 3.
      //    (Prvu znamenku množimo s 1, drugu s 3, treću s 1 itd. Broj ima 13 znamenaka.) 
    //    Zatim zbrojimo tako dobivenih 
      //    prvih 12 vrijednosti i izračunamo ostatak sume modulo 10. Ako je dobiveni broj nakon toga 
      //    različit od nule, oduzmemo ga od 10. Izračunata vrijednost mora biti jednaka 13. znamenci.
      
        long int n = 9780306406157;

        // Racunam sumu sa accumulate od prve do 12. znamenke(funkcije koje koristim sam objasnio u prijasnjim zadacima)
        int sum = accumulate(views::ints(1, 13) | views::transform([n](int i) {
            return (n / static_cast<long int>(std::pow(10, i))) % 10 * (i % 2 == 0 ? 1 : 3);
        }), 0);

        //fmt::print("{}\n", sum);

        // Provjeravam izracunatu sumu sa 13. znamenkom
        int remainder = sum % 10;
        int calculated_value = (remainder == 0) ? 0 : 10 - remainder;
        int thirteenth_digit = n % 10;

        //fmt::print("{}\n", calculated_value);

        if (calculated_value == thirteenth_digit) {
            fmt::print("ISBN-13 je tocan.\n");
        } else {
            fmt::print("ISBN-13 je netocan.\n");
        }
    }
    {
      //8.  Naći i ispisati sve troznamenkaste narcisoidne brojeve. Broj je narcisoidan ako je 
      //    jednak sumi svojih znameni dignutih na treću potenciju. Na primjer, 153 = 1³ + 5³ + 3³.

      // Idem po svim brojevima izmedu 100 i 1000(neukljuceno) te filtiram sve projeve koji zadovoljavaju
      // uvijet narcisoidnih brojeva; u tome mi opet pomaze accumulate()
      auto narcissistic_numbers = views::ints(100, 1000) | views::filter([](int num) {
                                                            auto digits = views::ints(0, 3) | views::transform([num](int power) {
                                                                return std::pow((num / static_cast<int>(std::pow(10, power))) % 10, 3);
                                                            });
                                                            return accumulate(digits, 0) == num;
                                                          });

      fmt::print("Troznamenkasti narcisoidni brojevi su:\n{}\n",fmt::join(narcissistic_numbers, ", "));
    }
  return 0;
}
