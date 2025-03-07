#ifndef __HARL_HPP__
#define __HARL_HPP__

#include <string>
#include <iostream>

class Harl {
private:
  void  debug( void );
  void  info( void );
  void  warning( void );
  void  error( void );

public:
  Harl();
  ~Harl();
  void  complain( std::string level );
};

// 함수 포인터 사용법
// typedef void (*FuncPtr)(int);  선언
// FuncPtr funcPtr = &myFunction; 할당
// funcPtr(10);                   호출

typedef void (Harl::*FuncPtr) (void);
// 함수포인터를 통한 호출의 장점은 여러가지가있는데,
// 이번 문제에서 제시하고자하는 의의는 호출이될 함수들을
// private로 정의한 것에서 유추할 때 함수의 직접노출을
// 피하고 간접적 호출을 통해 데이터의 캡슐화를 강화한 것으로 보인다.

#endif