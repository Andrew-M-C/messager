
#ifndef __CPPTOOLS_JSON_H__
#define __CPPTOOLS_JSON_H__

#include <exception>
#include <string>
#include <map>
#include <vector>
#include <stdint.h>
#include <stddef.h>

#include "cpp_tools.h"

namespace andrewmc {
namespace cpptools {
namespace json {

extern const void *JSON_NULL;


typedef enum {
    kTypeUnknown = 0,
    kTypeNull,
    kTypeNumber,
    kTypeString,
    kTypeObject,
    kTypeArray,
    kTypeBool,
    kTypeInvalid,
} ValueType_t;


class NotArrayTypeException: public std::exception {};
class NotObjectTypeException: public std::exception {};
class OutOfRangeException: public std::exception {};
class ObjectNotFoundException: public std::exception {};


class Value {
public:
    virtual ~Value();
    Value();
    Value(ValueType_t type);
    ValueType_t type() const throw();
    std::string description() const throw();
    std::string dumps() const throw();
    bool loads(std::string str) throw();

    // assignment: null type
    void operator=(const void *null_ptr);
    // assignment: number
    void operator=(signed char num);
    void operator=(unsigned char num);
    void operator=(signed short num);
    void operator=(unsigned short num);
    void operator=(signed int num);
    void operator=(unsigned int num);
    void operator=(signed long num);
    void operator=(unsigned long num);
    void operator=(signed long long num);
    void operator=(unsigned long long num);
    void operator=(float num);
    void operator=(double num);
    // assignment: string
    void operator=(const std::string &str);
    void operator=(const char *c_str);
    // assignment: BOOL
    void operator=(bool flag); 
    // assignment: array or object or other types
    void operator=(const Value &another_value);
    // []
    Value &operator[](int index) throw(OutOfRangeException, NotArrayTypeException);
    Value &operator[](const std::string &key) throw(NotObjectTypeException);
    Value &operator[](const char *c_key) throw(NotObjectTypeException);
    const Value &operator[](int index) const throw(OutOfRangeException, NotArrayTypeException);
    const Value &operator[](const std::string &key) const throw(NotObjectTypeException, ObjectNotFoundException);
    const Value &operator[](const char *c_key) const throw(NotObjectTypeException, ObjectNotFoundException);
    // get element without throwing
    Value &get(int index) throw();
    Value &get(const std::string &key) throw();
    Value &get(const char *c_key) throw();
    const Value &get(int index) const throw();
    const Value &get(const std::string &key) const throw();
    const Value &get(const char *c_key) const throw();
    // get value
    uint64_t unsigned_integer_value() const throw();
    int64_t signed_integer_value() const throw();
    int64_t integer_value() const throw();
    double double_value() const throw();
    const std::string &string_value() const throw();

private:
    ValueType_t     _type;
    uint64_t        _uint64_value;
    int64_t         _int64_value;
    double          _double_value;
    std::string     _string_value;
    std::vector<Value>              _array_value;
    std::map<std::string, Value>    _dict_value;
};


}   // end of namepsace json
}   // end of namepsace cpptools
}   // end of namepsace andrewmc


#endif  // eof
