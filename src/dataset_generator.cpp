//
// Created by kenenbek on 29.11.17.
//

#include <simgrid/msg.h>
#include <string>

XBT_LOG_NEW_DEFAULT_CATEGORY(dataset_generator, "messages specific for dataset_generator");

int dataset_generator(int argc, char *argv[]){
    double GIGA = 10^9;
    for (int i = 0; i < 1000; ++i){
        msg_task_t task = MSG_task_create(std::to_string(i).c_str(), 10, 100*GIGA, NULL);
        MSG_task_send(task, "Server1");
        MSG_process_sleep(100);
    }
    msg_task_t ftask = MSG_task_create("finalize", 1, 1, NULL);
    MSG_task_send(ftask, "Server1");
}