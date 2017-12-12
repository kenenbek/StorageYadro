//
// Created by kenenbek on 05.12.17.
//

#include <simgrid/msg.h>
#include "my_functions.h"
#include "storage.h"

XBT_LOG_NEW_DEFAULT_CATEGORY(client, "Messages specific for client");

int client(int argc, char *argv[]){
    int number_of_tests = 1;

    while (true){
        if (number_of_tests == 0) break;
        srand (time(NULL));
        int type = 1; //rand() % 2;

        switch(type){
            case 0:
                for (int i = 0; i < 500; ++i) {
                    MSG_process_create("read_request_client", read_request_client, NULL, MSG_host_self());
                    MSG_process_sleep(0.02);
                }
                break;
            case 1:
                for (int j = 0; j < 1000000; ++j) {
                    MSG_process_create("write_request_client", write_request_client, NULL, MSG_host_self());
                    MSG_process_sleep(0.02);
                }
                break;
        }
        number_of_tests--;
    }
    msg_task_t f_task = MSG_task_create("finalize", 0, 1, NULL);
    MSG_task_send(f_task, "Server1");
    return 0;
}


int read_request_client(int argc, char *argv[]){
    auto id = new ID("/kotok/kotok");
    msg_task_t task = MSG_task_create("name", 0, 10, id);
    MSG_task_send(task, "Server1");
    return 0;
}


int write_request_client(int argc, char *argv[]){
    auto dataset = new DataSet(0.5*1e9, "/JBOD1/avastSS.scr");
    msg_task_t task = MSG_task_create("name", 1, dataset->size, dataset);
    MSG_task_send(task, "Server1");
    return 0;
}

int receive_read_from_server(int argc, char *argv[]){

    return 0;
}