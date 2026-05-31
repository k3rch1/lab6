#include <gtest/gtest.h>
#include "stack.hpp"
#include "array_sequence.hpp"
#include "list_sequence.hpp"

TEST(stack, dctor_array) {
    stack<array_sequence, int> st;

    ASSERT_EQ(st.size(), 0);
}

TEST(stack, copy_ctor_array) {
    stack<array_sequence, int> st1;

    st1.push(1);
    st1.push(2);

    stack<array_sequence, int> st2(st1);

    ASSERT_EQ(st2.top(), 2);
    ASSERT_EQ(st2.size(), 2);

    st1.pop();

    ASSERT_EQ(st1.top(), 1);
    ASSERT_EQ(st2.top(), 2);
}

TEST(stack, move_ctor_array) {
    stack<array_sequence, int> st1;

    st1.push(1);
    st1.push(2);

    stack<array_sequence, int> st2(std::move(st1));

    ASSERT_EQ(st2.top(), 2);
    ASSERT_EQ(st2.size(), 2);
}

TEST(stack, push_array) {
    stack<array_sequence, int> st;

    for(auto i = 1; i < 4; ++i) st.push(i);

    ASSERT_EQ(st.size(), 3);
}

TEST(stack, top_array) {
    stack<array_sequence, int> st;

    for(auto i = 1; i < 4; ++i) st.push(i);

    ASSERT_EQ(st.top(), 3);
}

TEST(stack, pop_array) {
    stack<array_sequence, int> st;

    st.push(1);
    st.push(2);

    st.pop();

    ASSERT_EQ(st.top(), 1);
    ASSERT_EQ(st.size(), 1);
}

TEST(stack, empty_array) {
    stack<array_sequence, int> st;

    ASSERT_TRUE(st.empty());

    st.push(1);

    ASSERT_FALSE(st.empty());
}

TEST(stack, clear_array) {
    stack<array_sequence, int> st;

    for(auto i = 1; i < 4; ++i) st.push(i);

    st.clear();

    ASSERT_TRUE(st.empty());
}

TEST(stack, dctor_list) {
    stack<list_sequence, int> st;

    ASSERT_EQ(st.size(), 0);
}

TEST(stack, copy_ctor_list) {
    stack<list_sequence, int> st1;

    st1.push(1);
    st1.push(2);

    stack<list_sequence, int> st2(st1);

    ASSERT_EQ(st2.top(), 2);
    ASSERT_EQ(st2.size(), 2);

    st1.pop();

    ASSERT_EQ(st1.top(), 1);
    ASSERT_EQ(st2.top(), 2);
}

TEST(stack, move_ctor_list) {
    stack<list_sequence, int> st1;

    st1.push(1);
    st1.push(2);

    stack<list_sequence, int> st2(std::move(st1));

    ASSERT_EQ(st2.top(), 2);
    ASSERT_EQ(st2.size(), 2);
}

TEST(stack, push_list) {
    stack<list_sequence, int> st;

    for(auto i = 1; i < 4; ++i) st.push(i);

    ASSERT_EQ(st.size(), 3);
}

TEST(stack, top_list) {
    stack<list_sequence, int> st;

    for(auto i = 1; i < 4; ++i) st.push(i);

    ASSERT_EQ(st.top(), 3);
}

TEST(stack, pop_list) {
    stack<list_sequence, int> st;

    st.push(1);
    st.push(2);

    st.pop();

    ASSERT_EQ(st.top(), 1);
    ASSERT_EQ(st.size(), 1);
}

TEST(stack, empty_list) {
    stack<list_sequence, int> st;

    ASSERT_TRUE(st.empty());

    st.push(1);

    ASSERT_FALSE(st.empty());
}

TEST(stack, clear_list) {
    stack<list_sequence, int> st;

    for(auto i = 1; i < 4; ++i) st.push(i);

    st.clear();

    ASSERT_TRUE(st.empty());
}