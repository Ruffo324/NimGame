#include "stdafx.h"
#include "console_handler.h"
#include <stdexcept>
#include <Windows.h>
#include "console_utils.h"

namespace console_handler
{
   void console_handler_core::prepare_console(const int font_size)
  {
     // set console mode for color support
     DWORD current_mode;
     GetConsoleMode(console_utils::get_console_handle(), &current_mode);
     current_mode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
     SetConsoleMode(console_utils::get_console_handle(), current_mode);

     
     console_utils::set_console_raster_font(font_size);
     // Change console propertys for perfect game experience
     //console_utils::set_console_position(0, -1920);
     console_utils::set_console_position(0, 0);
    //console_utils::set_console_size(400, 800);
     //console_utils::set_console_size(1920, 1080);
     console_utils::set_console_size(1080, 720);
     //console_utils::set_console_fullscreen();

     //console_utils::set_console_size_fixed();
     console_utils::set_console_raster_font(font_size);



     
  }
};
