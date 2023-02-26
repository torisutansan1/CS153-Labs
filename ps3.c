#include "types.h"
#include "user.h"

#define PS

int PScheduler(void);

int main(int argc, char *argv[])
{
    
    PScheduler();

    exitTest(0);

    return 0;
}    
      
int PScheduler(void){
		 
    // Use this part to test the priority scheduler. Assuming that the priorities range between range between 0 to 31
    // 0 is the highest priority. All processes have a default priority of 10
    // You can use your own priority range/value setup

    int pid, ret_pid, exit_status;
    int i,j,k;
    int prpid = 0;

    printf(1, "\n");
  
    printf(1, "Testing PS and Donation/Inheritance:\n");
    printf(1, "Priority will change between processes\n");
    printf(1, "0 is the highest priority. Prior Def: 10\n");
    printf(1, "The parent processes will switch to priority 0\n");

    printf(1, "\n");

    setpriority(0); // Use your own setpriority interface
    for (i = 0; i < 3; i++)
    {
	pid = fork();
	if (pid > 0) { continue; } 
    else if (pid == 0) 
    {
            printf(1, " Child: %d Priority: %d \n", getpid(), 30 - 10 * i);
            setpriority(30 - 10 * i); // Use your own setpriority interface

            priorityDonate(pid);
            if(i == 2)
            {
                priorityDonate(pid);
            }
            for (j = 0; j < 50000; j++) 
            {
                asm("nop");
                for(k = 0; k < 10000; k++) 
                {
                    asm("nop"); 
                    //priorityDonate(pid);
                }
            }

            printf(1, "\n");

            priorityDonate(pid);
            
            printf(1, "Child: %d Priority: %d finished \n", getpid(), 30 - 10 * i);

            printf(1,"Prev PID is %d\n", prpid);
            prpid = getpid();

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
        for (i = 0; i < 3; i++) 
        {
            ret_pid = waitTest(&exit_status);
            printf(1, "RET: %d EXIT: %d \n", ret_pid, exit_status);
        }
        printf(1, " - If processes are donated/inherited, success. \n");
    }
    printf(1, "\n");
			
    return 0;
}