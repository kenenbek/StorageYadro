//
// Created by kenenbek on 15.12.17.
//

#include <simgrid/msg.h>
#include "my_functions.h"
#include "structures.h"

XBT_LOG_NEW_DEFAULT_CATEGORY(Cache, "messages specific for Cache");

int cache_manager(int argc, char *argv[]) {
    msg_host_t this_host = MSG_host_self();
    while (1) {
        msg_task_t task = NULL;
        int res = MSG_task_recv(&task, argv[1]); /* Then it posts asynchronous receives (@ref MSG_task_irecv) and*/

        if (strcmp(MSG_task_get_name(task), "finalize") == 0) { /* If the received task is "finalize", the process ends */
            MSG_task_destroy(task);
            break;
        }
        MSG_process_create("name", cache_executor, MSG_task_get_data(task), this_host);
        MSG_task_destroy(task);
    }
    return 0;
}


int cache_executor(int argc, char *argv[]) {
    auto flops_size = 0;
    auto packet_size = 64e3;
    auto meta = (FileInfo*) MSG_process_get_data(MSG_process_self());

    std::string receive_from_fabric_manager(meta->Cache_executor_from_FM.c_str());
    std::string send_to_load_balance_exec(meta->LB_Executor_ID_from_cache.c_str());

    msg_task_t ack_task = MSG_task_create("", flops_size, packet_size, NULL);
    while (1) {
        msg_task_t packet_data = NULL;
        MSG_task_recv(&packet_data, receive_from_fabric_manager.c_str()); /* Then it posts asynchronous receives (@ref MSG_task_irecv) and*/
        if (strcmp(MSG_task_get_name(packet_data), "finalize") == 0) { /* If the received task is "finalize", the process ends */
            MSG_task_destroy(packet_data);
            break;
        }
        //Send to ACK TO LB
        MSG_task_send(ack_task, send_to_load_balance_exec.c_str());

        msg_task_t drive_task = MSG_task_create("task", flops_size, packet_size, NULL);
        MSG_task_dsend(drive_task, "drive", NULL);
    }
    MSG_task_destroy(ack_task);
    return 0;
}