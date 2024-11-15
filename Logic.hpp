#ifndef LOGIC_HPP_
#define LOGIC_HPP_
#include "Global.hpp"
#include <unordered_map>
#include <unordered_set>
#include <iostream>

struct pair_hash {
    std::size_t operator()(const std::pair<uint8_t, uint8_t>& p) const {
        return std::hash<uint8_t>()(p.first) ^ (std::hash<uint8_t>()(p.second) << 1);
    }
};

struct pair_pair_hash{
    std::size_t operator()(const std::pair<std::pair<uint8_t, uint8_t>,std::pair<uint8_t, uint8_t>>& p) const {
        return pair_hash()(p.first) ^ (pair_hash()(p.second) << 1);
    }
};


class Logic {
    std::unordered_set<std::pair<uint8_t, uint8_t>, pair_hash> availableSpots_;
    std::unordered_set<uint8_t> sectorRelatedSpots_[SUBNUM];
    uint8_t sudokuMesh_[MESHSIZE];
    uint8_t availableSpotsImage_[MESHSIZE];
    //uint8_t discoverSubSecor(std::pair<uint8_t, uint8_t>) const ;
    void excludeSubSector(std::pair<uint8_t, uint8_t>,
                        std::unordered_set<std::pair<uint8_t, uint8_t>, pair_hash>&) const;
    void excludeCrossSpots(std::pair<uint8_t, uint8_t>, 
                        std::unordered_set<std::pair<uint8_t, uint8_t>, pair_hash>&) const;
    bool checkSpots(uint8_t, std::unordered_set<std::pair<uint8_t, uint8_t>, pair_hash>&) const;
    public:
    Logic();
    ~Logic();
    int init();
    int generateSudokuMesh();
    void meshOut() const;
    void lsOut(std::unordered_set<std::pair<uint8_t, uint8_t>, pair_hash>);
};

#endif //!LOGIC_HPP_