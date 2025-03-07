#include "Serializer.hpp"

Serializer::Serializer() {}
Serializer::Serializer(Serializer& copy) { (void)copy; }
Serializer& Serializer::operator=(Serializer& ref) { 
    (void)ref;
    return *this; 
}
Serializer::~Serializer() {}

uintptr_t Serializer::serialize(Data* ptr) {
    uint8_t* serialized_data = new uint8_t[sizeof(Header) + ptr->header.payload_len];

    // 헤더 복사
    std::memcpy(serialized_data, &(ptr->header), sizeof(Header));

    // 페이로드 복사
    std::memcpy(serialized_data + sizeof(Header), ptr->payload, ptr->header.payload_len);

    return reinterpret_cast<uintptr_t>(serialized_data);
}

Data* Serializer::deserialize(uintptr_t raw) {
    uint8_t* serialized_data = reinterpret_cast<uint8_t*>(raw);

    // 헤더 복사
    Header header;
    std::memcpy(&header, serialized_data, sizeof(Header));

    // Data 객체 생성
    Data* data = new Data(header.payload_len);

    // 헤더 설정
    std::memcpy(&(data->header), &header, sizeof(Header));

    // 페이로드 복사
    std::memcpy(data->payload, serialized_data + sizeof(Header), header.payload_len);

    return data;
}
