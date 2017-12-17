//
// Created by kenenbek on 29.11.17.
//

#include <simgrid/msg.h>
#include "storage.h"
#include "my_functions.h"
#include "structures.h"

XBT_LOG_NEW_DEFAULT_CATEGORY(server, "messages specific for server");

int server_manager(int argc, char *argv[]){
    std::string mailbox = argv[1];
    msg_host_t this_host = MSG_host_self();
    while (true){
        msg_task_t task = NULL;
        int res = MSG_task_receive(&task, mailbox.c_str());
        if (res == MSG_OK){
            if (!strcmp(MSG_task_get_name(task), "finalize")){
                MSG_task_destroy(task);
                break;
            }
            MSG_process_create("kj", server_executer, MSG_task_get_data(task), this_host);
            MSG_task_destroy(task);
        }
    }
    return 0;
}

int server_executer(int argc, char *argv[]){
    auto packet_size = 64e3;
    auto flops_amount = 0;
    auto meta = (FileInfo*) MSG_process_get_data(MSG_process_self());

    auto receive_from_lb_executor = meta->server_Executor_from_Load_Balancer_Executor.c_str();
    auto send_to_fm_fabric = meta->Fabric_executor_from_server_exec.c_str();

    msg_task_t start_task = MSG_task_create("", 0, 0, meta);
    MSG_task_send(start_task, "FabricManager");

    while(1){
        msg_task_t packet_data = NULL;
        int res1 = MSG_task_receive(&packet_data, receive_from_lb_executor);
        if (!strcmp(MSG_task_get_name(packet_data), "finalize")){
            MSG_task_destroy(packet_data);

            msg_task_t fin_task = MSG_task_create("finalize", 0, 0, NULL);
            MSG_task_send(fin_task, send_to_fm_fabric);
            break;
        }
        // Send data to Fabric Manager
        MSG_task_send(packet_data, send_to_fm_fabric);
    }
    return 0;
}

int read_process_server(int argc, char *argv[]){
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


/*
 * int server_manager(int argc, char *argv[]){
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
 */

//        //Receive ACK form Fabric Manager
//        msg_task_t ack_from_fabric_manager;
//        MSG_task_receive(&ack_from_fabric_manager, receive_from_fm_fabric);
//        MSG_task_destroy(ack_from_fabric_manager);
//
//
//        //send ack to Load_balancer
//        msg_task_t acktask = MSG_task_create("", 0, 0, NULL);
//        MSG_task_send(acktask, send_to_lb_executor);
//        MSG_task_destroy(task);