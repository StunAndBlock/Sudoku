#ifndef GLOBAL_HPP_
#define GLOBAL_HPP_

#include <stdint.h>
#include <unordered_set>

const uint8_t SLBNUM = 1;
const uint8_t SUBNUM = 9;
constexpr const uint8_t MESHSIZE = SUBNUM * SUBNUM; 



class pUI8hash {
    public:
        size_t operator()(const std::pair<uint8_t, uint8_t>& p) const {
            return std::hash<uint8_t>()(p.first) ^ (std::hash<uint8_t>()(p.second) << 1);
    }
};

class ppUI8hash{
    public:
        size_t operator()(const std::pair<std::pair<uint8_t, uint8_t>,std::pair<uint8_t, uint8_t>>& p) const {
            return pUI8hash()(p.first) ^ (pUI8hash()(p.second) << 1);
    }
};

#endif //!GLOBAL_HPP_