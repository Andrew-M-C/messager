
#include "tools_string.h"

#include <codecvt>
#include <string>
#include <locale>
#include <locale.h>

static std::locale const _UTF8("en_US.UTF-8");

// ==========
#define __PRIVATE_FUNCTIONS
#ifdef __PRIVATE_FUNCTIONS

// Convert UTF-8 byte string to wstring
static std::wstring _to_wstring(std::string const& s)
{
  std::wstring_convert<std::codecvt_utf8<wchar_t> > conv;
  return conv.from_bytes(s);
}


// Convert wstring to UTF-8 byte string
static std::string _to_string(std::wstring const& s)
{
  std::wstring_convert<std::codecvt_utf8<wchar_t> > conv;
  return conv.to_bytes(s);
}


// Converts a UTF-8 encoded string to upper case
static std::string _tou(std::string const& s)
{
  auto ss = _to_wstring(s);
  for (auto& c : ss) {
    c = std::toupper(c, _UTF8);
  }
  return _to_string(ss);
}


#endif


// ==========
#define __PUBLIC_FUNCTIONS
#ifdef __PUBLIC_FUNCTIONS

// reference: [C / C++ UTF-8 upper/lower case conversions](https://stackoverflow.com/questions/12493496/c-c-utf-8-upper-lower-case-conversions)
std::string andrewmc::messager::server::tools::string::utf8_uppercase(const std::string &str)
{
    return _tou(str);
}

#endif  // __PUBLIC_FUNCTIONS
