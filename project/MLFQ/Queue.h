#ifndef QUEUE_H
#define QUEUE_H
#include <vector>
#include "Job.h"
class Queue{
private:
    int maxAllotment;
    int timeslice;
    std::vector<Job*> jobs;
    int currentJobPos;
public:
    Queue();
    void addJob(Job* job);
    int findJobPos(Job* job);
    Job* removeJob(Job* job);
    int getSize();
    Job* getJob(int pos);
    Job* getCurrentJob();
    int getCurrentJobPos();
    int getMaxAllotment();
    int getTimeslice();
    void goToNextJob();
    void setCurrentJobPos(int pos);
    void moveJobToTargetQ(Queue* queue);
};
#endif // QUEUE_H
