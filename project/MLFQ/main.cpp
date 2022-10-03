//
//  main.cpp
//  MLFQ
//
//  Created by Nick Liu on 2022-10-02.
//

#include <iostream>
#include "Scheduler.h"
#include "Job.h"

int main(int argc, const char * argv[]) {
    
    Scheduler* scheduler = new Scheduler(3);
    scheduler->addJob(10);
    scheduler->addJob(30);
    scheduler->addJob(20);
    scheduler->run();
    scheduler->getResult();
}
