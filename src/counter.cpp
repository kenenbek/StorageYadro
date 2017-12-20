//
// Created by kenenbek on 18.12.17.
//

#include <simgrid/msg.h>
#include <algorithm>

XBT_LOG_NEW_DEFAULT_CATEGORY(logger, "Messages specific for logger");

int traffic_counter_sender(int argc, char* argv[]){
    MSG_process_daemonize(MSG_process_self());
    double packet_size = 64e3;
    double flops_size = 0;
    msg_task_t task = MSG_task_create("", flops_size, packet_size, NULL);
    char* mymailbox = argv[1];
    double bandwidth =  atof(argv[argc-1]);
    while(1){
        for (int i = 2; i < argc - 1; ++i) {
            char *mailbox = argv[i];
            double t1 = MSG_get_clock();
            msg_task_t ack_task = NULL;
            MSG_task_send(task, mailbox);
            MSG_task_receive(&ack_task, mymailbox);
            double t2 = MSG_get_clock();
            double max_b = std::max(0., 0.5 * ((t2-t1) * bandwidth - packet_size) / 1e6);
            XBT_INFO("Current traffic through %s is %f MB/s", mailbox, max_b);
        }
        MSG_process_sleep(0.1);
    }
    MSG_task_destroy(task);
    return 0;
};



int traffic_counter_receiver(int argc, char* argv[]){
    MSG_process_daemonize(MSG_process_self());
    double packet_size = 64e3;
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

int cpu_counter(int argc, char*argv[]){
    MSG_process_daemonize(MSG_process_self());
    msg_host_t host = MSG_host_self();
    const char* name = MSG_host_get_name(host);
    float full_load = atof(argv[1]);
    while (1){
        xbt_dynar_t d = xbt_dynar_new(sizeof(msg_process_t), NULL);
        MSG_host_get_process_list(host, d);
        double max_b = std::max(0., (xbt_dynar_length(d)/full_load) - 0.02);
        XBT_INFO("Load of %s is %.2f", name, max_b);
        xbt_dynar_free(&d);
        MSG_process_sleep(0.1);
    }
    return 0;
}