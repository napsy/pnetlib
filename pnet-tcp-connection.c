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

#include "pnet-tcp-connection.h"
#include "pnet-error.h"

#include <string.h>
#include <netdb.h>

#include <errno.h>

#define PNET_TCP_HEADER_MAGIC 0xDEADBEEF

/* TODO: alignment. */
struct _pnet_tcp_connection_header {
    uint32_t magic,
             length;
    uint8_t reserved;
};

struct _pnet_tcp_conn {
    pnet_tcp_connection_t *server,
                          *client;
};
void *
_pnet_tcp_recv_thread(struct _pnet_tcp_conn *conns)
{
   pnet_tcp_connection_t *server = conns->server,
                          *client = conns->client;
   uint8_t *data;
   ssize_t size;
    
   server->accept_cb((pnet_connection_t *)server, (pnet_connection_t *)client, server->accept_data);

   if (server->async_recv) {
       while (1) {
           data = pnet_tcp_recv(client, &size);
           if (!data) {
               /* XXX: handle error. */
               break;
           } else {
               if (!server->recv_cb((pnet_connection_t *)client, data, size)) /* user callback returned false. */
                   break;
           }
       }
       pnet_tcp_destroy(client);
   }

   free(conns);
}

pnet_connection_t *
pnet_tcp_server_new(uint16_t port,
                    bool async_recv,
                    bool (*recv_cb)(pnet_connection_t *conn, uint8_t *data, ssize_t size),
                    int params,
                    pnet_error_t **error)
{
    pnet_tcp_connection_t *conn;
    int r, opt = 1;

    conn = malloc(sizeof(pnet_tcp_connection_t));
    if (!conn)
        return NULL;

    pnet_connection_init(&conn->super, PNET_TCP_CONNECTION_TYPE);

#ifdef __linux__
    if ((conn->sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == 0) {
        free(conn);
        *error = pnet_error("Call to socket() failed");
        return NULL;
    }

    memset(&conn->addr, 0, sizeof(struct sockaddr_in));
    conn->addr.sin_family = AF_INET;
    conn->addr.sin_port = htons(port);
    conn->addr.sin_addr.s_addr = htonl(INADDR_ANY);

    if (setsockopt(conn->sockfd, SOL_SOCKET, SO_REUSEADDR, &opt,
                sizeof(opt)) == -1) {
        *error = pnet_error("Unable to reuse port");
        close(conn->sockfd);
        free(conn);
        return NULL;
    }

    r = bind(conn->sockfd, (struct sockaddr *)&conn->addr, sizeof(conn->addr));
    if (r == -1) {
        close(conn->sockfd);
        free(conn);
        *error = pnet_error("Call to bind() failed");
        return NULL;
    }

    r = listen(conn->sockfd, 10);
    if (r == -1) {
        close(conn->sockfd);
        free(conn);
        *error = pnet_error("Call to listen() failed");
        return NULL;
    }

#endif
    conn->async_recv = async_recv;
    conn->recv_cb = recv_cb;
    return (pnet_connection_t *)conn;
}

int
pnet_tcp_server_run(pnet_connection_t *server_conn,
                    bool (*accept_cb)(pnet_connection_t *server_conn, pnet_connection_t *client_conn, void *data),
                    void *data)
{
    int sockfd;
    socklen_t sin_size = sizeof(struct sockaddr_in);
    pnet_tcp_connection_t *tcp_server_conn = (pnet_tcp_connection_t *)server_conn,
                          *client;
    struct sockaddr_in addr;

    tcp_server_conn->accept_cb = accept_cb;

    while (1) {
        sockfd = accept(tcp_server_conn->sockfd, (struct sockaddr *)&addr,
                &sin_size);
        if (sockfd == -1)
            continue;

        client = malloc(sizeof(pnet_tcp_connection_t));
        if (!client)
            return -1;

        pnet_connection_init(&client->super, PNET_TCP_CONNECTION_TYPE);
        client->sockfd = sockfd;
        memcpy(&client->addr, &addr, sizeof(struct sockaddr_in));
        
        struct _pnet_tcp_conn *conns = malloc(sizeof(*conns));
        conns->server = tcp_server_conn;
        conns->client = client;
        pthread_create(&tcp_server_conn->recv_thread, NULL, _pnet_tcp_recv_thread,
                        conns);
    }
}
pnet_connection_t *
pnet_tcp_client_new(const char *host,
                    int port,
                    bool (*recv_cb)(uint8_t *data, ssize_t size),
                    int params,
                    pnet_error_t **error)
{
    pnet_tcp_connection_t *conn;
    struct hostent *he;
    int r;
    socklen_t addr_size = sizeof(struct sockaddr_in);


    he = gethostbyname(host);
    if (!he) {
        *error = pnet_error("Host cound not be resolved");
        return NULL;
    }

    conn = malloc(sizeof(pnet_tcp_connection_t));
    if (!conn)
        return NULL;

    pnet_connection_init(&conn->super, PNET_TCP_CONNECTION_TYPE);

#ifdef __linux__
    if ((conn->sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == -1) {
        free(conn);
        perror("ERROR");
        *error = pnet_error("Call to socket() failed");
        return NULL;
    }
    memset(&conn->addr, 0, sizeof(struct sockaddr_in));
    conn->addr.sin_family = AF_INET;
    conn->addr.sin_port = htons(port);
    bcopy (he->h_addr, &(conn->addr.sin_addr.s_addr), he->h_length);
    //conn->addr.sin_addr = he->h_addr;
#endif
    r = connect(conn->sockfd, (struct sockaddr *)&conn->addr, addr_size);
    if (r == -1) {
        close(conn->sockfd);
        free(conn);
        perror("Error");
        *error = pnet_error("Unable to connect()");
        return NULL;
    }

    return (pnet_connection_t *)conn;
}

uint8_t *
pnet_tcp_recv(pnet_tcp_connection_t *conn,
              ssize_t *size)
{
    pthread_mutex_lock(&conn->super.recv_mutex);
    uint8_t *data;
    struct _pnet_tcp_connection_header header;
    ssize_t r, got = 0, left;

#ifdef __linux__
    /* Get the header */
    r = recv(conn->sockfd, &header, sizeof(header), MSG_WAITALL);
    if (header.magic != PNET_TCP_HEADER_MAGIC) {
        *size = -1;
        pthread_mutex_unlock(&conn->super.recv_mutex);
        return NULL;
    }

    left = header.length;
    data = malloc(header.length);
    while (left > 0) {
        r = recv(conn->sockfd, data + got, left, 0);
        if (r <= 0) {
            *size = r;
            free(data);
            pthread_mutex_unlock(&conn->super.recv_mutex);
            return NULL;
        }
        left -= r;
        got += r;
    }
#endif
    *size = got;
    pthread_mutex_unlock(&conn->super.recv_mutex);
    return data;
}

int
pnet_tcp_send(pnet_tcp_connection_t *conn,
              uint8_t *data,
              ssize_t size)
{
    pthread_mutex_lock(&conn->super.send_mutex);
    struct _pnet_tcp_connection_header header;
    ssize_t r, got = 0, left = size;

    header.magic = PNET_TCP_HEADER_MAGIC;
    header.length = size;

#ifdef __linux__
    /* Send the header */
    r = send(conn->sockfd, &header, sizeof(header), 0);
    if (r != sizeof(header)) {
        pthread_mutex_unlock(&conn->super.send_mutex);
        return -1;
    }
    
    while (left > 0) {
        r = send(conn->sockfd, data + got, left, 0);
        if (r <= 0) {
            pthread_mutex_unlock(&conn->super.send_mutex);
            return -2;
        }
        left -= r;
        got += r;
    }
#endif
    pthread_mutex_unlock(&conn->super.send_mutex);
    return 0;
}

void
pnet_tcp_destroy(pnet_tcp_connection_t *conn)
{
    close(conn->sockfd);
    free(conn);
}

