#include "Http.hpp"

#include <string>
#include <sstream>

namespace Http {

bool Parser::isReadHeader(const std::string& string) {
  return (string.find(Http::CRLF) != std::string::npos);
}



Method Request::method() const {
  return _requestLine.method;
}



std::string Response::toString() const {
  std::ostringstream oss = std::ostringstream();
  oss << _statusLine;
  return oss.str();
}

std::ostream& operator<<(std::ostream& stream, const Response::StatusLine& statusLine) {
  stream << statusLine.value;
  return stream;
}

}
