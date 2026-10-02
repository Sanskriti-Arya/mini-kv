#pragma once
#include <fstream>
#include <string>
#include <unordered_map>

// Append-only log. Each record is length-prefixed so values may contain spaces/newlines:
//   SET <klen> <vlen>\n<key><value>\n
//   DEL <klen>\n<key>\n
class Storage {
public:
    explicit Storage(const std::string& path);
    void load(std::unordered_map<std::string, std::string>& out);
    void appendSet(const std::string& key, const std::string& value);
    void appendDel(const std::string& key);

private:
    std::string path_;
    std::ofstream log_;
};
