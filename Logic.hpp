#ifndef LOGIC_HPP_
#define LOGIC_HPP_
#include "Global.hpp"
#include <unordered_map>
#include <iterator>
#include <iostream>
#include <random>
#include <chrono>
#include <thread>



class Logic {
    public:
        enum Difficulty : uint8_t {Easy, Medium, Hard, Extreame, Nightmare};
        Logic();
        ~Logic();
        int init();
        void meshOut() const;
        void lsOut(std::unordered_set<std::pair<uint8_t, uint8_t>, pUI8hash>);
        void create();
    private:
        const uint8_t ATMOSTMISSINGCELLS_ = MESHSIZE - 17;
        Difficulty level_;
        uint8_t nMissingCells_;
        std::unordered_set<std::pair<uint8_t, uint8_t>, pUI8hash> availableSpots_;
        uint8_t sudokuMesh_debug[MESHSIZE];
        std::unordered_set<std::pair<uint8_t, uint8_t>, pUI8hash> sudokuMesh_[9];
        uint8_t availableSpotsImage_[MESHSIZE];
        std::mt19937 gen_;

        uint8_t uBByCord(const uint8_t&) const;
        uint8_t lBByCord(const uint8_t&) const;
        //uint8_t discoverSubSecor(std::pair<uint8_t, uint8_t>) const ;
        void excludeSubSector(std::pair<uint8_t, uint8_t>,
                            std::unordered_set<std::pair<uint8_t, uint8_t>, pUI8hash>&) const;
        void excludeCrossSpots(std::pair<uint8_t, uint8_t>, 
                            std::unordered_set<std::pair<uint8_t, uint8_t>, pUI8hash>&) const;
        bool checkSpots(uint8_t, std::unordered_set<std::pair<uint8_t, uint8_t>, pUI8hash>&) const;
        int generateCompleteMesh();
        void applyDifficulty();
        void generateMissing();
};

#endif //!LOGIC_HPP_