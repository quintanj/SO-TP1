#include <vector>
#include <queue>
#include "sched_rr.h"
#include "basesched.h"
#include <iostream>

using namespace std;

SchedRR::SchedRR(vector<int> argn) {
	// Round robin recibe la cantidad de cores y sus cpu_quantum por parámetro
	vector<int> quantums(argn[0]);
	for(int i = 0; i < argn[0]; i++){
		quantums[i] = argn[i+1];		//cargamos los quantums
	}
	queue<int> colaReady;
}

SchedRR::~SchedRR() {

}


void SchedRR::load(int pid) {
	this->colaReady.push(pid);			//agregamos el elemento a la cola ready
}

void SchedRR::unblock(int pid) {
	//agregar a la cola
}

int SchedRR::tick(int cpu, const enum Motivo m) {
	int nextPid;
	switch (m) {

    	case TICK :
    		if (current_pid(cpu) == IDLE_TASK && !colaReady.empty()){
    			nextPid = IDLE_TASK;
    		}else{

       			quantumsActuales[cpu]--;
       			if (quantumsActuales[cpu] > 0){
       				nextPid = current_pid(cpu);
       			}else{
       				colaReady.push(current_pid(cpu));
       				quantumsActuales[cpu] = quantums[cpu];
       				nextPid = colaReady.front();
       				colaReady.pop();
       			}
       		break;
       		}

    	case BLOCK :/*
    		quantumsActuales[cpu] = quantums[cpu];
			if(!colaReady.empty()){
    			nextPid = colaReady.pop();

    		}else{
        		nextPid = IDLE_TASK;
        	}    		
        	*/
        	break;

    	case EXIT :
    		//reestablecemos el quantum actual del procesador correspondiente
    		quantumsActuales[cpu] = quantums[cpu];	

    		if(!colaReady.empty()){
    			nextPid = colaReady.front();
    			colaReady.pop();

    		}else{
        		nextPid = IDLE_TASK;
        	}
        	break;

    	default: cout << "Motivo entro mal" << endl;
	} 

	return nextPid;
}




