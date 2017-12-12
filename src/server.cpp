//
// Created by kenenbek on 29.11.17.
//

#include <simgrid/msg.h>
#include "storage.h"
#include "my_functions.h"

XBT_LOG_NEW_DEFAULT_CATEGORY(server, "messages specific for server");

int server(int argc, char *argv[]){
    std::string mailbox = "Server1";
    msg_task_t task = NULL;
    while (true){
        int res = MSG_task_receive(&task, mailbox.c_str());
        if (res == MSG_OK){
            if (!strcmp(MSG_task_get_name(task), "finalize")){
                MSG_task_destroy(task);
                break;
            }

            if (MSG_task_get_initial_flops_amount(task) == 1.0){
                MSG_process_create("write", write_process_server, MSG_task_get_data(task), MSG_host_self());
            } else{
                MSG_process_create("read", read_process_server, MSG_task_get_data(task), MSG_host_self());
            }
            MSG_task_destroy(task);
            task = NULL;

        }else{
            XBT_INFO("FAIL");
        }
    }
    return 0;
}

int read_process_server(int argc, char *argv[]){
    XBT_INFO("ook");
    auto id = (ID*) MSG_process_get_data(MSG_process_self());
    std::string fullPath = id->fullPath;
    msg_file_t file = MSG_file_open(fullPath.c_str(), NULL);
    MSG_file_read(file, MSG_file_get_size(file));
    MSG_file_close(file);
    return 0;
}

int write_process_server(int argc, char *argv[]){
    auto dataSet = (DataSet*) MSG_process_get_data(MSG_process_self());
    std::string fullPath = dataSet->fullPath;
    //XBT_INFO(fullPath.c_str());
    msg_file_t file = MSG_file_open(fullPath.c_str(), NULL);
    MSG_file_write(file, MSG_file_get_size(file));
    MSG_file_close(file);
    return 0;
}