//
// Created by kenenbek on 18.12.17.
//

#include <simgrid/msg.h>

XBT_LOG_NEW_DEFAULT_CATEGORY(link_logger, "Messages specific for load_balancer");

int traffic_counter_sender(int argc, char* argv[]){
    MSG_process_daemonize(MSG_process_self());
    double packet_size = 63e3;
    double flops_size = 0;
    msg_task_t task = MSG_task_create("", flops_size, packet_size, NULL);
    char* mymailbox = argv[1];
    char *mailbox = argv[2];
    double bandwidth =  atof(argv[3]);
    while(1){
        double t1 = MSG_get_clock();
        msg_task_t ack_task = NULL;
        MSG_task_send(task, mailbox);
        MSG_task_receive(&ack_task, mymailbox);
        double t2 = MSG_get_clock();
        XBT_INFO("Current traffic through is %f MB/s", (t2-t1) * bandwidth / 1e6);
        MSG_process_sleep(1);
    }
    MSG_task_destroy(task);
    return 0;
};



int traffic_counter_receiver(int argc, char* argv[]){
    MSG_process_daemonize(MSG_process_self());
    double packet_size = 63e3;
    double flops_size = 0;
    msg_task_t task = MSG_task_create("", flops_size, packet_size, NULL);
    char* mymailbox = argv[1];
    char *mailbox = argv[2];
    while(1){
        msg_task_t receive_task = NULL;
        MSG_task_receive(&receive_task, mymailbox);
        MSG_task_send(task, mailbox);
    }
    MSG_task_destroy(task);
    return 0;
};