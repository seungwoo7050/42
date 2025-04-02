/**
 * @file my_split.c
 * @brief 문자열을 구분자로 분리하여 배열로 반환하는 함수
 *
 * @param s 분리할 문자열 
 * @param c 구분자 문자
 * @return char** 분리된 문자열 배열, 할당 실패 시 NULL 반환
 */
#include "mylibc.h"

static int count_words(const char *s, char c) {
	int count = 0;
	while (*s) {
		while (*s == c)
			++s;
		if (*s)
			++count;
		while (*s && *s != c)
			++s;
	}
	return count;
}

char **my_split(char const *s, char c) {
	int words = count_words(s, c);
	char **arr = malloc((words + 1) * sizeof(char *));
	if (!arr)
		return NULL;
	int index = 0;
	while (*s) {
		while (*s == c)
			++s;
		if (*s) {
			const char *start = s;
			while (*s && *s != c)
				++s;
			size_t len = s - start;
			arr[index] = my_substr(start, 0, len);
			if (!arr[index]) {
				while (index > 0)
					free(arr[--index]);
				free(arr);
				return NULL;
			}
			++index;
		}
	}
	arr[index] = NULL;
	return arr;
}