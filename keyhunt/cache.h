#ifndef CACHE_H
#define CACHE_H
#include <unordered_map>
#include <list>
#include "secp256k1/Point.h"
#include "secp256k1/Int.h"

struct IntHash {
    size_t operator()(Int const &a) const noexcept {
        return (size_t)(a.bits64[0] ^ a.bits64[1]);
    }
};

struct IntEq {
    bool operator()(Int const &a, Int const &b) const noexcept {
        return const_cast<Int&>(a).IsEqual(const_cast<Int*>(&b));
    }
};

class LRUCache {
public:
    explicit LRUCache(size_t cap = 0) : capacity_(cap) {}
    void setCapacity(size_t cap) { capacity_ = cap; clear(); }
    size_t capacity() const { return capacity_; }
    void clear() { map_.clear(); order_.clear(); }
    bool get(const Int &k, Point &v) {
        auto it = map_.find(k);
        if(it==map_.end()) return false;
        order_.splice(order_.begin(), order_, it->second.second);
        v = it->second.first;
        return true;
    }
    void put(const Int &k, const Point &v) {
        if(capacity_==0) return;
        auto it = map_.find(k);
        if(it!=map_.end()) {
            it->second.first = v;
            order_.splice(order_.begin(), order_, it->second.second);
            return;
        }
        if(map_.size() >= capacity_) {
            const Int &old = order_.back();
            map_.erase(old);
            order_.pop_back();
        }
        order_.push_front(k);
        map_.emplace(order_.front(), std::make_pair(v, order_.begin()));
    }
private:
    size_t capacity_;
    std::list<Int> order_;
    std::unordered_map<Int, std::pair<Point,std::list<Int>::iterator>, IntHash, IntEq> map_;
};

#endif // CACHE_H
