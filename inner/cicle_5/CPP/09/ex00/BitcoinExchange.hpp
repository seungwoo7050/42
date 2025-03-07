#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <string>
#include <map>
#include <fstream>
#include <exception>
#include <iostream>
#include <sstream>


class BitcoinExchange {
private:
  std::map<std::string, double> exchange_rates;

  BitcoinExchange();
  void loadCSV(const std::string& filename);

public:
  BitcoinExchange(const std::string& filename);
  BitcoinExchange(const BitcoinExchange& copy);
  BitcoinExchange& operator=(const BitcoinExchange& ref);
  ~BitcoinExchange();

  void evaluateInputFile(const char* filename);
  double getExchangeRate(const std::string& date) const;
  bool isValidDate(const std::string& date) const;
};



#endif