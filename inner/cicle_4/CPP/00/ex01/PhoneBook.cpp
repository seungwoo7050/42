 #include "PhoneBook.hpp"

// 기본 생성자, 소멸자
PhoneBook::PhoneBook() : index(0), index_sign(0) {};
PhoneBook::~PhoneBook() {}

// 유틸 함수
bool  IsWhiteSpaceString(const std::string& str) {
  for (size_t i = 0; i < str.size(); i++) {
    if ((str[i] < 9 || str[i] > 13) && str[i] != 32) {
      return false;
    }
  }
  return true;
}
void  GetlineSafeIter(std::string& input) {
  do {
    getline(std::cin, input);
    if (std::cin.eof()) {
      break ;
		}
  } while(input.empty() || IsWhiteSpaceString(input));
  if (std::cin.bad()) {
    std::cout << "입력 오류로 프로그램을 종료합니다." << std::endl;
		exit (1);
  }	else {
    return ;
  }
}

// ADD
void  AddContact(PhoneBook& ref) {
  std::string input;

  std::cout << std::endl;
  std::cout << "연락처를 구성할 필드를 요청에 맞추어 하나씩 차례대로 입력해주세요."  << std::endl;
  ref.SetContact();
  if (std::cin.eof()) {
		clearerr(stdin);
		std::cin.clear();
    return ;
	}
  if (ref.GetIndex() == 7) {
    std::cout << "***** 전체 연락처의 저장이 완료되었습니다. *****" << std::endl;
    std::cout << "추가 요청시 1번 연락처부터 삭제되며 차례대로 저장됩니다." << std::endl;
  } else {
    std::cout << ref.GetIndex() + 1 << "번 인덱스에 연락처 저장이 완료되었습니다." << std::endl;
  }
  ref.AddIndex();
}
void  PhoneBook::SetContact() {
  std::string input;
  
  std::cout << (index + 1) << "번 인덱스에 저장될 연락처에 대한 정보를 입력해주세요." << std::endl;
  std::cout << "공란은 저장할 수 없습니다." << std::endl;

  std::cout << "Frist Name: ";
  GetlineSafeIter(input);
  if (std::cin.eof()) { return ; }
  contacts[index].SetFirstName(input);

  std::cout << "Last Name: ";
  GetlineSafeIter(input);
  if (std::cin.eof()) { return ; }
  contacts[index].SetLastName(input);

  std::cout << "Nick Name: ";
  GetlineSafeIter(input);
  if (std::cin.eof()) { return ; }
  contacts[index].SetNickName(input);

  std::cout << "Phone Number: ";
  GetlineSafeIter(input);
  if (std::cin.eof()) { return ; }
  contacts[index].SetPhoneNumber(input);

  std::cout << "Darkest Secret: ";
  GetlineSafeIter(input);
  if (std::cin.eof()) { return ; }
  contacts[index].SetDarkestSecret(input);
}
int PhoneBook::GetIndex() { return index; }
void  PhoneBook::AddIndex() {
  if (index == 7) {
    index = 0;
    index_sign = 1;
  } else {
    index += 1;
  }
}

// SEARCH
void  SearchContact(PhoneBook& ref) {
  PrintContacts(ref);
  std::string idx;
  std::cout << std::endl;
  std::cout << "자세하게 보고싶은 연락처의 인덱스를 입력하세요: ";
  GetlineSafeIter(idx);
  if (std::cin.eof()) {
    clearerr(stdin);
		std::cin.clear();
    return ;
  }
  int i = idx[0] - '0';
  if (idx.length() > 1) {
    std::cout << "잘못된 번호입니다. 인덱스의 범위는 [1, 8] 입니다." << std::endl;  
  } else if (i == 0 || i == 9) {
    std::cout << "잘못된 번호입니다. 인덱스의 범위는 [1, 8] 입니다." << std::endl;  
  } else if (ref.GetIndex() < i && ref.GetIndexSign() == 0) {
    std::cout << "아직 저장되지 않은 인덱스 번호입니다." << std::endl;  
  } else {
    PrintFormContact();
    PrintContact(ref, i);
  }
}
void  PrintContacts(PhoneBook& ref) {
  PrintFormContacts();
  if (ref.GetIndexSign() == 0) {
    for (int i = 0; i < ref.GetIndex(); i++) {
      std::cout << std::setw(10) << std::right << i + 1 << "|";
      PrintString(ref.GetContact(i).GetFirstName());
      PrintString(ref.GetContact(i).GetLastName());
      PrintString(ref.GetContact(i).GetNickName());
      std::cout << std::endl;
    }
  } else {
    for (int i = 0; i < 8; i++) {
      std::cout << std::setw(10) << std::right << i + 1 << "|";
      PrintString(ref.GetContact(i).GetFirstName());
      PrintString(ref.GetContact(i).GetLastName());
      PrintString(ref.GetContact(i).GetNickName());
      std::cout << std::endl;
    }
  }
}
void  PrintContact(PhoneBook& ref, int idx) {
  std::cout << std::setw(10) << std::right << idx << "|";
  idx -= 1;
  PrintString(ref.GetContact(idx).GetFirstName());
  PrintString(ref.GetContact(idx).GetLastName());
  PrintString(ref.GetContact(idx).GetNickName());
  PrintString(ref.GetContact(idx).GetPhoneNumber());
  PrintString(ref.GetContact(idx).GetDarkestSecret());
  std::cout << std::endl;
}
void  PrintFormContacts() {
  PrintString("Index");
  PrintString("FirstName");
  PrintString("LastName");
  PrintString("NickName");
  std::cout << std::endl;
}
void  PrintFormContact() {
  PrintString("Index");
  PrintString("FirstName");
  PrintString("LastName");
  PrintString("NickName");
  PrintString("Phone");
  PrintString("Secret");
  std::cout << std::endl;
}
void  PrintString(std::string str) {
  if (str.length() < 10) {
    std::cout << std::setw(10) << std::right << str;
  } else {
    std::cout << str.substr(0, 9) << ".";
  }
  std::cout << "|";
}
Contact  PhoneBook::GetContact(int idx) {
  return  contacts[idx];
}
int PhoneBook::GetIndexSign() { return index_sign; }