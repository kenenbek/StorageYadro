//
// Created by kenenbek on 28.11.17.
//

#ifndef STORAGEYADRO_MYFUNCTIONS_H
#define STORAGEYADRO_MYFUNCTIONS_H

#include <string>
#include <map>

int dataset_generator(int argc, char *argv[]);
int server(int argc, char *argv[]);
int client(int argc, char *argv[]);
int cache(int argc, char *argv[]);

int read_process_server(int argc, char *argv[]);
int write_process_server(int argc, char *argv[]);

int read_request_client(int argc, char *argv[]);
int write_request_client(int argc, char *argv[]);


int load_balancer(int argc, char *argv[]);
int server_manager(int argc, char *argv[]);
int server_executer(int argc, char *argv[]);
int PCIeFabric_manager(int argc, char *argv[]);
int PCIeFabric_executor(int argc, char *argv[]);
int cache_manager(int argc, char *argv[]);
int cache_executor(int argc, char *argv[]);
int adapter_manager(int argc, char *argv[]);
int load_balancer_packet_sender(int argc, char *argv[]);
int adapter_manager(int argc, char *argv[]);
#endif //STORAGEYADRO_MYFUNCTIONS_H

