#include "Data.hpp"
#include "Serializer.hpp"

int main(){
    Data d;

    d.id = 67;
    d.name = "test";

    uintptr_t S = Serializer::serialize(&d);
    
    Data *data = Serializer::deserialize(S);

    std::cout << "id: " << data->id << std::endl;
    std::cout << "name: " << data->name << std::endl;

    std::cout << "original: " << &d << std::endl;
    std::cout << "deserialized: " << data << std::endl;

    if (data == &d) {
        std::cout << "pointers match!" << std::endl;
    } else {
        std::cout << "pointers mismatch!" << std::endl;
    }
}

