#include "SedIFL.hpp"

SedIFL::SedIFL(std::string _filename) : filename(_filename) {}

int  SedIFL::replace(std::string origin, std::string replace) {
  std::ifstream infile(filename.c_str());
  if (!infile.is_open()) {
    std::cout << "파일 열기 실패!" << std::endl;
    if (infile.bad()) {
      std::cout << "심각한 오류 발생!" << std::endl;
    }
    return 1;
  }

  std::ofstream outfile((filename + ".replace").c_str());
  if (!outfile.is_open()) {
    std::cout << "파일 열기 실패!" << std::endl;
    if (outfile.bad()) {
      std::cout << "심각한 오류 발생!" << std::endl;
    }
    return 1;
  }

  std::string line;
  while(std::getline(infile, line)) {
    std::size_t pos = 0;
    if (origin != "") {
      while ((pos = line.find(origin, pos)) != std::string::npos) {
        line.erase(pos, origin.length());
        line.insert(pos, replace);
        pos += replace.length();
      }
    }
    outfile << line;
    if (!infile.eof()) 
      outfile << std::endl;
  }

  infile.close();
  outfile.close();
  return 0;
}