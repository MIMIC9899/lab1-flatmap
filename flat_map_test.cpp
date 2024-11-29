#include <gtest/gtest.h>
#include "flat_map.h"
#include <string>
#include <vector>

class FlatMapTest : public ::testing::Test {
protected:
    FlatMap map;
};

// 1. Тест конструктора по умолчанию
TEST_F(FlatMapTest, DefaultConstructor) {
    EXPECT_FALSE(map.contains("test"));
}

// 2. Тест вставки и доступа к элементам
TEST_F(FlatMapTest, InsertionAndAccess) {
    map["key1"] = "value1";
    EXPECT_TRUE(map.contains("key1"));
    EXPECT_EQ(map["key1"], "value1");
}

// 3. Тест перезаписи значения
TEST_F(FlatMapTest, ValueOverwrite) {
    map["key1"] = "value1";
    map["key1"] = "value2";
    EXPECT_EQ(map["key1"], "value2");
}

// 4. Тест удаления элемента
TEST_F(FlatMapTest, EraseElement) {
    map["key1"] = "value1";
    EXPECT_EQ(map.erase("key1"), 1);
    EXPECT_FALSE(map.contains("key1"));
}

// 5. Тест удаления несуществующего элемента
TEST_F(FlatMapTest, EraseNonexistentElement) {
    EXPECT_EQ(map.erase("nonexistent"), 0);
}

// 6. Тест очистки контейнера
TEST_F(FlatMapTest, ClearContainer) {
    map["key1"] = "value1";
    map["key2"] = "value2";
    map.clear();
    EXPECT_FALSE(map.contains("key1"));
    EXPECT_FALSE(map.contains("key2"));
}

// 7. Тест конструктора копирования
TEST_F(FlatMapTest, CopyConstructor) {
    map["key1"] = "value1";
    map["key2"] = "value2";

    FlatMap map2(map);
    EXPECT_TRUE(map.contains("key1"));
    EXPECT_TRUE(map.contains("key2"));
    EXPECT_EQ(map["key1"], "value1");
    EXPECT_EQ(map["key2"], "value2");
    EXPECT_TRUE(map2.contains("key1"));
    EXPECT_TRUE(map2.contains("key2"));
    EXPECT_EQ(map2["key1"], "value1");
    EXPECT_EQ(map2["key2"], "value2");
}

// 8. Тест оператора присваивания
TEST_F(FlatMapTest, AssignmentOperator) {
    map["key1"] = "value1";
    FlatMap map2;
    map2 = map;
    EXPECT_TRUE(map2.contains("key1"));
    EXPECT_EQ(map2["key1"], "value1");
    EXPECT_TRUE(map.contains("key1"));
    EXPECT_EQ(map["key1"], "value1");
}

// 9. Тест проверки размера
TEST_F(FlatMapTest, SizeCheck) {
    std::vector<std::string> keys = {"key1", "key2", "key3", "key4", "key5"};
    for (const std::string& key : keys) {
        map[key] = "value_" + key;
    }

    EXPECT_EQ(map.size(), 5);
}

// 10. Тест сортировки ключей
TEST_F(FlatMapTest, KeyOrdering) {
    map["c"] = "3";
    map["a"] = "1";
    map["b"] = "2";

    Iterator it = map.begin();
    EXPECT_EQ((*it).key, "a");
    ++it;
    EXPECT_EQ((*it).key, "b");
    ++it;
    EXPECT_EQ((*it).key, "c");
}

// 11. Тест итераторов
TEST_F(FlatMapTest, IteratorTest) {
    map["a"] = "1";
    map["b"] = "2";
    map["c"] = "3";

    Iterator it = map.begin();
    EXPECT_EQ((*it).value, "1");
    ++it;
    EXPECT_EQ((*it).value, "2");
    ++it;
    EXPECT_EQ((*it).value, "3");
    ++it;
    EXPECT_EQ(it, map.end());
}

// 12. Тест обратного обхода итератором
TEST_F(FlatMapTest, ReverseIteratorTest) {
    map["a"] = "1";
    map["b"] = "2";
    map["c"] = "3";

    Iterator it = map.end();
    --it;
    EXPECT_EQ((*it).value, "3");
    --it;
    EXPECT_EQ((*it).value, "2");
    --it;
    EXPECT_EQ((*it).value, "1");
}

// 13. Тест на стресс с большим количеством элементов
TEST_F(FlatMapTest, StressTest) {
    const int COUNT = 1000;
    for (int i = 0; i < COUNT; ++i) {
        map[std::to_string(i)] = "value" + std::to_string(i);
    }

    for (int i = 0; i < COUNT; ++i) {
        EXPECT_TRUE(map.contains(std::to_string(i)));
        EXPECT_EQ(map[std::to_string(i)], "value" + std::to_string(i));
    }
}

// 14. Тест на удаление всех элементов через erase
TEST_F(FlatMapTest, EraseAllElements) {
    map["a"] = "1";
    map["b"] = "2";
    map["c"] = "3";

    EXPECT_EQ(map.erase("a"), 1);
    EXPECT_EQ(map.erase("b"), 1);
    EXPECT_EQ(map.erase("c"), 1);

    Iterator it = map.begin();
    EXPECT_EQ(it, map.end());
}

// 15. Тест на работу с пустыми строками
TEST_F(FlatMapTest, EmptyStrings) {
    map[""] = "";
    EXPECT_TRUE(map.contains(""));
    EXPECT_EQ(map[""], "");
}

// 16. Тест на последовательное обновление значений
TEST_F(FlatMapTest, SequentialUpdates) {
    map["key"] = "value1";
    EXPECT_EQ(map["key"], "value1");

    map["key"] = "value2";
    EXPECT_EQ(map["key"], "value2");

    map["key"] = "value3";
    EXPECT_EQ(map["key"], "value3");
}

// 17. Тест на сравнение итераторов
TEST_F(FlatMapTest, IteratorComparison) {
    map["a"] = "1";
    map["b"] = "2";

    Iterator it1 = map.begin();
    Iterator it2 = map.begin();

    EXPECT_TRUE(it1 == it2);
    EXPECT_FALSE(it1 != it2);

    ++it1;
    EXPECT_FALSE(it1 == it2);
    EXPECT_TRUE(it1 != it2);
}

// 18. Тест на копирование с последующей модификацией
TEST_F(FlatMapTest, CopyAndModify) {
    map["key1"] = "value1";
    FlatMap map2 = map;

    map2["key1"] = "value2";
    EXPECT_EQ(map["key1"], "value1");
    EXPECT_EQ(map2["key1"], "value2");
}

// 19. Тест на работу с русскими символами
TEST_F(FlatMapTest, RussianCharacters) {
    map["привет"] = "мир";
    EXPECT_TRUE(map.contains("привет"));
    EXPECT_EQ(map["привет"], "мир");
}

// 20. Тест на множественные операции
TEST_F(FlatMapTest, MultipleOperations) {
    map["a"] = "1";
    map["b"] = "2";
    map["c"] = "3";

    EXPECT_EQ(map.erase("b"), 1);
    map["d"] = "4";
    map["b"] = "5";

    EXPECT_EQ(map["a"], "1");
    EXPECT_EQ(map["b"], "5");
    EXPECT_EQ(map["c"], "3");
    EXPECT_EQ(map["d"], "4");
}