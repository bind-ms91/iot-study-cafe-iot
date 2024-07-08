#ifndef HTTP_HPP
#define HTTP_HPP

#include <string>
#include <map>

namespace Http {

static const std::string CRLF = "\r\n";

struct StartLine {};

enum Method {
  HM_GET,
  HM_HEAD,
  HM_POST,
  HM_PUT,
  HM_DELETE,
  HM_CONNECT,
  HM_OPTIONS,
  HM_TRACE,
};

std::map<std::string, Method> methodMap_init() {
  std::map<std::string, Method> methodMap;

  methodMap["GET"] = HM_GET;
  methodMap["HEAD"] = HM_HEAD;
  methodMap["POST"] = HM_POST;
  methodMap["PUT"] = HM_PUT;
  methodMap["DELETE"] = HM_DELETE;
  methodMap["CONNECT"] = HM_CONNECT;
  methodMap["OPTIONS"] = HM_OPTIONS;
  methodMap["TRACE"] = HM_TRACE;

  return methodMap;
}

static std::map<std::string, Method> methodMap = methodMap_init();



class Parser {

public :
  bool isReadHeader(const std::string& string);

private :

};



class Message {

public :
  virtual ~Message() = 0;

private :
  StartLine _startLine;

};



class Request : public Message {

public :
  Method method() const;

private :
  struct RequestLine : public StartLine {
    Method method;
  };

  RequestLine _requestLine;
  std::map<std::string, std::string> _headerFields;

};



class Response : public Message {

public :
  struct StatusLine : public StartLine {
    int value;
  };

  std::string toString() const;


private :
  StatusLine _statusLine;
  std::map<std::string, std::string> _headerFields;

};

std::ostream& operator<<(std::ostream& stream, const Response::StatusLine& statusLine);

}

#endif  // HTTP_HPP
