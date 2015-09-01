#ifndef __SCHED_RR2__
#define __SCHED_RR2__

#include <vector>
#include <queue>
#include <utility>
#include "basesched.h"
#include <iostream>

class SchedRR2 : public SchedBase {
	public:
		SchedRR2(std::vector<int> argn);
        ~SchedRR2();
		virtual void load(int pid);
		virtual void unblock(int pid);
		virtual int tick(int cpu, const enum Motivo m);
		
	private:
		std::vector<std::queue<int> > colaReady; 				//vector de colasReady de cada cpu
		std::vector<int> quantums; 								//vector de quantums de cada cpu
		std::vector<int> quantumsActuales; 						//vector de quantumsActuales de cada cpu
		std::vector<int> cantTasks;								//cantidad de tareas en un cpu (BLOCKED + READY + RUNNING)
		std::queue<std::pair<int, int> > cpuTareasBloqueadas;	//vector de quantumsActuales de cada cpu
		int cpuMenosTareas();									//devuelve el cpu con menos tareas (BLOCKED + READY + RUNNING)
};

#endif


//    condition ? value_if_true : value_if_false

