#include <initializer_list>
#include <algorithm>
#include <stdexcept>


class IntVector {
public:
    IntVector() : size_(0), capacity_(0), data_(nullptr) {}

    explicit IntVector(size_t size) : size_(size), capacity_(size), data_(new int[size]()) {}

    explicit IntVector(std::initializer_list<int> init)
        : size_(init.size()), capacity_(init.size()), data_(new int[init.size()]) {
        std::copy(init.begin(), init.end(), data_);
    }

    explicit IntVector(const IntVector& other)
        : size_(other.size_), capacity_(other.capacity_), data_(new int[other.capacity_]) {
        std::copy(other.data_, other.data_ + other.size_, data_);
    }

    explicit IntVector(IntVector&& other) noexcept
        : size_(other.size_), capacity_(other.capacity_), data_(other.data_) {
        other.size_ = 0;
        other.capacity_ = 0;
        other.data_ = nullptr;
    }

    IntVector& operator=(const IntVector& other) {
        if (this != &other) {
            IntVector temp(other);  // Используем идиому Copy-and-Swap
            Swap(temp);
        }
        return *this;
    }

    IntVector& operator=(IntVector&& other) noexcept {
        if (this != &other) {
            delete[] data_;  // Освобождаем старую память
            data_ = other.data_;
            size_ = other.size_;
            capacity_ = other.capacity_;
            other.data_ = nullptr;
            other.size_ = 0;
            other.capacity_ = 0;
        }
        return *this;
    }

    ~IntVector() {
        delete[] data_;
    }

    void Swap(IntVector& other) noexcept {
        std::swap(size_, other.size_);
        std::swap(capacity_, other.capacity_);
        std::swap(data_, other.data_);
    }

    int& operator[](size_t index) {
        if (index >= size_) {
            throw std::out_of_range("Index out of bounds");
        }
        return data_[index];
    }

    const int& operator[](size_t index) const {
        if (index >= size_) {
            throw std::out_of_range("Index out of bounds");
        }
        return data_[index];
    }

    size_t Size() const {
        return size_;
    }

    size_t Capacity() const {
        return capacity_;
    }

    void PushBack(int value) {
        if (size_ == capacity_) {
            Reserve(capacity_ == 0 ? 1 : capacity_ * 2);
        }
        data_[size_++] = value;
    }

    void PopBack() {
        if (size_ == 0) {
            throw std::underflow_error("Cannot pop from an empty vector");
        }
        --size_;
    }

    void Clear() {
        size_ = 0;
    }

    void Reserve(size_t new_capacity) {
        if (new_capacity <= capacity_) {
            return;
        }
        int* new_data = new int[new_capacity];
        std::copy(data_, data_ + size_, new_data);
        delete[] data_;
        data_ = new_data;
        capacity_ = new_capacity;
    }

private:
    size_t size_;
    size_t capacity_;
    int* data_;
};
