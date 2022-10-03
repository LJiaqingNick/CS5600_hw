#include <iostream>
#include "Scheduler.h"

Scheduler::Scheduler(int levels_i, int boostFrequency_i){
    levels = levels_i;
    boostFrequency = boostFrequency_i;
    nextBoost = boostFrequency_i;
    time = 0;
    // used for assign the pid
    pid = 0;
    // -1 means no job
    int i;
    for (i = 0; i < levels; i++) {
        queues.push_back(new Queue());
    }
}

int Scheduler::getBoostFrequency() {
    return boostFrequency;
}

void Scheduler::addJob(int runtime) {
    pid++;
    Job* job = new Job(pid, runtime);
    job->setTimeslice(queues[0]->getTimeslice());
    job->setAllotment(queues[0]->getMaxAllotment());
    queues[0]->addJob(job);
}

int Scheduler::getLevels() {
    return levels;
}

int Scheduler::getTime() {
    return time;
}

int Scheduler::jobsLeft() {
    int i, jobsLeft;
    jobsLeft = 0;
    for (i = 0; i < levels; i++) {
        jobsLeft += queues[i]->getSize();
    }
    return jobsLeft;
}

void Scheduler::run() {
    if (jobsLeft() == 0) {
        return;
    }
    for (int i = 0; i < levels; i++) {
        while (queues[i]->getSize() > 0) {
            Job* currentJob = queues[i]->getCurrentJob();
            if (!currentJob->isFirstExected()) {
                currentJob->setFirstExecTime(time);
            }

            currentJob->run();
            std::cout << "(Time: " << time << ")" << " Job: " << currentJob->getPid() << ", runtime left: " << currentJob->getRuntime() << ", timeslice: " << currentJob->getTimeslice() << ", allotment: " << currentJob->getAllotment() << ", queue level: " << i << std::endl;
            time++;
            if (currentJob->getRuntime() == 0) {
                currentJob->setFinishTime(time);
                queues[i]->moveJobToTargetQ(finished);
            } else if (currentJob->getTimeslice() == 0) {
                if ((currentJob->getAllotment() == 0)) {
                    if (i == (levels - 1)) {
                        currentJob->setTimeslice(queues[i]->getTimeslice());
                        currentJob->setAllotment(queues[i]->getMaxAllotment());
                        queues[i]->goToNextJob();
                    } else {
                        queues[i]->moveJobToTargetQ(queues[i+1]);
                        queues[i]->goToNextJob();

                    }
                }

            }
            if (time == nextBoost && levels > 1) {
                boost();
                i = 0;
            }
        }
    }
}

void Scheduler::getResult() {
    double responseTime = 0;
    double turnaroundTime = 0;
    std::cout << "----------------------------------------------------------------------------------" << std::endl;
    std::cout << "Statics:" << std::endl;
    std::cout << "There are " << levels << " levels" << std::endl;
    std::cout << "Below are all the jobs:" << std::endl;
    //Dont forget to change back.
    int queueSize = finished->getSize();
    for (int i = 0; i < queueSize; i++) {
        Job* current = finished->getJob(i);
        std::cout << "Job " << current->getPid() << " runtime: " << current->getStartRuntime() << ", arrive time: " << current->getArrivalTime() << ", complete time: " << current->getFinishTime() << std::endl;
        responseTime = responseTime + current->getFirstExecTime() - current->getArrivalTime();
        turnaroundTime = turnaroundTime + current->getFinishTime() - current->getArrivalTime();
    }
    responseTime = responseTime / queueSize;
    turnaroundTime = turnaroundTime / queueSize;
    std::cout << "Average turnaround time: " << turnaroundTime << ", average response time: " << responseTime << std::endl;
}

void Scheduler::boost() {
    if (levels > 1) {
        Queue* target = queues[0];
        for (int i = 1; i < levels; i++) {
            for (int j = 0; j < queues[i]->getSize(); j++) {
                queues[i]->moveJobToTargetQ(j, target);
            }
            queues[i]->setCurrentJobPos(0);
        }
    }
}
