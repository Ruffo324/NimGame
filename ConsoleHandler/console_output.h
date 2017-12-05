#pragma once
#include "console_handler.h"
#include <string>
#include "SHAPE_RECTANGLE.h"

namespace console_handler
{
  class console_output
  {
  public:
    static CONSOLE_HANDLER_API void print(std::string message);
    static CONSOLE_HANDLER_API void reset_color();
    static CONSOLE_HANDLER_API void print_line(std::string message);
    static CONSOLE_HANDLER_API void print_separatorline(std::string pattern);
    static CONSOLE_HANDLER_API void print_rectangle(SHAPE_RECTANGLE square, std::string color_string, char text_char = ' ');
    // shapes
    static CONSOLE_HANDLER_API void fill_background(std::string color_string, char text_char = ' ');
  };
}
