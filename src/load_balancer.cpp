//
// Created by kenenbek on 16.12.17.
//

#include <simgrid/msg.h>
#include "my_functions.h"
#include "structures.h"

XBT_LOG_NEW_DEFAULT_CATEGORY(load_balancer, "Messages specific for load_balancer");

int load_balancer(int argc, char *argv[]){
    int VESNIN_SERVER_NUMBER = 1;
    msg_host_t this_host = MSG_host_self();
    for (int i = 0; i < 4; i++){
        FileInfo* file = new FileInfo(std::to_string(i), 65e6, (i % VESNIN_SERVER_NUMBER) + 1);
        MSG_process_create("", load_balancer_packet_sender, file, this_host);
        MSG_process_sleep(0.1);
    }

    //FINALIZE all SERVERs
    for(int i = 1; i < VESNIN_SERVER_NUMBER + 4; i++){
        msg_task_t fin_task = MSG_task_create("finalize", 0, 0, NULL);
        MSG_task_send(fin_task, ("Server" + std::to_string(i)).c_str());
    }
    msg_task_t fin_task1 = MSG_task_create("finalize", 0, 0, NULL);
    msg_task_t fin_task2 = MSG_task_create("finalize", 0, 0, NULL);
    MSG_task_send(fin_task1, "FabricManager");
    MSG_task_send(fin_task2, "CacheManager");
    return 0;
}

double get_average(double x){
    static int sum, n;
    return (((float)sum)/++n);
}

int load_balancer_packet_sender(int argc, char *argv[]){
    auto meta = (FileInfo*) MSG_process_get_data(MSG_process_self());
    auto file_size = meta->size;
    auto server_address = meta->server_Executor_from_Load_Balancer_Executor.c_str();
    auto my_address = meta->LB_Executor_ID_from_cache.c_str();
    auto packet_size = 65e3;

    msg_task_t task = MSG_task_create("new_file_task", 0, 10, meta);
    MSG_task_send(task, meta->server_name.c_str());
    auto n_sending = file_size / packet_size;

    double t1 = MSG_get_clock();

    msg_task_t packet_task = MSG_task_create("", 0, packet_size, NULL);
    for (int i = 0; i < n_sending; ++i) {

        msg_task_t ack_task = NULL;
        MSG_task_send(packet_task, server_address);

        MSG_task_receive(&ack_task, my_address);
        ack_task = NULL;
    }
    double t2 = MSG_get_clock();

    XBT_INFO("file %s took %f sec, response_time %f sec", meta->filename.c_str(), t2 - t1, (t2-t1)/n_sending);

    msg_task_t fin_task = MSG_task_create("finalize", 0, 0, NULL);
    MSG_task_send(fin_task, server_address);

    MSG_task_destroy(packet_task);
    delete meta;
    return 0;
}