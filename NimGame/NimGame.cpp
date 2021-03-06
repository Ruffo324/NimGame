// NimGame.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "console_handler.h"
#include <iostream>
#include "console_output.h"
#include "console_utils.h"
#include "console_ascii.h"
#include "ascii_block_list.h"
#include "dynamic_grid.h"
#include "main.h"
#include "play.h"

using namespace std;
using namespace console_handler;


void test()
{
  console_output::fill_background("{_#FFFFFF}");
}

int main()
{
  //console_utils::set_console_position(0, -1920); // Debug: Left screen @home
  console_handler_core::prepare_console(1, true);
  console_output::fill_background("{_#FFFFFF}");

  sites::main::draw();
  //sites::play::new_game();


  getchar();
  return 0;
}
