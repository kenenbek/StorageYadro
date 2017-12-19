//
// Created by kenenbek on 18.12.17.
//

#include <simgrid/msg.h>
#include <atomic>
#include "my_functions.h"

XBT_LOG_NEW_DEFAULT_CATEGORY(drive, "messages specific for drive");


void add_to_foo(std::atomic<double>* foo, double bar) {
    auto current = foo->load();
    while (!foo->compare_exchange_weak(current, current + bar));
}

int drive(int argc, char *argv[]){
    MSG_process_daemonize(MSG_process_self());
    char *mailbox = argv[1];
    double packet_size = 64e3;
    msg_task_t task = NULL;
    auto size = new std::atomic<double>(0);
    MSG_process_create("scounter", drive_size_counter, size, MSG_host_self());
    while (1){
        MSG_task_receive(&task, mailbox);
        add_to_foo(size, packet_size);
        task = NULL;
    }
    MSG_task_destroy(task);
    return 0;
}


int drive_size_counter(int argc, char *argv[]){
    MSG_process_daemonize(MSG_process_self());
    auto size = (std::atomic<double>*) MSG_process_get_data(MSG_process_self());
    while (1){
        XBT_INFO("Size of drive is %.2f GB", (double) *size / 10e9);
        MSG_process_sleep(1);
    }
    return 0;
}