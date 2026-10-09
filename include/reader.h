#pragma once

#include <termios.h>

int set_raw_terminal(struct termios *old_attr, struct termios *new_attr);
int set_cannonical_terminal(struct termios *old_attr);
