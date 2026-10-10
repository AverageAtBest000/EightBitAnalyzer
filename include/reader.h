#pragma once

#include <string>
#include <termios.h>

int read_pico_stream(int fd, std::string &read_chars);

int set_raw_terminal(struct termios *old_attr, struct termios *new_attr,
                     int fd);
int set_cannonical_terminal(struct termios *old_attr, int fd);
