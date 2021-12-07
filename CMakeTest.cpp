#include <iostream>
#include <gtest/gtest.h>
#include "hash.h"


using namespace std;


// »нициализаци€ таблиц дл€ дальнейшего тестировани€
class HashTableTest : public::testing::Test
{
protected:

    void SetUp() override
    {
        t1.insert("James", {20, 60 });
        t1.insert("Sara", {19, 65 });
        t1.insert("Olga", {18, 70 });
        t1.insert("Maxim", {21, 85 });
        t1.insert("Petr", { 16, 50 });

        t2.insert("Oleg", {12, 55 });
        t2.insert("Vlad", {14,  60 });
        t2.insert("Andrey", {15, 90 });
        t2.insert("Alex", {20, 95 });
       

    }
    HashTable t0;
    HashTable t1;
    HashTable t2;
};


// ќдин из тестов, провер€ющий перегрузку оператора сравнени€
TEST_F(HashTableTest, SwapWorks) {
    t1.swap(t2);
    EXPECT_EQ(t1.size(), 3);
    EXPECT_EQ(t2.size(), 2);
    EXPECT_EQ(t2["James"].weight, 60);
}
TEST_F(HashTableTest, EraseWorks) {
    bool r = t2.erase("Vlad");
    EXPECT_EQ(r, true);
}
TEST_F(HashTableTest, EmptyWorks) {
    bool r = t1.empty();
    EXPECT_EQ(r, false);
    r = t0.empty();
    EXPECT_EQ(r, true);
}
TEST_F(HashTableTest, ContainsWorks) {
    bool r = t1.contains("Maxim");
    EXPECT_EQ(r, true);
    r = t1.contains("Fedoruk");
    EXPECT_EQ(r, false);
}
TEST_F(HashTableTest, AtWorks) {
    Value& s = t1.at("Sara");
    EXPECT_EQ(s.weight, 65);
    ASSERT_ANY_THROW(t1.at("try_to_break_my_table"));
}
TEST_F(HashTableTest, OperatorsWork) {
    bool r1 = t1 == t2;
    EXPECT_EQ(r1, false);
    bool r2 = t1 != t2;
    EXPECT_EQ(r2, true);
    unsigned int r3 = t2["Alex"].weight;
    EXPECT_EQ(r3, 95);
    t1 = t2;
    r1 = t1 == t2;
    EXPECT_EQ(r1, true);
}
TEST_F(HashTableTest, CopyConstructWorks) {
    HashTable t3 = t1;
    EXPECT_EQ(t3.size(), 2);
    bool r0 = t3.contains("Petr");
    EXPECT_EQ(r0, true);
    bool r2 = t3.contains("Andrey");
    EXPECT_EQ(r2, false);

}
TEST_F(HashTableTest, MoveConstructWorks) {
    HashTable t4 = std::move(t2);

    bool r0 = t4.contains("Vlad");
    bool r1 = t4.contains("Andrey");
    bool r2 = t4.contains("Alex");
    bool r3 = t2.empty();
    EXPECT_EQ(r0, true);
    EXPECT_EQ(r1, true);
    EXPECT_EQ(r2, true);
    EXPECT_EQ(r3, true);
}