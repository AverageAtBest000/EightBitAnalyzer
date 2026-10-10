#include "reader.h"

#include <cerrno>
#include <string>
#include <unistd.h>

int read_pico_stream(int fd, std::string &read_chars) {
  char read_buffer[256];

  ssize_t num_chars = read(fd, read_buffer, sizeof(read_buffer));
  while (num_chars == -1 && errno == EINTR) {
    num_chars = read(fd, read_buffer, sizeof(read_buffer));
  }

  if (num_chars <= 0) {
    return num_chars;
  }

  read_chars.append(read_buffer, num_chars);
  return num_chars;
}

/*
 * @brief disables ICANON and ECHO while initialitzing old_attr and new_attr-
 * @return 0 if succesful, -1 otherwise
 */
int set_raw_terminal(struct termios *old_attr, struct termios *new_attr,
                     int fd) {

  if (tcgetattr(fd, old_attr) != 0) {
    return -1;
  }

  *new_attr = *old_attr;
  new_attr->c_lflag &= ~ICANON;

  new_attr->c_lflag &= ~ECHO;

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
