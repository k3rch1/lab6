#pragma once

template<class T>
class stack {
public:
    virtual ~stack() = default;

    virtual size_t size() const noexcept = 0;
    virtual bool empty() const noexcept = 0;

    virtual T& top() = 0;
    virtual const T& top() const = 0;

    virtual void push(const T& value) = 0;
    virtual void push(T&& value) = 0;

    virtual void pop() = 0;
    virtual void clear() = 0;
};