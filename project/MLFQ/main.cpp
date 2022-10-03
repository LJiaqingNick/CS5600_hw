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
    
    Scheduler* scheduler = new Scheduler(3, 15);
    scheduler->addJob(50);
    for (int i = 0; i < 20; i++) {
        scheduler->addJob(15);
    }

    scheduler->run();
    scheduler->getResult();
}
