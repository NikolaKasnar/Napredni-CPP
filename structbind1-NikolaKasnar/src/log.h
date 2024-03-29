#pragma once
#include <string>
#include <array>
#include <fmt/format.h>
#include <tuple>
 
class Log{
    std::string _sender; 
    int         _priority; 
    std::array<char,3> _code;                            
    std::string _message; 
public:
    Log(std::string sender,  int priority, std::array<char,3> code, 
        std::string message); 
    
    //get funkcije za pristup privatim funkcijama
    std::string & sender() { return _sender;}
    std::string const & sender() const { return _sender;}
    int & priority() { return _priority;}
    int const & priority() const { return _priority;}
    std::array<char,3> & code() {return _code;}
    std::array<char,3> const & code() const {return _code;}
    std::string & message() { return _message;}
    std::string const & message() const { return _message;}
    
};

template <>
struct std::tuple_size<Log>{
    static constexpr int value =  4;
};

template <>
struct std::tuple_element<0, Log>{
     using type = std::string;
};

template <>
struct std::tuple_element<1, Log>{
     using type = int;
};

template <>
struct std::tuple_element<2, Log>{
     using type = std::array<char,3>;
};

template <>
struct std::tuple_element<3, Log>{
     using type = std::string;
};

// Deklariramo tri funkcijska predloska kao u primjeru
template <std::size_t N> decltype(auto) get(Log const &);
template <std::size_t N> decltype(auto) get(Log &);
template <std::size_t N> decltype(auto) get(Log &&);

// Inicijaliziramo te funkcije
template <>
inline decltype(auto) get<0>(Log & objekt){
    return objekt.sender();
}
template <>
inline decltype(auto) get<1>(Log & objekt){
    return objekt.priority();
}
template <>
inline decltype(auto) get<2>(Log & objekt){
    return objekt.code();
}
template <>
inline decltype(auto) get<3>(Log & objekt){
    return objekt.message();
}
template <>
inline decltype(auto) get<0>(Log const & objekt){
    return objekt.sender();
}
template <>
inline decltype(auto) get<1>(Log const & objekt){
    return objekt.priority();
}
template <>
inline decltype(auto) get<2>(Log const & objekt){
    return objekt.code();
}
template <>
inline decltype(auto) get<3>(Log const & objekt){
    return objekt.message();
}
template <>
inline decltype(auto) get<0>(Log && objekt){
    return objekt.sender();
}
template <>
inline decltype(auto) get<1>(Log && objekt){
    return objekt.priority();
}
template <>
inline decltype(auto) get<2>(Log && objekt){
    return objekt.code();
}
template <>
inline decltype(auto) get<3>(Log && objekt){
    return objekt.message();
}