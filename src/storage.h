//
// Created by kenenbek on 04.12.17.
//

#ifndef STORAGEYADRO_STORAGE_H
#define STORAGEYADRO_STORAGE_H

#include <iostream>
#include <queue>
#include <cstdlib>
#include <algorithm>
#include <simgrid/msg.h>
#include "storage.h"

class Event{
public:
    double startTime;
    double endTime;
    double remainingSize;
    double sentSize;
    double size;

    Event(double start, double dur_time, double size);
    Event(double start, double size);
    bool operator<(const Event& otherEvent) const;
    bool operator<(const double& currentTime) const;
    bool operator() (const Event & event, const double & right);
    friend std::ostream& operator << (std::ostream& os, const Event& event);
};

class DataSet{
public:
    double size;
    double remainingSize;
    std::string fullPath;

    explicit DataSet(double sz, std::string path);
};

class ID{
public:
    std::string fullPath;

    explicit ID(std::string name);
};


class  Storage{
public:
    std::string name;
    double writeRate;
    double readRate;
    double fullSize;
    double lastTimeRequest;
    std::vector<Event> readQueue;
    std::vector<Event> writeQueue;

    explicit Storage(std::string name, double readRate, double writeRate);
    ~Storage();
    int write(DataSet& dataSet);
    int read(int id);
    void updateDuration(std::vector<Event>& queue, DataSet& dataSet);
    void deleteOcurredEventsFromQueue(std::vector<Event>& queue);
};

#endif //STORAGEYADRO_STORAGE_H
