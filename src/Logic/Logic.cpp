#include "Logic.hpp"

uint8_t Logic::lBByCord(const uint8_t& cord) const{
    return (cord/3*3);
}

uint8_t Logic::uBByCord(const uint8_t& cord) const{
    return ((cord/3+1)*3);
}

void Logic::excludeSubSector(std::pair<uint8_t, uint8_t> spot, 
                            std::unordered_set<std::pair<uint8_t, uint8_t>, pUI8hash>& numSpecificAS) const {
    for (uint8_t x = lBByCord(spot.first); x < uBByCord(spot.first); x++){
        for (uint8_t y = lBByCord(spot.second); y <  uBByCord(spot.second); y++){
            auto pos = numSpecificAS.find(std::pair(x, y));
                if (pos != numSpecificAS.end()) {
                    numSpecificAS.erase(pos);
                }
        }
    }

}

void Logic::excludeCrossSpots(std::pair<uint8_t, uint8_t> spot, 
                            std::unordered_set<std::pair<uint8_t, uint8_t>, pUI8hash>& numSpecificAS) const {
    for (auto it = numSpecificAS.begin(); it != numSpecificAS.end();){
        if (it->first == spot.first || it->second == spot.second){
            it = numSpecificAS.erase(it);
        } else {
            it++; 
        }
    }
}



bool Logic::checkSpots(uint8_t placed,std::unordered_set<std::pair<uint8_t, uint8_t>, pUI8hash>& numSpecificAS) const{
    if (numSpecificAS.size() + placed < 9){
        return true;
    }
        std::unordered_set<std::pair <std::pair<uint8_t, uint8_t> , std::pair<uint8_t, uint8_t>>, ppUI8hash> subSectorDevided;
        std::unordered_set<uint8_t> xCross;
        std::unordered_set<uint8_t> yCross;
        std::pair<uint8_t, uint8_t> xSubMeshBound;
        std::pair<uint8_t, uint8_t> ySubMeshBound;
        std::pair <std::pair<uint8_t, uint8_t> , std::pair<uint8_t, uint8_t>> subMeshBounds;
        for(const auto& iPair : numSpecificAS){
            if (auto iter = xCross.find(iPair.first) == xCross.end()){
                xCross.insert(iPair.first);
            }

            if (auto iter = yCross.find(iPair.second) == yCross.end()){
                yCross.insert(iPair.second);
            }
            xSubMeshBound = std::pair(lBByCord(iPair.first),uBByCord(iPair.first));
            ySubMeshBound = std::pair(lBByCord(iPair.second),uBByCord(iPair.second));
            subMeshBounds = std::pair(xSubMeshBound, ySubMeshBound);
            if (auto iter = subSectorDevided.find(subMeshBounds) == subSectorDevided.end()){
                subSectorDevided.insert(subMeshBounds);
            }

        }
            // std::cout << "\t\tavailablespots recalc at least: " 
            //         <<  "\nsubsector:" << subSectorDevided.size() 
            //         << "\nx cross:" << xCross.size()
            //         << "\nycross:" << yCross.size()
            //         << "\n";
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
    level_ = Difficulty::Easy;
    std::random_device rd;
    gen_.seed(rd());
    for (uint8_t x = 0, meshIndex = 0; x < SUBNUM; x++){
        for (uint8_t y = 0; y < SUBNUM; y++, meshIndex++){
            // availableCords_[n].insert(dimCord);
            // availableY_[n].insert(dimCord);
            
            availableSpots_.insert(std::pair(x,y));
            sudokuMesh_debug[meshIndex] = 0;
        }
    }

    return 0;
}


void Logic::create(){
    generateCompleteMesh();
    meshOut();
    applyDifficulty();
    generateMissing();
    meshOut(); 
}

int Logic::generateCompleteMesh(){
    std::unordered_set<std::pair<uint8_t, uint8_t>, pUI8hash> numSpecificAS;
    std::pair<uint8_t, uint8_t> spot;
    std::unordered_set<std::pair<uint8_t, uint8_t>, pUI8hash> prev[9];
    std::unordered_set<std::pair<uint8_t, uint8_t>, pUI8hash> initial = availableSpots_;
    std::pair<uint8_t, uint8_t> prevSpot;
    for (uint8_t n = SLBNUM; n <= 9; n++){
        numSpecificAS = availableSpots_;
        for (uint8_t placed = 0; placed < 9;){
             //std::cout << "\t\t-------n:" << (int)n << "-------\n";
            prev[placed] = numSpecificAS;
            auto it = numSpecificAS.begin();
                std::uniform_int_distribution<int> dist(0, numSpecificAS.size()-1);
                std::advance(it, dist(gen_));
            spot = std::pair(it->first, it->second);
            excludeSubSector(spot,numSpecificAS);
            excludeCrossSpots(spot,numSpecificAS);
            sudokuMesh_debug[spot.second * SUBNUM + spot.first] = n;
            sudokuMesh_[n-1].insert(spot);
            // lsOut(numSpecificAS);
            // meshOut();
            if (checkSpots(placed+1, numSpecificAS)){
                // std::cout << "generation error||||||||||||||||||||||||||||||||||||||||||||||||||||||||" << "\n";
                numSpecificAS = prev[placed];
                numSpecificAS.erase(spot);
                sudokuMesh_debug[spot.second * SUBNUM + spot.first] = 0;
                sudokuMesh_[n-1].erase(spot);
                if(numSpecificAS.empty()){
                    if(placed != 0){
                        placed--;
                        numSpecificAS = prev[placed];
                        numSpecificAS.erase(prevSpot);
                        availableSpots_.insert(prevSpot);
                        sudokuMesh_debug[prevSpot.second * SUBNUM + prevSpot.first] = 0;
                        sudokuMesh_[n-1].erase(prevSpot);
                    } else {
                        // n--;
                        // placed = 7;
                        // numSpecificAS = prev[n-1][placed];
                        // numSpecificAS.erase(prevSpot[placed]);
                        n = 0;
                        placed = 9;
                        availableSpots_ = initial;
                        numSpecificAS =  initial;
                        for(uint8_t i = 0; i < 9; i++){
                            sudokuMesh_[i].clear();
                        }
                    }
                }
            } else{
                prevSpot = spot;
                availableSpots_.erase(spot);
                placed++;
            }
        }
        //meshOut();
    }
    // for (uint8_t n = SLBNUM; n <= 9; n++){
    //     numSpecificAS = availableSpots_;

    //     for (uint8_t placed = 0, i = 0; placed != 9;){
    //         std::cout << "\t\t-------n:" << (int)n << "-------\n";
    //         std::cout << "\t\tavailablespots: " << numSpecificAS.size() << "\n";
    //         auto it = numSpecificAS.begin();
    //         if (checkSpots(placed, numSpecificAS)) {
    //             std::cerr << "this generation is unsolvable\n" << std::endl;
    //                 numSpecificAS = prev;
    //             availableSpots_.insert(prevSpot);
    //             sudokuMesh_[prevSpot.second * SUBNUM + prevSpot.first] = 0;
    //             numSpecificAS.erase(prevSpot);
    //             placed--;
    //         } else {
    //             if (placed < 1 && (n == 1)){
    //                 std::uniform_int_distribution<int> dist(0, numSpecificAS.size()-1);
    //                 std::advance(it, dist(gen_));
    //             }
    //             prev = numSpecificAS;
    //             spot = std::pair(it->first, it->second);
    //             std::cout << "\tchoosing spot -> [" << (int)it->first << (int)it->second << "]\n";
    //             prevSpot = spot;
    //             availableSpots_.erase(spot);
    //             excludeSubSector(spot,numSpecificAS);
    //             excludeCrossSpots(spot,numSpecificAS);
    //             sudokuMesh_[spot.second * SUBNUM + spot.first] = n;
    //             placed++;
    //             i++;
    //         }
    //        lsOut(numSpecificAS);
    //     }
    //     meshOut();

    return 1;
}

void Logic::applyDifficulty(){
    uint8_t minMissingCells = 0;
    uint8_t maxMissingCells = 0;
    switch (level_)
    {
    case Difficulty::Nightmare:
        minMissingCells = 56; // max available 25
        maxMissingCells = ATMOSTMISSINGCELLS_-5; //min available 22
        break;
    case Difficulty::Extreame:
        minMissingCells = 56-6; // max available 31
        maxMissingCells = ATMOSTMISSINGCELLS_-9; // min available 26 50-55
        break;    
    case Difficulty::Hard:
        minMissingCells = 56-14; // max available 37
        maxMissingCells = ATMOSTMISSINGCELLS_-15; // min available 30 42-49
        break;
    case Difficulty::Medium:
        minMissingCells = 56-24; // max available 43
        maxMissingCells = ATMOSTMISSINGCELLS_-23; // min availavle 34 32-41
        break;
    case Difficulty::Easy:
        minMissingCells = 56-36; // max available 49
        maxMissingCells = ATMOSTMISSINGCELLS_-33; //min available 38  20-31
        break;
    default:
        break;
    }
    std::uniform_int_distribution<uint8_t> dist(minMissingCells, maxMissingCells);
    nMissingCells_ = dist(gen_);

}

void Logic::generateMissing(){
    std::cout << "\nto delete: " << (int)nMissingCells_ << "\n";
    uint8_t averageToDelete = nMissingCells_/9;
    int8_t uBDelta =  9 - (averageToDelete + 2);
    int8_t lBDelta = -uBDelta;
    std::uniform_int_distribution<int8_t> distDelta(lBDelta, uBDelta);
    int8_t delta = 0;
    uint8_t delPosN = 0;
    for(uint8_t n = 0; n < 9; n++){
        delta = distDelta(gen_);
        for(uint8_t nDelNTimes = 0 ; nDelNTimes < (averageToDelete + delta) ; nDelNTimes++){
            if(nMissingCells_){
                std::uniform_int_distribution<uint8_t> distPos(0, sudokuMesh_[n].size()-1);
                delPosN = distPos(gen_);
                auto it = sudokuMesh_[n].begin();
                advance(it, delPosN);
                sudokuMesh_[n].erase(it);
                sudokuMesh_debug[it->second * SUBNUM + it->first] = 0;
                nMissingCells_--;
            }
        }

    }
    for(uint8_t i = 0; i < nMissingCells_; i++ ){
        auto it = sudokuMesh_[i%9].begin();
        sudokuMesh_[i%9].erase(it);
        sudokuMesh_debug[it->second * SUBNUM + it->first] = 0;
    }

}

void Logic::meshOut() const {
    std::cout << std::endl << "======================================" << std::endl;
    for(uint8_t i = 0; i < 81 ; i++){
        std::cout << int(sudokuMesh_debug[i]) << " ";
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
    // for debug
    for(uint8_t i = 0; i < 81 ; i++){
        if(sudokuMesh_debug[i]){
            std::cout << (int)sudokuMesh_debug[i];
        } else {
            std::cout << '.';
        }
    }
    std::cout << "\n";
    uint8_t cluesOnField = 0;
    for(uint8_t i = 1 ; i <=9 ; i++){
        std::cout << (int)i << ": ";
        for (const auto& pCords: sudokuMesh_[i-1]){
            std::cout << " [" << (int)pCords.first << ";" << (int)pCords.second << "] ";
            cluesOnField++;
        }
        std::cout << "\n";
    }
    std::cout << "Clues on mesh" << (int)cluesOnField++ << "\n";
}

void Logic::lsOut(std::unordered_set<std::pair<uint8_t, uint8_t>, pUI8hash> availableSpots) {
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