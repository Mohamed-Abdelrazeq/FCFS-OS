#include <stdio.h>
#include <stdlib.h>

// STRUCTURE
struct process_struct
{
	int pid;
	int at; // Arrival Time
	int pt; // CPU Burst time
	int bt;
	int tr;// Completion, waiting, turnaround, response time
} ps[100], rq[30], bq[100], current_proccess,out[100];

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
	int i = 0;
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
	// usage
	int usageCounter = 0;
	int endFlag = 1;

	printf("Enter total number of processes: ");
	scanf("%d", &n);

	// DEFAULT VALUES
	for (int i = 0; i < 30; i++)
	{
		rq[i].pid = 999;
		rq[i].tr = 0;
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
	
	int howManyAreIn = 0;
	// LOGIC
	while (endFlag != 0 || howManyAreIn != n)
	{

		int block = 0;
		endFlag = 0;

		printf("\n%d ", i);

		// CHECK BQ
		if (bqf != 0)
		{

			for (int j = bqe; j < bqf; j++)
			{

				if (bq[j].bt != 0)
				{
					bq[j].tr++; 
					bq[j].bt = bq[j].bt - 1;
					printf("%d: BLOCKED ", bq[j].pid);
					endFlag = 1;
				}

				else
				{
					rq[rqf] = bq[j];
					bqe++;
					// f is bigger
					rqf++;
				}

			}

		}

		// CHECK RFT
		if (i == rft && rft != 0)
		{

			if (current_proccess.bt == 0)
			{
				out[current_proccess.pid] = current_proccess;
			}
			else if(!block)
			{
				current_proccess.tr++;
				bq[bqf] = current_proccess;
				bq[bqf].bt = bq[bqf].bt - 1;
				bqf++;

				printf("%d: BLOCKED ", current_proccess.pid);
				endFlag = 1;
			}
			is_running = 0;

		}

		// CHECK AT
		for (int k = 0; k < n; k++)
		{
			if (ps[k].at == i){
				howManyAreIn++;
			}
			if (ps[k].at == i && ps[k].pt != 0)
			{
				rq[rqf] = ps[k];
				rqf++;
			}
		}

		// CHECK RQ
		if (rqf != 0)
		{

			if (is_running)
			{
				current_proccess.tr++;
				printf("%d: RUNNING ", current_proccess.pid);
				usageCounter++;
				endFlag = 1;
				for (int k = 0; k < rqf - rqe; k++)
				{
					rq[k + rqe].tr++;
					printf("%d: READY ",rq[k + rqe].pid);
					endFlag = 1;

				}
			}

			if (!is_running && rqf != rqe)
			{
				
				struct process_struct temp[rqf - rqe];

				for (int k = 0; k < rqf - rqe; k++)
				{
					temp[k] = rq[rqe + k];
				}

				qsort((void *)temp, rqf - rqe, sizeof(struct process_struct), comparatorPID);

				for (int k = 0; k < rqf - rqe; k++)
				{
					temp[k].tr++;
					rq[rqe + k] = temp[k];
					if (k != 0) printf("%d: READY ",rq[k + rqe].pid);
					endFlag = 1;
				}

				printf("%d: RUNNING ", temp[0].pid);
				usageCounter++;
				endFlag = 1;
				rft = i + temp[0].pt;
				is_running = 1;
				current_proccess = temp[0];
				rqe++;
			}
			
			
		}
		i++;
	}

	printf("\nFinishing Time : %d\n",i - 2);
	float utlization = (float)usageCounter/(float)(i-1);
	printf("CPU Utilization : %f\n",utlization);
	for (int p = 0; p < n; p++){
		printf("Turnaround Time of Proccess : %d: %d\n",out[p].pid,out[p].tr);
	}

	return 0;
}
