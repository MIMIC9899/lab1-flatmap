#include "flat_map.h"
#include <algorithm>
#include <iostream>
// Конструктор по умолчанию
FlatMap::FlatMap() : data_(nullptr), size_(0), capacity_(0) {std::cout << "1";}

// Конструктор копирования
FlatMap::FlatMap(const FlatMap& other_map) : size_(other_map.size_), capacity_(other_map.capacity_) {
    if (capacity_ > 0) {
        data_ = new Pair[capacity_];
        for (std::size_t i = 0; i < size_; ++i) {
            data_[i] = other_map.data_[i];
        }
    } else {
        data_ = nullptr;
    }
}

// Деструктор
FlatMap::~FlatMap() {
    delete[] data_;
}

// Оператор присваивания
FlatMap& FlatMap::operator=(const FlatMap& other_map) {
    if (this != &other_map) {
        FlatMap temp(other_map);
        std::swap(data_, temp.data_);
        std::swap(size_, temp.size_);
        std::swap(capacity_, temp.capacity_);
    }
    return *this;
}

// Бинарный поиск
int FlatMap::binary_search(const std::string& key) const {
    int left = 0;
    int right = size_ - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (data_[mid].key == key) {
            return mid;
        }
        if (data_[mid].key < key) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return -1;
}

// Изменение размера массива
void FlatMap::resize() {
    std::size_t new_capacity = (capacity_ == 0) ? 1 : capacity_ * 2;
    Pair* new_data = new Pair[new_capacity];
    for (std::size_t i = 0; i < size_; ++i) {
        new_data[i] = data_[i];
    }
    delete[] data_;
    data_ = new_data;
    capacity_ = new_capacity;
}

// Оператор доступа по ключу
std::string& FlatMap::operator[](const std::string& key) {
    int pos = binary_search(key);
    if (pos != -1) {
        return data_[pos].value;
    }

    // Если ключ не найден, создаем новый элемент
    if (size_ == capacity_) {
        // Если массив полон, увеличиваем его размер
        resize();
    }

    // Находим позицию для вставки, сохраняя сортировку
    int insert_pos = size_;
    for (int i = size_ - 1; i >= 0; --i) {
        if (data_[i].key > key) {
            data_[i + 1] = data_[i];
            insert_pos = i;
        } else {
            break;
        }
    }

    // Вставляем новый элемент
    data_[insert_pos].key = key;
    data_[insert_pos].value = "";
    ++size_;
    return data_[insert_pos].value;
}

std::size_t FlatMap::size() const {
    return size_;
}

// Проверка наличия ключа
bool FlatMap::contains(const std::string& key) {
    return binary_search(key) != -1;
}

// Удаление элемента по ключу
std::size_t FlatMap::erase(const std::string& key) {
    int pos = binary_search(key);
    if (pos == -1) {
        return 0;
    }

    // Сдвигаем все элементы влево
    for (std::size_t i = pos; i < size_ - 1; ++i) {
        data_[i] = data_[i + 1];
    }
    --size_;
    return 1;
}

// Очистка контейнера
void FlatMap::clear() {
    delete[] data_;
    data_ = nullptr;
    size_ = 0;
    capacity_ = 0;
}