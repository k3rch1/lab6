#pragma once
#include <cstddef>
#include <concepts>
#include <utility>

template<template<class> class container, class T>
concept stack_container = requires(container<T> c, T v) {
    { c.size() } -> std::same_as<size_t>;
    { c.empty() } -> std::same_as<bool>;
    { c.back() } -> std::same_as<T&>;
    c.append(v);
    c.append(std::move(v));
    c.remove(size_t{0});
    c.clear();
};

template<template<class> class container, class T>
requires stack_container<container, T>
class stack {
private:
    container<T> items;

public:
    size_t size() const noexcept;
    bool empty() const noexcept;

    T& top();
    const T& top() const;

    void push(const T& value);
    void push(T&& value);

    void pop();
    void clear();
};

template<template<class> class container, class T>
requires stack_container<container, T>
size_t stack<container, T>::size() const noexcept {
    return items.size();
}

template<template<class> class container, class T>
requires stack_container<container, T>
bool stack<container, T>::empty() const noexcept {
    return items.empty();
}

template<template<class> class container, class T>
requires stack_container<container, T>
T& stack<container, T>::top() {
    return items.back();
}

template<template<class> class container, class T>
requires stack_container<container, T>
const T& stack<container, T>::top() const {
    return items.back();
}

template<template<class> class container, class T>
requires stack_container<container, T>
void stack<container, T>::push(const T& value) {
    items.append(value);
}

template<template<class> class container, class T>
requires stack_container<container, T>
void stack<container, T>::push(T&& value) {
    items.append(std::move(value));
}

template<template<class> class container, class T>
requires stack_container<container, T>
void stack<container, T>::pop() {
    if (empty()) throw std::out_of_range("seq empty");
    items.remove(size() - 1);
}

template<template<class> class container, class T>
requires stack_container<container, T>
void stack<container, T>::clear() {
    items.clear();
}