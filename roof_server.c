/*
 *
 *  roof_server.c: Write cmds in POSIX shared memory to file/hardware
 *                 (Server process)
 */

#include "roof_common.h"
#include "cmd_hndlr.h"

void error (char *msg);

int main (int argc, char **argv)
{
    struct shared_memory *shm_ptr;
    sem_t *mutex_sem, *cmd_count_sem, *spool_signal_sem;
    int fd_shm, fd_log;
    unsigned char mycmd;
    
    // Open log file
    if ((fd_log = open (LOGFILE, O_CREAT | O_WRONLY | O_APPEND | O_SYNC, 0666)) == -1)
        error ("fopen");

    //  mutual exclusion semaphore, mutex_sem with an initial value 0.
    if ((mutex_sem = sem_open (SEM_MUTEX_NAME, O_CREAT, 0660, 0)) == SEM_FAILED)
        error ("sem_open");
    
    // Get shared memory 
    if ((fd_shm = shm_open (SHARED_MEM_NAME, O_RDWR | O_CREAT, 0660)) == -1)
        error ("shm_open");

    if (ftruncate (fd_shm, sizeof (struct shared_memory)) == -1)
       error ("ftruncate");
    
    if ((shm_ptr = mmap (NULL, sizeof (struct shared_memory), PROT_READ | PROT_WRITE, MAP_SHARED,
            fd_shm, 0)) == MAP_FAILED)
       error ("mmap");

    // Initialize the shared memory
    shm_ptr->cmd_buf_idx = shm_ptr->cmd_run_idx = 0; 
 
    // counting semaphore, indicating the number of available cmd slots. Initial value = MAX_CMDS
    if ((cmd_count_sem = sem_open (SEM_CMD_COUNT_NAME, O_CREAT, 0660, MAX_CMDS)) == SEM_FAILED)
        error ("sem_open");

    // counting semaphore, indicating the number of cmds to be run. Initial value = 0
    if ((spool_signal_sem = sem_open (SEM_SPOOL_SIGNAL_NAME, O_CREAT, 0660, 0)) == SEM_FAILED)
        error ("sem_open");

    // Initialization complete; now we can set mutex semaphore as 1 to 
    // indicate shared memory segment is available
    if (sem_post (mutex_sem) == -1)
        error ("sem_post: mutex_sem");
    
    while (1) 
    {  // forever
        // Is there a command to run? P (spool_signal_sem);
        if (sem_wait (spool_signal_sem) == -1)
            error ("sem_wait: spool_signal_sem");
    
        mycmd = shm_ptr->cmd_buf[shm_ptr->cmd_run_idx];

        /* Since there is only one process (the roof manager) using the 
           cmd_run_idx, mutex semaphore is not necessary */
        (shm_ptr->cmd_run_idx)++;
        if (shm_ptr->cmd_run_idx == MAX_CMDS)
            shm_ptr->cmd_run_idx = 0;

        /* Contents of one cmd buffer has been executed.
           One more cmd buffer is available for use by clients.
           Release buffer: V (cmd_count_sem);  */
        if (sem_post (cmd_count_sem) == -1)
            error ("sem_post: cmd_count_sem");
        
        // This where cmd is executed add code here for desired action
        // write the string to file
        if (cmd_parser(mycmd, fd_log) != 1)
            error ("write: logfile");

    }
}

// Print system error and exit
void error (char *msg)
{
    perror (msg);
    exit (1);
}