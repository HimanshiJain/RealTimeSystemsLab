#include<iostream>
#include<vector>
#include<algorithm>
#include<queue>
using namespace std;

#define tab "\t"
#define dtab "\t\t"

struct job{
	int release_time;
	int execution_time;
	int priority;
	char job_id;
};

struct priqu{
	bool operator()(const job &a, const job &b){ //higher number means higher priority
		return a.priority<b.priority;
	}
};

bool operator<(const job &a, const job &b){ //ascending order of release_time
	return a.release_time<b.release_time;
}

void input_jobs(vector<job> &jobs){
	int n;
	cout<<"Enter the number of jobs to be scheduled.\n";
	cin>>n;
	for(int i=0; i<n; ++i){
		job j;
		cout<<"\nEnter the job_id, priority, release time and execution time of the job\n";
		cin>>j.job_id>>j.priority>>j.release_time>>j.execution_time;
		jobs.push_back(j);
	}
	sort(jobs.begin(), jobs.end());
	for(int i=0; i<jobs.size(); ++i){
		cout<<jobs[i].job_id<<tab<<jobs[i].release_time<<endl;
	}
}

void populate_pq(vector<job> jobs, int time, vector<int> &in_q, priority_queue<job, vector<job>, priqu> &pq){

	int index = 0;
	while(index<jobs.size() && jobs[index].release_time <= time){
		if(in_q[index] == 0){
			pq.push(jobs[index]);
			in_q[index] = 1;
		}
		index++;
	}
}

void execute_job(job j, int &time, float &waiting_time){
	cout<<j.job_id<<dtab<<j.priority<<dtab<<j.release_time<<dtab<<time<<dtab<<j.execution_time<<endl;
	waiting_time += time - j.release_time;
	time += j.execution_time;
}

void priority_non_pre(vector<job> &jobs){
	int time = jobs[0].release_time;
	priority_queue<job, vector<job>, priqu> pq;
	vector<int> in_q (jobs.size(), 0);
	populate_pq(jobs, time, in_q, pq);
	float waiting_time = 0;
	cout<<"job_id"<<tab<<"Priority"<<tab<<"release_time"<<tab<<"execution started"<<tab<<"execution_time"<<endl;
	while(!pq.empty()){
		execute_job(pq.top(), time, waiting_time);
		pq.pop();
		populate_pq(jobs, time, in_q, pq); //assuming overlapping jobs only i.e. case where processor may be idle is nor covered
	}	

	cout<<"\nThe average waiting time for the jobs through priority driven non preemptive approach is:\t"<<waiting_time/jobs.size()<<endl;
}
	
int main(){
	vector<job> jobs;
	input_jobs(jobs);
	priority_non_pre(jobs);
return 0;
}
