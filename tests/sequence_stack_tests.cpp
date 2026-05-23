#include <gtest/gtest.h>
#include "sequence_stack.hpp"
#include "array_sequence.hpp"
#include "list_sequence.hpp"

TEST(sequence_stack, copy_ctor_array) {
    sequence_stack<int> st1(new array_sequence<int>);

    st1.push(1);
    st1.push(2);

    sequence_stack<int> st2(st1);

    ASSERT_EQ(st2.top(), 2);
    ASSERT_EQ(st2.size(), 2);

    st1.pop();

    ASSERT_EQ(st1.top(), 1);
    ASSERT_EQ(st2.top(), 2);
}

TEST(sequence_stack, move_ctor_array) {
    sequence_stack<int> st1(new array_sequence<int>);

    st1.push(1);
    st1.push(2);

    sequence_stack<int> st2(std::move(st1));

    ASSERT_EQ(st2.top(), 2);
    ASSERT_EQ(st2.size(), 2);
}

TEST(sequence_stack, push_array) {
    sequence_stack<int> st(new array_sequence<int>);

    for(auto i = 1; i < 4; ++i) st.push(i);

    ASSERT_EQ(st.size(), 3);
}

TEST(sequence_stack, top_array) {
    sequence_stack<int> st(new array_sequence<int>);

    for(auto i = 1; i < 4; ++i) st.push(i);

    ASSERT_EQ(st.top(), 3);
}

TEST(sequence_stack, pop_array) {
    sequence_stack<int> st(new array_sequence<int>);

    st.push(1);
    st.push(2);

    st.pop();

    ASSERT_EQ(st.top(), 1);
    ASSERT_EQ(st.size(), 1);
}

TEST(sequence_stack, empty_array) {
    sequence_stack<int> st(new array_sequence<int>);

    ASSERT_TRUE(st.empty());

    st.push(1);

    ASSERT_FALSE(st.empty());
}

TEST(sequence_stack, clear_array) {
    sequence_stack<int> st(new array_sequence<int>);

    for(auto i = 1; i < 4; ++i) st.push(i);

    st.clear();

    ASSERT_TRUE(st.empty());
}

TEST(sequence_stack, copy_ctor_list) {
    sequence_stack<int> st1(new list_sequence<int>);

    st1.push(1);
    st1.push(2);

    sequence_stack<int> st2(st1);

    ASSERT_EQ(st2.top(), 2);
    ASSERT_EQ(st2.size(), 2);

    st1.pop();

    ASSERT_EQ(st1.top(), 1);
    ASSERT_EQ(st2.top(), 2);
}

TEST(sequence_stack, move_ctor_list) {
    sequence_stack<int> st1(new list_sequence<int>);

    st1.push(1);
    st1.push(2);

    sequence_stack<int> st2(std::move(st1));

    ASSERT_EQ(st2.top(), 2);
    ASSERT_EQ(st2.size(), 2);
}

TEST(sequence_stack, push_list) {
    sequence_stack<int> st(new list_sequence<int>);

    for(auto i = 1; i < 4; ++i) st.push(i);

    ASSERT_EQ(st.size(), 3);
}

TEST(sequence_stack, top_list) {
    sequence_stack<int> st(new list_sequence<int>);

    for(auto i = 1; i < 4; ++i) st.push(i);

    ASSERT_EQ(st.top(), 3);
}

TEST(sequence_stack, pop_list) {
    sequence_stack<int> st(new list_sequence<int>);

    st.push(1);
    st.push(2);

    st.pop();

    ASSERT_EQ(st.top(), 1);
    ASSERT_EQ(st.size(), 1);
}

TEST(sequence_stack, empty_list) {
    sequence_stack<int> st(new list_sequence<int>);

    ASSERT_TRUE(st.empty());

    st.push(1);

    ASSERT_FALSE(st.empty());
}

TEST(sequence_stack, clear_list) {
    sequence_stack<int> st(new list_sequence<int>);

    for(auto i = 1; i < 4; ++i) st.push(i);

    st.clear();

    ASSERT_TRUE(st.empty());
}