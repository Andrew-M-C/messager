
#include "tools_string.h"
#include "srv_log.h"

#include <string>
#include <stdlib.h>

#define _VERSION_CODE(x, y, z)  (((x) << 24) + ((y << 16)) + ((z) << 0))

// ==========
#define __PRIVATE_FUNCTIONS
#ifdef __PRIVATE_FUNCTIONS


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
    char *c_buff = (char *)malloc(len);
    const char *c_src = s.c_str();
    c_buff[len - 1] = '\0';

    size_t index = 0;
    while (index < len)
    {
        char byte = c_src[index];
        if (0 == (byte & 0x80))
        {
            if (byte >= 'a' && byte <= 'z') {
                c_buff[index] = byte + ('A' - 'a');
            }
            else {
                c_buff[index] = byte;
            }
            index += 1;
        }
        else if (0xC0 == (byte & 0xE0))
        {
            c_buff[index] = byte;
            c_buff[index + 1] = c_src[index + 1];
            index += 2;
        }
        else if (0xE0 == (byte & 0xF0))
        {
            c_buff[index] = byte;
            c_buff[index + 1] = c_src[index + 1];
            c_buff[index + 2] = c_src[index + 2];
            index += 3;
        }
        else    // (0xF0 == (byte & 0xF8))
        {
            c_buff[index] = byte;
            c_buff[index + 1] = c_src[index + 1];
            c_buff[index + 2] = c_src[index + 2];
            c_buff[index + 3] = c_src[index + 3];
            index += 4;
        }
    }


    std::string ret_str;
    ret_str.assign(c_buff);

    free(c_buff);
    c_buff = NULL;

    return ret_str;
}
#endif  // end of '#if _VERSION_CODE(...'

#endif  // end of __PRIVATE_FUNCTIONS


// ==========
#define __PUBLIC_FUNCTIONS
#ifdef __PUBLIC_FUNCTIONS

// reference: [C / C++ UTF-8 upper/lower case conversions](https://stackoverflow.com/questions/12493496/c-c-utf-8-upper-lower-case-conversions)
std::string andrewmc::messager::server::tools::string::utf8_uppercase(const std::string &str)
{
    return _tou(str);
}

#endif  // __PUBLIC_FUNCTIONS
