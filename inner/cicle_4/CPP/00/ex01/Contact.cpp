/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Contact.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungwok <seungwok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 16:41:13 by seungwok          #+#    #+#             */
/*   Updated: 2024/04/29 16:41:14 by seungwok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Contact.hpp"

  void  Contact::SetFirstName(std::string str) { first_name = str; }
  void  Contact::SetLastName(std::string str) { last_name = str; }
  void  Contact::SetNickName(std::string str) { nick_name = str; }
  void  Contact::SetPhoneNumber(std::string str) { phone_number = str;}
  void  Contact::SetDarkestSecret(std::string str) { darkest_secret = str; }

  std::string Contact::GetFirstName() { return first_name; }
  std::string Contact::GetLastName() { return last_name; }
  std::string Contact::GetNickName() { return nick_name; }
  std::string Contact::GetPhoneNumber() { return phone_number; }
  std::string Contact::GetDarkestSecret() { return darkest_secret; }