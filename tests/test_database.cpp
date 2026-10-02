#include <cstdio>
#include <iostream>
#include "Database.h"

static int failures = 0;
#define CHECK(c) do { if (!(c)) { std::cerr << "FAIL line " << __LINE__ << ": " #c "\n"; ++failures; } } while (0)

void test_basic() {
    Database db;
    db.set("name", "Sia");
    CHECK(db.get("name") == "Sia");
    db.set("name", "Ana");
    CHECK(db.get("name") == "Ana");
    CHECK(!db.get("missing"));
    CHECK(db.del("name"));
    CHECK(!db.del("name"));
    CHECK(!db.get("name"));
}

void test_persistence() {
    const char* path = "test_tmp.db";
    std::remove(path);
    {
        Database db(path);
        db.set("age", "21");
        db.set("bio", "likes C++\nand spaces");
        db.set("gone", "x");
        db.del("gone");
    }
    Database db2(path);
    CHECK(db2.get("age") == "21");
    CHECK(db2.get("bio") == "likes C++\nand spaces");
    CHECK(!db2.get("gone"));
    CHECK(db2.size() == 2);
    std::remove(path);
}

int main() {
    test_basic();
    test_persistence();
    std::cout << (failures ? "FAILED\n" : "All tests passed\n");
    return failures;
}
