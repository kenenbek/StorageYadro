/* Copyright (c) 2014-2016. The SimGrid Team. All rights reserved.          */

/* This program is free software; you can redistribute it and/or modify it
 * under the terms of the license (GNU LGPL) which comes with this package. */

#include <chrono>
#include <simgrid/msg.h>
#include <simgrid/plugins/file_system.h>
#include "my_functions.h"

#define INMEGA (1024*1024)

XBT_LOG_NEW_DEFAULT_CATEGORY(YADRO, "Messages specific for YADRO");

int main(int argc, char **argv)
{
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

    MSG_init(&argc, argv);
    MSG_storage_file_system_init();
    MSG_create_environment(argv[1]);

    MSG_function_register("load_balancer", load_balancer);
    MSG_function_register("server_manager", server_manager);
    MSG_function_register("PCIeFabric_manager", PCIeFabric_manager);
    MSG_function_register("Cache_manager", cache_manager);
    MSG_function_register("adapter_manager", adapter_manager);
    MSG_function_register("drive", drive);
    MSG_function_register("traffic_counter_sender", traffic_counter_sender);
    MSG_function_register("traffic_counter_receiver", traffic_counter_receiver);
    MSG_function_register("cpu_counter", cpu_counter);

    MSG_launch_application(argv[2]);

    int res = MSG_main();

    XBT_INFO("Simulation time %g", MSG_get_clock());

    return res != MSG_OK;
}
