// src/hello.c
#include "hello.h"

void hello_say_hello(char* buffer, size_t buffer_size) {
    if (buffer && buffer_size > 0) {
        strncpy(buffer, "Hello, World!", buffer_size - 1);
        buffer[buffer_size - 1] = '\0'; // 确保字符串结束
    }
}

void hello_say_hello_with_name(char* buffer, size_t buffer_size, const char* name) {
    if (buffer && buffer_size > 0 && name) {
        snprintf(buffer, buffer_size, "Hello, %s!", name);
    }
}

void hello_get_greeting(char* buffer, size_t buffer_size) {
    if (buffer && buffer_size > 0) {
        strncpy(buffer, "Greetings from TDD!", buffer_size - 1);
        buffer[buffer_size - 1] = '\0'; // 确保字符串结束
    }
}

void hello_get_version(char* buffer, size_t buffer_size) {
    if (buffer && buffer_size > 0) {
        snprintf(buffer, buffer_size, "Rich v1.0.0 - 大富翁程序集成测试版");
    }
}