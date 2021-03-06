#pragma once
#include <Windows.h>
#include <xstring>
#include "COLOR_STRUCT.h"

namespace console_handler
{
  class console_bmp
  {
  public:
    console_bmp(int width, int height);
    void write_text(const char char_value) const;
    bool save(const char* filename) const;
    ~console_bmp();
  private:
    int width;
    int height;
    unsigned char** data_;
    HBITMAP bitmap_handle;
    HFONT get_font(const std::string name, int size, bool italic, bool bold, bool underline, bool strike_out) const;
  };
}
