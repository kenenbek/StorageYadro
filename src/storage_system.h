//
// Created by kenenbek on 04.12.17.
//

#ifndef STORAGEYADRO_STORAGE_SYSTEM_H
#define STORAGEYADRO_STORAGE_SYSTEM_H

#include <vector>
#include "storage.h"

class StorageSystem{
public:
    std::vector<Storage> StorageArray;
    StorageSystem(){
        StorageArray.emplace_back(Storage("SSD", 1, 1));
        StorageArray.emplace_back(Storage("JBOD1", 1, 1));
        StorageArray.emplace_back(Storage("JBOD2", 1, 1));
    }
    int write(const DataSet& dataset);
    int read(const DataSet& id);
};

std::map<std::string, Storage> initializeStorageSystems();


#endif //STORAGEYADRO_STORAGE_SYSTEM_H
