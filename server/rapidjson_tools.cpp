
#include "rapidjson_tools.h"

void andrewmc::messager::server::tools::json_init(rapidjson::Document &dom)
{
    dom.SetObject();
    return;
}


void andrewmc::messager::server::tools::json_add_uint32(rapidjson::Document &dom, const char key[], uint32_t number)
{
    if (NULL == key) {
        return;
    }
    rapidjson::Document::AllocatorType& allocator = dom.GetAllocator();

    rapidjson::Value strKey(rapidjson::kStringType);
    strKey.SetString(key, strlen(key), allocator);

    rapidjson::Value numValue(rapidjson::kNumberType);
    numValue.SetUint(number);

    dom.AddMember(strKey, numValue, allocator);
    return;
}


void andrewmc::messager::server::tools::json_add_uint64(rapidjson::Document &dom, const char key[], uint64_t number)
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


void andrewmc::messager::server::tools::json_add_double(rapidjson::Document &dom, const char key[], double number)
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


void andrewmc::messager::server::tools::json_add_string(rapidjson::Document &dom, const char key[], const char *value)
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


std::string andrewmc::messager::server::tools::json_dump(rapidjson::Document &dom)
{
    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    dom.Accept(writer);
    return buffer.GetString();
}

