#include "Character.hpp"
#include "Ice.hpp"
#include "Cure.hpp"
#include "MateriaSource.hpp"
#include <iostream>

int main() {
    // MateriaSource 생성 및 학습
    IMateriaSource* src = new MateriaSource();
    src->learnMateria(new Ice());
    src->learnMateria(new Cure());

    // Character 생성
    ICharacter* me = new Character("Mr.42");

    // Materia 생성 및 장착
    AMateria* tmp;
    tmp = src->createMateria("ice");
    me->equip(tmp);
    tmp = src->createMateria("cure");
    me->equip(tmp);

    // 다른 Character 생성
    ICharacter* bob = new Character("bob");

    // Materia 사용
    me->use(0, *bob);
    me->use(1, *bob);

    // 추가 테스트: 장착 및 해제
    tmp = src->createMateria("ice");
    me->equip(tmp);
    me->unequip(2);  // 해제 테스트
    me->use(2, *bob);  // 빈 슬롯 사용 시도 (아무 일도 일어나지 않아야 함)
    delete tmp;


    tmp = src->createMateria("ice");
    me->equip(tmp);
    tmp = src->createMateria("cure");
    me->equip(tmp);
    // Inventory가 가득 찬 상태에서 Materia 장착 시도
    tmp = src->createMateria("ice");
    me->equip(tmp);  // 슬롯이 꽉 찬 상태이므로 아무 일도 일어나지 않아야 함
    delete tmp;
    
    // Character 복사 생성자 테스트
    ICharacter* cloneMe = new Character(*(Character*)me);
    cloneMe->use(0, *bob);
    cloneMe->use(1, *bob);
    
    // Character 대입 연산자 테스트
    Character* operMe = new Character("Mr.42(=)");
    *operMe = *(Character*)me;
    operMe->use(0, *bob);
    operMe->use(1, *bob);

    // Cleanup
    delete operMe;
    delete cloneMe;
    delete bob;
    delete me;
    delete src;

    return 0;
}
