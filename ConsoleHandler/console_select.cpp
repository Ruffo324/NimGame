#include "stdafx.h"
#include "console_select.h"
#include <Windows.h>
#include <conio.h>
#include "console_output.h"
#include "console_utils.h"


namespace console_handler
{
  class console_utils;

  MENU_ITEM_RECTANGLE console_select::select_menu_item(std::vector<MENU_ITEM_RECTANGLE> menu_items)
  {
    int current_selected_index = -1;
    int last_selected_index = -1;
    char input = 0;
    bool was_arrow_key = false;

    // until enter
    while (input != '\r')
    {
      if (last_selected_index != current_selected_index) {
        // redraw last
        if(last_selected_index != -1)
        draw_border_around_menu_item(menu_items[last_selected_index], ' ', menu_items[last_selected_index].menu_item.item_background);

        const MENU_ITEM_RECTANGLE current_item = menu_items[current_selected_index];

        // draw border
        draw_border_around_menu_item(current_item, current_item.menu_item.border_char, current_item.menu_item.border_color_code);
      }

      input = _getch();
      if (input == -32)
      {
        was_arrow_key = true;
        continue;
      }
      // remind last index
      last_selected_index = current_selected_index;

      if (was_arrow_key)
        switch (input)
        {
          //  arrow rigth
        case 'M':
          current_selected_index++;
          if (current_selected_index + 1 > int(menu_items.size()))
            current_selected_index = 0;
          break;
          //  arrow left
        case 'K':
          current_selected_index--;
          if (current_selected_index < 0)
            current_selected_index = int(menu_items.size()) - 1;
          break;
          //  arrow up
        case 'H':
          break;
          //  arrow down
        case 'P':
          break;
        default:
          // TODO: Hint with wrong key
          break;
        }

      was_arrow_key = false;
    }
    return menu_items[0];
  }

  void console_select::draw_border_around_menu_item(const MENU_ITEM_RECTANGLE menu_item, const char border_char, const std::string border_color_code)
  {
    // calculate box properties
    const int item_height = (menu_item.item_rectangle.right.Y - menu_item.item_rectangle.left.Y);
    const int item_width = (menu_item.item_rectangle.right.X - menu_item.item_rectangle.left.X);
    
    std::string top_bottom_line = border_color_code;
    std::string border_left_right = border_color_code;
    for (int i = 0; i <= item_width; i++)
      top_bottom_line += border_char;

    for (int i = 0; i <= menu_item.menu_item.border_size; i++)
      border_left_right += border_char;

    // draw border
    for (int height = 0; height <= item_height; height++)
    {
      console_utils::set_console_cursor_pos({
        short(menu_item.item_rectangle.left.X),
        short(menu_item.item_rectangle.left.Y + short(height))
        });
      
      for (int width = 0; width <= item_width; width++)
      {
        if (height <= menu_item.menu_item.border_size || height >=  item_height - menu_item.menu_item.border_size)
        {
          console_output::print(top_bottom_line);
          break;
        }
        if(width == 0 || width == item_width - menu_item.menu_item.border_size)
        {
          console_utils::set_console_cursor_pos(
            { menu_item.item_rectangle.left.X + short(width), menu_item.item_rectangle.left.Y + short(height)});
          console_output::print(border_left_right);
        }
      }
    }
  }
}