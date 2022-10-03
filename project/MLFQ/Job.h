#include <iostream>
#ifndef JOB_H
#define JOB_H
class Job{
private:
    int pid;
    int allotment;
    int timeslice;
    int runtime;
    int arrivalTime;
    int finishTime;
    bool isFirstExec;
    int firstExecTime;
    int startRuntime;
public:
    Job(int pid_i, int runtime_i, int allotment_i=1, int startTime_i=0);
    bool isJobFinish();
    void run();
    int getTimeslice();
    int getAllotment();
    int getPid();
    int getRuntime();
    int getArrivalTime();
    int getFinishTime();
    int getFirstExecTime();
    int getStartRuntime();
    bool isFirstExected();
    void setArrivalTime(int time);
    void setTimeslice(int time);
    void setAllotment(int allotment_i);
    void setFinishTime(int time);
    void setFirstExecTime(int time);
};
#endif // JOB_H
