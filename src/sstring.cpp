#include "sstring.h"
#include <algorithm>
#include <iostream>

namespace saman
{

std::ostream& operator<<(std::ostream& out, const SString& str)
{
    return out << str.m_str;	//In GCC 8.1.1 I spend some time to understand why this a infinite recursion!
                                //I didn't included iostream!
}

bool operator==(const SString& left, const SString& right)
{
    return std::strcmp(left.m_str, right.m_str) == 0;
}

SString operator+(const SString& left, const SString& right)
{
    SString ret{left.m_len + right.m_len};
    std::strcpy(ret.m_str, left.m_str);
    std::strcat(ret.m_str, right.m_str);
    return ret;
}

SString::SString(const char* str) : SString{std::strlen(str)}
{
    std::strcpy(m_str, str);
}

SString::SString(const SString& str) : SString{str.m_len}
{
    std::strncpy(m_str, str.m_str, m_len);
    m_str[m_len] = '\0';
}

SString::SString(SString&& str) : m_len{str.m_len}, m_str{str.m_str}
{
    str.m_str = nullptr;	//Because of this m_str can be null in the destructor
    str.m_len = 0;
}

SString::~SString()
{
    if (m_str == nullptr)	//See move constructor
        return;
    delete[] m_str;
    m_str = nullptr;
}

SString& SString::operator=(const SString& right)
{
    SString tmp{right};
    std::swap(m_str, tmp.m_str);
    m_len = tmp.m_len;
    return *this;
}

SString& SString::operator=(SString&& right)
{
    std::swap(m_str, right.m_str);
    std::swap(m_len, right.m_len);
    return *this;
}

SString& SString::operator+=(const SString& right)
{
    SString res{*this + right};
    *this = std::move(res);
    return *this;
}

SString SString::operator()(const std::size_t from, const std::size_t length) const
{
    if (from >= m_len || length == 0)
        return SString();
   auto len = std::min(m_len, length);
   SString res{len};
   std::copy_n(m_str + from, len, res.m_str);
   res[len] = '\0';
   return res;
}

}
