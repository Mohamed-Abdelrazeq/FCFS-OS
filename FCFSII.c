/*.................C Program to Implement FCFS ( First Come First Serve ) CPU SCheduling Algorithm.....................
FCFS - A Non Preemptive Algorithm
This Program works for same as well as different arrival times
Video Explanation: https://www.youtube.com/watch?v=M9Hj6u3H2tA&list=PLVKIC9j3jSYtCEAffM_51qVWeQus70cqc&index=7
*/
#include <stdio.h>
#include <stdlib.h>
struct process_struct
{
  int pid;
  int at; // Arrival Time
  int pt; // CPU Burst time
  int bt;
  int ct, wt, tat, rt, start_time;             // Completion, waiting, turnaround, response time
} ps[100], rq[100], bq[100], current_proccess; // Array of structure to store the info of each process.

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
  int rqe = 0;
  int rqf = 0;
  int bqe = 0;
  int bqf = 0;
  int rft = 0;
  int is_running = 0;
  printf("Enter total number of processes: ");
  scanf("%d", &n);

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

  // SORT AT
  qsort((void *)ps, n, sizeof(struct process_struct), comparatorAT);

  // LOGIC
  for (int i = 0; i < 100; i++)
  {

    // CHECK RFT
    if (i == rft && rft != 0)
    {

      if (current_proccess.bt == 0)
      {
        is_running = 0;
        printf("%D ENDED\n", current_proccess.pid);
        rqe++;
      }
      else
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
        rq[rqf] = ps[k];
        rqf++;
      }
    }

    // printf("%d",rqf);

    // CHECK BQ
    if (bqf != 0)
    {

      for (int j = 0; j < bqf; j++)
      {
        
        if (bq[j].bt != 0)
        {
          bq[j].bt = bq[j].bt - 1;
          printf("%d BLOCKED\n", bq[j].pid);
        }

        else
        {
          rq[rqf] = bq[j];
          rqf++;
        }
      }

    }

    // CHECK RQ
    if (rqf != 0 && rqf != rqe)
    {

      qsort((void *)rq, rqf, sizeof(struct process_struct), comparatorPID);

      if (!is_running)
      {
        printf("%d  STARTED RUNNING\n", rq[rqe].pid);
        rft = i + rq[rqe].pt;
        is_running = 1;
        current_proccess = rq[rqe];
        rqe++;
      }
      else
      {
        printf("%d STILL RUNNING\n", current_proccess.pid);
      }
    }

    printf("\n++++++++++++++++%d\n", i);
  }

  // SORT PID
  qsort((void *)ps, n, sizeof(struct process_struct), comparatorPID);

  // OUTPUT
  printf("\nProcess No.\tAT\tBT\tCPU Burst Time\tCT\tTAT\tWT\tRT\n");
  for (int i = 0; i < n; i++)
    printf("%d\t\t%d\t%d\t%d\t\t%d\t%d\t%d\t%d\n", ps[i].pid, ps[i].at, ps[i].bt, ps[i].pt, ps[i].ct, ps[i].tat, ps[i].wt, ps[i].rt);

  printf("\n");

  return 0;
}