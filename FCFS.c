#include <stdio.h>
#include <stdlib.h>

// STRUCTURE
struct process_struct
{
	int pid;
	int at; // Arrival Time
	int pt; // CPU Burst time
	int bt;
	int ct, wt, tat, rt, start_time; // Completion, waiting, turnaround, response time
} ps[100], rq[10], bq[100], current_proccess;

// FUNCTIONS
int findmax(int a, int b)
{
	return a > b ? a : b;
}

int comparatorAT(const void *a, const void *b)
{
	int x = ((struct process_struct *)a)->at;
	int y = ((struct process_struct *)b)->at;
	if (x < y)
		return -1; // No sorting
	else
		return 1; // Sort
}

int comparatorPID(const void *a, const void *b)
{
	int x = ((struct process_struct *)a)->pid;
	int y = ((struct process_struct *)b)->pid;
	if (x < y)
		return -1; // No sorting
	else
		return 1; // Sort
}

int main()
{

	int n;
	// Run Queue
	int rqe = 0;
	int rqf = 0;
	// Block Queue
	int bqe = 0;
	int bqf = 0;
	// Run Finish Time
	int rft = 0;
	int is_running = 0;
	int conflict = 0;

	printf("Enter total number of processes: ");
	scanf("%d", &n);

	// DEFAULT VALUES
	for (int i = 0; i < 10; i++)
	{
		rq[i].pid = 999;
	}
	// STANDARD SCAN
	for (int i = 0; i < n; i++)
	{
		// SCAN PROCCESS NUMBER
		scanf("%d", &ps[i].pid);
		// SCAN PROCCESSING TIME
		scanf("%d", &ps[i].pt);
		// SCAN BLOCKING TIME
		scanf("%d", &ps[i].bt);
		// SCAN ARRIVAL TIME
		scanf("%d", &ps[i].at);
	}
	// LOGIC
	for (int i = 0; i < 10; i++)
	{

		int block = 0;

		printf("\n++++++++++++++++%d\n", i);


		// CHECK BQ
		if (bqf != 0)
		{

			for (int j = 0; j < bqf; j++)
			{

				if (bq[j].bt != 0)
				{
					bq[j].bt = bq[j].bt - 1;
					printf("%d BLOCKED TIME LEFT = %d\n", bq[j].pid,bq[j].bt);
					block=1;
				}

				else
				{
					rq[rqf] = bq[j];
					rqf++;
				}
			}
		}


		// CHECK RFT
		if (i == rft && rft != 0)
		{

			if (current_proccess.bt == 0)
			{
				is_running = 0;
				printf("%D ENDED\n", current_proccess.pid);
				rqe++;
			}
			else if(!block)
			{
				bq[bqf] = current_proccess;
				is_running = 0;
				printf("%d BLOCKED\n", current_proccess.pid);
				bqf++;
			}
		}

		// CHECK AT
		for (int k = 0; k < n; k++)
		{
			if (ps[k].at == i)
			{
				printf("%d Proccess added to RQ\n", ps[k].pid);
				printf("rqf of this proccess is %d\n", rqf);
				rq[rqf] = ps[k];
				rqf++;
			}
		}

	
		// CHECK RQ
		if (rqf != 0 && rqf != rqe)
		{

			if (!is_running)
			{

				printf("CONFLICT\n");
				struct process_struct temp[rqf - rqe];
				for (int k = 0; k < rqf - rqe; k++)
				{
					temp[k] = rq[k];
				}

				qsort((void *)temp, rqf - rqe, sizeof(struct process_struct), comparatorPID);

				// TEST
				for (int k = 0; k < rqf-rqe; k++)
				{
					printf("TEST %d \n", temp[k].pid);
				}

				printf("%d  STARTED RUNNING\n", temp[0].pid);
				rft = i + temp[0].pt;
				is_running = 1;
				current_proccess = temp[0];
				rqe++;
			}
			else
			{
				printf("%d STILL RUNNING\n", current_proccess.pid);
			}
		}
	}

	return 0;
}
