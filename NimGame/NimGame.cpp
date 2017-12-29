// NimGame.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "console_handler.h"
#include <iostream>
#include "console_output.h"
#include "console_utils.h"
#include "console_select.h"
#include "console_ascii.h"
#include "ascii_block_list.h"
#include "dynamic_menu.h"

using namespace std;
using namespace console_handler;

int main()
{
  console_utils::set_console_position(0, -1920);
  console_handler_core::prepare_console(1, true);
  console_output::fill_background("{_#FFFFFF}");

  // test menu
  vector<menu_item> menu_items;
  for (int i = 0; i < 8; i++)
    menu_items.push_back(menu_item("Settings", "{#FFFFFF}", "{_#8c9eff}", "../Icons/Settings.bmp", "{#FFFFFF}", ' ',
                                   "{_#03b7a5}", 5));

  dynamic_menu main_menu = dynamic_menu(menu_items, 5, 10);
  main_menu.draw();
  main_menu.select();

  // testing icon to ansii
  console_utils::set_console_cursor_pos({0, 0});
  //ascii_block_list("Hallo Welt!", 15, COLOR_STRUCT("#FFFFFF")).print();


  getchar();
  return 0;
}
