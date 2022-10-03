#include "Job.h"

Job::Job(int pid_i, int runtime_i, int allotment_i, int startTime_i) {
    pid = pid_i;
    runtime = runtime_i;
    allotment = allotment_i;
    arrivalTime = startTime_i;
    finishTime = 0;
    startRuntime = runtime_i;
    isFirstExec = false;
}

int Job::getPid() {
    return pid;
}

bool Job::isJobFinish() {
    return runtime == 0;
}

void Job::run() {
    runtime = runtime - 1;
    timeslice = timeslice - 1;
    if (!isFirstExec) {
        isFirstExec = true;
    }
    if (timeslice == 0) {
        if (allotment > 0) {
            timeslice = 10;
            allotment--;
        }
    }
}

bool Job::isFirstExected() {
    return isFirstExec;
}

int Job::getTimeslice() {
    return timeslice;
}
int Job::getAllotment() {
    return allotment;
}

int Job::getRuntime() {
    return runtime;
}

int Job::getArrivalTime() {
    return arrivalTime;
}

int Job::getFinishTime() {
    return finishTime;
}

int Job::getFirstExecTime() {
    return firstExecTime;
}
int Job::getStartRuntime() {
    return startRuntime;
}

void Job::setFirstExecTime(int time) {
    firstExecTime = time;
}
void Job::setTimeslice(int time) {
    timeslice = time;
}
void Job::setAllotment(int allotment_i) {
    allotment = allotment_i;
}

void Job::setArrivalTime(int time) {
    arrivalTime = time;
}

void Job::setFinishTime(int time) {
    finishTime = time;
}
