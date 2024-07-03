#ifndef OFFSET_H
#define OFFSET_H

#include <functional>

struct offset {
    int x;
    int y;
    bool operator==(const offset& other) const {
        return x == other.x && y == other.y;
    }
};


namespace std
{
    template<>
    struct hash<offset> {
        size_t operator()(const offset& o) const {
            return hash<int>()(o.x) ^ (hash<int>()(o.y) << 1);
        }
    };
}
#endif // OFFSET_H