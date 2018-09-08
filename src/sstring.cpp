#include "sstring.h"
#include <algorithm>

namespace saman
{

bool operator==(const SString& left, const SString& right)
{
    return std::strcmp(left.m_str, right.m_str) == 0;
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

SString::SString(SString&& str)
{
    m_str = str.m_str;
    m_len = str.m_len;
    str.m_str = nullptr;
    str.m_len = 0;
}


SString::~SString()
{
    if (m_str == nullptr)
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

SString SString::operator+(const SString& right) const
{
    SString ret{m_len + right.m_len};
    std::strcpy(ret.m_str, m_str);
    std::strcat(ret.m_str, right.m_str);
    return ret;
}

SString& SString::operator+=(const SString& right)
{
    SString res{*this + right};
    *this = std::move(res);
    return *this;
}

SString SString::operator()(const std::size_t from, const std::size_t length) const
{
    if (from >= m_len)
        return SString();
   auto len = std::min(m_len, length);
   SString res{len};
   std::copy_n(m_str + from, len, res.m_str);
   res[len] = '\0';
   return res;
}

std::ostream& operator<<(std::ostream& out, const SString& str)
{
   out << str.m_str;
   return out;
}
}
