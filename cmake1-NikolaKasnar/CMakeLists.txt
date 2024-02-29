cmake_minimum_required(VERSION 3.13)
project(dz_Project)

# Postavlja cmake module path na direktorij u kojem se nalazi findSFML.cmake
list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake/modules)

# Pronalazi sve biblioteke iz SFML-a koje su nam potrebne, nama je potrebna samo graphics library ali ih on ovdje sve dovuče za svaki slučaj
find_package(SFML 2.5 COMPONENTS system window graphics network audio REQUIRED)

add_executable(1.dz src/main.cpp)

# Postavljam target_compile_options, target_compile_definitions, target_include_directories itarget_link_libraries kao sto je opisano u predavanjima o Cmakeu
target_compile_options(1.dz PRIVATE ${SFML_COMPILE_OPTIONS})
target_compile_definitions(1.dz PRIVATE ${SFML_COMPILE_DEFINITIONS})
target_include_directories(1.dz PRIVATE ${SFML_INCLUDE_DIRECTORIES})
target_link_libraries(1.dz PRIVATE ${SFML_LIBRARIES})

# Nakon sto se build direktorij generira u njega kopiram sliku iz data direktorija, inace dovivam poruku "Failed to load image "cb.bmp". Reason: Unable to open file", nadam se da je ovo rjesenje okej s obzirom na ogranicenja zadace
configure_file(${CMAKE_SOURCE_DIR}/data/cb.bmp ${CMAKE_BINARY_DIR}/cb.bmp COPYONLY)
