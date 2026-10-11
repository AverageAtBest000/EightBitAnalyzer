#include "reader.h"
#include "shared.h"
#include "writer.h"

#include <fstream>
#include <string>
#include <unistd.h>

int read_pico_stream_to_file(int fd, std::ofstream &file) {

  char read_buffer[256];
  int n = num_samples;

  std::string read_chars;
  std::string to_write;

  while (n > 0) {
    int num_chars = read(fd, read_buffer, sizeof(read_buffer));
    if (num_chars == 0)
      continue;
    if (num_chars == -1)
      return -1;

    read_chars.append(read_buffer, num_chars);

    auto newline_pos = read_chars.find('\n');

    while (n > 0 && newline_pos != std::string::npos) {
      to_write.append(read_chars.substr(0, newline_pos + 1));
      read_chars.erase(0, newline_pos + 1);
      n--;
      newline_pos = read_chars.find('\n');
    }
  }

  write_to_file(file, to_write);

  return 0;
}

/*
 * @brief calls cfmakeraw(). Makes VMIN 1 and VTIME 0
 * @return 0 if succesful, -1 otherwise
 */
int set_raw_terminal(struct termios *old_attr, struct termios *new_attr,
                     int fd) {

  if (tcgetattr(fd, old_attr) != 0) {
    return -1;
  }

  *new_attr = *old_attr;

  cfmakeraw(new_attr);

  new_attr->c_cc[VMIN] = 1;
  new_attr->c_cc[VTIME] = 0;

  if (tcsetattr(fd, TCSANOW, new_attr) != 0) {
    return -1;
  }
  return 0;
}

/*
 * @brief sets teminal attributes to old_attr
 * @return 0 if succesful, -1 otherwise
 */
int set_cannonical_terminal(struct termios *old_attr, int fd) {

  if (tcsetattr(fd, TCSANOW, old_attr) != 0) {
    return -1;
  }

  return 0;
}
