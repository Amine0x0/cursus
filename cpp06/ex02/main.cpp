#include "funcs.hpp"
#include <ctime>

int main() {
    std::srand(std::time(NULL));
    
    for (int i = 0; i < 5; i++) {
        Base* obj = generate();
        identify(obj);
        identify(*obj);
        delete obj;
    }
    return 0;
}