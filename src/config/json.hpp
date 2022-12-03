#ifndef CONFIG_JSON_H
#define CONFIG_JSON_H

#include "nlohmann/json.hpp"

using JSON = nlohmann::json;

namespace todo {
namespace config {
namespace json {

static const int INDENT = 2;

} // namespace json
} // namespace config
} // namespace todo

#endif
