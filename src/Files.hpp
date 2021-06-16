#pragma once
#include <filesystem>
#include <string>

namespace files {
std::string
asset_path()
{
  const auto parent_dir_path = std::filesystem::path(__FILE__).parent_path().parent_path().string();
  return parent_dir_path + "/res/";
}
}
