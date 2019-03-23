/*
 *
 *  roof_common.h: Common Defs for Roof server
 *                 
 */
#ifndef ROOF_COMMON_H
#define ROOF_COMMON_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <semaphore.h>
#include <sys/mman.h>

#define MAX_CMDS 10

#define LOGFILE "/tmp/retroof.log"

#define SEM_MUTEX_NAME "/sem-mutex"
#define SEM_CMD_COUNT_NAME "/sem-cmd-count"
#define SEM_SPOOL_SIGNAL_NAME "/sem-spool-signal"
#define SHARED_MEM_NAME "/retrfmem"

// Shared memory data structures
struct shared_memory {
    unsigned char cmd_buf[MAX_CMDS];
    int cmd_buf_idx;
    int cmd_run_idx;
};

#ifdef __cplusplus
}
#endif
#endif // ROOF_COMMON_H