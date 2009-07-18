#include "pnet-file-io.h"

#include "pnet-tcp-connection.h"

typedef struct {
    const char filename[64];
    long long size;
    int mode;
} pnet_file_t;


/* Client function to request a file form server. */
int
pnet_file_recv(pnet_connection_t *conn,
              const char *remote_filename,
              const char *local_filename)
{
    pnet_tcp_send(conn, remote_filename, strlen(remote_filename) + 1);

}


/* Server function to respond to file requests. */
int
pnet_file_send(pnet_connection_t *conn,
               const char *filename)

