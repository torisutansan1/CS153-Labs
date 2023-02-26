#include "types.h"
#include "user.h"

#define LOTTERY

int PScheduler(void);

int main(int argc, char *argv[])
{
    
    PScheduler();

    exitTest(0);

    return 0;
}    
      
int PScheduler(void)
{
    // Use this part to test the priority scheduler. Assuming that the priorities range between range between 0 to 31
    // 0 is the highest priority. All processes have a default priority of 10
    // You can use your own priority range/value setup
    int pid, ret_pid, exit_status;
    int i,j,k;

    printf(1, "\n");
  
    printf(1, "Testing the priority scheduler and setpriority system call:\n");
    printf(1, "Assuming that the priorities range between range between 0 to 31\n");
    printf(1, "0 is the highest priority. All processes have a default priority of 10\n");
    printf(1, "The parent processes will switch to priority 0\n");

    printf(1, "\n");

    setpriority(0); // Use your own setpriority interface

    for (i = 0; i < 6; i++)
    {
	pid = fork();
	if (pid > 0) { continue; } 
    else if ( pid == 0) 
    {
            printf(1, " Child: %d Tickets: %d", getpid(), 6 - 1 * i);
            printf(1, "\n");
            setpriority(6-1*i); // Use your own setpriority interface

            for (j = 0; j < 473293; j++) 
            {
                for(k = 0; k < 1000; k++) 
                {
                    asm("nop"); 
                }
            }
            
            printf(1, " - C#%d finished!\n", getpid());

            for (j = 0; j < 321372; j++) 
            {
                for(k = 0; k < 1000; k++) 
                {
                    asm("nop"); 
                }
            }

            exitTest(0);
        } 
        else 
        {
            printf(2," \n Error fork() \n");
            exitTest(-1);
        }
    }

    if (pid > 0) 
    {
        printf(1, "\n");
        for (i = 0; i < 6; i++) 
        {
            ret_pid = waitTest(&exit_status);
            printf(1, "R: %d E: %d \n", ret_pid, exit_status);
        }
        printf(1, " - If processes are randomized, success. \n");
    }
    printf(1, "\n");
			
    return 0;
}