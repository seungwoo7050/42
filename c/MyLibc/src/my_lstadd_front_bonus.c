/**
 * @file my_lstadd_front_bonus.c
 * @brief 리스트의 앞에 노드를 추가하는 함수
 * 
 * @param alst 리스트의 포인터에 대한 포인터 
 * @param new 추가할 새로운 노드
 */
#include "mylibc.h"

void my_lstadd_front(t_list **alst, t_list *new) {
	if (alst && new) {
		new->next = *alst;
		*alst = new;
	}
}