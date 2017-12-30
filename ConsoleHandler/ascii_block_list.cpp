#include "stdafx.h"
#include "ascii_block_list.h"
#include "console_utils.h"

namespace console_handler
{
  ascii_block_list::ascii_block_list(const std::string string_value, const int font_size_value,
                                     const COLOR_STRUCT foreground_color_value)
    : original_string(string_value), font_size(font_size_value), foreground_color(foreground_color_value)
  {
    create_blocks();
  }

  ascii_block_list::ascii_block_list(const std::string string_value, const int font_size_value)
    : original_string(string_value), font_size(font_size_value)

  {
    create_blocks();
  }

  void ascii_block_list::center_block_list(const bool center, const int item_side_length)
  {
    center_ = center;
    item_side_length_ = item_side_length;
  }

  void ascii_block_list::draw()
  {
    const COORD current_cursor_position = console_utils::get_console_cursor_position();
    const short offset_center = center_ ? short(((item_side_length_ - int(font_size / 2) * ascii_blocks.size()) / 2)) : 0;
    for (int i = 0; i < ascii_blocks.size(); i++)
    {
      console_utils::set_console_cursor_pos({
        (current_cursor_position.X + short((int(font_size / 2) * i))) + offset_center,
        current_cursor_position.Y
      });
      ascii_blocks[i].draw();
    }
  }

  void ascii_block_list::create_blocks()
  {
    bool color_code_parsing = false;
    std::string current_parsing_color_code = "";

    // Parse chars and color_codes
    for (int i = 0; i < original_string.length(); i++)
    {
      if (color_code_parsing)
      {
        if (original_string[i] == '}')
        {
          color_code_parsing = false;
          foreground_color = COLOR_STRUCT(current_parsing_color_code);
          current_parsing_color_code = "";
          continue;
        }

        current_parsing_color_code += original_string[i];
        continue;
      }

      if (original_string[i] == '{')
      {
        color_code_parsing = true;
        continue;
      }
      
      ascii_blocks.push_back(ascii_block(original_string[i], font_size, foreground_color));
    }
  }
}
