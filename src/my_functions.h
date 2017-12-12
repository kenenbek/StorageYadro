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

#endif //STORAGEYADRO_MYFUNCTIONS_H
