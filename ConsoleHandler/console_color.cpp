#include "stdafx.h"
#include <list>
#include <map>
#include <cctype>
#include "console_color.h"
#include <unordered_map>
#include <deque>

namespace console_handler
{
  std::map<std::string, std::string> console_color::cached_translations_;

  /**
   * \brief Translates a color coded message string to a ansi color code.
   * \param message The message with the hexadecimal color codes
   * \return Message with ansi color codes
   */
  std::string console_color::parse_string_to_ansi_string(std::string message)
  {
    std::map<int, std::string> color_codes;

    // search for color codes
    bool color_code_parse = false;
    int color_code_position = 0;
    std::string current_color_code = "";
    for (unsigned int i = 0; i < message.length(); i++)
    {
      // current parsing code
      if (color_code_parse)
      {
        // end of color code -> end & continue;
        if (message[i] == '}')
        {
          color_code_parse = false;
          color_codes.insert(make_pair(color_code_position, current_color_code));
          continue;
        }

        // color code contains invalid char -> throw exception
        if (!isalnum(message[i]) && message[i] != '_' && message[i] != '#' && message[i] != ';')
          throw "Invalid char in color code! Parsed string: " + message;

        // add char to color code
        current_color_code += message[i];
      }

      // begin of new color code? -> add & continue;
      if (message[i] == '{')
      {
        color_code_parse = true;
        color_code_position = i;
        current_color_code = "";
      }
    }

    // build color structs
    COLOR_STRUCT last_foreground = COLOR_STRUCT(255, 255, 255);
    COLOR_STRUCT last_background = COLOR_STRUCT(-1, 0, 0);

    // replace color codes with ascii
    int offset = 0;
    for (auto const& color_code : color_codes)
    {
      const bool background = strstr(color_code.second.c_str(), "_");
      std::string ascii_color_code = color_code_to_ansi(color_code.second,
                                                        background ? last_foreground : last_background);

      message = message.substr(0, color_code.first + offset) +
        ascii_color_code +
        message.substr(color_code.first + color_code.second.length() + 1 + offset + 1);

      offset += int(ascii_color_code.length()) - (int(color_code.second.length()) + 2);

      if (color_code.second == ";")
      {
        last_background.red = -1;

        last_foreground.red = 255;
        last_foreground.green = 255;
        last_foreground.blue = 255;
      }
      else
      {
        if (background)
          last_background = COLOR_STRUCT(color_code.second);
        else
          last_foreground = COLOR_STRUCT(color_code.second);
      }
    }

    return message;
  }

  /**
   * //TODO: Move to COLOR_STRUCT
   * \brief Translates a color code to the wanted ansi color code
   * \param color_code The color code wich should be translated
   * \param last_color_struct Last back/foreground color struct. Used for background/foreground combinations
   * \return Translated ansi color code string
   */
  std::string console_color::color_code_to_ansi(std::string color_code, const COLOR_STRUCT last_color_struct)
  {
    // reset code -> return;
    if (color_code == ";")
      return "\x1B[0m";

    const COLOR_STRUCT parsed_color = COLOR_STRUCT(color_code);
    const bool background = color_code[0] == '_';

    // get ansii string from cache
    const auto iter = cached_translations_.find(color_code);
    if (iter != cached_translations_.end())
    {
      return iter->second;
    }

    // create ansii string, and save in cache
    std::string ansii_string = color_struct_to_ansi(parsed_color, last_color_struct, background);
    cached_translations_.insert(std::pair<std::string, std::string>(color_code, ansii_string));
    return ansii_string;
  }

  /**
   * \brief Creates a console ansi string from 2 given color structs
   * \param color_struct The main color struct
   * \param last_color_struct Last back/foreground color struct. Used for background/foreground combinations
   * \param background Is the main color struct a background color struct
   * \return Ansi color coded string
   */
  std::string console_color::color_struct_to_ansi(const COLOR_STRUCT color_struct,
                                                  const COLOR_STRUCT last_color_struct, const bool background)
  {
    // Create ascii string
    std::string ansi_color_string = "\x1B[38;2;";

    // foreground
    if (background)
      ansi_color_string += std::to_string(last_color_struct.red) + ";" +
        std::to_string(last_color_struct.green) + ";" +
        std::to_string(last_color_struct.blue);
    else
      ansi_color_string += std::to_string(color_struct.red) + ";" +
        std::to_string(color_struct.green) + ";" +
        std::to_string(color_struct.blue);

    // background
    if (background)
      ansi_color_string += ";48;2;" + std::to_string(color_struct.red) + ";" +
        std::to_string(color_struct.green) + ";" +
        std::to_string(color_struct.blue);

    //TODO: remove late if sure this isn't used
    //else if (last_color_struct.red != -1)
    //ansi_color_string += ";48;2;" + std::to_string(last_color_struct.red) + ";" +
    //std::to_string(last_color_struct.green) + ";" +
    //std::to_string(last_color_struct.blue);

    return ansi_color_string + "m";
  }

  std::string console_color::clean_string(std::string string_value)
  {
    bool color_code_parsing = false;

    std::string clean_string = "";
    // Parse chars and color_codes
    for (int i = 0; i < string_value.length(); i++)
    {
      if (color_code_parsing)
      {
        if (string_value[i] == '}')
        {
          color_code_parsing = false;
          continue;
        }
        continue;
      }

      if (string_value[i] == '{')
      {
        color_code_parsing = true;
        continue;
      }

      clean_string += string_value[i];
    }
    return clean_string;
  }
}
