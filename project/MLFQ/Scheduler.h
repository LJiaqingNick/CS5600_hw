#ifndef SCHEDULER_H
#define SCHEDULER_H
#include <iostream>
#include <vector>
#include "Queue.h"
#include "Job.h"

class Scheduler{
private:
    int levels;
    std::vector<Queue*> queues;
    int boostFrequency;
    int nextBoost;
    int time;
    int pid;
    Queue* finished = new Queue();

public:
    Scheduler(int levels_i=1, int boostFrequency_i=0);
    void addJob(int runtime);
    bool isBoostTime();
    void boost();
    int getBoostFrequency();
    int getLevels();
    int getTime();
    void run();
    void getResult();
    int jobsLeft();
};
#endif // SCHEDULER_H
