#include "Database.h"

Database::Database(const std::string& path) {
    if (!path.empty()) {
        storage_ = std::make_unique<Storage>(path);
        storage_->load(table_);
    }
}

void Database::set(const std::string& key, const std::string& value) {
    table_[key] = value;
    if (storage_) storage_->appendSet(key, value);
}

std::optional<std::string> Database::get(const std::string& key) const {
    auto it = table_.find(key);
    if (it == table_.end()) return std::nullopt;
    return it->second;
}

bool Database::del(const std::string& key) {
    bool removed = table_.erase(key) > 0;
    if (removed && storage_) storage_->appendDel(key);
    return removed;
}
