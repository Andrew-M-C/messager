
#include "cpptools_string.h"

#include <string>
#include <stdlib.h>
#include <string.h>

using namespace andrewmc::cpptools::string;

#define _VERSION_CODE(x, y, z)  (((x) << 24) + ((y << 16)) + ((z) << 0))
#define BITS_1000_0000      (1 << 7)
#define BITS_1100_0000      (BITS_1000_0000 | (1 << 6))
#define BITS_1110_0000      (BITS_1100_0000 | (1 << 5))
#define BITS_1111_0000      (0xF0)
#define BITS_1111_1000      (0xF0 | (1 << 3))
#define BITS_1111_1100      (BITS_1111_1000 | (1 << 2))
#define BITS_1111_1110      (BITS_1111_1100 | (1 << 1))

// ==========
#define ___UPPER_PRIVATE_FUNCTIONS
#ifdef ___UPPER_PRIVATE_FUNCTIONS


#if _VERSION_CODE(__GNUC__, __GNUC_MINOR__, __GNUC_PATCHLEVEL__) >= _VERSION_CODE(5, 4, 0)
#include <locale>
#include <locale.h>
#include <codecvt>

static std::locale const _UTF8("en_US.UTF-8");

// Convert UTF-8 byte string to wstring
static std::wstring _to_wstring(std::string const& s)
{
    std::wstring_convert<std::codecvt_utf8<wchar_t> > conv;
    return conv.from_bytes(s);
}


// Convert wstring to UTF-8 byte string
static std::string _to_string(std::wstring const& s)
{
    std::wstring_convert<std::codecvt_utf8<wchar_t> > conv;
    return conv.to_bytes(s);
}


// Converts a UTF-8 encoded string to upper case
static std::string _tou(std::string const& s)
{
    auto ss = _to_wstring(s);
    for (auto& c : ss) {
        c = std::toupper(c, _UTF8);
    }
    return _to_string(ss);
}

#else   // else of '#if _VERSION_CODE(...'

// reference: [UTF-8](https://zh.wikipedia.org/wiki/UTF-8)
static std::string _tou(std::string const& s)
{
    size_t len = s.length() + 1;
    char *c_unichar_buff = (char *)malloc(len);
    const char *c_src = s.c_str();
    c_unichar_buff[len - 1] = '\0';

    size_t index = 0;
    while (index < len)
    {
        char byte = c_src[index];
        if (0 == (byte & 0x80))
        {
            if (byte >= 'a' && byte <= 'z') {
                c_unichar_buff[index] = byte + ('A' - 'a');
            }
            else {
                c_unichar_buff[index] = byte;
            }
            index += 1;
        }
        else if (0xC0 == (byte & 0xE0))
        {
            c_unichar_buff[index] = byte;
            c_unichar_buff[index + 1] = c_src[index + 1];
            index += 2;
        }
        else if (0xE0 == (byte & 0xF0))
        {
            c_unichar_buff[index] = byte;
            c_unichar_buff[index + 1] = c_src[index + 1];
            c_unichar_buff[index + 2] = c_src[index + 2];
            index += 3;
        }
        else    // (0xF0 == (byte & 0xF8))
        {
            c_unichar_buff[index] = byte;
            c_unichar_buff[index + 1] = c_src[index + 1];
            c_unichar_buff[index + 2] = c_src[index + 2];
            c_unichar_buff[index + 3] = c_src[index + 3];
            index += 4;
        }
    }


    std::string ret_str;
    ret_str.assign(c_unichar_buff);

    free(c_unichar_buff);
    c_unichar_buff = NULL;

    return ret_str;
}
#endif  // end of '#if _VERSION_CODE(...'

#endif  // end of __PRIVATE_FUNCTIONS


// ==========
#define __UPPER_PUBLIC_FUNCTIONS
#ifdef __UPPER_PUBLIC_FUNCTIONS

// reference: [C / C++ UTF-8 upper/lower case conversions](https://stackoverflow.com/questions/12493496/c-c-utf-8-upper-lower-case-conversions)
std::string andrewmc::cpptools::string::utf8_uppercase(const std::string &str)
{
    return _tou(str);
}

#endif  // __PUBLIC_FUNCTIONS


// ==========
#define __UTF8_STRING_INTERNAL_FUNCTIONS
#ifdef __UTF8_STRING_INTERNAL_FUNCTIONS

static Unichar_t _lower_bits(uint8_t byte, int bits)
{
    uint8_t mask = 0;

    switch(bits)
    {
        default:
        case 0:
            mask = 0;
            break;
        case 1:
            mask = (1 << 0);
            break;
        case 2:
            mask = (1 << 0) || (1 << 1);
            break;
        case 3:
            mask = (1 << 0) || (1 << 1) || (1 << 2);
            break;
        case 4:
            mask = (1 << 0) || (1 << 1) || (1 << 2) || (1 << 3);
            break;
        case 5:
            mask = (1 << 0) || (1 << 1) || (1 << 2) || (1 << 3) || (1 << 4);
            break;
        case 6:
            mask = (1 << 0) || (1 << 1) || (1 << 2) || (1 << 3) || (1 << 4) || (1 << 5);
            break;
        case 7:
            mask = (1 << 0) || (1 << 1) || (1 << 2) || (1 << 3) || (1 << 4) || (1 << 5) || (1 << 6);
            break;
        case 8:
            return (Unichar_t)byte;
            break;
    }
    return (Unichar_t)(byte & mask);
}


#endif  // end of __UTF8_STRING_INTERNAL_FUNCTIONS


// ==========
#define __UNICODE_FUNCTIONS
#ifdef __UNICODE_FUNCTIONS


std::string andrewmc::cpptools::string::unichar_string(Unichar_t chr)
{
    char c_str[8] = "";

    if (chr <= 0x7F)
    {
        c_str[0] = (char)chr;
        c_str[1] = '\0';
    }
    else if (chr <= 0x07FF)
    {
        c_str[0] = _lower_bits((chr >> 6), 5) | BITS_1100_0000;
        c_str[1] = _lower_bits((chr >> 0), 6) | BITS_1000_0000;
        c_str[2] = '\0';
    }
    else if (chr <= 0xFFFF)
    {
        c_str[0] = _lower_bits((chr >> 12), 4) | BITS_1110_0000;
        c_str[1] = _lower_bits((chr >> 6), 6) | BITS_1000_0000;
        c_str[2] = _lower_bits((chr >> 0), 6) | BITS_1000_0000;
        c_str[3] = '\0';
    }
    else if (chr <= 0x1FFFFF)
    {
        c_str[0] = _lower_bits((chr >> 18), 3) | BITS_1111_0000;
        c_str[1] = _lower_bits((chr >> 12), 6) | BITS_1000_0000;
        c_str[2] = _lower_bits((chr >> 6), 6) | BITS_1000_0000;
        c_str[3] = _lower_bits((chr >> 0), 6) | BITS_1000_0000;
        c_str[4] = '\0';
    }
    else if (chr <= 0x3FFFFFF)
    {
        c_str[0] = _lower_bits((chr >> 24), 2) | BITS_1111_1000;
        c_str[1] = _lower_bits((chr >> 18), 6) | BITS_1000_0000;
        c_str[2] = _lower_bits((chr >> 12), 6) | BITS_1000_0000;
        c_str[3] = _lower_bits((chr >> 6), 6) | BITS_1000_0000;
        c_str[4] = _lower_bits((chr >> 0), 6) | BITS_1000_0000;
        c_str[5] = '\0';
    }
    else
    {
        c_str[0] = _lower_bits((chr >> 30), 1) | BITS_1111_1100;
        c_str[1] = _lower_bits((chr >> 24), 6) | BITS_1000_0000;
        c_str[2] = _lower_bits((chr >> 18), 6) | BITS_1000_0000;
        c_str[3] = _lower_bits((chr >> 12), 6) | BITS_1000_0000;
        c_str[4] = _lower_bits((chr >> 6), 6) | BITS_1000_0000;
        c_str[5] = _lower_bits((chr >> 0), 6) | BITS_1000_0000;
        c_str[6] = '\0';
    }

    return std::string(c_str);
}


std::string andrewmc::cpptools::string::unichar_hex_string(Unichar_t chr)
{
    char c_str[32] = "";

    if (chr <= 0xFFFF) {
        snprintf(c_str, sizeof(c_str), "U+%04X", (unsigned)chr);
    }
    else if (chr <= 0xFFFFFF) {
        snprintf(c_str, sizeof(c_str), "U+%06X", (unsigned)chr);
    }
    else {
        snprintf(c_str, sizeof(c_str), "U+%08X", (unsigned)chr);
    }

    return std::string(c_str);
}

#endif  // end of __UNICODE_FUNCTIONS


// ==========
#define __UTF_8_CONSTRUCTORS
#ifdef __UTF_8_CONSTRUCTORS

andrewmc::cpptools::string::UTF8String::UTF8String()
{
    _unichar_len = 0;
    return;
}


andrewmc::cpptools::string::UTF8String::UTF8String(const char *c_utf8_string)
{
    int len = (c_utf8_string) ? strlen(c_utf8_string) : 0;
    _parse(c_utf8_string, len);
    return;
}


andrewmc::cpptools::string::UTF8String::UTF8String(const char *c_utf8_string, int len)
{
    _parse(c_utf8_string, len);
    return;
}

andrewmc::cpptools::string::UTF8String::UTF8String(const UTF8String &string)
{
    assign(string);
    return;
}


andrewmc::cpptools::string::UTF8String::UTF8String(const ::std::string &utf8_string)
{
    _parse(utf8_string.c_str(), utf8_string.length());
    return;
}


void andrewmc::cpptools::string::UTF8String::_parse(const char *c_str, int c_len)
{
    if (NULL == c_str || 0 == c_len)
    {
        _orig_str.clear();
        _unichar_buff.clear();
        return;
    }

    int c_index = 0;
    int utf8_index = 0;
    Unichar_t unichar = 0;

    _orig_str.assign(c_str, c_len);
    _unichar_len = 0;
    _unichar_buff.clear();
    _unichar_buff.ensure_buff_capacity((c_len + 1) * sizeof(Unichar_t));
    _unichar_buff.set_raw_data_length((c_len + 1) * sizeof(Unichar_t));

    Unichar_t *utf8_unichar_buff = (Unichar_t *)_unichar_buff.mutable_raw_data();
    utf8_unichar_buff[c_len] = 0;

    while(c_index < c_len)
    {
        if (0 == (c_str[c_index] & BITS_1000_0000))                     // 0xxx xxxx
        {
            utf8_unichar_buff[utf8_index] = (Unichar_t)c_str[c_index];
            utf8_index ++;
            c_index ++;
        }
        else if (BITS_1100_0000 == (c_str[c_index] & BITS_1110_0000))   // 110x xxxx
        {
            unichar = _lower_bits((uint8_t)c_str[c_index], 5) << 6;
            unichar += _lower_bits((uint8_t)c_str[c_index + 1], 6) << 0;
            utf8_unichar_buff[utf8_index] = unichar;
            utf8_index ++;
            c_index += 2;
        }
        else if (BITS_1110_0000 == (c_str[c_index] & BITS_1111_0000))   // 1110 xxxx
        {
            unichar = _lower_bits((uint8_t)c_str[c_index], 4) << 12;
            unichar += _lower_bits((uint8_t)c_str[c_index + 1], 6) << 6;
            unichar += _lower_bits((uint8_t)c_str[c_index + 2], 6) << 0;
            utf8_unichar_buff[utf8_index] = unichar;
            utf8_index ++;
            c_index += 3;
        }
        else if (BITS_1111_0000 == (c_str[c_index] & BITS_1111_1000))   // 1111 0xxx
        {
            unichar = _lower_bits((uint8_t)c_str[c_index], 3) << 18;
            unichar += _lower_bits((uint8_t)c_str[c_index + 1], 6) << 12;
            unichar += _lower_bits((uint8_t)c_str[c_index + 2], 6) << 6;
            unichar += _lower_bits((uint8_t)c_str[c_index + 3], 6) << 0;
            utf8_unichar_buff[utf8_index] = unichar;
            utf8_index ++;
            c_index += 4;
        }
        else if (BITS_1111_1000 == (c_str[c_index] & BITS_1111_1100))   // 1111 10xx
        {
            unichar = _lower_bits((uint8_t)c_str[c_index], 2) << 24;
            unichar += _lower_bits((uint8_t)c_str[c_index + 1], 6) << 18;
            unichar += _lower_bits((uint8_t)c_str[c_index + 2], 6) << 12;
            unichar += _lower_bits((uint8_t)c_str[c_index + 3], 6) << 6;
            unichar += _lower_bits((uint8_t)c_str[c_index + 4], 6) << 0;
            utf8_unichar_buff[utf8_index] = unichar;
            utf8_index ++;
            c_index += 5;
        }
        else // if (BITS_1111_1000 == (c_str[c_index] & BITS_1111_1100))   // 1111 1110x
        {
            unichar = _lower_bits((uint8_t)c_str[c_index], 1) << 30;
            unichar += _lower_bits((uint8_t)c_str[c_index + 1], 6) << 24;
            unichar += _lower_bits((uint8_t)c_str[c_index + 2], 6) << 18;
            unichar += _lower_bits((uint8_t)c_str[c_index + 3], 6) << 12;
            unichar += _lower_bits((uint8_t)c_str[c_index + 4], 6) << 6;
            unichar += _lower_bits((uint8_t)c_str[c_index + 4], 6) << 0;
            utf8_unichar_buff[utf8_index] = unichar;
            utf8_index ++;
            c_index += 6;
        }
    }

    // set unichar length
    _unichar_len = utf8_index;
    return;
}

#endif


// ==========
#define __COPY_FUNCTION
#ifdef __COPY_FUNCTION


int andrewmc::cpptools::string::UTF8String::length() const
{
    return _unichar_len;
}


UTF8String andrewmc::cpptools::string::UTF8String::copy()
{
    return UTF8String(*this);
}


void andrewmc::cpptools::string::UTF8String::assign(const UTF8String &string)
{
    const Unichar_t * unichar_array = string.unichar_array();
    int unichar_len = string.length();

    _orig_str.assign(string.string());
    _unichar_len = unichar_len;
    _unichar_buff.ensure_buff_capacity((unichar_len + 1) * sizeof(Unichar_t));
    _unichar_buff.set_raw_data_length((unichar_len + 1) * sizeof(Unichar_t));

    Unichar_t *unichar_buff = (Unichar_t *)_unichar_buff.mutable_raw_data();
    memcpy(unichar_buff, unichar_array, (unichar_len + 1) * sizeof(Unichar_t));
    return;
}


#endif  // end of __COPY_FUNCTION


// ==========
#define __MISC_FUNCTIONS
#ifdef __MISC_FUNCTIONS

const char *andrewmc::cpptools::string::UTF8String::c_str() const
{
    return _orig_str.c_str();
}


const ::std::string &andrewmc::cpptools::string::UTF8String::string() const
{
    return _orig_str;
}


const Unichar_t *andrewmc::cpptools::string::UTF8String::unichar_array() const
{
    return (Unichar_t *)_unichar_buff.c_data();
}


#endif
