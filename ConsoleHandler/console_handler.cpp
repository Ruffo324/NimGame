#include "stdafx.h"
#include "console_handler.h"
#include <stdexcept>
#include <Windows.h>
#include "console_utils.h"
#include "console_ascii.h"

namespace console_handler
{
  /**
   * \brief Prepares the windows terminal for the console handler.
   * \param font_size The font size for the console cursor
   * \param fullscreen Open console in fullscreen mode
   */
  void console_handler_core::prepare_console(const int font_size, const bool fullscreen)
  {
    // set console mode for color support
    DWORD current_mode;
    GetConsoleMode(console_utils::get_console_handle(), &current_mode);
    current_mode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(console_utils::get_console_handle(), current_mode);

    if (font_size != -1)
      console_utils::set_console_raster_font(font_size);

    // Change console propertys for perfect game experience
    //console_utils::set_console_position(0, -1920);
    //console_utils::set_console_position(0, 0);
    //console_utils::set_console_size(400, 800);
    //console_utils::set_console_size(1920, 1080);
    if (font_size == 1)
      console_utils::set_console_size(1080, 720);

    console_utils::set_console_size_fixed();
    if (fullscreen)
      console_utils::set_console_fullscreen();

    if (font_size != -1)
      console_utils::set_console_raster_font(font_size);
  }
};
