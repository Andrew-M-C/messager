
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
std::string json_dump(rapidjson::Document &dom);
void json_add_number(rapidjson::Document &dom, const char key[], int64_t number);
void json_add_number(rapidjson::Document &dom, const char key[], uint64_t number);
void json_add_number(rapidjson::Document &dom, const char key[], double number);
void json_add_number(rapidjson::Document &dom, const char key[], int number);
void json_add_string(rapidjson::Document &dom, const char key[], const char *value);
rapidjson::Value &json_add_object(rapidjson::Document &dom, const char key[]);
rapidjson::Value &json_add_array(rapidjson::Document &dom, const char key[]);

void json_add_number(rapidjson::Value &val, const char key[], double number, rapidjson::Document &dom);
void json_add_number(rapidjson::Value &val, const char key[], uint64_t number, rapidjson::Document &dom);
void json_add_number(rapidjson::Value &val, const char key[], int64_t number, rapidjson::Document &dom);
void json_add_number(rapidjson::Value &val, const char key[], int number, rapidjson::Document &dom);
void json_add_string(rapidjson::Value &val, const char key[], const char *value, rapidjson::Document &dom);

void json_array_push(rapidjson::Value &array, double number, rapidjson::Document &dom);
void json_array_push(rapidjson::Value &array, uint64_t number, rapidjson::Document &dom);
void json_array_push(rapidjson::Value &array, int64_t number, rapidjson::Document &dom);
void json_array_push(rapidjson::Value &array, int number, rapidjson::Document &dom);
void json_array_push(rapidjson::Value &array, const char string[], rapidjson::Document &dom);

rapidjson::Value &json_add_object(rapidjson::Value &val, const char key[], rapidjson::Document &dom);
rapidjson::Value &json_add_array(rapidjson::Value &val, const char key[], rapidjson::Document &dom);

}}}}
