//
// Created by kenenbek on 15.12.17.
//

#include <simgrid/msg.h>
#include "my_functions.h"
#include "structures.h"

XBT_LOG_NEW_DEFAULT_CATEGORY(PCIeF, "messages specific for PCIeF");

int PCIeFabric_manager(int argc, char *argv[]) {
    msg_host_t this_host = MSG_host_self();

    while (1) {
        msg_task_t task = NULL;
        int res = MSG_task_recv(&task, argv[1]); /* Then it posts asynchronous receives (@ref MSG_task_irecv) and*/
        if (strcmp(MSG_task_get_name(task), "finalize") == 0) { /* If the received task is "finalize", the process ends */
            MSG_task_destroy(task);
            break;
        }
        MSG_process_create("name", PCIeFabric_executor, MSG_task_get_data(task), this_host);
        MSG_task_destroy(task);
    }
    return 0;
}


int PCIeFabric_executor(int argc, char *argv[]) {
    auto flops_size = 0;
    auto packet_size = 64e3;
    auto meta = (FileInfo*) MSG_process_get_data(MSG_process_self());

    std::string receive_from_server_executor(meta->Fabric_executor_from_server_exec);
    std::string send_to_cache_executor(meta->Cache_executor_from_FM.c_str());

    msg_task_t start_task = MSG_task_create("", 0, 0, meta);
    MSG_task_send(start_task, "CacheManager");

    while (1) {
        msg_task_t packet_data = NULL;
        MSG_task_recv(&packet_data, receive_from_server_executor.c_str()); /* Then it posts asynchronous receives (@ref MSG_task_irecv) and*/
        if (strcmp(MSG_task_get_name(packet_data), "finalize") == 0) { /* If the received task is "finalize", the process ends */
            MSG_task_destroy(packet_data);

            msg_task_t fin_task = MSG_task_create("finalize", 0, 0, NULL);
            MSG_task_send(fin_task, send_to_cache_executor.c_str());
            break;
        }

        //Send to Cache
        MSG_task_send(packet_data, send_to_cache_executor.c_str());
    }

    return 0;
}