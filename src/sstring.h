#pragma once

#include <cstring>
#include <iosfwd>

namespace saman
{

class SString
{
public:
    SString(const char* str = "");
    explicit SString(std::size_t len): m_len{len}, m_str{new char[m_len + 1]} {}
    SString(const SString& str);
    SString(SString&& str);
    ~SString();
    inline std::size_t length() {return m_len;}


    explicit inline operator const char* () const {return m_str;}
    inline char& operator[](const std::size_t index) {return *(m_str + index);}
    inline const char& operator[](const std::size_t index) const {return *(m_str + index);}
    SString& operator=(const SString& right);
    SString& operator=(SString&& right);
    //bool operator==(const SString& right) const {return std::strcmp(m_str, right.m_str) == 0;}
    SString operator+(const SString& right) const;
    SString& operator+=(const SString& right);
    SString operator()(const std::size_t from, const std::size_t length) const;

    friend bool operator==(const SString& left, const SString& right);
    friend std::ostream& operator<<(std::ostream& out, const SString& str);
private:
    std::size_t m_len;
    char* m_str;
};

}
