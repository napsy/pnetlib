#ifndef __PNET_EXE_CONNECTION_H__
#define __PNET_EXE_CONNECTION_H__

#include <stdbool.h>
#include <stdint.h>

#include "pnet-tcp-connection.h"
#include "pnet-list.h"

struct pnet_exe_task_s {
    uint8_t cmd;
    void *arg;
    uint16_t arg_size;
    uint8_t arg_hash[64];
    bool valid;

    pnet_list_t *sources;
};

typedef struct {
    pnet_tcp_connection_t conn;
} pnet_exe_connection_t;

void
pnet_exe_init();

#endif

