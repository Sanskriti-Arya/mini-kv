#include <chrono>
#include <iostream>
#include <sstream>
#include "Database.h"

static void bench(size_t n) {
    using clk = std::chrono::steady_clock;
    Database db; // in-memory: measures the hash table, not the disk
    auto t0 = clk::now();
    for (size_t i = 0; i < n; ++i) db.set("key" + std::to_string(i), "value" + std::to_string(i));
    auto t1 = clk::now();
    size_t hits = 0;
    for (size_t i = 0; i < n; ++i) hits += db.get("key" + std::to_string(i)).has_value();
    auto t2 = clk::now();
    auto sec = [](auto a, auto b) { return std::chrono::duration<double>(b - a).count(); };
    std::cout << "SET: " << static_cast<size_t>(n / sec(t0, t1)) << " ops/s\n"
              << "GET: " << static_cast<size_t>(n / sec(t1, t2)) << " ops/s (" << hits << " hits)\n";
}

int main(int argc, char** argv) {
    Database db(argc > 1 ? argv[1] : "data.db");
    std::string line;
    while (std::cout << "> " && std::getline(std::cin, line)) {
        std::istringstream ss(line);
        std::string cmd, key;
        ss >> cmd >> key;
        for (auto& c : cmd) c = std::toupper(c);
        if (cmd == "SET") {
            std::string value;
            std::getline(ss >> std::ws, value);
            if (key.empty() || value.empty()) std::cout << "ERR usage: SET key value\n";
            else { db.set(key, value); std::cout << "OK\n"; }
        } else if (cmd == "GET") {
            auto v = db.get(key);
            std::cout << (v ? *v : "NOT_FOUND") << '\n';
        } else if (cmd == "DELETE" || cmd == "DEL") {
            std::cout << (db.del(key) ? "OK" : "NOT_FOUND") << '\n';
        } else if (cmd == "BENCH") {
            bench(key.empty() ? 1000000 : std::stoul(key));
        } else if (cmd == "EXIT" || cmd == "QUIT") {
            break;
        } else if (!cmd.empty()) {
            std::cout << "ERR unknown command\n";
        }
    }
}
