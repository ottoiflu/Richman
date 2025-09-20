// src/hello.cpp
#include "hello.h"

std::string Hello::sayHello() {
    return "Hello, World!";
}

std::string Hello::sayHello(const std::string& name) {
    return "Hello, " + name + "!";
}

std::string Hello::getGreeting() {
    return "Greetings from TDD!";
}