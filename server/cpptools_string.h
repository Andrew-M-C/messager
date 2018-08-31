
#ifndef __CPPTOOLS_STRING_H__
#define __CPPTOOLS_STRING_H__

#include <string>
#include <stdint.h>
#include <stddef.h>

#include "cpp_tools.h"

namespace andrewmc {
namespace cpptools {
namespace string {

std::string utf8_uppercase(const std::string &str);

typedef uint32_t Unichar_t;

std::string unichar_string(Unichar_t chr);
std::string unichar_hex_string(Unichar_t chr);

class UTF8String {
public:
    UTF8String();
    UTF8String(const char *c_utf8_string);
    UTF8String(const char *c_utf8_string, int len);
    UTF8String(const ::std::string &utf8_string);
    UTF8String(const UTF8String &string);

    void assign(const char *c_utf8_string);
    void assign(const char *c_utf8_string, int len);
    void assign(const ::std::string &utf8_string);
    void assign(const UTF8String &string);
    UTF8String copy();

    int length() const;
    Unichar_t get_char(int index) const throw(std::out_of_range);
    Unichar_t operator [] (int index) const throw(std::out_of_range);

    void operator = (const char *c_utf8_string);
    void operator = (const ::std::string &utf8_string);
    void operator = (const UTF8String &string);

    bool operator == (const char *c_utf8_string) const;
    bool operator == (const ::std::string &utf8_string) const;
    bool operator == (const UTF8String &string) const;

    UTF8String operator + (const char *c_utf8_string) const;
    UTF8String operator + (const ::std::string &utf8_string) const;
    UTF8String operator + (const UTF8String &string) const;

    const char *c_str() const;
    const ::std::string &string() const;
    const Unichar_t *unichar_array() const;

private:
    ::andrewmc::cpptools::Data      _unichar_buff;
    ::std::string                   _orig_str;
    int                             _unichar_len;
    void _parse(const char *c_str, int len);
};

}   // end of namepsace string
}   // end of namepsace cpptools
}   // end of namepsace andrewmc


#endif  // eof
