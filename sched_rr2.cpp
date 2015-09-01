#include <utility>
#include <vector>
#include <queue>
#include "sched_rr2.h"
#include "basesched.h"
#include <iostream>

using namespace std;

SchedRR2::SchedRR2(vector<int> argn) {
	// Round robin recibe la cantidad de cores y sus cpu_quantum por parámetro
	
	quantums.resize(argn[0]);
	colaReady.resize(argn[0]);				//cantidad de colas = cantidad de cpus
	quantumsActuales.resize(argn[0]);
	cantTasks.resize(argn[0]);				//cantidad de tareas de cada cpu
	for(int i = 0; i < argn[0]; i++){
		quantums[i] = argn[i + 1];
		cantTasks[i] = 0;					//todas las cpu tienen cant tareas 0
		}
	quantumsActuales = quantums;
	
	
}

SchedRR2::~SchedRR2() {

}


void SchedRR2::load(int pid) {
	int cpu = cpuMenosTareas();		//busco cpu con menos tareas
	cantTasks[cpu]++;				//sumo una tarea al cpu
	colaReady[cpu].push(pid);		//agrego el pid a la colaReady del cpu con menos tareas
}

void SchedRR2::unblock(int pid) {
	int cpu;
	pair<int, int> taskCpu = cpuTareasBloqueadas.front();	//tomo primera tupla de la cola de (task,cpu)
	
	while((taskCpu.first) != pid){				//si no coincide el pid sigo en el loop
		cpuTareasBloqueadas.push(taskCpu);		//no es la tarea que busco, la encolo de vuelta
		cpuTareasBloqueadas.pop();				//saco la primera de la cola
		taskCpu = cpuTareasBloqueadas.front();	//pongo la que sigue
		}
	//la tarea a desbloquear ya no está en la cola cpuTareasBloqueadas
	//tengo la tarea y el cpu al cual pertenece en la tupla taskCpu, la agrego en su cola correspondiente
	cpu = taskCpu.second;		
	colaReady[cpu].push(pid);		
}

int SchedRR2::tick(int cpu, const enum Motivo m) {
	int nextPid;
	
		switch (m) {
    	case TICK:
     	//Si la tarea era IDLE_TASK y no hay ninguna tarea en la cola, sigue ejecutando IDLE_TASK 
    		if (current_pid(cpu) == IDLE_TASK){
				if (!colaReady[cpu].empty()){
					quantumsActuales[cpu] = quantums[cpu];	//cpu reinicia quantum
       				nextPid = colaReady[cpu].front();		//sigue la próxima en la cola(siempre hay una tarea!!!!)
       				colaReady[cpu].pop();					//y se quita de la cola
				}else{
					nextPid = IDLE_TASK;					//si no hay tareas en la cola sigue IDLE_TASK
					}
    		}else{
       			quantumsActuales[cpu]--;
       			if (quantumsActuales[cpu] == 0){
					//se quedó sin tiempo
       				colaReady[cpu].push(current_pid(cpu));	//pongo la tarea actual en la cola
       				quantumsActuales[cpu] = quantums[cpu];	//cpu reinicia quantum
       				nextPid = colaReady[cpu].front();			//sigue la próxima en la cola(siempre hay una tarea!!!!)
       				colaReady[cpu].pop();						//y se quita de la cola
       			}else{
       				//le queda tiempo, sigue ejecutando la misma
       				nextPid = current_pid(cpu);
       			}
       		}
       		break;
    	case BLOCK:
			{//formo la tupla de tarea bloqueada con su respectivo cpu
			pair<int, int> blockedTask (current_pid(cpu), cpu); //***********VER SI ESTA BIEN ESTO************
			cpuTareasBloqueadas.push(blockedTask);				//la pongo en la cola de tareas bloqueadas
			if(!colaReady[cpu].empty()){						//si hay tareas en la cola, mando la que sigue
				nextPid = colaReady[cpu].front();	
				colaReady[cpu].pop();						//la saco de la cola
				quantumsActuales[cpu] = quantums[cpu];	//actualizo el quantum
			}else{
				nextPid = IDLE_TASK;					//sino mando la IDLE_TASK
				}
			break;
		}
    	case EXIT:
			cantTasks[cpu]--;				//resto la cantidad de tareas en el cpu
			
			if(!colaReady[cpu].empty()){						//si hay tareas en la cola, mando la que sigue
				nextPid = colaReady[cpu].front();				
				colaReady[cpu].pop();
				quantumsActuales[cpu] = quantums[cpu];
			}else{
				nextPid = IDLE_TASK;
				}
			break;
	} 

	return nextPid;

}

int SchedRR2::cpuMenosTareas(){
	int cpu = 0;
	for(unsigned int i = 0; i < cantTasks.size(); i++){
		cpu = (cantTasks[cpu]<=cantTasks[i])? cpu : i;
	}
	
	return cpu;
}
