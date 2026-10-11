#include "reader.h"
#include "writer.h"
#include <fcntl.h>
#include <fstream>
#include <termios.h>
#include <unistd.h>

int main() {
  // make new csv file for data collection
  std::ofstream csv;
  if (make_file(csv, "data.csv") != 0)
    return -1;

  // open pico stream
  int fd = open("/dev/ttyACM0", O_RDWR);

  if (fd == -1)
    return -1;

  // set pico stream to non-cannonical for real time reading
  termios old_attr, new_attr;
  if (set_raw_terminal(&old_attr, &new_attr, fd) == -1)
    return -1;

  // write g to pico in order to begin the program
  char c = 'g';
  if (write(fd, &c, 1) == -1)
    return -1;

  // read the pico stram into csv
  if (read_pico_stream_to_file(fd, csv) != 0)
    return -1;

  close_file(csv);
  // return pico stream to old_attr
  set_cannonical_terminal(&old_attr, fd);
  return 0;
}
