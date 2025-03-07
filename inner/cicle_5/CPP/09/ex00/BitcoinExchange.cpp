#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange() {}
BitcoinExchange::BitcoinExchange(const std::string& filename) {
  loadCSV(filename);
}
BitcoinExchange::BitcoinExchange(const BitcoinExchange& copy)
: exchange_rates(copy.exchange_rates) { }
BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange& ref) {
	if (this != &ref) {
		exchange_rates = ref.exchange_rates;
	}
	return *this;
}
BitcoinExchange::~BitcoinExchange() { }

void BitcoinExchange::loadCSV(const std::string& filename) {
	// Database 파일 검사 (csv 형식)
	if (filename.size() < 4 || filename.substr(filename.size() - 4) != ".csv") {
		throw std::runtime_error("Error: Invalid database file");
	}

	// Database 파일 열기
	std::ifstream file(filename.c_str());
	if (!file.is_open()) {
		throw std::runtime_error("Error: Invalid database file");
	}

	// 연 파일 내용을 통해 map 초기화
	std::string line;
	std::getline(file, line);
	while (std::getline(file, line)) {
		std::istringstream iss(line);
		std::string date;
		std::string rate_str;
		if (std::getline(iss, date, ',') && std::getline(iss, rate_str)) {
			std::stringstream rate_stream(rate_str);
			double rate;
			if (!(rate_stream >> rate)) {
				throw std::runtime_error("Error: Invalid database file");
			}
			exchange_rates[date] = rate;
		} else {
			throw std::runtime_error("Error: Invalid database file");
		}
	}
	file.close();
}

void BitcoinExchange::evaluateInputFile(const char* filename) {
	// Input 파일 열기 (형식 제한 없음)
	std::ifstream file(filename);
	if (!file.is_open()) {
		throw std::runtime_error("Error: Invalid input file");
	}

	// 연 파일 내용 읽으면서 적절한 값 출력
	std::string line;
	std::getline(file, line);
	while (std::getline(file, line)) {
		std::istringstream iss(line);
		std::string date;
		std::string value_str; 
		try {
			if (std::getline(iss, date, '|') && std::getline(iss, value_str)) {
				date = date.substr(0, date.find_last_not_of(" \t") + 1);
				value_str = value_str.substr(value_str.find_first_not_of(" \t"));
				std::stringstream value_stream(value_str);
				double value;
				if (!(value_stream >> value)) {
					throw std::invalid_argument("invalid numeric value.");				
				}
				if (value < 0) {
					throw std::invalid_argument("not a positive number.");				
				}
				if (value > 1000) {
					throw std::invalid_argument("too large a number.");				
				}
				if (!isValidDate(date)) {
					throw std::invalid_argument("invalid date.");
				}
				double rate = getExchangeRate(date);
				std::cout << date << " => " << value << " = " << (value * rate) << std::endl;
			} else {
				std::cout << "Error: bad input => " << iss.str() << "." << std::endl;
			}	
		} catch (const std::invalid_argument& e) {
			std::cout << "Error: " << e.what() << std::endl;
		} catch (const std::exception& e) {
			std::cout << "Error: " << e.what() << std::endl;		
		}
	}
	file.close();
}

bool BitcoinExchange::isValidDate(const std::string& date) const {
	if (date.size() != 10 || date[4] != '-' || date[7] != '-') {
		return false;
	}

	std::istringstream year_stream(date.substr(0, 4));
	std::istringstream month_stream(date.substr(5, 2));
	std::istringstream day_stream(date.substr(8, 2));

	int year, month, day;
	if (!(year_stream >> year) || !(month_stream >> month) || !(day_stream >> day)){
		return false;
	}
	if (year <= 0 || month <= 0 || month > 12 || day <= 0) {
		return false;
	}
	return true;
}

double BitcoinExchange::getExchangeRate(const std::string& date) const {
	std::map<std::string, double>::const_iterator it = exchange_rates.lower_bound(date);
	if (it == exchange_rates.end() || it->first != date) {
		if (it == exchange_rates.begin()) {
			throw std::runtime_error("Date not found.");
		}
		--it;
	}
	return it->second;
}