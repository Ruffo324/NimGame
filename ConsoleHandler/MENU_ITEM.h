#pragma once
#include <string>

namespace console_handler
{
  //TODO: add constructor
  struct MENU_ITEM
  {
    std::string caption;
    std::string item_background;
    std::string ascii_icon;
    char border_char;
    std::string border_color_code;
    int border_size;

    int length;
    int width;
  };
}
