//
// Created by victor on 4/11/17.
//

#include <boost/algorithm/string.hpp>
#include <proxygen/httpserver/filters/DirectResponseHandler.h>
#include "UserRequestHandlerFactory.h"
#include "UserRequestHandler.h"
#include "LoggingFilter.h"
#include "Validations.h"
#include "CorsFilter.h"

namespace restdbxx {

const std::string USERS_PATH = "/__users";
void UserRequestHandlerFactory::onServerStart(folly::EventBase *evb) noexcept {
}
void UserRequestHandlerFactory::onServerStop() noexcept {

}
proxygen::RequestHandler *UserRequestHandlerFactory::onRequest(proxygen::RequestHandler *handler,
                                                               proxygen::HTTPMessage *message) noexcept {
  std::string path = message->getPath();
  Validations::sanitize_path(path);
  bool result = boost::algorithm::starts_with(path, USERS_PATH);
  if (result) {
    VLOG(google::GLOG_INFO) << "path matches, handling this request with UserRequestHandler";
    return new UserRequestHandler();
  }

  VLOG(google::GLOG_INFO) << "path doesnt match";
  return handler;
}
UserRequestHandlerFactory::~UserRequestHandlerFactory() {

}
UserRequestHandlerFactory::UserRequestHandlerFactory() {}

}
