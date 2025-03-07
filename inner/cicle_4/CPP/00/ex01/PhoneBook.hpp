/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PhoneBook.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungwok <seungwok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 16:41:37 by seungwok          #+#    #+#             */
/*   Updated: 2024/04/29 16:44:07 by seungwok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __PHONEBOOK_HPP__
#define __PHONEBOOK_HPP__

#include "Contact.hpp"
#include <iostream>
#include <iomanip>

class PhoneBook {
private:
  Contact contacts[8];
  int     index;
  int     index_sign;

public:
  PhoneBook();
  ~PhoneBook();

  void    AddIndex();
  int     GetIndex();
  int     GetIndexSign();
  void    SetContact();
  Contact GetContact(int idx);
};

// UTIL
bool  IsWhiteSpaceString(const std::string& str);
void  GetlineSafeIter(std::string& input);


// ADD
void  AddContact(PhoneBook &ref);

// SEARCH
void  SearchContact(PhoneBook& ref);
void  PrintContacts(PhoneBook& ref);
void  PrintContact(PhoneBook& ref, int idx);
void  PrintFormContacts();
void  PrintFormContact();
void  PrintString(std::string str);

#endif

// std::cin.clear()
// std::cin 객체의 에러 플래그를 초기화 하고 입력 버퍼를 비운다.
// 하지만, 파일 끝 표시기는 초기화하지 않는다.
// 에러플래그는 std::ios 클래스에서 정의된 플래그
// std::ios::failbit 플래그와 같은 다양한 비트로 구성

// clearerr(stdin)
// 표준 입력 스트림에 대한 오류 표시기와 파일 끝 표시기를 초기화한다.
// std::ios::badbit 및 std::ios::eofbit 두 개의 플래그로 구성

// crtl + D 를 누르면 EOF 입력
// 파일끝 표시기가 켜지고 버퍼에 EOF이 남아있는상태이다.
// std::cin.clear 로 버퍼를 비우고,
// clearerr(stdin) 으로 표준 입력 스트림의 파일 끝 표시기를 초기화해준다.