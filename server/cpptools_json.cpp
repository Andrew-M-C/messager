
#include "cpptools_json.h"

#include <string>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

using namespace andrewmc::cpptools::json;

#define _DEBUG(fmt, args...)    printf("## " __FILE__ ", %d: " fmt "\n", __LINE__, ##args)

static int g_object_count = 0;
static const uint32_t g_null_storage = 0;
const void *andrewmc::cpptools::json::JSON_NULL = (void *)(&g_null_storage);
const Value g_not_a_value = Value(kTypeInvalid);

// ==========
#define __CONSTRUCT_AND_DESTRUCT
#ifdef __CONSTRUCT_AND_DESTRUCT

andrewmc::cpptools::json::Value::~Value()
{
    _DEBUG("%s deleted, %d object(s) remain", this->description().c_str(), --g_object_count);
    return;
}


andrewmc::cpptools::json::Value::Value()
{
    _type = kTypeUnknown;
    _uint64_value = 0;
    _int64_value = 0;
    _double_value = 0.0;
    return;
}


andrewmc::cpptools::json::Value::Value(ValueType_t type)
{
    _type = type > kTypeInvalid ? kTypeInvalid : type;
    _uint64_value = 0;
    _int64_value = 0;
    _double_value = 0.0;
    return;
}


ValueType_t andrewmc::cpptools::json::Value::type() const throw()
{
    return _type;
}


std::string andrewmc::cpptools::json::Value::description() const throw()
{
    const char *type_str[] = {
        "unknown",
        "null",
        "number",
        "string",
        "object",
        "array",
        "bool",
        "invalid"
    };

    char buff[128];
    snprintf(buff, sizeof(buff), "JSON value, type %s, ID 0x%p", type_str[(int)_type], this);
    return std::string(buff);
}

#endif  // end of __CONSTRUCT_AND_DESTRUCT
