/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungwok <seungwok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 16:41:20 by seungwok          #+#    #+#             */
/*   Updated: 2024/04/29 16:45:08 by seungwok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PhoneBook.hpp"

int main(void) {
  std::string	input;
	PhoneBook		phonebook;

  while(true) {
		std::cout << std::endl;
		std::cout << "***** CPP00:EX01 전화번호부 *****" << std::endl;
		std::cout << "ADD:	새로운 연락처를 저장합니다." << std::endl;
		std::cout << "SEARCH: 특정 연락처를 화면에 표시합니다." << std::endl;
		std::cout << "EXIT:	프로그램을 종료하고 전화번호부를 삭제합니다." << std::endl;
    std::cout << "명령어중 원하시는 동작을 입력하세요." << std::endl << ": ";

		getline(std::cin, input);
		if (std::cin.bad()) {
    	std::cout << "입력 오류로 프로그램을 종료합니다." << std::endl;
			exit (1);
  	}
		if (!input.compare("EXIT")) {
			std::cout << "저장된 모든 정보를 삭제하고 프로그램을 종료합니다." << std::endl;
			return 0;
		} else if (!input.compare("ADD")) {
			AddContact(phonebook);
		} else if (!input.compare("SEARCH")) {
			SearchContact(phonebook);
		}
		if (std::cin.eof()) {
			clearerr(stdin);
			std::cin.clear();
		}
	}
	return 0;
}

// **** std::getline ****
// 한 줄의 문자열을 읽어 문자열 객체에 저장하는 표준라이브러리 함수

// * 형태1: 
// std::istream& std::getline(std::istream& is, std::string& str);
// is:   입력 스트림 객체 (ex: std::cin)
// str:  입력된 문자열을 저장할 문자열 객체 
// 한 줄의 문자열을 읽고, 개행 문자를 포함하여 객체에 저장합니다.
// * 형태2:
// std::istream& std::getline(std::istream& is, std::string& str, char delim);
// delim: 구분문자
// 입력 스트림에서 구분 문자열을 만날 떄 까지 문자를 읽고, 구분자를 제외한 문자열을 객체에 저장합니다.

// *** 오류처리: (11표준에서 추가된 기능이며 98표준에서는 사용 불가능하다.)
// * 형태1:
// 성공적으로 문자열을 읽으면 is 객체를 반환하고, 실패하면 is 객체를 failbit 플래그를 설정하여 반환한다.
// if(std::getline(std::cin, std).fail()) {
// std::cerr << "Error reading input" << endl;
// }
// * 형태2:
// 예외를 발생시킬수 있으며 이를통한 오류처리가 가능하다.
// try {
// std::getline(std::cin, str);
// } catch (const std::ios_base::failure& e) {
// std::cerr << Error << e.what() << endl;
// return 1;
// }

// *** std::cin 과의 차이점:
// 입력단위의 차이:
// std::cin 은 개별 문자 단위로 읽지만, std::getline 한 줄의 문자열 단위로 읽는다.
// 개행 문자 처리:
// std::cin 은 개행문자를 무시하지만, std::getline 은 개행문자를 포함하여 읽는다.
// 오류 처리:
// std::getline 은 오류 상황을 명확하게 나타내는 반환 값과 예외를 제공하지만, std::cin 은 이 부분에대하여 극히 제한적이다.

// *** 98 표준에 따른 getline 에러처리방법
// 에러 코드 사용
// #define ERR_FAIL -1
// int getline_safe(std::string& input) {
// 	std::getline(std::cin, input);
// 	if (std::cin.bad()) {
// 		std::cin.clear();
// 		return ERR_FAIL;
// 	} else {
// 		return 0;
// 	}
// }

// *** 프롬프트를 통한 입력값 검사
// 1. EOF은 배제해도된다.
// 2. 길이가 0인지, 혹은 특정 문자열을 포함하는지 사용자의 정의에 맞게 조건 검사
// 3. while 루프를 통해 입력을 받는 경우 명령어에 맞는 동작을 위한 검사

// *** cin 의 함수를 통한 오류검사
// 1.std::cin.bad():
// 입력 스트림 std::cin 객체의 badbit 플래그 상태를 확인하는 함수.
// badbit 플래그는 입력 스트림에 오류가 발생했는지 여부를 나타낸다.
// 설정되는 경우:
// 파일 열기 실패
// 잘못된 포맷의 입력
// 입력 스트림의 끝에 도달하기 전에 std::cin.eof() 함수가 호출된 경우
// 다른 스트림 객체에서 std::cin 객체로 std:;tie() 함수를 사용한 후 해당 스트림 객체에 오류가 발상
// 반환 값:
// 플래그가 설정된 경우 true, 설정되지 않은 경우 false 를 반환