
#include "tools_rapidjson.h"
#include "coevent.h"
#include <map>

namespace andrewmc {
namespace messager {
namespace server {
namespace cgi {

// ==========
// test
namespace test {
void process(andrewmc::libcoevent::TCPServer *server, std::map<std::string, std::string> &session_para, std::map<std::string, std::string> &req_para, rapidjson::Document &resp, andrewmc::cpptools::Data &post_data);
}

}}}}
