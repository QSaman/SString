#pragma once

#include <cstring>
#include <iosfwd>

namespace saman
{

class SString
{
    /*
     * You cannot define both conversion constructor and conversion operator without explicit keyword.
     * In other words if you don't put explicit keyword before both of them:
     * SString(const char*);
     * operator const char*() const;
     *
     * then we have:
     * SString str{"foo"};
     * 1. Suppose you define operator== which is a binary operator as a free function (symmetric):
     *
     * 1.1. "foo" == str;
     *      The compiler will find two operators. One is operator==(const char*, const char*) which
     *      is a built-in operator. So it converts str to a char* using conversion operator.
     *      The other operator is operator==(const SString&, const SString&). So it tries to convert
     *      "foo" to SString using conversion constructor. Since the compiler has two options to
     *      choose from it's a compile error
     * 1.2. str == "foo";
     *      The compiler again will find two operators which is a compile error
     *
     * 2. Suppose you define operator== as a member function (asymmetric):
     *
     * 1.1. "foo" == str;
     *      Since "foo" is a c-string, the compiler only finds the built-in operator and we don't have
     *      compile error.
     *1.2. str == "foo";
     *      Compiler finds two operators. the built-in one and tries to convert str to char* using
     *      conversion operator. The other one is member function operator and it tries to convert
     *      "foo" to SString using conversion constructor. Again it's a compile error.
     *
     * For resolving these problems I put explicit in front of conversion operator
     *
     * Note: See operator<< and notice the compiler doesn't use conversion constructor to convert a
     * char* into SString! So std::cout << "foo" uses the built-in operator not from SString
     * */

    friend SString operator+(const SString& left, const SString& right);
public:
    SString(const char* str = "");
    explicit SString(std::size_t len): m_len{len}, m_str{new char[m_len + 1]} {}
    SString(const SString& str);
    SString(SString&& str);
    ~SString();
    inline std::size_t length() const {return m_len;}
    inline const char* c_str() const {return m_str;}


    explicit inline operator const char* () const {return m_str;}
    inline char& operator[](const std::size_t index) {return *(m_str + index);}
    inline const char& operator[](const std::size_t index) const {return *(m_str + index);}
    SString& operator=(const SString& right);
    SString& operator=(SString&& right);
    SString& operator+=(const SString& right);
    SString operator()(const std::size_t from, const std::size_t length) const;
private:
    std::size_t m_len;
    char* m_str;
};

std::ostream& operator<<(std::ostream& out, const SString& str);
bool operator==(const SString& left, const SString& right);
}
