#pragma once

#include <fstream>
#include <termios.h>

int read_pico_stream_to_file(int fd, std::ofstream &file);

int set_raw_terminal(struct termios *old_attr, struct termios *new_attr,
                     int fd);
int set_cannonical_terminal(struct termios *old_attr, int fd);
