
#include <string>
#include <stdio.h>
#include <syslog.h>
#include <stdint.h>

#include <rapidjson/rapidjson.h>
#include <rapidjson/document.h>
#include <rapidjson/writer.h>
#include <rapidjson/stringbuffer.h>

namespace andrewmc {
namespace messager {
namespace server {
namespace tools {

// ==========
// RapidJSON
void json_init(rapidjson::Document &dom);
void json_add_uint32(rapidjson::Document &dom, const char key[], uint32_t number);
void json_add_uint64(rapidjson::Document &dom, const char key[], uint64_t number);
void json_add_double(rapidjson::Document &dom, const char key[], double number);
void json_add_string(rapidjson::Document &dom, const char key[], const char *value);
std::string json_dump(rapidjson::Document &dom);

}}}}
