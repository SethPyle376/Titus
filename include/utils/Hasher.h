//
// Created by Seth Pyle on 9/25/20.
//

#ifndef TITUS_HASHER_H
#define TITUS_HASHER_H

#include <cstdint>
#include <cstddef>

class Hasher {
private:
    uint64_t hash = 0xcbf29ce484222325ull;
public:
    template <typename T>
    inline void data(const T* data, size_t size) {
      size /= sizeof(*data);
      for (size_t i = 0; i < size; i++)
        hash = (hash * 0x104217461b3ull) ^ data[i];
    }

    inline void u32(uint32_t value) {
      hash = (hash * 0x104217461b3ull) ^ value;
    }

    uint64_t getHash() {
      return hash;
    }
};

#endif //TITUS_HASHER_H
