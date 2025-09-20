// tests/test_hello.c
#include "test_framework.h"
#include "hello.h"

TEST(HelloTest, SayHello) {
    char buffer[100];
    hello_say_hello(buffer, sizeof(buffer));
    EXPECT_STREQ("Hello, World!", buffer);
}

TEST(HelloTest, SayHelloWithName) {
    char buffer[100];
    
    hello_say_hello_with_name(buffer, sizeof(buffer), "Alice");
    EXPECT_STREQ("Hello, Alice!", buffer);
    
    hello_say_hello_with_name(buffer, sizeof(buffer), "Bob");
    EXPECT_STREQ("Hello, Bob!", buffer);
}

TEST(HelloTest, GetGreeting) {
    char buffer[100];
    hello_get_greeting(buffer, sizeof(buffer));
    EXPECT_STREQ("Greetings from TDD!", buffer);
}