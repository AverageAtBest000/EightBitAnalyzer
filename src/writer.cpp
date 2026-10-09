#include <fstream>
#include <termios.h>
#include <unistd.h>

/* @brief makes a new file
 * @ return 0 if succesful -1 otherwise
 */
int make_file(std::ofstream &file, std::string file_name) {
  file.open(file_name);

  if (!file.is_open())
    return -1;
}

/* @brief closes file
 */
void close_file(std::ofstream &file) { file.close(); }

/*
 * @brief writes line to file - appends newline at the end
 */
void write_to_file(std::ofstream &file, const std::string &line) {

  file << line << "\n";
}
