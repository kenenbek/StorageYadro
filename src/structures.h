//
// Created by kenenbek on 16.12.17.
//

#ifndef STORAGEYADRO_STRUCTURES_H
#define STORAGEYADRO_STRUCTURES_H

struct FileInfo{
public:
    double size;
    std::string filename;
    std::string LB_Executor_ID_from_cache;
    std::string server_name;
    std::string server_Executor_from_Load_Balancer_Executor;
    std::string Fabric_executor_from_server_exec;
    std::string Cache_executor_from_FM;

    FileInfo(std::string filename_arg, double size_arg, int vesnin_server_number){
        size = size_arg;
        filename = filename_arg;
        server_name = "Server" + std::to_string(vesnin_server_number);
        server_Executor_from_Load_Balancer_Executor = server_name + "_" + filename_arg + "_" + "LB";
        Fabric_executor_from_server_exec = "Fabric_executor_" + filename_arg;
        Cache_executor_from_FM = "Cache_executor_" + filename_arg;
        LB_Executor_ID_from_cache = "LB_Executor_" + filename_arg;
    }
};

#endif //STORAGEYADRO_STRUCTURES_H
