//
// Created by kenenbek on 04.12.17.
//

#include "storage.h"

#include <iostream>
#include <queue>
#include <algorithm>
#include <simgrid/msg.h>
#include "storage.h"

XBT_LOG_NEW_DEFAULT_CATEGORY(storage, "Messages specific for this msg storage");

struct Print {           // function object type:
    void operator() (Event& event) {XBT_INFO("start: %.2f, end: %.2f", event.startTime, event.endTime);}
} PrintQueue;

/*============================================================
 * Event implementation
=============================================================*/

Event::Event(double start, double end, double sizex){
    startTime = start;
    endTime = end;
    size = sizex;
    remainingSize = size;
    sentSize = 0;
}

Event::Event(double start, double sizex){
    startTime = start;
    size = sizex;
    remainingSize = size;
    sentSize = 0;
}


bool Event::operator<(const Event& otherEvent) const
{
    return remainingSize < otherEvent.remainingSize;
}

bool Event::operator<(const double& currentTime) const
{
    return endTime < currentTime;
}

bool Event::operator() (const Event & event, const double & currentTime){
    return event.endTime < currentTime;
}

bool operator<(const double& currentTime, const Event & event){
    return event.endTime > currentTime;
};



/*============================================================
 * Dataset implementation
=============================================================*/
DataSet::DataSet(double sz, std::string path){
    size = sz;
    remainingSize = sz;
    fullPath = path;
}

/*============================================================
 * Document ID implementation
 *
=============================================================*/

ID::ID(std::string name) {
    fullPath = name;
}


/*============================================================
 * Storage implementation
=============================================================*/

int Storage::write(DataSet& dataSet){
//    if (writeQueue.size() > 0){
//        deleteOcurredEventsFromQueue(writeQueue);
//    }
    updateDuration(writeQueue, dataSet);
    lastTimeRequest = MSG_get_clock();
}

int Storage::read(int i){
    deleteOcurredEventsFromQueue(readQueue);
    //updateDuration(readQueue, dataSet);
    lastTimeRequest = MSG_get_clock();
    return 0;
}

Storage::Storage(std::string n, double r, double w){
    name = n;
    readRate = r;
    writeRate = w;
    lastTimeRequest = 0;
}

Storage::~Storage(){
    auto n = writeQueue.size();
    auto k = readQueue.size();
    std::for_each(writeQueue.begin(), writeQueue.end(), PrintQueue);
    std::for_each(readQueue.begin(), readQueue.end(), PrintQueue);

}

void Storage::updateDuration(std::vector<Event>& queue, DataSet& dataSet){
    /*
     * Updates duratuion for all events in the queue
     * Returns duration for a new Events
     */
    auto bandwidth = writeRate;
    double currentTime = MSG_get_clock();
    auto n = queue.size();
    if (n == 0){
        Event event(currentTime, currentTime + dataSet.size/bandwidth, dataSet.size);
        queue.push_back(event);
        return;
    }
    double currentMoment = MSG_get_clock();

    double lastMoment = lastTimeRequest;
    for(auto i = 0; i < n; ++i) {
        if (queue[i].endTime < currentMoment) {
            for (auto j = i; j < n; ++j){
                queue[j].sentSize += bandwidth / (n - i) * (queue[i].endTime - lastMoment);
                queue[j].remainingSize = queue[j].size - queue[j].sentSize;
            }
        } else{
            for (int k = i; k < n; ++k) {
                queue[k].sentSize += (bandwidth / (n - k)) * (currentMoment - lastMoment);
                queue[k].remainingSize = queue[k].size - queue[k].sentSize;
            }
            break;
        }
        lastMoment = queue[i].endTime;
    }

    if (queue.size() > 0){
        deleteOcurredEventsFromQueue(writeQueue);
        n = queue.size();
    }

    //Add new Event to the queue
    Event event(currentTime, dataSet.size);
    queue.push_back(event);
    std::sort(queue.begin(), queue.end());

    // Update each time of the EVENT queue
    for(auto i = 0; i < n + 1; ++i) {

        double currentBandwidth = bandwidth / (n - i + 1);
        double newBandwidth = bandwidth / (n - i);

        double minDuration = queue[i].remainingSize / currentBandwidth;
        queue[i].endTime = currentMoment + queue[i].remainingSize / currentBandwidth;

        for(auto j = i + 1; j < n + 1; ++j) {
            queue[j].remainingSize -= currentBandwidth * minDuration;
            queue[j].endTime = currentMoment + queue[j].remainingSize / newBandwidth;
        }

        currentMoment += minDuration;
    }
}


void Storage::  deleteOcurredEventsFromQueue(std::vector<Event>& queue){
    auto up = std::upper_bound(queue.begin(), queue.end(), MSG_get_clock());
    std::for_each(queue.begin(), up, PrintQueue);

    queue.erase(queue.begin(), up);

    //exit(0);
}


/*============================================================
=============================================================*/

//friend std::ostream& Event::operator << (std::ostream& os, const Event& event) {
//    os << event.endTime << std::endl;
//    return os ;
//}
//bool Event::operator() (const Event & left, const Event & right)
//{
//    return left.remainingSize < right.remainingSize;
//}

bool comp (Event& i, Event& j) {
    return (i.remainingSize < j.remainingSize);
}
