#include <termios.h>
#include <unistd.h>

/*
 * @brief disables ICANON and ECHO while initialitzing old_attr and new_attr-
 * @return 0 if succesful, -1 otherwise
 */
int set_raw_terminal(struct termios *old_attr, struct termios *new_attr) {

  if (tcgetattr(STDIN_FILENO, old_attr) != 0) {
    return -1;
  }

  *new_attr = *old_attr;
  new_attr->c_lflag &= ~ICANON;

  new_attr->c_lflag &= ~ECHO;

  if (tcsetattr(STDIN_FILENO, TCSANOW, new_attr) != 0) {
    return -1;
  }

  return 0;
}

/*
 * @brief sets teminal attributes to old_attr
 * @return 0 if succesful, -1 otherwise
 */
int set_cannonical_terminal(struct termios *old_attr) {

  if (tcsetattr(STDIN_FILENO, TCSANOW, old_attr) != 0) {
    return -1;
  }

  return 0;
}
