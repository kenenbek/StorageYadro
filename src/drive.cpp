//
// Created by kenenbek on 18.12.17.
//

#include <simgrid/msg.h>
#include <atomic>
#include <cinttypes>
#include "my_functions.h"

XBT_LOG_NEW_DEFAULT_CATEGORY(drive, "messages specific for drive");


int disk(int argc, char *argv[]){
    MSG_process_daemonize(MSG_process_self());
    char *mailbox = argv[1];
    auto packet_size = (int) 64e3;
    msg_task_t task = NULL;
    std::atomic_uint_fast64_t disk_size(0);
    MSG_process_create(argv[1], disk_size_counter, &disk_size, MSG_host_self());
    while (1){
        MSG_task_receive(&task, mailbox);
        disk_size += packet_size;
        global_cache_size -= packet_size;
        task = NULL;
    }
    MSG_task_destroy(task);
    return 0;
}


int disk_size_counter(int argc, char *argv[]){
    MSG_process_daemonize(MSG_process_self());
    double mega = 1000000;
    const char* host_name = MSG_host_get_name(MSG_host_self());
    msg_process_t process = MSG_process_self();
    auto size = (std::atomic_uint_fast64_t*) MSG_process_get_data(process);
    const char* name = MSG_process_get_name(process);

    while (1){
        XBT_INFO("Size of %s is %.2f MB" " Size of cache is %.2fMB", name, size->load() / mega, global_cache_size.load() / mega);
        MSG_process_sleep(0.1);
    }
    return 0;
}