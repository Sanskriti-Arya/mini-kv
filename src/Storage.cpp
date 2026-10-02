#include "Storage.h"

Storage::Storage(const std::string& path) : path_(path) {}

void Storage::load(std::unordered_map<std::string, std::string>& out) {
    std::ifstream in(path_, std::ios::binary);
    std::string op;
    while (in >> op) {
        size_t klen = 0, vlen = 0;
        if (op == "SET") { if (!(in >> klen >> vlen)) break; }
        else if (op == "DEL") { if (!(in >> klen)) break; }
        else break;
        in.get(); // newline
        std::string key(klen, '\0'), val(vlen, '\0');
        if (!in.read(key.data(), klen)) break;          // truncated record: stop
        if (op == "SET" && !in.read(val.data(), vlen)) break;
        in.get(); // trailing newline
        if (op == "SET") out[key] = val; else out.erase(key);
    }
    log_.open(path_, std::ios::binary | std::ios::app);
}

void Storage::appendSet(const std::string& k, const std::string& v) {
    log_ << "SET " << k.size() << ' ' << v.size() << '\n' << k << v << '\n';
    log_.flush();
}

void Storage::appendDel(const std::string& k) {
    log_ << "DEL " << k.size() << '\n' << k << '\n';
    log_.flush();
}
