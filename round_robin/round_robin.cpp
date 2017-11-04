//Take (5) jobs with release time and execution time and assign them on a single processor based on the
//Round Robin Approach
#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

#define tab "\t"
#define dtab "\t\t"
#define quantum 5

struct job{
	char job_id;
	int release_time;
	int execution_time;
	int remaining_time;
	int last_execution;
};

bool operator<(const job &a, const job &b){
	return a.release_time > b.release_time;
}

void input_jobs(vector<job> &jobs){
	int n;
	cout<<"Enter the number of jobs to be scheduled.\n";
	cin>>n;
	for(int i=0; i<n; ++i){
		job j;
		cout<<"\nEnter the job_id (single char), release time and execution time of the job\n";
		cin>>j.job_id>>j.release_time>>j.execution_time;
		j.remaining_time = j.execution_time;
		j.last_execution = j.release_time;
		jobs.push_back(j);
	}

	sort(jobs.begin(), jobs.end());
	reverse(jobs.begin(), jobs.end());
}

void print_execution_stat(int time, job j){
	cout<<endl;
	cout<<j.job_id<<dtab<<j.release_time<<dtab<<time<<dtab;
}

void execute_jobs(vector<job> &jobs){
	int n = jobs.size();
	int exec_count = n;
	int time = 0;
	float waiting_time = 0;
	cout<<"\njob_id"<<tab<<"release_time"<<tab<<"execution started"<<tab<<"period of execution"<<tab<<"remaining_time\n";
	while(exec_count!=0){
		for(int i=0; i<n; ){
			if(jobs[i].release_time <=time && jobs[i].remaining_time>0){
				print_execution_stat(time, jobs[i]);
				if(jobs[i].remaining_time<quantum){
					cout<<jobs[i].remaining_time;
					time += jobs[i].remaining_time;
					jobs[i].remaining_time = 0;
					exec_count--;
				}else{
					cout<<5;
					waiting_time += time - jobs[i].last_execution;
					time +=quantum;
					jobs[i].last_execution = time;
					jobs[i].remaining_time -= quantum;
				}
				cout<<dtab<<tab<<jobs[i].remaining_time;
				++i;
			}else if(jobs[i].release_time >time ){
				time = jobs[i].release_time;
			}else {
				++i;
			}
		}
	}

	cout<<"\nAverage waiting time for round robin approach is \t"<<waiting_time/n<<endl;

}

int main(){
	vector<job> jobs;
	input_jobs(jobs);
	
	execute_jobs(jobs);
	
return 0;
}
