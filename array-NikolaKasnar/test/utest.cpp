#include "gtest/gtest.h"
#include "../src/array.h"

#include <memory>
#include <stdexcept>

// Definiram listu tipova za aprametrizirani test
using Types = ::testing::Types<int, char, long, float, double>;
constexpr std::size_t N = 5; // velicina arraya

template <typename T>
class ArrayTest : public ::testing::Test {
protected:
    Array<T, N> arr;

    void SetUp() override {
        // Ovaj kod će se izvršiti prije testova.
    }

    // Per-test tear-down
    void TearDown() override {
        // Kod koji se izvršava nakon testova. Dozvoljava izuzetke.
    }
};

TYPED_TEST_SUITE(ArrayTest, Types);

// Test za obicni konstruktor
TYPED_TEST(ArrayTest, ObicniKonstruktor) {
    for (std::size_t i = 0; i < N; ++i) {
        EXPECT_EQ(this->arr[i], TypeParam());  // Inicijalizira polje sa jednom od vrijednosti navedenih gore
    }
}

// test za konstruktor sa pocetnom vrijednosti
TYPED_TEST(ArrayTest, KonstruktorSaPocetnomVrijednosti) {
    TypeParam value = 42;
    Array<TypeParam, N> expectedArr(value);

    this->arr = expectedArr;
    
    for (std::size_t i = 0; i < N; ++i) {
        EXPECT_EQ(this->arr[i], expectedArr[i]);
    }
}

// Konstruktor sa inicijalizacijskom listom
TYPED_TEST(ArrayTest, KonstruktorSaInicijalizacijskomListom) {
    Array<TypeParam, N> expectedArr{'a', 'b', 'c', 'd', 'e'};
    this->arr = expectedArr;
    
    for (std::size_t i = 0; i < N; ++i) {
        EXPECT_EQ(this->arr[i], expectedArr[i]);
    }
}

// Testirati izbacivanje izuzetka kod suviše velikog broja inicijalizacijskih vrijednosti parametriziranim testom
TYPED_TEST(ArrayTest, IzbacivanjeIzuzetka) {
    // Stvorimo polje sa incijalizacijskom listom koja namjerno ima previše elemenata
    EXPECT_THROW(({
        Array<TypeParam, N> tooLongArr{'a', 'b', 'c', 'd', 'e', 'f'}; //tu mogu tipa maknuti element 'b' i onda cu dobiti test failed jer lista sadrzi dozvoljenu kolicinu elemenata
        }),
        std::runtime_error
    );
}

//test za operator indeksiranja []
TYPED_TEST(ArrayTest, OperatorIndeksiranja) {
    Array<TypeParam, N> originalArr{'a', 'b', 'c', 'd', 'e'};
    this->arr = originalArr;

    // Testiramo ne-konstanti operator indeksiranja
    for (std::size_t i = 0; i < N; ++i) {
        this->arr[i] = 'x'; // Dodijelimo novu vrijednost na zadani indeks
        EXPECT_EQ(this->arr[i], 'x'); // Potvrdimo novu vrijednsot, tu mogu promijenit 'x' u nesto drugo da dobijem test failed
    }

    // Testiramo konstantni operator indeksiranja
    const Array<TypeParam, N>& constArr = this->arr;
    for (std::size_t i = 0; i < N; ++i) {
        EXPECT_EQ(constArr[i], 'x'); // Potvrdimo vrijednost, u testu za ne-konstanti operator su sve pretvorene u 'x'
    }
}

// Testiramo opreator indeksiranja sa only move tipom podataka
TYPED_TEST(ArrayTest, OperatorIndeksiranjaSaOnlyMoveTipom) {
    // Inicijaliziramo polje sa std::unique_ptr tipom podataka
    Array<std::unique_ptr<int>, N> arrUniquePtr;
    for (std::size_t i = 0; i < N; ++i) {
        arrUniquePtr[i] = std::make_unique<int>(i);
    }

    // Pomaknemo elemente koristeci oprator indeksiranja i std::move()
    for (std::size_t i = 0; i < N; ++i) {
        Array<std::unique_ptr<int>, N> movedArr;
        movedArr[i] = std::move(arrUniquePtr[i]);

        // Potvrdimo da originalno polje vise ne sadrzi element
        EXPECT_EQ(arrUniquePtr[i], nullptr);

        // Potvrdimo da movedArr sadrzi taj element
        EXPECT_NE(movedArr[i], nullptr);
    }
}

// Test za copy konstruktor
TYPED_TEST(ArrayTest, CopyKonstruktor) {
    Array<TypeParam, N> originalArr{'a', 'b', 'c', 'd', 'e'};
    this->arr = originalArr;

    // Napravim kopiju
    Array<TypeParam, N> copyArr(originalArr);

    // Provjerim jesu li dva polja jednaka
    for (std::size_t i = 0; i < N; ++i) {
        EXPECT_EQ(copyArr[i], originalArr[i]);
    }
}

// Test za operator pridruzivanja kopiranjem
TYPED_TEST(ArrayTest, OperatorPridruzivanja) {
    Array<TypeParam, N> originalArr{'a', 'b', 'c', 'd', 's'};
    this->arr = originalArr;

    // Napravim pridruzivanje kopiranjem
    Array<TypeParam, N> assignedArr = originalArr;

    // Provjerim jesu li dva polja jednaka
    for (std::size_t i = 0; i < N; ++i) {
        EXPECT_EQ(assignedArr[i], originalArr[i]);
    }
}

// Test za range-for petlju
TYPED_TEST(ArrayTest, RangeForPetlja) {
    Array<TypeParam, N> originalArr{'x', 'y',  'z', 'p', 'q'};
    this->arr = originalArr;

    // Koristim range for pelju za pomicanje i provjeru svakog elementa
    int i = 0;
    for (const auto& element : originalArr) {
        EXPECT_EQ(element, originalArr[i]);
        ++i;
    }
}

// Test za operator uspredivanja ==
TYPED_TEST(ArrayTest, OperatorUsporedivanja) {
    // Inicijaliziramo dva pola istog tipa
    Array<TypeParam, N> arr1{'a', 'b', 'c', 'd', 'e'};
    Array<TypeParam, N> arr2{'a', 'b', 'c', 'd', 'e'};
    EXPECT_EQ(arr1, arr2);  // Provjerimo jesu li jednaki

    // Provjera za usporedbu dva polja razlicitog tipa
    if constexpr (std::is_convertible<TypeParam, double>::value) {
        Array<TypeParam, N> arr3{1, 2, 3, 4, 5};
        Array<double, N> arr4{1.0, 2.0, 3.0, 4.0, 5.0}; //ako promjenim neki od brojeva tipa 1.0 u 2.0 dobit cu fail
        EXPECT_EQ(arr3, arr4);
    }
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
