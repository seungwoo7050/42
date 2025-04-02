#include "read_one_line.h"
#include "read_one_line_utils.h"
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 42
#endif

/**
 * @brief t_fd_node 구조체는 각 파일 디스크립터에 대한 남은 데이터 버퍼를 저장합니다
 * 
 */
typedef struct s_fd_node {
    int fd;                 /**< 파일 디스크립터 */
    char *buffer;           /**< 해당 파일 디스크립터의 남은 데이터 */
    struct s_fd_node *next; /**< 다음 노드를 가리키는 포인터 */
} t_fd_node;

/**
 * @brief 파일 디스크립터에 해당하는 노드를 검색하거나 새로 생성합니다
 * 
 * @param fd 찾고자 하는 파일 디스크립터
 * @param head 노드 리스트의 헤드 포인터
 * @return t_fd_node* 해당 파일 디스크립터의 노드, 실패 시 NULL
 */
static t_fd_node *get_fd_node(int fd, t_fd_node **head) {
    t_fd_node *current = *head;
    while (current) {
        if (current->fd == fd)
            return current;
        current = current->next;
    }
    current = (t_fd_node *)malloc(sizeof(t_fd_node));
    if (!current)
        return NULL;
    current->fd = fd;
    current->buffer = strdup("");
    if (!current->buffer) {
        free(current);
        return NULL;
    }
    current->next = *head;
    *head = current;
    return current;
}

/**
 * @brief 파일 디스크립터에 해당하는 노드를 리스트에서 제거하고 메모리를 해제합니다
 * 
 * @param fd 제거할 파일 디스크립터
 * @param head 노드 리스트의 헤드 포인터
 */
static void remove_fd_node(int fd, t_fd_node **head) {
    t_fd_node *current = *head;
    t_fd_node *prev = NULL;
    while (current) {
        if (current->fd == fd) {
            if (prev)
                prev->next = current->next;
            else
                *head = current->next;
            free(current->buffer);
            free(current);
            return;
        }
        prev = current;
        current = current->next;
    }
}

/**
 * @brief 파일 디스크립터로부터 한 줄을 읽어 반환합니다.
 * 
 * 내부 static linked list를 사용하여 각 파일 디스크립터의 남은 데이터를 관리합니다
 * read() 시스템 콜을 통해 BUFFER_SIZE 단위로 읽고, 개행 문자('\n')가 나올 때까지 반복합니다
 * 
 * @param fd 읽어올 파일의 파일 디스크립터
 * @return char* 읽은 한 줄의 문자열, 실패하거나 읽을 내용이 없으면 NULL
 */
char *read_one_line(int fd) {
    static t_fd_node *fd_list = NULL;
    t_fd_node *node;
    char buffer[BUFFER_SIZE + 1];
    ssize_t bytes_read;
    char *newline_ptr;
    char *temp;
    char *line;

    if (fd < 0 || BUFFER_SIZE <= 0)
        return NULL;

    node = get_fd_node(fd, &fd_list);
    if (!node)
        return NULL;
    
    /* 버퍼에 개행 문자가 포함될 때까지 읽습니다 */
    while ((newline_ptr = strchr(node->buffer, '\n')) == NULL) {
        bytes_read = read(fd, buffer, BUFFER_SIZE);
        if (bytes_read < 0) {
            free(node->buffer);
            node->buffer = NULL;
            remove_fd_node(fd, &fd_list);
            return NULL;
        }
        if (bytes_read == 0)
            break; /* 파일 끝(EOF) */
        buffer[bytes_read] = '\0';
        temp = strjoin(node->buffer, buffer);
        free(node->buffer);
        node->buffer = temp;
        if (!node->buffer)
            return NULL;
    }

    /* 개행문자가 buffer의 맨 처음이 아닌 그 어딘가에 있는 경우를 위한 후처리 과정 */
    /* 함수의 정의된 동작을 위해 \n까지 자르고, 남은 문자열은 buffer에 다시 보관된다 */
    if (node->buffer && node->buffer[0] != '\0') {
        size_t len = 0;
        if (newline_ptr)
            len = newline_ptr - node->buffer + 1;
        else
            len = strlen(node->buffer);
        line = substr(node->buffer, 0, len);
        /* strdup는 size 지정없이 시작점(전달한 매개변수)부터 NULL을 만날 때까지의 문자열을 복사한다 */
        temp = strdup(node->buffer + len);
        free(node->buffer);
        node->buffer = temp;
        if (node->buffer && node->buffer[0] == '\0') {
            free(node->buffer);
            node->buffer = NULL;
            remove_fd_node(fd, &fd_list);
        }
        return line;
    }

    remove_fd_node(fd, &fd_list);
    return NULL;
}