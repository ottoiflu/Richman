// tests/test_hello.cpp
#include "gtest/gtest.h"
#include "hello.h"

TEST(HelloTest, SayHello) {
    Hello hello;
    EXPECT_EQ(hello.sayHello(), "Hello, World!");
}

TEST(HelloTest, SayHelloWithName) {
    Hello hello;
    EXPECT_EQ(hello.sayHello("Alice"), "Hello, Alice!");
    EXPECT_EQ(hello.sayHello("Bob"), "Hello, Bob!");
}

TEST(HelloTest, GetGreeting) {
    Hello hello;
    EXPECT_EQ(hello.getGreeting(), "Greetings from TDD!");
}