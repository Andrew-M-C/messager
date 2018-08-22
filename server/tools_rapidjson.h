
#include "coevent.h"

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
namespace json {

// ==========
// RapidJSON
void init(rapidjson::Document &dom);
std::string dump(rapidjson::Document &dom);
void add_number(rapidjson::Document &dom, const char key[], int64_t number);
void add_number(rapidjson::Document &dom, const char key[], uint64_t number);
void add_number(rapidjson::Document &dom, const char key[], double number);
void add_number(rapidjson::Document &dom, const char key[], int number);
void add_string(rapidjson::Document &dom, const char key[], const char *value);
void add_bool(rapidjson::Document &dom, const char key[], BOOL value);
rapidjson::Value &add_object(rapidjson::Document &dom, const char key[]);
rapidjson::Value &add_array(rapidjson::Document &dom, const char key[]);

void add_number(rapidjson::Value &val, const char key[], double number, rapidjson::Document &dom);
void add_number(rapidjson::Value &val, const char key[], uint64_t number, rapidjson::Document &dom);
void add_number(rapidjson::Value &val, const char key[], int64_t number, rapidjson::Document &dom);
void add_number(rapidjson::Value &val, const char key[], int number, rapidjson::Document &dom);
void add_string(rapidjson::Value &val, const char key[], const char *value, rapidjson::Document &dom);
void add_bool(rapidjson::Value &val, const char key[], BOOL value, rapidjson::Document &dom);

void array_push(rapidjson::Value &array, double number, rapidjson::Document &dom);
void array_push(rapidjson::Value &array, uint64_t number, rapidjson::Document &dom);
void array_push(rapidjson::Value &array, int64_t number, rapidjson::Document &dom);
void array_push(rapidjson::Value &array, int number, rapidjson::Document &dom);
void array_push(rapidjson::Value &array, const char string[], rapidjson::Document &dom);

rapidjson::Value &add_object(rapidjson::Value &val, const char key[], rapidjson::Document &dom);
rapidjson::Value &add_array(rapidjson::Value &val, const char key[], rapidjson::Document &dom);

}}}}}
