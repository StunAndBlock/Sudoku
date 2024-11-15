#include "Logic.hpp"


void Logic::excludeSubSector(std::pair<uint8_t, uint8_t> spot, 
                            std::unordered_set<std::pair<uint8_t, uint8_t>, pair_hash>& numSpecificAS) const {
    for (uint8_t x = spot.first/3*3; x <  (spot.first/3+1)*3; x++){
        for (uint8_t y = spot.second/3*3; y <  (spot.second/3+1)*3; y++){
            auto pos = numSpecificAS.find(std::pair(x, y));
                if (pos != numSpecificAS.end()) {
                    numSpecificAS.erase(pos);
                }
        }
    }

}

void Logic::excludeCrossSpots(std::pair<uint8_t, uint8_t> spot, 
                            std::unordered_set<std::pair<uint8_t, uint8_t>, pair_hash>& numSpecificAS) const {
    for (auto it = numSpecificAS.begin(); it != numSpecificAS.end();){
        if (it->first == spot.first || it->second == spot.second){
            it = numSpecificAS.erase(it);
        } else {
            it++; 
        }
    }
}



bool Logic::checkSpots(uint8_t placed, std::unordered_set<std::pair<uint8_t, uint8_t>, pair_hash>& numSpecificAS) const{
    if (numSpecificAS.size() + placed < 9){
        return true;
    }
        std::unordered_set<std::pair <std::pair<uint8_t, uint8_t> , std::pair<uint8_t, uint8_t>>, pair_pair_hash> subSectorDevided;
        std::unordered_set<uint8_t> xCross;
        std::unordered_set<uint8_t> yCross;
        std::pair<uint8_t, uint8_t> xRange;
        std::pair<uint8_t, uint8_t> yRange;
        std::pair <std::pair<uint8_t, uint8_t> , std::pair<uint8_t, uint8_t>> rangePair;
        for(const auto& iPair : numSpecificAS){
            if (auto iter = xCross.find(iPair.first) == xCross.end()){
                xCross.insert(iPair.first);
            }

            if (auto iter = yCross.find(iPair.second) == yCross.end()){
                yCross.insert(iPair.second);
            }
            xRange = std::pair((iPair.first/3*3),(iPair.first/3+1)*3);
            yRange = std::pair((iPair.second/3*3),(iPair.second/3+1)*3);
            rangePair = std::pair(xRange, yRange);
            if (auto iter = subSectorDevided.find(rangePair) == subSectorDevided.end()){
                subSectorDevided.insert(rangePair);
            }

        }
            std::cout << "\t\tavailablespots recalc at least: " 
                    <<  "\nsubsector:" << subSectorDevided.size() 
                    << "\nx cross:" << xCross.size()
                    << "\nycross:" << yCross.size()
                    << "\n";
            if (subSectorDevided.size() + placed < 9 ||  xCross.size() + placed < 9 || yCross.size() + placed < 9) {
                return true;
            }
    return false;
}

Logic::Logic(){


}

Logic::~Logic(){



}

int Logic::init(){
    for (uint8_t x = 0, meshIndex = 0; x < SUBNUM; x++){
        for (uint8_t y = 0; y < SUBNUM; y++, meshIndex++){
            // availableCords_[n].insert(dimCord);
            // availableY_[n].insert(dimCord);
            availableSpots_.insert(std::pair(x,y));
            sudokuMesh_[meshIndex] = 0;
        }
    }

    return 0;
}

int Logic::generateSudokuMesh(){
    std::unordered_set<std::pair<uint8_t, uint8_t>, pair_hash> numSpecificAS;
    std::pair<uint8_t, uint8_t> spot;
    std::unordered_set<std::pair<uint8_t, uint8_t>, pair_hash> prev;
    std::pair<uint8_t, uint8_t> prevSpot;
    std::unordered_set<std::pair<uint8_t, uint8_t>, pair_hash> unsuc;
    uint8_t placed = 0;
    for (uint8_t n = SLBNUM; n <= 9; n++){
        placed = 0;
        numSpecificAS = availableSpots_;
        for (uint8_t i = 0; placed != 9;){
            std::cout << "\t\t-------n:" << (int)n << " iter:" << (int)i << "-------\n";
            std::cout << "\t\tavailablespots: " << numSpecificAS.size() << "\n";
            auto it = numSpecificAS.begin();
            if (checkSpots(placed, numSpecificAS)) {
                std::cerr << "this generation is unsolvable\n" << std::endl;
                numSpecificAS = prev;
                availableSpots_.insert(prevSpot);
                sudokuMesh_[prevSpot.second * SUBNUM + prevSpot.first] = 0;
                numSpecificAS.erase(prevSpot);
                placed--;
            } else {
                prev = numSpecificAS;
                spot = std::pair(it->first, it->second);
                std::cout << "\tchoosing spot -> [" << (int)it->first << (int)it->second << "]\n";
                prevSpot = spot;
                availableSpots_.erase(spot);
                excludeSubSector(spot,numSpecificAS);
                excludeCrossSpots(spot,numSpecificAS);
                sudokuMesh_[spot.second * SUBNUM + spot.first] = n;
                placed++;
            }
           lsOut(numSpecificAS);
        }
        meshOut();
    
    }
    return 1;
}

void Logic::meshOut() const {
    std::cout << std::endl << "======================================" << std::endl;
    for(uint8_t i = 0; i < 81 ; i++){
        std::cout << int(sudokuMesh_[i]) << " ";
        if((i+1) % 3 == 0){
            std::cout << "| ";
        }
        if ((i+1)%27 == 0){
            std::cout << std::endl << "-----------------------";
        }
        if((i+1) % 9 == 0){
            std::cout << std::endl;
        }
    }
}

void Logic::lsOut(std::unordered_set<std::pair<uint8_t, uint8_t>, pair_hash> availableSpots) {
    int a=0;
    for (int i = 0; i < 81 ; i++){
        availableSpotsImage_[i] = 0;
    }
    for(auto it : availableSpots){

        availableSpotsImage_[it.second * SUBNUM + it.first] = 1;
        std::cout << a<< ": " << '[' << (int)it.first<<  (int)it.second << ']' << std::endl;
        a++;
    }

    for(uint8_t i = 0; i < 81 ; i++){
        std::cout << int(availableSpotsImage_[i]) << " ";
        if((i+1) % 3 == 0){
            std::cout << "| ";
        }
        if ((i+1)%27 == 0){
            std::cout << std::endl << "-----------------------";
        }
        if((i+1) % 9 == 0){
            std::cout << std::endl;
        }
    }
}