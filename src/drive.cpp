//
// Created by kenenbek on 18.12.17.
//

#include <simgrid/msg.h>
XBT_LOG_NEW_DEFAULT_CATEGORY(drive, "messages specific for drive");
int drive(int argc, char *argv[]){
    MSG_process_daemonize(MSG_process_self());
    char *mailbox = argv[1];
    double size = 0;
    msg_task_t task = NULL;
    while (1){
        MSG_task_receive(&task, mailbox);
        XBT_INFO("my current size is %f", size/1e3);
        size += MSG_task_get_bytes_amount(task);
        task = NULL;
    }
    MSG_task_destroy(task);
    return 0;
}