/*
 * Copyright (c) 2009, Luka Napotnik <luka.napotnik@gmail.com>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *    - Redistributions of source code must retain the above copyright
 *      notice, this list of conditions and the following disclaimer.
 *    - Redistributions in binary form must reproduce the above copyright
 *      notice, this list of conditions and the following disclaimer in the
 *      documentation and/or other materials provided with the distribution.
 *    - Neither the name of the <organization> nor the
 *      names of its contributors may be used to endorse or promote products
 *      derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY <copyright holder> ''AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL <copyright holder> BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */



#ifndef __PNET_TCP_CONNECTION_H__
#define __PNET_TCP_CONNECTION_H__

#ifdef __linux__
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <pthread.h>
#endif

#include "pnet-connection.h"
#include "pnet-error.h"

#define PNET_TCP_CONNECTION_TYPE 1

typedef struct {
    /* The parent class*/
    pnet_connection_t super;

#ifdef __linux__
    int sockfd;
    struct sockaddr_in addr;
    pthread_t recv_thread;
#endif

#ifdef WIN32
    SOCKET sockfd;
#endif

    bool async_recv;
    bool (*recv_cb)(pnet_connection_t *conn,
                    uint8_t *data,
                    ssize_t size);

    bool (*accept_cb)(pnet_connection_t *server_conn,
                      pnet_connection_t *client_conn,
                      void *data);
    void *accept_data;
} pnet_tcp_connection_t;

/* ----------------------------------------------
 * pnet_tcp_server_new()
 * ----------------------------------------------
 * Creates a new server connection
 * Parameters:
 *   port - port on which the server will listen to
 *   recv_cb - a function pointer fo async receiving,
 *   params - extra parameters
 * Returns:
 *   pointer to a connection representation or NULL
 *   on failure.
 */

pnet_connection_t *
pnet_tcp_server_new(uint16_t port,
                    bool async_recv,
                    bool (*recv_cb)(pnet_connection_t *conn, uint8_t *data, ssize_t size),
                    int params,
                    pnet_error_t **error);

int
pnet_tcp_server_run(pnet_connection_t *server_conn,
                    bool (*accept_cb)(pnet_connection_t *server_conn, pnet_connection_t *client_conn, void *data),
                    void *data);

/* ----------------------------------------------
 * pnet_tcp_client_new()
 * ----------------------------------------------
 * Creates a new server connection
 * Parameters:
 *   host - host to connect to
 *   port - port on which to connect
 *   recv_cb - a function pointer fo async receiving,
 *   params - extra parameters
 * Returns:
 *   pointer to a connection representation or NULL
 *   on failure.
 */
pnet_connection_t *
pnet_tcp_client_new(const char *host,
                    int port,
                    bool (*recv_cb)(uint8_t *data, ssize_t size),
                    int params,
                    pnet_error_t **error);

uint8_t *
pnet_tcp_recv(pnet_tcp_connection_t *conn,
              ssize_t *size);

int
pnet_tcp_send(pnet_tcp_connection_t *conn,
              uint8_t *data,
              ssize_t size);

void
pnet_tcp_destroy(pnet_tcp_connection_t *conn);

#endif /* __PNET_CONNECTION_H__ */


