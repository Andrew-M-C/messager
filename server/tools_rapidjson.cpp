
#include "tools_rapidjson.h"


// ==========
#define __DOM_OPERATIONS
#ifdef __DOM_OPERATIONS

void andrewmc::messager::server::tools::json::init(rapidjson::Document &dom)
{
    dom.SetObject();
    return;
}


void andrewmc::messager::server::tools::json::add_number(rapidjson::Document &dom, const char key[], int64_t number)
{
    if (NULL == key) {
        return;
    }
    rapidjson::Document::AllocatorType& allocator = dom.GetAllocator();

    rapidjson::Value strKey(rapidjson::kStringType);
    strKey.SetString(key, strlen(key), allocator);

    rapidjson::Value numValue(rapidjson::kNumberType);
    numValue.SetInt64(number);

    dom.AddMember(strKey, numValue, allocator);
    return;
}


void andrewmc::messager::server::tools::json::add_number(rapidjson::Document &dom, const char key[], uint64_t number)
{
    if (NULL == key) {
        return;
    }
    rapidjson::Document::AllocatorType& allocator = dom.GetAllocator();

    rapidjson::Value strKey(rapidjson::kStringType);
    strKey.SetString(key, strlen(key), allocator);

    rapidjson::Value numValue(rapidjson::kNumberType);
    numValue.SetUint64(number);

    dom.AddMember(strKey, numValue, allocator);
    return;
}


void andrewmc::messager::server::tools::json::add_number(rapidjson::Document &dom, const char key[], double number)
{
    if (NULL == key) {
        return;
    }
    rapidjson::Document::AllocatorType& allocator = dom.GetAllocator();

    rapidjson::Value strKey(rapidjson::kStringType);
    strKey.SetString(key, strlen(key), allocator);

    rapidjson::Value numValue(rapidjson::kNumberType);
    numValue.SetDouble(number);

    dom.AddMember(strKey, numValue, allocator);
    return;
}


void andrewmc::messager::server::tools::json::add_number(rapidjson::Document &dom, const char key[], int number)
{
    return andrewmc::messager::server::tools::json::add_number(dom, key, (int64_t)number);
}


void andrewmc::messager::server::tools::json::add_string(rapidjson::Document &dom, const char key[], const char *value)
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


void andrewmc::messager::server::tools::json::add_bool(rapidjson::Document &dom, const char key[], BOOL value)
{
    if (!key) {
        return;
    }

    rapidjson::Document::AllocatorType& allocator = dom.GetAllocator();
    rapidjson::Value boolValue(value ? rapidjson::kTrueType : rapidjson::kFalseType);
    rapidjson::Value strKey(rapidjson::kStringType);

    strKey.SetString(key, strlen(key), allocator);
    dom.AddMember(strKey, boolValue, allocator);
    return;
}


std::string andrewmc::messager::server::tools::json::dump(rapidjson::Document &dom)
{
    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    dom.Accept(writer);
    return buffer.GetString();
}


rapidjson::Value &andrewmc::messager::server::tools::json::add_object(rapidjson::Document &dom, const char key[])
{
    if (!key) {
        key = "unknown key";
    }
    rapidjson::Document::AllocatorType& allocator = dom.GetAllocator();
    rapidjson::Value objValue(rapidjson::kObjectType);
    rapidjson::Value strKey(rapidjson::kStringType);

    strKey.SetString(key, strlen(key), allocator);
    dom.AddMember(strKey, objValue, allocator);
    return dom[key];
}


rapidjson::Value &andrewmc::messager::server::tools::json::add_array(rapidjson::Document &dom, const char key[])
{
    if (!key) {
        key = "unknown key";
    }
    rapidjson::Document::AllocatorType& allocator = dom.GetAllocator();
    rapidjson::Value arrayValue(rapidjson::kArrayType);
    rapidjson::Value strKey(rapidjson::kStringType);

    strKey.SetString(key, strlen(key), allocator);
    dom.AddMember(strKey, arrayValue, allocator);
    return dom[key];
}


#endif  // end of __DOM_OPERATIONS


// ==========
#define __VALUE_OPERATIONS
#ifdef __VALUE_OPERATIONS

void andrewmc::messager::server::tools::json::add_number(rapidjson::Value &val, const char key[], double number, rapidjson::Document &dom)
{
    if (!key) {
        return;
    }
    rapidjson::Document::AllocatorType& allocator = dom.GetAllocator();

    rapidjson::Value strKey(rapidjson::kStringType);
    strKey.SetString(key, strlen(key), allocator);

    rapidjson::Value numValue(rapidjson::kNumberType);
    numValue.SetDouble(number);

    val.AddMember(strKey, numValue, allocator);
    return;
}


void andrewmc::messager::server::tools::json::add_number(rapidjson::Value &val, const char key[], uint64_t number, rapidjson::Document &dom)
{
    if (!key) {
        return;
    }
    rapidjson::Document::AllocatorType& allocator = dom.GetAllocator();

    rapidjson::Value strKey(rapidjson::kStringType);
    strKey.SetString(key, strlen(key), allocator);

    rapidjson::Value numValue(rapidjson::kNumberType);
    numValue.SetUint64(number);

    val.AddMember(strKey, numValue, allocator);
    return;
}


void andrewmc::messager::server::tools::json::add_number(rapidjson::Value &val, const char key[], int64_t number, rapidjson::Document &dom)
{
    if (!key) {
        return;
    }
    rapidjson::Document::AllocatorType& allocator = dom.GetAllocator();

    rapidjson::Value strKey(rapidjson::kStringType);
    strKey.SetString(key, strlen(key), allocator);

    rapidjson::Value numValue(rapidjson::kNumberType);
    numValue.SetInt64(number);

    val.AddMember(strKey, numValue, allocator);
    return;
}


void andrewmc::messager::server::tools::json::add_number(rapidjson::Value &val, const char key[], int number, rapidjson::Document &dom)
{
    return andrewmc::messager::server::tools::json::add_number(val, key, (int64_t)number, dom);
}


void andrewmc::messager::server::tools::json::add_string(rapidjson::Value &val, const char key[], const char *value, rapidjson::Document &dom)
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


void andrewmc::messager::server::tools::json::add_bool(rapidjson::Value &val, const char key[], BOOL value, rapidjson::Document &dom)
{
    if (!key) {
        return;
    }
    rapidjson::Document::AllocatorType& allocator = dom.GetAllocator();
    rapidjson::Value boolValue(value ? rapidjson::kTrueType : rapidjson::kFalseType);
    rapidjson::Value strKey(rapidjson::kStringType);

    strKey.SetString(key, strlen(key), allocator);
    val.AddMember(strKey, boolValue, allocator);
    return;
}


#endif  // end of __VALUE_OPERATIONS


// ==========
#define __ARRAY_OPERATIONS
#ifdef __ARRAY_OPERATIONS

void andrewmc::messager::server::tools::json::array_push(rapidjson::Value &array, double number, rapidjson::Document &dom)
{
    rapidjson::Document::AllocatorType& allocator = dom.GetAllocator();
    rapidjson::Value numValue(rapidjson::kNumberType);
    numValue.SetDouble(number);
    array.PushBack(numValue, allocator);
    return;
}


void andrewmc::messager::server::tools::json::array_push(rapidjson::Value &array, uint64_t number, rapidjson::Document &dom)
{
    rapidjson::Document::AllocatorType& allocator = dom.GetAllocator();
    rapidjson::Value numValue(rapidjson::kNumberType);
    numValue.SetUint64(number);
    array.PushBack(numValue, allocator);
    return;
}


void andrewmc::messager::server::tools::json::array_push(rapidjson::Value &array, int64_t number, rapidjson::Document &dom)
{
    rapidjson::Document::AllocatorType& allocator = dom.GetAllocator();
    rapidjson::Value numValue(rapidjson::kNumberType);
    numValue.SetInt64(number);
    array.PushBack(numValue, allocator);
    return;
}


void andrewmc::messager::server::tools::json::array_push(rapidjson::Value &array, int number, rapidjson::Document &dom)
{
    return andrewmc::messager::server::tools::json::array_push(array, (int64_t)number, dom);
}


void andrewmc::messager::server::tools::json::array_push(rapidjson::Value &array, const char str[], rapidjson::Document &dom)
{
    if (!str) {
        return;
    }
    rapidjson::Document::AllocatorType& allocator = dom.GetAllocator();
    rapidjson::Value strValue(rapidjson::kStringType);
    strValue.SetString(str, strlen(str), allocator);
    array.PushBack(strValue, allocator);
    return;
}


#endif  // end of __ARRAY_OPERATIONS


// ==========
#define __ADD_ARRAR_OR_OBJ_IN_OBJ
#ifdef __ADD_ARRAR_OR_OBJ_IN_OBJ

rapidjson::Value &andrewmc::messager::server::tools::json::add_object(rapidjson::Value &val, const char key[], rapidjson::Document &dom)
{
    if (!key) {
        key = "unknown key";
    }
    rapidjson::Document::AllocatorType& allocator = dom.GetAllocator();
    rapidjson::Value objValue(rapidjson::kObjectType);
    rapidjson::Value strKey(rapidjson::kStringType);

    strKey.SetString(key, strlen(key), allocator);
    val.AddMember(strKey, objValue, allocator);
    return val[key];
}


rapidjson::Value &andrewmc::messager::server::tools::json::add_array(rapidjson::Value &val, const char key[], rapidjson::Document &dom)
{
    if (!key) {
        key = "unknown key";
    }
    rapidjson::Document::AllocatorType& allocator = dom.GetAllocator();
    rapidjson::Value arrayValue(rapidjson::kArrayType);
    rapidjson::Value strKey(rapidjson::kStringType);

    strKey.SetString(key, strlen(key), allocator);
    val.AddMember(strKey, arrayValue, allocator);
    return val[key];
}


#endif  // end of __ADD_ARRAR_OR_OBJ_IN_OBJ
