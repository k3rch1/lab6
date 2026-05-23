#pragma once

#include "stack.hpp"
#include "array_sequence.hpp"
#include "list_sequence.hpp" 
#include "sequence.hpp"

template<class T>
class sequence_stack : public stack<T> {
private:
    sequence<T>* items;
public:
    explicit sequence_stack(sequence<T>* data);

    sequence_stack(const sequence_stack& other);
    sequence_stack(sequence_stack&& other) noexcept;

    sequence_stack& operator=(const sequence_stack& other);
    sequence_stack& operator=(sequence_stack&& other) noexcept;

    ~sequence_stack() override;

    size_t size() const noexcept override;
    bool empty() const noexcept override;

    T& top() override;
    const T& top() const override;

    void push(const T& value) override;
    void push(T&& value) override;

    void pop() override;
    void clear() override;
};

template<class T>
sequence_stack<T>::sequence_stack(sequence<T>* data) : items(data) {}

template<class T>
sequence_stack<T>::sequence_stack(const sequence_stack& other) {
    if (auto* arr = dynamic_cast<array_sequence<T>*>(other.items)) items = new array_sequence<T>(*arr);
    else if (auto* list = dynamic_cast<list_sequence<T>*>(other.items)) items = new list_sequence<T>(*list);
    else throw std::runtime_error("unknown sequence type");
}

template<class T>
sequence_stack<T>::sequence_stack(sequence_stack&& other) noexcept : items(other.items) {
    other.items = nullptr;
}

template<class T>
sequence_stack<T>&
sequence_stack<T>::operator=(const sequence_stack& other) {
    if (this == &other) return *this;
    delete items;

    if (auto* arr = dynamic_cast<array_sequence<T>*>(other.items)) items = new array_sequence<T>(*arr);
    else if (auto* list = dynamic_cast<list_sequence<T>*>(other.items)) items = new list_sequence<T>(*list);
    else throw std::runtime_error("unknown sequence type");

    return *this;
}

template<class T>
sequence_stack<T>& sequence_stack<T>::operator=(sequence_stack&& other) noexcept {
    if (this == &other) return *this;
    delete items;

    items = other.items;
    other.items = nullptr;

    return *this;
}

template<class T>
sequence_stack<T>::~sequence_stack() {
    delete items;
}

template<class T>
size_t sequence_stack<T>::size() const noexcept {
    return items->size();
}

template<class T>
bool sequence_stack<T>::empty() const noexcept {
    return items->empty();
}

template<class T>
T& sequence_stack<T>::top() {
    return items->back();
}

template<class T>
const T& sequence_stack<T>::top() const {
    return items->back();
}

template<class T>
void sequence_stack<T>::push(const T& value) {
    items->append(value);
}

template<class T>
void sequence_stack<T>::push(T&& value) {
    items->append(std::move(value));
}

template<class T>
void sequence_stack<T>::pop() {
    if (empty()) throw std::out_of_range("seq empty");
    items->remove(size() - 1);
}

template<class T>
void sequence_stack<T>::clear() {
    items->clear();
}