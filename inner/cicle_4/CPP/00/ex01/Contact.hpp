/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Contact.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungwok <seungwok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 16:41:17 by seungwok          #+#    #+#             */
/*   Updated: 2024/04/29 16:41:18 by seungwok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __CONTACT_HPP__
#define __CONTACT_HPP__

#include <string>

class Contact { 
private:
  std::string first_name;
  std::string last_name;
  std::string nick_name;
  std::string phone_number;
  std::string darkest_secret;
  
public:
  void  SetFirstName(std::string str);
  void  SetLastName(std::string str);
  void  SetNickName(std::string str);
  void  SetPhoneNumber(std::string str);
  void  SetDarkestSecret(std::string str);

  std::string  GetFirstName();
  std::string  GetLastName();
  std::string  GetNickName();
  std::string  GetPhoneNumber();
  std::string  GetDarkestSecret();
};

#endif