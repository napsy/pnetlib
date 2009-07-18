#ifndef __PNET_FILE_IO_H__
#define __PNET_FILE_IO_H__

#include "pnet-connecion.h"

typedef struct {
    const char filename[64];
    long long size;
    int mode;
} pnet_file_t;


/* Client function to request a file form server. */
int
pnet_file_recv(pnet_connection_t *conn,
              const char *remote_filename,
              const char *local_filename);


/* Server function to respond to file requests. */
int
pnet_file_send(pnet_connection_t *conn,
               const char *filename)
#endif /* __PNET_FILE_IO_H__ */

