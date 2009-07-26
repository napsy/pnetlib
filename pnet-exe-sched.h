#ifndef __PNET_EXE_SCHED_H__
#define __PNET_EXE_SCHED_H__

#include <stdlib.h>

#include "pnet-exe-connection.h"
#include "pnet-list.h"

#ifdef __linux__
#include <unistd.h>
#endif

#define PNET_EXE_SCHEDULE_TIMEOUT 25 /* Timeout in miliseconds. */

pnet_list_t *task_list,
            *sched_list;

int
pnet_exe_hashcmp(uint8_t *hash1, uint8_t *hash2);

int
pnet_exe_group(struct pnet_exe_task_s *target_task, 
               int target_index);
void
pnet_exe_schedule();

void *
pnet_exe_schedule_thread(void *data);

#endif

