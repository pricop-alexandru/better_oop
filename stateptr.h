#include <algorithm>  // For std::swap
#include "interface.h"

class StatePtr {
public:
    // Constructor
    explicit StatePtr(Interface* ptr = nullptr) : ptr_(ptr) {}

    // Destructor
    ~StatePtr() {
        delete ptr_;
    }

    // Getters
    Interface* get() const { return ptr_; }

    // Copy Constructor
    StatePtr(const StatePtr& other) : ptr_(other.ptr_ ? other.ptr_->clone() : nullptr) {}

    // Copy Assignment Operator
    StatePtr& operator=(StatePtr other) {
        swap(*this, other);
        return *this;
    }

    // Swap Function
    friend void swap(StatePtr& first, StatePtr& second) noexcept {
        using std::swap;
        swap(first.ptr_, second.ptr_);
    }

    // Dereference and Arrow Operators
    Interface& operator*() const { return *ptr_; }
    Interface* operator->() const { return ptr_; }

private:
    Interface* ptr_;
};