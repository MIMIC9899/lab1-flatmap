#pragma once
#include <string>
#include "pair.h"
#include "flat_map_iterator.h"

class FlatMap {
private:
    Pair* data_;
    std::size_t size_;
    std::size_t capacity_;

    int binary_search(const std::string& key) const;
public:
    // стандартный конструктор
    FlatMap();
    // конструктор копирования
    FlatMap(const FlatMap& other_map);
    // деструктор
    ~FlatMap();
    // оператор присваивания
    FlatMap& operator=(const FlatMap& other_map);
    // доступ / вставка элемента по ключу
    std::string& operator[](const std::string& key);
    // получить количество элементов в таблице
    std::size_t size() const;
    // возвращает true, если запись с таким ключом присутствует в таблице
    bool contains(const std::string& key);
    // удаление элемента по ключу, возвращает количество удаленных элементов (0 или 1)
    std::size_t erase(const std::string& key);
    // очистка таблицы, после которой size() возвращает 0, а contains() - false на любой ключ
    void clear();

    void resize();
    Iterator begin() { return (data_); }
    Iterator end() { return {data_ + size_}; }

};
