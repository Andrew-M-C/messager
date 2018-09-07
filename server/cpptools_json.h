
#ifndef __CPPTOOLS_JSON_H__
#define __CPPTOOLS_JSON_H__

#include <exception>
#include <string>
#include <map>
#include <vector>
#include <stdint.h>
#include <stddef.h>

#include <rapidjson/rapidjson.h>
#include <rapidjson/document.h>

#include "cpp_tools.h"

namespace andrewmc {
namespace cpptools {
namespace json {

extern rapidjson::Document kDomForAllocator;


// ==========
// DOM operations

std::string dump(rapidjson::Document &dom);


// ==========
// value operations

void add_number(rapidjson::Value &val, const char *key, signed char number, rapidjson::Document &dom=kDomForAllocator);
void add_number(rapidjson::Value &val, const char *key, unsigned char number, rapidjson::Document &dom=kDomForAllocator);
void add_number(rapidjson::Value &val, const char *key, signed short number, rapidjson::Document &dom=kDomForAllocator);
void add_number(rapidjson::Value &val, const char *key, unsigned short number, rapidjson::Document &dom=kDomForAllocator);
void add_number(rapidjson::Value &val, const char *key, signed int number, rapidjson::Document &dom=kDomForAllocator);
void add_number(rapidjson::Value &val, const char *key, unsigned int number, rapidjson::Document &dom=kDomForAllocator);
void add_number(rapidjson::Value &val, const char *key, signed long number, rapidjson::Document &dom=kDomForAllocator);
void add_number(rapidjson::Value &val, const char *key, unsigned long number, rapidjson::Document &dom=kDomForAllocator);
void add_number(rapidjson::Value &val, const char *key, signed long long number, rapidjson::Document &dom=kDomForAllocator);
void add_number(rapidjson::Value &val, const char *key, unsigned long long number, rapidjson::Document &dom=kDomForAllocator);
void add_number(rapidjson::Value &val, const char *key, float number, rapidjson::Document &dom=kDomForAllocator);
void add_number(rapidjson::Value &val, const char *key, double number, rapidjson::Document &dom=kDomForAllocator);
void add_number(rapidjson::Document &dom, const char *key, signed char number);
void add_number(rapidjson::Document &dom, const char *key, unsigned char number);
void add_number(rapidjson::Document &dom, const char *key, signed short number);
void add_number(rapidjson::Document &dom, const char *key, unsigned short number);
void add_number(rapidjson::Document &dom, const char *key, signed int number);
void add_number(rapidjson::Document &dom, const char *key, unsigned int number);
void add_number(rapidjson::Document &dom, const char *key, signed long number);
void add_number(rapidjson::Document &dom, const char *key, unsigned long number);
void add_number(rapidjson::Document &dom, const char *key, signed long long number);
void add_number(rapidjson::Document &dom, const char *key, unsigned long long number);
void add_number(rapidjson::Document &dom, const char *key, float number);
void add_number(rapidjson::Document &dom, const char *key, double number);

void add_bool(rapidjson::Value &val, const char *key, bool flag, rapidjson::Document &dom=kDomForAllocator);
void add_bool(rapidjson::Document &dom, const char *key, bool flag);

void add_string(rapidjson::Value &val, const char *key, const char *value, rapidjson::Document &dom=kDomForAllocator);
void add_string(rapidjson::Value &val, const char *key, const std::string &value, rapidjson::Document &dom=kDomForAllocator);
void add_string(rapidjson::Document &dom, const char *key, const char *value);
void add_string(rapidjson::Document &dom, const char *key, const std::string &value);

rapidjson::Value &add_object(rapidjson::Value &val, const char *key, rapidjson::Document &dom=kDomForAllocator);
rapidjson::Value &add_object(rapidjson::Document &dom, const char *key);

rapidjson::Value &add_array(rapidjson::Value &val, const char *key, rapidjson::Document &dom=kDomForAllocator);
rapidjson::Value &add_array(rapidjson::Document &dom, const char *key);

void append(rapidjson::Value &array, rapidjson::Value &val_to_append, rapidjson::Document &dom=kDomForAllocator);
void append_number(rapidjson::Value &array, signed char number, rapidjson::Document &dom=kDomForAllocator);
void append_number(rapidjson::Value &array, unsigned char number, rapidjson::Document &dom=kDomForAllocator);
void append_number(rapidjson::Value &array, signed short number, rapidjson::Document &dom=kDomForAllocator);
void append_number(rapidjson::Value &array, unsigned short number, rapidjson::Document &dom=kDomForAllocator);
void append_number(rapidjson::Value &array, signed int number, rapidjson::Document &dom=kDomForAllocator);
void append_number(rapidjson::Value &array, unsigned int number, rapidjson::Document &dom=kDomForAllocator);
void append_number(rapidjson::Value &array, signed long number, rapidjson::Document &dom=kDomForAllocator);
void append_number(rapidjson::Value &array, unsigned long number, rapidjson::Document &dom=kDomForAllocator);
void append_number(rapidjson::Value &array, signed long long number, rapidjson::Document &dom=kDomForAllocator);
void append_number(rapidjson::Value &array, unsigned long long number, rapidjson::Document &dom=kDomForAllocator);
void append_number(rapidjson::Value &array, float number, rapidjson::Document &dom=kDomForAllocator);
void append_number(rapidjson::Value &array, double number, rapidjson::Document &dom=kDomForAllocator);
void append_bool(rapidjson::Value &array, bool flag, rapidjson::Document &dom=kDomForAllocator);
void append_string(rapidjson::Value &array, const char *str, rapidjson::Document &dom=kDomForAllocator);
void append_string(rapidjson::Value &array, const std::string &str, rapidjson::Document &dom=kDomForAllocator);

void append(rapidjson::Document &dom_array, rapidjson::Value &val_to_append);
void append_number(rapidjson::Document &dom_array, signed char number);
void append_number(rapidjson::Document &dom_array, unsigned char number);
void append_number(rapidjson::Document &dom_array, signed short number);
void append_number(rapidjson::Document &dom_array, unsigned short number);
void append_number(rapidjson::Document &dom_array, signed int number);
void append_number(rapidjson::Document &dom_array, unsigned int number);
void append_number(rapidjson::Document &dom_array, signed long number);
void append_number(rapidjson::Document &dom_array, unsigned long number);
void append_number(rapidjson::Document &dom_array, signed long long number);
void append_number(rapidjson::Document &dom_array, unsigned long long number);
void append_number(rapidjson::Document &dom_array, float number);
void append_number(rapidjson::Document &dom_array, double number);
void append_bool(rapidjson::Document &dom_array, bool flag);
void append_string(rapidjson::Document &dom_array, const char *str);
void append_string(rapidjson::Document &dom_array, const std::string &str);

}   // end of namepsace json
}   // end of namepsace cpptools
}   // end of namepsace andrewmc


#endif  // eof
