#include "Application.hpp"

#include <string>
#include <cstdlib>
#include <unistd.h>

#include "Select.hpp"

//void application_readConfigurationFile(Application* application) {
//  Buffer* buffer = buffer_new();
//  scanf("%s\n", buffer->data);
//}

Application::Application()
: _localServer("9873")
{
//  const std::string localServerPortNumber = "9873";  // TODO read from configuration.ini
//  _localServer = LocalServer(localServerPortNumber);

  _select.readFDSet_add(_localServer.listenSocketFD());
}

void Application::launch() {
  _loop();
}

void Application::_accept() {
  const int localServerClientSocketFD = _localServer.accept();
  if (localServerClientSocketFD == -1) {
    fprintf(stderr, "local server accept failed");

    return;
  }

  _select.readFDSet_add(localServerClientSocketFD);
}

void Application::_loop() {
  while (true) {
    _select.select();

    if (_select.readFDSet_isSet(_localServer.listenSocketFD())) {
      fprintf(stderr, "listen socket fd is set\n");

      _accept();
    }

    LocalServer::ClientSocketFDStreamMap::iterator it = _localServer.clientSocketFDStreamMap().begin();
    while (it != _localServer.clientSocketFDStreamMap().end()) {
      const int fd = it->first;
      ++it;

      if (_select.readFDSet_isSet(fd)) {
        fprintf(stderr, "read fd %d is set\n", fd);

        const std::string* readMessage = _localServer.read(fd);
        if (readMessage == NULL) {
          _select.readFDSet_remove(fd);
          continue;
        }

        printf("%s\n", readMessage->c_str());
        _localServer.write(fd, "HTTP/1.1 200 OK\r\n");
      }
    }

    sleep(1);
  }
}
