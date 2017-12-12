//
// Created by kenenbek on 04.12.17.
//

#include "storage_system.h"
#include "storage.h"


int StorageSystem::write(const DataSet& dataset){
    auto partialSize = dataset.size;
    auto n = StorageArray.size();
    for (int i = 0; i < n; ++i) {
        DataSet partialDataset(partialSize, "");
        StorageArray[i].write(partialDataset);
    }
    return 0;
}


std::map<std::string, Storage> initializeStorageSystems(){
    unsigned int cur1, cur2, cur3;
    msg_storage_t st;


    xbt_dynar_t SSD_storages = MSG_host_get_attached_storage_list(MSG_host_by_name("SSD"));
    xbt_dynar_t JBOD1_storages = MSG_host_get_attached_storage_list(MSG_host_by_name("JBOD1"));
    xbt_dynar_t JBOD2_storages = MSG_host_get_attached_storage_list(MSG_host_by_name("JBOD2"));

    StorageSystem s1;
    StorageSystem s2;
    StorageSystem s3;

    std::vector<Storage> SSDStorageVector;
    std::vector<Storage> JBOD1StorageVector;
    std::vector<Storage> JBOD2StorageVector;

    xbt_dynar_foreach(SSD_storages, cur1, st){
        double readRate = 150;
        double writeRate = 150;
        const char* name = MSG_storage_get_name(st);
        double fullSize = MSG_storage_get_size(st);
        //xbt_dict_t dic = MSG_storage_get_properties(st);

        Storage storage(name, readRate, writeRate);
        storage.fullSize = fullSize;
        SSDStorageVector.emplace_back(storage);
    }

    xbt_dynar_foreach(JBOD1_storages, cur2, st){
        double readRate = 150;
        double writeRate = 150;
        const char* name = MSG_storage_get_name(st);
        double fullSize = MSG_storage_get_size(st);
        //xbt_dict_t dic = MSG_storage_get_properties(st);

        Storage storage(name, readRate, writeRate);
        storage.fullSize = fullSize;
        JBOD1StorageVector.emplace_back(storage);
    }

    xbt_dynar_foreach(JBOD2_storages, cur3, st){
        double readRate = 150;
        double writeRate = 150;
        const char* name = MSG_storage_get_name(st);
        double fullSize = MSG_storage_get_size(st);
        //xbt_dict_t dic = MSG_storage_get_properties(st);

        Storage storage(name, readRate, writeRate);
        storage.fullSize = fullSize;
        JBOD2StorageVector.emplace_back(storage);
    }

    xbt_dynar_free(&SSD_storages);
    xbt_dynar_free(&JBOD1_storages);
    xbt_dynar_free(&JBOD2_storages);

};