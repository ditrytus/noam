#pragma once

#include <memory>

template<typename T>
class Clonable {
public:
    virtual std::unique_ptr<T> clone() const = 0;
};