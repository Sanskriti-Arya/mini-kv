#pragma once
#include <memory>
#include <optional>
#include <string>
#include <unordered_map>
#include "Storage.h"

class Database {
public:
    // Empty path = in-memory only.
    explicit Database(const std::string& path = "");

    void set(const std::string& key, const std::string& value);
    std::optional<std::string> get(const std::string& key) const;
    bool del(const std::string& key);
    size_t size() const { return table_.size(); }

private:
    std::unordered_map<std::string, std::string> table_;
    std::unique_ptr<Storage> storage_;
};
