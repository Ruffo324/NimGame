#pragma once
#include "console_handler.h"
#include <string>
#include <Windows.h>
#include <vector>
#include "ascii_block_type.h"
#include "COLOR_STRUCT.h"

//TODO: fix warnings correctly
#pragma warning( disable: 4251 )

namespace console_handler
{
  class CONSOLE_HANDLER_API ascii_block
  {
  public:
    /**
     * \brief Contains the color wich is used as transparent.
     */
    const COLOR_STRUCT transparent_color = COLOR_STRUCT(255, 0, 255);

    /**
     * \brief Textlines with color codes and fillup chars
     */
    std::vector<std::string> text_lines;

    /**
    * \brief Only used if the original content was an text char.
    * \brief Contains the original text char.
    */
    char original_char;

    /**
     * \brief The fillup text_char.
     * \brief Mostly space.
     */
    char text_char;

    /**
    * \brief Contains the bitmap path.
    * \brief Always used.
    */
    std::string bitmap_path;

    /**
    * \brief The type of the source of the ascii block.
    */
    ascii_block_type ascii_block_type;

    /**
    * \brief The size of the ascii block
    */
    SIZE ascii_block_size;

    /**
     * \brief If not given, the color of the bitmap used. (Placeholder Color_struct)
     * \brief Forground color for the parsed bitmap.
     */
    COLOR_STRUCT foreground_color;

    // Functions
    void draw();

    // Constructors
    ascii_block(std::string bitmap_path_value, SIZE size_value);
    ascii_block(std::string bitmap_path_value, SIZE size_value, char text_char_value);
    ascii_block(std::string bitmap_path_value, SIZE size_value, COLOR_STRUCT foreground_color_value);
    ascii_block(std::string bitmap_path_value, SIZE size_value, char text_char_value, COLOR_STRUCT foreground_color_value);
    ascii_block(char text_char, int font_size, COLOR_STRUCT foreground_color_value);

    void add_padding(const int padding);
  private:
    void generate_text_lines();
    int real_width_;
    bool bitmap_exists() const;
    int padding_ = 0;
    static std::string char_to_file_compatible_string(char incompatible_char);
  };
}
