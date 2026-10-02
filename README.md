# mini-kv

A tiny Redis-like key-value store in C++17.

## Build
    cmake -S . -B build && cmake --build build
    ctest --test-dir build --output-on-failure

## Run
    ./build/mini-kv [datafile]     # default: data.db

    > SET name Sia
    OK
    > GET name
    Sia
    > DELETE name
    OK
    > GET name
    NOT_FOUND
    > BENCH 1000000

## Design
- `Database`: `unordered_map` hash table + public API (set/get/del).
- `Storage`: append-only, length-prefixed log, replayed on startup.
