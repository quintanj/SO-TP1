#include <vector>
#include <queue>
#include "sched_rr.h"
#include "basesched.h"
#include <iostream>
#include <stdio.h>

using namespace std;

SchedRR::SchedRR(vector<int> argn) {
	// Round robin recibe la cantidad de cores y sus cpu_quantum por parámetro
	
	quantums.resize(argn[0]);					//establece tam del vector
	
	for(int i = 0; i < argn[0]; i++){			
		quantums[i] = argn[i+1];				//cargamos los quantums
	}
	quantumsActuales = quantums;				//cargamos a quantumsActuales
}

SchedRR::~SchedRR() {

}


void SchedRR::load(int pid) {
	colaReady.push(pid);			//agregamos el elemento a la cola ready
}

void SchedRR::unblock(int pid) {
	colaReady.push(pid);				//el elemento se desbloqueó, vuelve a la colaReady
}

int SchedRR::tick(int cpu, const enum Motivo m) {
	
	int nextPid;
	
	switch (m) {

    	case TICK:
     	//Si la tarea era IDLE_TASK y no hay ninguna tarea en la cola, sigue ejecutando IDLE_TASK 
    		if (current_pid(cpu) == IDLE_TASK){
				if (!colaReady.empty()){
					quantumsActuales[cpu] = quantums[cpu];	//cpu reinicia quantum
       				nextPid = colaReady.front();			//sigue la próxima en la cola(siempre hay una tarea!!!!)
       				colaReady.pop();						//y se quita de la cola
				}else{
					nextPid = IDLE_TASK;					//si no hay tareas en la cola sigue IDLE_TASK
					}
    		}else{
       			quantumsActuales[cpu]--;
       			if (quantumsActuales[cpu] == 0){
					//se quedó sin tiempo
       				colaReady.push(current_pid(cpu));		//pongo la tarea actual en la cola
       				quantumsActuales[cpu] = quantums[cpu];	//cpu reinicia quantum
       				nextPid = colaReady.front();			//sigue la próxima en la cola(siempre hay una tarea!!!!)
       				colaReady.pop();						//y se quita de la cola
       			}else{
       				//le queda tiempo, sigue ejecutando la misma
       				nextPid = current_pid(cpu);
       			}
       			
       		}
       		break;

    	case BLOCK:
			if(!colaReady.empty()){						//si hay tareas en la cola, mando la que sigue
				nextPid = colaReady.front();	
				colaReady.pop();						//la saco de la cola
				quantumsActuales[cpu] = quantums[cpu];	//actualizo el quantum
			}else{
				nextPid = IDLE_TASK;					//sino mando la IDLE_TASK
				}
			break;
    	case EXIT:
			if(!colaReady.empty()){						//si hay tareas en la cola, mando la que sigue
				nextPid = colaReady.front();
				colaReady.pop();
				quantumsActuales[cpu] = quantums[cpu];
			}else{
				nextPid = IDLE_TASK;
				}
			break;
	} 

	return nextPid;
}




