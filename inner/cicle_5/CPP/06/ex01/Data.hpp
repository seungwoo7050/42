#ifndef DATA_HPP
#define DATA_HPP

#include <cstring> // std::memcpy

// uint8_t, uint32_t 정의
typedef unsigned char uint8_t;
typedef unsigned int uint32_t;

struct Header {
    uint32_t payload_len;
    // 추가 헤더 멤버를 여기에 선언할 수 있습니다.
};

struct Data {
    Header header;
    uint8_t* payload;

    // 생성자
    Data(uint32_t len) : payload(new uint8_t[len]) {
        header.payload_len = len;
    }

    // 소멸자
    ~Data() { delete[] payload; }

    // 복사 생성자 (복사할 경우를 대비)
    Data(const Data& other) : payload(new uint8_t[other.header.payload_len]) {
        header.payload_len = other.header.payload_len;
        std::memcpy(payload, other.payload, other.header.payload_len);
    }

    // 대입 연산자 오버로딩 (복사할 경우를 대비)
    Data& operator=(const Data& other) {
        if (this != &other) {
            delete[] payload;
            header.payload_len = other.header.payload_len;
            payload = new uint8_t[other.header.payload_len];
            std::memcpy(payload, other.payload, other.header.payload_len);
        }
        return *this;
    }
};

#endif
