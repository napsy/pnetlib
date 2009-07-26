#include "pnet-exe-connection.h"

#include "pnet-exe-sched.h"

#ifdef __linux__
#include <pthread.h>
#endif

pnet_exe_init()
{
    task_list = sched_list = NULL;

#ifdef __linux__
    pthread_t thread;

    pthread_create(&thread, NULL, pnet_exe_schedule_thread, NULL);
    pthread_join(thread, NULL);
#endif

}
