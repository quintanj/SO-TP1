#ifndef __SCHED_RR2__
#define __SCHED_RR2__

#include <vector>
#include <queue>
#include <tuple>
#include "basesched.h"

class SchedRR2 : public SchedBase {
	public:
		SchedRR2(std::vector<int> argn);
        ~SchedRR2();
		virtual void load(int pid);
		virtual void unblock(int pid);
		virtual int tick(int cpu, const enum Motivo m);
		
		
		std::vector<queue<int> > colaReady; 				//vector de colasReady de cada cpu
		std::vector<int> quantums; 							//vector de quantums de cada cpu
		std::vector<int> quantumsActuales; 					//vector de quantumsActuales de cada cpu
		std::vector<int> cantTasks;							//cantidad de tareas en un cpu BLOCKED + READY + RUNNING
		std::queue<tuple<int, int> > cpuTareaBloqueada;	 	//vector de quantumsActuales de cada cpu
		
};

#endif
