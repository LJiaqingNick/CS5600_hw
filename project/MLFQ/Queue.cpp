#include "Queue.h"
#define TIMESLICE 10

Queue::Queue() {
    maxAllotment = 1;
    timeslice = TIMESLICE;
    currentJobPos = 0;
}

int Queue::getSize() {
    return (int)jobs.size();
}

Job* Queue::getJob(int pos) {
    return jobs.at(pos);
}

int Queue::getMaxAllotment() {
    return maxAllotment;
}

int Queue::getTimeslice() {
    return timeslice;
}

void Queue::addJob(Job* job) {
    jobs.push_back(job);
}

int Queue::getCurrentJobPos() {
    return currentJobPos;
}

Job* Queue::getCurrentJob() {
    return jobs[currentJobPos];
}

void Queue::goToNextJob() {
    if (currentJobPos >= (jobs.size()-1)) {
        currentJobPos = 0;
    } else {
        currentJobPos++;
    }
}

void Queue::setCurrentJobPos(int pos) {
    currentJobPos = pos;
}

void Queue::moveJobToTargetQ(Queue* queue) {
    Job* job = jobs.at(currentJobPos);
    queue->addJob(job);
    jobs.erase(jobs.begin() + currentJobPos);
}
