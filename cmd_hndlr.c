#include <string.h>
#include "roof_cmd.h"

int cmd_parser(unsigned char ucmd, int fd_print)
{
    char mybuf[128];
    int ret = 1;
    switch(ucmd)
    {
        case CMD_NONE:
            // Do nothing
            strcpy (mybuf, "CMD_NONE was called.");
        break;
        case CMD_OPEN:
            // Open Roof
            strcpy (mybuf, "CMD_OPEN was called.");
        break;
        case CMD_CLOSE:
            // Close Roof
            strcpy (mybuf, "CMD_CLOSE was called.");
        break;
        case CMD_STATE_CHECK:
            // Get current state of Roof
            strcpy (mybuf, "CMD_STATE_CHECK was called.");
        break;
        case CMD_STOP:
            // Stop Roof actuator
            strcpy (mybuf, "CMD_STOP was called.");
        break;
        default:
            // Unknown Command was issued
            strcpy (mybuf, "UNKNOWN command was called.");
    }
    // write the string to file
    printf("%s",mybuf);
    if (write (fd_print, mybuf, strlen (mybuf)) != strlen (mybuf))
        ret = -1;
    
    return(ret);
}