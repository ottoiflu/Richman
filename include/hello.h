// include/hello.h
#ifndef HELLO_H
#define HELLO_H

#include <string>

class Hello {
public:
    std::string sayHello();
    std::string sayHello(const std::string& name);
    std::string getGreeting();
};

#endif // HELLO_H