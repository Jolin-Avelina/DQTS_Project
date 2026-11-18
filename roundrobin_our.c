#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAXP 20
#define QUANTUM 1
// later change to 0.1

struct Process
{
    int pid; // replace with pid_t later if needed
    int a;   // int arrival time
    int b;   // burst time
    int c;   // completion time
    int rt;  // remaining time
    int tat; // turnaround time, leave empty at first, tat=c-a
    int wt;  // wait time, leave empty at first, wt=tat-bt
};

int RoundRobin()
{
    // initialize processes
    srand(time(0));
    int n, i, time=0, quantum = 0;
    struct Process processes[MAXP];
    float avg_tat = 0, avg_wt = 0;

    // set number of processes to 5 for now
    n = 5;

    // generate random AT and BT values for each processes
    // later replace this with that of sample processes

    for (i = 0; i < n; i++)
    {
        processes[i].pid = i + 1;
        processes[i].a = rand() % 10;
        processes[i].b = rand() % 10 + 1;
        processes[i].rt = processes[i].b;
    }

    // print out chart of a, b and rt
    printf("PN A B R\n");
    for (i = 0; i < n; i++)
    {
        printf("%d %d %d %d\n", i,
               processes[i].pid,
               processes[i].a,
               processes[i].b,
               processes[i].rt);
    }

    while (1)
    {
        int flag = 1;
        for (i = 0; i < n; i++)
        {
            // repeat while there is still a process with remaining time >10
            if (processes[i].rt > 0)
            {
                // flag=0
                flag = 0;

                // check if remaining time exceeds time quantum
                if (processes[i].rt > QUANTUM)
                { // add QUANTUM
                    quantum += QUANTUM;
                    time += QUANTUM;
                    processes[i].rt -= QUANTUM;
                }
                else
                { // add remaining time, bringing it to 0
                    quantum += processes[i].rt;
                    time += processes[i].rt;
                    processes[i].rt = 0;
                }

                // if remaining time==0
                if (processes[i].rt == 0)
                { // calculate c,t and w for each process
                    processes[i].c = time;
                    processes[i].tat = processes[i].c - processes[i].a;
                    processes[i].wt = processes[i].tat - processes[i].b;

                    avg_tat += processes[i].tat;
                    avg_wt += processes[i].wt; // divide later
                }
            }
        }
        if (flag == 1)
        {
            break;
        }
    }

    avg_wt /= n;
    avg_tat /= n;

    // Print table chart
    printf("\n|%-7s|%-7s|%-7s|%-7s|%-7s|%-7s|%-7s|\n", "Process", "AT", "BT", "CT", "TAT", "WT", "RT");
    for (i = 0; i < n; i++)
    {
        printf("|%-7d|%-7d|%-7d|%-7d|%-7d|%-7d|%-7d|\n",
               processes[i].pid, processes[i].a,
               processes[i].b, processes[i].c,
               processes[i].tat,
               processes[i].wt,
               processes[i].b);
    }

    printf("\navg_tat %.2f\n", avg_tat);
    printf("avg_wt %.2f\n", avg_wt);
    return 0;
};

int main()
{
    printf("Hello World\n");
    RoundRobin();
    return 0;
}