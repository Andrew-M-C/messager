
#include "cpptools_json.h"

#include <string>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include <rapidjson/writer.h>
#include <rapidjson/stringbuffer.h>

using namespace andrewmc::cpptools::json;

#define _DEBUG(fmt, args...)    printf("## " __FILE__ ", %d: " fmt "\n", __LINE__, ##args)
rapidjson::Document andrewmc::cpptools::json::kDomForAllocator;

// ==========
#define __DOCUMENT_FUNCTIONS
#ifdef __DOCUMENT_FUNCTIONS

std::string andrewmc::cpptools::json::dump(rapidjson::Document &dom)
{
    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    dom.Accept(writer);
    return buffer.GetString();
}


#endif  // end of __DOCUMENT_FUNCTIONS


// ==========
#define __ADD_NUMBER_FUNCTIONS
#ifdef __ADD_NUMBER_FUNCTIONS

void andrewmc::cpptools::json::add_number(rapidjson::Value &val, const char *key, signed char number, rapidjson::Document &dom)
{
    if ((NULL == key) || '\0' == *key) {
        return;
    }
    rapidjson::Value strKey(rapidjson::kStringType);
    strKey.SetString(key, strlen(key), dom.GetAllocator());

    rapidjson::Value numValue(rapidjson::kNumberType);
    numValue.SetInt(number);

    val.AddMember(strKey, numValue, dom.GetAllocator());
}


void andrewmc::cpptools::json::add_number(rapidjson::Value &val, const char *key, unsigned char number, rapidjson::Document &dom)
{
    if ((NULL == key) || '\0' == *key) {
        return;
    }
    rapidjson::Value strKey(rapidjson::kStringType);
    strKey.SetString(key, strlen(key), dom.GetAllocator());

    rapidjson::Value numValue(rapidjson::kNumberType);
    numValue.SetUint(number);

    val.AddMember(strKey, numValue, dom.GetAllocator());
}


void andrewmc::cpptools::json::add_number(rapidjson::Value &val, const char *key, signed short number, rapidjson::Document &dom)
{
    if ((NULL == key) || '\0' == *key) {
        return;
    }
    rapidjson::Value strKey(rapidjson::kStringType);
    strKey.SetString(key, strlen(key), dom.GetAllocator());

    rapidjson::Value numValue(rapidjson::kNumberType);
    numValue.SetInt(number);

    val.AddMember(strKey, numValue, dom.GetAllocator());
}


void andrewmc::cpptools::json::add_number(rapidjson::Value &val, const char *key, unsigned short number, rapidjson::Document &dom)
{
    if ((NULL == key) || '\0' == *key) {
        return;
    }
    rapidjson::Value strKey(rapidjson::kStringType);
    strKey.SetString(key, strlen(key), dom.GetAllocator());

    rapidjson::Value numValue(rapidjson::kNumberType);
    numValue.SetUint(number);

    val.AddMember(strKey, numValue, dom.GetAllocator());
}


void andrewmc::cpptools::json::add_number(rapidjson::Value &val, const char *key, signed int number, rapidjson::Document &dom)
{
    if ((NULL == key) || '\0' == *key) {
        return;
    }
    rapidjson::Value strKey(rapidjson::kStringType);
    strKey.SetString(key, strlen(key), dom.GetAllocator());

    rapidjson::Value numValue(rapidjson::kNumberType);
    numValue.SetInt(number);

    val.AddMember(strKey, numValue, dom.GetAllocator());
}


void andrewmc::cpptools::json::add_number(rapidjson::Value &val, const char *key, unsigned int number, rapidjson::Document &dom)
{
    if ((NULL == key) || '\0' == *key) {
        return;
    }
    rapidjson::Value strKey(rapidjson::kStringType);
    strKey.SetString(key, strlen(key), dom.GetAllocator());

    rapidjson::Value numValue(rapidjson::kNumberType);
    numValue.SetUint(number);

    val.AddMember(strKey, numValue, dom.GetAllocator());
}


void andrewmc::cpptools::json::add_number(rapidjson::Value &val, const char *key, signed long number, rapidjson::Document &dom)
{
    if ((NULL == key) || '\0' == *key) {
        return;
    }
    rapidjson::Value strKey(rapidjson::kStringType);
    strKey.SetString(key, strlen(key), dom.GetAllocator());

    rapidjson::Value numValue(rapidjson::kNumberType);
    numValue.SetInt64(number);

    val.AddMember(strKey, numValue, dom.GetAllocator());
}


void andrewmc::cpptools::json::add_number(rapidjson::Value &val, const char *key, unsigned long number, rapidjson::Document &dom)
{
    if ((NULL == key) || '\0' == *key) {
        return;
    }
    rapidjson::Value strKey(rapidjson::kStringType);
    strKey.SetString(key, strlen(key), dom.GetAllocator());

    rapidjson::Value numValue(rapidjson::kNumberType);
    numValue.SetUint64(number);

    val.AddMember(strKey, numValue, dom.GetAllocator());
}


void andrewmc::cpptools::json::add_number(rapidjson::Value &val, const char *key, signed long long number, rapidjson::Document &dom)
{
    if ((NULL == key) || '\0' == *key) {
        return;
    }
    rapidjson::Value strKey(rapidjson::kStringType);
    strKey.SetString(key, strlen(key), dom.GetAllocator());

    rapidjson::Value numValue(rapidjson::kNumberType);
    numValue.SetInt64(number);

    val.AddMember(strKey, numValue, dom.GetAllocator());
}


void andrewmc::cpptools::json::add_number(rapidjson::Value &val, const char *key, unsigned long long number, rapidjson::Document &dom)
{
    if ((NULL == key) || '\0' == *key) {
        return;
    }
    rapidjson::Value strKey(rapidjson::kStringType);
    strKey.SetString(key, strlen(key), dom.GetAllocator());

    rapidjson::Value numValue(rapidjson::kNumberType);
    numValue.SetUint64(number);

    val.AddMember(strKey, numValue, dom.GetAllocator());
}


void andrewmc::cpptools::json::add_number(rapidjson::Value &val, const char *key, float number, rapidjson::Document &dom)
{
    if ((NULL == key) || '\0' == *key) {
        return;
    }
    rapidjson::Value strKey(rapidjson::kStringType);
    strKey.SetString(key, strlen(key), dom.GetAllocator());

    rapidjson::Value numValue(rapidjson::kNumberType);
    numValue.SetDouble(number);

    val.AddMember(strKey, numValue, dom.GetAllocator());
}


void andrewmc::cpptools::json::add_number(rapidjson::Value &val, const char *key, double number, rapidjson::Document &dom)
{
    if ((NULL == key) || '\0' == *key) {
        return;
    }
    rapidjson::Value strKey(rapidjson::kStringType);
    strKey.SetString(key, strlen(key), dom.GetAllocator());

    rapidjson::Value numValue(rapidjson::kNumberType);
    numValue.SetDouble(number);

    val.AddMember(strKey, numValue, dom.GetAllocator());
}


void andrewmc::cpptools::json::add_number(rapidjson::Document &dom, const char *key, signed char number)
{
    if ((NULL == key) || '\0' == *key) {
        return;
    }
    rapidjson::Value strKey(rapidjson::kStringType);
    strKey.SetString(key, strlen(key), dom.GetAllocator());

    rapidjson::Value numValue(rapidjson::kNumberType);
    numValue.SetInt(number);

    dom.AddMember(strKey, numValue, dom.GetAllocator());
}


void andrewmc::cpptools::json::add_number(rapidjson::Document &dom, const char *key, unsigned char number)
{
    if ((NULL == key) || '\0' == *key) {
        return;
    }
    rapidjson::Value strKey(rapidjson::kStringType);
    strKey.SetString(key, strlen(key), dom.GetAllocator());

    rapidjson::Value numValue(rapidjson::kNumberType);
    numValue.SetUint(number);

    dom.AddMember(strKey, numValue, dom.GetAllocator());
}


void andrewmc::cpptools::json::add_number(rapidjson::Document &dom, const char *key, signed short number)
{
    if ((NULL == key) || '\0' == *key) {
        return;
    }
    rapidjson::Value strKey(rapidjson::kStringType);
    strKey.SetString(key, strlen(key), dom.GetAllocator());

    rapidjson::Value numValue(rapidjson::kNumberType);
    numValue.SetInt(number);

    dom.AddMember(strKey, numValue, dom.GetAllocator());
}


void andrewmc::cpptools::json::add_number(rapidjson::Document &dom, const char *key, unsigned short number)
{
    if ((NULL == key) || '\0' == *key) {
        return;
    }
    rapidjson::Value strKey(rapidjson::kStringType);
    strKey.SetString(key, strlen(key), dom.GetAllocator());

    rapidjson::Value numValue(rapidjson::kNumberType);
    numValue.SetUint(number);

    dom.AddMember(strKey, numValue, dom.GetAllocator());
}


void andrewmc::cpptools::json::add_number(rapidjson::Document &dom, const char *key, signed int number)
{
    if ((NULL == key) || '\0' == *key) {
        return;
    }
    rapidjson::Value strKey(rapidjson::kStringType);
    strKey.SetString(key, strlen(key), dom.GetAllocator());

    rapidjson::Value numValue(rapidjson::kNumberType);
    numValue.SetInt(number);

    dom.AddMember(strKey, numValue, dom.GetAllocator());
}


void andrewmc::cpptools::json::add_number(rapidjson::Document &dom, const char *key, unsigned int number)
{
    if ((NULL == key) || '\0' == *key) {
        return;
    }
    rapidjson::Value strKey(rapidjson::kStringType);
    strKey.SetString(key, strlen(key), dom.GetAllocator());

    rapidjson::Value numValue(rapidjson::kNumberType);
    numValue.SetUint(number);

    dom.AddMember(strKey, numValue, dom.GetAllocator());
}


void andrewmc::cpptools::json::add_number(rapidjson::Document &dom, const char *key, signed long number)
{
    if ((NULL == key) || '\0' == *key) {
        return;
    }
    rapidjson::Value strKey(rapidjson::kStringType);
    strKey.SetString(key, strlen(key), dom.GetAllocator());

    rapidjson::Value numValue(rapidjson::kNumberType);
    numValue.SetInt(number);

    dom.AddMember(strKey, numValue, dom.GetAllocator());
}


void andrewmc::cpptools::json::add_number(rapidjson::Document &dom, const char *key, unsigned long number)
{
    if ((NULL == key) || '\0' == *key) {
        return;
    }
    rapidjson::Value strKey(rapidjson::kStringType);
    strKey.SetString(key, strlen(key), dom.GetAllocator());

    rapidjson::Value numValue(rapidjson::kNumberType);
    numValue.SetUint(number);

    dom.AddMember(strKey, numValue, dom.GetAllocator());
}


void andrewmc::cpptools::json::add_number(rapidjson::Document &dom, const char *key, signed long long number)
{
    if ((NULL == key) || '\0' == *key) {
        return;
    }
    rapidjson::Value strKey(rapidjson::kStringType);
    strKey.SetString(key, strlen(key), dom.GetAllocator());

    rapidjson::Value numValue(rapidjson::kNumberType);
    numValue.SetInt(number);

    dom.AddMember(strKey, numValue, dom.GetAllocator());
}


void andrewmc::cpptools::json::add_number(rapidjson::Document &dom, const char *key, unsigned long long number)
{
    if ((NULL == key) || '\0' == *key) {
        return;
    }
    rapidjson::Value strKey(rapidjson::kStringType);
    strKey.SetString(key, strlen(key), dom.GetAllocator());

    rapidjson::Value numValue(rapidjson::kNumberType);
    numValue.SetUint(number);

    dom.AddMember(strKey, numValue, dom.GetAllocator());
}


void andrewmc::cpptools::json::add_number(rapidjson::Document &dom, const char *key, float number)
{
    if ((NULL == key) || '\0' == *key) {
        return;
    }
    rapidjson::Value strKey(rapidjson::kStringType);
    strKey.SetString(key, strlen(key), dom.GetAllocator());

    rapidjson::Value numValue(rapidjson::kNumberType);
    numValue.SetDouble(number);

    dom.AddMember(strKey, numValue, dom.GetAllocator());
}


void andrewmc::cpptools::json::add_number(rapidjson::Document &dom, const char *key, double number)
{
    if ((NULL == key) || '\0' == *key) {
        return;
    }
    rapidjson::Value strKey(rapidjson::kStringType);
    strKey.SetString(key, strlen(key), dom.GetAllocator());

    rapidjson::Value numValue(rapidjson::kNumberType);
    numValue.SetDouble(number);

    dom.AddMember(strKey, numValue, dom.GetAllocator());
}

#endif  // end of __ADD_NUMBER_FUNCTIONS


// ==========
#define __ADD_BOOL_FUNCTIONS
#ifdef __ADD_BOOL_FUNCTIONS

void andrewmc::cpptools::json::add_bool(rapidjson::Value &val, const char *key, bool flag, rapidjson::Document &dom)
{
    if ((NULL == key) || '\0' == *key) {
        return;
    }
    rapidjson::Value strKey(rapidjson::kStringType);
    strKey.SetString(key, strlen(key), dom.GetAllocator());

    rapidjson::Value numValue(flag ? rapidjson::kTrueType : rapidjson::kFalseType);
    numValue.SetBool(flag);

    val.AddMember(strKey, numValue, dom.GetAllocator());
}


void andrewmc::cpptools::json::add_bool(rapidjson::Document &dom, const char *key, bool flag)
{
    if ((NULL == key) || '\0' == *key) {
        return;
    }
    rapidjson::Value strKey(rapidjson::kStringType);
    strKey.SetString(key, strlen(key), dom.GetAllocator());

    rapidjson::Value numValue(flag ? rapidjson::kTrueType : rapidjson::kFalseType);
    numValue.SetBool(flag);

    dom.AddMember(strKey, numValue, dom.GetAllocator());
}


#endif  // end of __ADD_BOOL_FUNCTIONS


// ==========
#define __ADD_STRING_FUNCTIONS
#ifdef __ADD_STRING_FUNCTIONS

void andrewmc::cpptools::json::add_string(rapidjson::Value &val, const char *key, const char *value, rapidjson::Document &dom)
{
    if (!(key && value)) {
        return;
    }
    rapidjson::Document::AllocatorType& allocator = dom.GetAllocator();
    rapidjson::Value strValue(rapidjson::kStringType);
    rapidjson::Value strKey(rapidjson::kStringType);

    strKey.SetString(key, strlen(key), allocator);
    strValue.SetString(value, strlen(value), allocator);
    val.AddMember(strKey, strValue, allocator);
    return;
}


void andrewmc::cpptools::json::add_string(rapidjson::Value &val, const char *key, const std::string &value, rapidjson::Document &dom)
{
    if (NULL == key) {
        return;
    }
    rapidjson::Document::AllocatorType& allocator = dom.GetAllocator();
    rapidjson::Value strValue(rapidjson::kStringType);
    rapidjson::Value strKey(rapidjson::kStringType);

    strKey.SetString(key, strlen(key), allocator);
    strValue.SetString(value.c_str(), value.length(), allocator);
    val.AddMember(strKey, strValue, allocator);
    return;
}


void andrewmc::cpptools::json::add_string(rapidjson::Document &dom, const char *key, const char *value)
{
    if (!(key && value)) {
        return;
    }
    rapidjson::Document::AllocatorType& allocator = dom.GetAllocator();
    rapidjson::Value strValue(rapidjson::kStringType);
    rapidjson::Value strKey(rapidjson::kStringType);

    strKey.SetString(key, strlen(key), allocator);
    strValue.SetString(value, strlen(value), allocator);
    dom.AddMember(strKey, strValue, allocator);
    return;
}


void andrewmc::cpptools::json::add_string(rapidjson::Document &dom, const char *key, const std::string &value)
{
    if (NULL == key) {
        return;
    }
    rapidjson::Document::AllocatorType& allocator = dom.GetAllocator();
    rapidjson::Value strValue(rapidjson::kStringType);
    rapidjson::Value strKey(rapidjson::kStringType);

    strKey.SetString(key, strlen(key), allocator);
    strValue.SetString(value.c_str(), value.length(), allocator);
    dom.AddMember(strKey, strValue, allocator);
    return;
}

#endif


// ==========
#define __ADD_OBJECT_FUNCTIONS
#ifdef __ADD_OBJECT_FUNCTIONS

rapidjson::Value &andrewmc::cpptools::json::add_object(rapidjson::Value &val, const char *key, rapidjson::Document &dom)
{
    if (NULL == key) {
        key = "";
    }
    rapidjson::Document::AllocatorType& allocator = dom.GetAllocator();
    rapidjson::Value objValue(rapidjson::kObjectType);
    rapidjson::Value strKey(rapidjson::kStringType);

    strKey.SetString(key, strlen(key), allocator);
    val.AddMember(strKey, objValue, allocator);
    return val[key];
}


rapidjson::Value &andrewmc::cpptools::json::add_object(rapidjson::Document &dom, const char *key)
{
    if (NULL == key) {
        key = "";
    }
    rapidjson::Document::AllocatorType& allocator = dom.GetAllocator();
    rapidjson::Value objValue(rapidjson::kObjectType);
    rapidjson::Value strKey(rapidjson::kStringType);

    strKey.SetString(key, strlen(key), allocator);
    dom.AddMember(strKey, objValue, allocator);
    return dom[key];
}

#endif  // end of __ADD_OBJECT_FUNCTIONS


// ==========
#define __ADD_ARRAY_FUNCTIONS
#ifdef __ADD_ARRAY_FUNCTIONS

rapidjson::Value &andrewmc::cpptools::json::add_array(rapidjson::Value &val, const char *key, rapidjson::Document &dom)
{
    if (NULL == key) {
        key = "";
    }
    rapidjson::Document::AllocatorType& allocator = dom.GetAllocator();
    rapidjson::Value arrayValue(rapidjson::kArrayType);
    rapidjson::Value strKey(rapidjson::kStringType);

    strKey.SetString(key, strlen(key), allocator);
    val.AddMember(strKey, arrayValue, allocator);
    return val[key];
}


rapidjson::Value &andrewmc::cpptools::json::add_array(rapidjson::Document &dom, const char *key)
{
    if (NULL == key) {
        key = "";
    }
    rapidjson::Document::AllocatorType& allocator = dom.GetAllocator();
    rapidjson::Value arrayValue(rapidjson::kArrayType);
    rapidjson::Value strKey(rapidjson::kStringType);

    strKey.SetString(key, strlen(key), allocator);
    dom.AddMember(strKey, arrayValue, allocator);
    return dom[key];
}

#endif  // end of __ADD_ARRAY_FUNCTIONS


// ==========
#define __VALUE_APPEND_FUNCTIONS
#ifdef __VALUE_APPEND_FUNCTIONS

void andrewmc::cpptools::json::append(rapidjson::Value &array, rapidjson::Value &val_to_append, rapidjson::Document &dom)
{
    array.PushBack(val_to_append, dom.GetAllocator());
    return;
}


void andrewmc::cpptools::json::append_number(rapidjson::Value &array, signed char number, rapidjson::Document &dom)
{
    rapidjson::Value numValue(rapidjson::kNumberType);
    numValue.SetInt(number);
    array.PushBack(numValue, dom.GetAllocator());
    return;
}


void andrewmc::cpptools::json::append_number(rapidjson::Value &array, unsigned char number, rapidjson::Document &dom)
{
    rapidjson::Value numValue(rapidjson::kNumberType);
    numValue.SetUint(number);
    array.PushBack(numValue, dom.GetAllocator());
    return;
}


void andrewmc::cpptools::json::append_number(rapidjson::Value &array, signed short number, rapidjson::Document &dom)
{
    rapidjson::Value numValue(rapidjson::kNumberType);
    numValue.SetInt(number);
    array.PushBack(numValue, dom.GetAllocator());
    return;
}


void andrewmc::cpptools::json::append_number(rapidjson::Value &array, unsigned short number, rapidjson::Document &dom)
{
    rapidjson::Value numValue(rapidjson::kNumberType);
    numValue.SetUint(number);
    array.PushBack(numValue, dom.GetAllocator());
    return;
}


void andrewmc::cpptools::json::append_number(rapidjson::Value &array, signed int number, rapidjson::Document &dom)
{
    rapidjson::Value numValue(rapidjson::kNumberType);
    numValue.SetInt(number);
    array.PushBack(numValue, dom.GetAllocator());
    return;
}


void andrewmc::cpptools::json::append_number(rapidjson::Value &array, unsigned int number, rapidjson::Document &dom)
{
    rapidjson::Value numValue(rapidjson::kNumberType);
    numValue.SetUint(number);
    array.PushBack(numValue, dom.GetAllocator());
    return;
}


void andrewmc::cpptools::json::append_number(rapidjson::Value &array, signed long number, rapidjson::Document &dom)
{
    rapidjson::Value numValue(rapidjson::kNumberType);
    numValue.SetInt64(number);
    array.PushBack(numValue, dom.GetAllocator());
    return;
}


void andrewmc::cpptools::json::append_number(rapidjson::Value &array, unsigned long number, rapidjson::Document &dom)
{
    rapidjson::Value numValue(rapidjson::kNumberType);
    numValue.SetUint64(number);
    array.PushBack(numValue, dom.GetAllocator());
    return;
}


void andrewmc::cpptools::json::append_number(rapidjson::Value &array, signed long long number, rapidjson::Document &dom)
{
    rapidjson::Value numValue(rapidjson::kNumberType);
    numValue.SetInt64(number);
    array.PushBack(numValue, dom.GetAllocator());
    return;
}


void andrewmc::cpptools::json::append_number(rapidjson::Value &array, unsigned long long number, rapidjson::Document &dom)
{
    rapidjson::Value numValue(rapidjson::kNumberType);
    numValue.SetUint64(number);
    array.PushBack(numValue, dom.GetAllocator());
    return;
}


void andrewmc::cpptools::json::append_number(rapidjson::Value &array, float number, rapidjson::Document &dom)
{
    rapidjson::Value numValue(rapidjson::kNumberType);
    numValue.SetDouble(number);
    array.PushBack(numValue, dom.GetAllocator());
    return;
}


void andrewmc::cpptools::json::append_number(rapidjson::Value &array, double number, rapidjson::Document &dom)
{
    rapidjson::Value numValue(rapidjson::kNumberType);
    numValue.SetDouble(number);
    array.PushBack(numValue, dom.GetAllocator());
    return;
}


void andrewmc::cpptools::json::append_bool(rapidjson::Value &array, bool flag, rapidjson::Document &dom)
{
    rapidjson::Value boolValue(flag ? rapidjson::kTrueType : rapidjson::kFalseType);
    array.PushBack(boolValue, dom.GetAllocator());
    return;
}


void andrewmc::cpptools::json::append_string(rapidjson::Value &array, const char *str, rapidjson::Document &dom)
{
    if (NULL == str) {
        str = "";
    }
    rapidjson::Value strValue(rapidjson::kStringType);
    strValue.SetString(str, strlen(str), dom.GetAllocator());
    array.PushBack(strValue, dom.GetAllocator());
    return;
}


void andrewmc::cpptools::json::append_string(rapidjson::Value &array, const std::string &str, rapidjson::Document &dom)
{
    rapidjson::Value strValue(rapidjson::kStringType);
    strValue.SetString(str.c_str(), str.length(), dom.GetAllocator());
    array.PushBack(strValue, dom.GetAllocator());
    return;
}

#endif  // end of __VALUE_APPEND_FUNCTIONS


// ==========
#define __DOM_APPEND_FUNCTIONS
#ifdef __DOM_APPEND_FUNCTIONS

void andrewmc::cpptools::json::append(rapidjson::Document &dom_array, rapidjson::Value &val_to_append)
{
    dom_array.PushBack(val_to_append, dom_array.GetAllocator());
    return;
}


void andrewmc::cpptools::json::append_number(rapidjson::Document &dom_array, signed char number)
{
    rapidjson::Value numValue(rapidjson::kNumberType);
    numValue.SetInt(number);
    dom_array.PushBack(numValue, dom_array.GetAllocator());
    return;
}


void andrewmc::cpptools::json::append_number(rapidjson::Document &dom_array, unsigned char number)
{
    rapidjson::Value numValue(rapidjson::kNumberType);
    numValue.SetUint(number);
    dom_array.PushBack(numValue, dom_array.GetAllocator());
    return;
}


void andrewmc::cpptools::json::append_number(rapidjson::Document &dom_array, signed short number)
{
    rapidjson::Value numValue(rapidjson::kNumberType);
    numValue.SetInt(number);
    dom_array.PushBack(numValue, dom_array.GetAllocator());
    return;
}


void andrewmc::cpptools::json::append_number(rapidjson::Document &dom_array, unsigned short number)
{
    rapidjson::Value numValue(rapidjson::kNumberType);
    numValue.SetUint(number);
    dom_array.PushBack(numValue, dom_array.GetAllocator());
    return;
}


void andrewmc::cpptools::json::append_number(rapidjson::Document &dom_array, signed int number)
{
    rapidjson::Value numValue(rapidjson::kNumberType);
    numValue.SetInt(number);
    dom_array.PushBack(numValue, dom_array.GetAllocator());
    return;
}


void andrewmc::cpptools::json::append_number(rapidjson::Document &dom_array, unsigned int number)
{
    rapidjson::Value numValue(rapidjson::kNumberType);
    numValue.SetUint(number);
    dom_array.PushBack(numValue, dom_array.GetAllocator());
    return;
}


void andrewmc::cpptools::json::append_number(rapidjson::Document &dom_array, signed long number)
{
    rapidjson::Value numValue(rapidjson::kNumberType);
    numValue.SetInt64(number);
    dom_array.PushBack(numValue, dom_array.GetAllocator());
    return;
}


void andrewmc::cpptools::json::append_number(rapidjson::Document &dom_array, unsigned long number)
{
    rapidjson::Value numValue(rapidjson::kNumberType);
    numValue.SetUint64(number);
    dom_array.PushBack(numValue, dom_array.GetAllocator());
    return;
}


void andrewmc::cpptools::json::append_number(rapidjson::Document &dom_array, signed long long number)
{
    rapidjson::Value numValue(rapidjson::kNumberType);
    numValue.SetInt64(number);
    dom_array.PushBack(numValue, dom_array.GetAllocator());
    return;
}


void andrewmc::cpptools::json::append_number(rapidjson::Document &dom_array, unsigned long long number)
{
    rapidjson::Value numValue(rapidjson::kNumberType);
    numValue.SetUint64(number);
    dom_array.PushBack(numValue, dom_array.GetAllocator());
    return;
}


void andrewmc::cpptools::json::append_number(rapidjson::Document &dom_array, float number)
{
    rapidjson::Value numValue(rapidjson::kNumberType);
    numValue.SetDouble(number);
    dom_array.PushBack(numValue, dom_array.GetAllocator());
    return;
}


void andrewmc::cpptools::json::append_number(rapidjson::Document &dom_array, double number)
{
    rapidjson::Value numValue(rapidjson::kNumberType);
    numValue.SetDouble(number);
    dom_array.PushBack(numValue, dom_array.GetAllocator());
    return;
}


void andrewmc::cpptools::json::append_bool(rapidjson::Document &dom_array, bool flag)
{
    rapidjson::Value boolValue(flag ? rapidjson::kTrueType : rapidjson::kFalseType);
    dom_array.PushBack(boolValue, dom_array.GetAllocator());
    return;
}


void andrewmc::cpptools::json::append_string(rapidjson::Document &dom_array, const char *str)
{
    if (NULL == str) {
        str = "";
    }
    rapidjson::Value strValue(rapidjson::kStringType);
    strValue.SetString(str, strlen(str), dom_array.GetAllocator());
    dom_array.PushBack(strValue, dom_array.GetAllocator());
    return;
}


void andrewmc::cpptools::json::append_string(rapidjson::Document &dom_array, const std::string &str)
{
    rapidjson::Value strValue(rapidjson::kStringType);
    strValue.SetString(str.c_str(), str.length(), dom_array.GetAllocator());
    dom_array.PushBack(strValue, dom_array.GetAllocator());
    return;
}

#endif  // end of __DOM_APPEND_FUNCTIONS
