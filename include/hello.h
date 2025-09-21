// include/hello.h
#ifndef HELLO_H
#define HELLO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

// 问候功能函数声明
// 注意：C语言中我们使用字符数组而不是std::string
void hello_say_hello(char* buffer, size_t buffer_size);
void hello_say_hello_with_name(char* buffer, size_t buffer_size, const char* name);
void hello_get_greeting(char* buffer, size_t buffer_size);

// 版本信息功能函数声明 - 新功能示例
void hello_get_version(char* buffer, size_t buffer_size);

#ifdef __cplusplus
}
#endif

#endif /* HELLO_H */