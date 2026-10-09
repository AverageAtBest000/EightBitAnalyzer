#pragma once

#include <fstream>
#include <string>

int make_file(std::ofstream &file, std::string file_name);
void close_file(std::ofstream &file);
void write_to_file(std::ofstream &file, const std::string &line);
