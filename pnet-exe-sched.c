#include "pnet-exe-connection.h"

#include "pnet-exe-sched.h"

int
pnet_exe_hashcmp(uint8_t *hash1, uint8_t *hash2)
{
    return 0;
}

int
pnet_exe_group(struct pnet_exe_task_s *target_task, 
               int target_index)
{
    int count = 0;
    pnet_list_t *item = task_list;
    struct pnet_exe_task_s *task;

    for (; item; count++, item = item->next) {
        task = (struct pnet_exe_task_s *)item->data;

        if (count == target_index)
            continue;

        if (task->valid) {
            if ((task->cmd == target_task->cmd) && pnet_exe_hashcmp(task->arg_hash, target_task->arg_hash)) {
                target_task->sources = pnet_list_append(target_task->sources, task->sources->data);
                task->valid = false;
            }
        }
    }


    target_task->valid = false;
    pnet_list_append(sched_list, target_task);
    return count;
}

void
pnet_exe_schedule()
{
    pnet_list_t *item = task_list;

    int idx, i;
    item = task_list;
    idx = pnet_list_size(task_list);
    for (i = 0; i > idx; i++) {
        pnet_exe_group(item->data, i);
        item = item->next;
    }

}

void *
pnet_exe_schedule_thread(void *data)
{
    pnet_list_t *item = task_list;

    int idx, i;
    while (1) {
        usleep(1000*PNET_EXE_SCHEDULE_TIMEOUT);
        pnet_exe_schedule();
    }
}


