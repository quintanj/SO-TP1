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
}

int SchedRR2::tick(int cpu, const enum Motivo m) {
}
