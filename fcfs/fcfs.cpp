//Take (5) jobs with release time and execution time and assign them on a single processor based on the First Come First Serve Basis
#include<iostream>
#include<queue>
using namespace std;

#define tab "\t"
#define dtab "\t\t"
struct job{
	int release_time;
	int execution_time;
};

bool operator<(const job &a, const job &b){
	return a.release_time > b.release_time;
}

void input_jobs(priority_queue<job> &pq){
	int n;
	cout<<"Enter the number of jobs to be scheduled.\n";
	cin>>n;
	for(int i=0; i<n; ++i){
		job j;
		cout<<"\nEnter the release time and execution time of the job\n";
		cin>>j.release_time>>j.execution_time;
		pq.push(j);
	}
}

void print_job(int &time, float &waiting_time, job j){
	cout<<endl<<j.release_time<<dtab<<time<<dtab<<j.execution_time<<endl;
	waiting_time += time - j.release_time;
	time += j.execution_time;
}


void assign_to_processor(priority_queue<job> pq){
	int n = pq.size();
	int time = 0;
	float waiting_time = 0;
	cout<<endl<<"release_time"<<tab<<"execution started"<<tab<<"execution_time"<<endl;
	for(int i=0; i<n; ++i){
		print_job(time, waiting_time,  pq.top());
		pq.pop();
	}
	cout<<"\nAverage waiting time for the given set of jobs on a single processor for the first come first serve basis is\t";
	cout<<waiting_time/n<<endl;
}


int main(){
	priority_queue<job> pq;
	input_jobs(pq);

	assign_to_processor(pq);
return 0;
}
