#pragma once

#include <boost/optional.hpp>

#include <formats/json/value.hpp>
#include <http/content_type.hpp>

#include <server/handlers/exceptions.hpp>

namespace server {
namespace handlers {

/// JSON error message builder.
/// Useful for handlers derived from HttpHandlerBase but responding via JSON.
class JsonErrorBuilder {
 public:
  static constexpr bool kIsExternalBodyFormatted = true;

  explicit JsonErrorBuilder(const CustomHandlerException& ex);

  JsonErrorBuilder(const std::string& error_code, std::string internal_message,
                   const std::string& external_error_body,
                   boost::optional<const formats::json::Value&> details = {});

  const std::string& GetInternalMessage() const { return internal_message_; };

  const std::string& GetExternalBody() const { return json_error_body_; }

  static const ::http::ContentType& GetContentType() {
    return ::http::content_type::kApplicationJson;
  }

 private:
  std::string internal_message_;
  std::string json_error_body_;
};

}  // namespace handlers
}  // namespace server
