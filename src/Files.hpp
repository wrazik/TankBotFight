#pragma once
#include <filesystem>
#include <string>

namespace files {
inline std::string asset_path() {
  const auto parent_dir_path = std::filesystem::path(__FILE__).parent_path().parent_path().string();
  return parent_dir_path + "/res/";
}

inline std::string default_size_path() {
  const auto parent_dir_path = std::filesystem::path(__FILE__).parent_path().parent_path().string();
  return parent_dir_path + "/res/PNG/Default size/";
}
}  // namespace files
