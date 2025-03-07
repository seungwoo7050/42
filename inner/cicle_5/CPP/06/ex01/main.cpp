#include <iostream>
#include "Serializer.hpp"
#include "Data.hpp"

void printData(const Data& data, const std::string& msg) {
    std::cout << msg << std::endl;
    std::cout << "Payload length: " << data.header.payload_len << std::endl;
    std::cout << "Payload data: ";
    for (uint32_t i = 0; i < data.header.payload_len; ++i) {
        std::cout << static_cast<int>(data.payload[i]) << " ";
    }
    std::cout << std::endl;
}

int main() {
    uint32_t payload_len = 10;
    Data data(payload_len);

    // 페이로드 데이터 설정
    for (uint32_t i = 0; i < payload_len; ++i) {
        data.payload[i] = i;
    }

    // 직렬화하기 전 데이터 출력
    printData(data, "Before serialization:");

    // Data 객체의 주소를 직렬화
    uintptr_t raw = Serializer::serialize(&data);

    // 직렬화한 데이터 출력 (raw 값을 직접 출력)
    std::cout << "Serialized data (uintptr_t): " << raw << std::endl;

    // 직렬화된 데이터를 역직렬화
    Data* deserializedData = Serializer::deserialize(raw);

    // 역직렬화한 후 데이터 출력
    printData(*deserializedData, "After deserialization:");

    // 역직렬화된 데이터가 원본 데이터와 같은지 확인
    bool is_equal = (deserializedData->header.payload_len == data.header.payload_len);
    for (uint32_t i = 0; i < payload_len && is_equal; ++i) {
        if (deserializedData->payload[i] != data.payload[i]) {
            is_equal = false;
        }
    }

    if (is_equal) {
        std::cout << "Deserialization successful!" << std::endl;
    } else {
        std::cout << "Deserialization failed!" << std::endl;
    }

    // 동적으로 할당된 메모리 해제
    delete[] reinterpret_cast<uint8_t*>(raw);
    delete deserializedData;

    return 0;
}
