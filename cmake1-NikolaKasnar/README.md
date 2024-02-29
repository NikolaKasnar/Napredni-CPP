**Zadatak**. Repozitorij sadrži direktorij s programom u `src/main.cpp` datoteci, 
sa slikom `data/cb.bmp` i cmake modulom `cmake/modules/FindSFML.cmake`. Program 
koristi SFML grafičku biblioteku kao vanjsku zavisnost. Zadatak je sljedeći:

- Instalirati binarnu verziju SFML biblioteke na svom računalu 
   (`https://www.sfml-dev.org/download/sfml/2.6.0/`)
- Konstruirati cmake sustav za izgradnju koji će izgraditi program.

*Ograničenja*: 

- Za nalaženje SFML biblioteke treba koristiti modul `cmake/modules/FindSFML.cmake`.
Taj modul ne eksportira ciljeve već samo definira odgovarajuće varijable. Vidjeti u 
datoteci `cmake/modules/FindSFML.cmake` kako se modul koristi. 

- Ne mijenjati strukturu direktorija. Samo dodavati CMakeLists.txt datoteke tamo gdje 
je to potrebno. 

- Program se mora korektno kompilirati i izvršavati.

Za sve nedoumice konzultirati CMake dokumentaciju. 
