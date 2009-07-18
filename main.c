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

#include <stdio.h>

#include "pnet-connection.h"
#include "pnet-tcp-connection.h"

#ifdef __linux__
#include <unistd.h>
#endif

bool got_data(pnet_tcp_connection_t *conn, uint8_t *data, ssize_t size)
{
    printf("I got data %d bytes \'%s\'\n", size, data);
    free(data);

    return true;
}

bool got_conn(pnet_tcp_connection_t *server, pnet_tcp_connection_t *client, void *data)
{
    printf("Got a new connection ...\n");
    return true;
}

int main(int argc, char **argv)
{
    pnet_connection_t *conn;
    pnet_error_t *error = NULL;

    if (argc < 2) {
        printf("Running as client\n");
        conn = pnet_tcp_client_new("localhost", 11111, got_data, 0, &error);
        if (error) {
            printf("Error: %s\n", error->message);
            free(error);
        } else {
            while (1) {
                pnet_tcp_send(conn, "Hello there!", sizeof("Hello there!") + 1);
                usleep(2000); /* send message every 2 msec.*/
            }
            pnet_tcp_destroy(conn);
        }

        
    } else {
        if (strcmp(argv[1], "-s") == 0) {
            printf("Running as server\n");
            conn = pnet_tcp_server_new(11111, true, got_data, 0, &error);
            if (error) {
                printf("Error: %s\n", error->message);
                free(error);
            } else {
                pnet_tcp_server_run(conn, got_conn, NULL); 
                pnet_tcp_destroy(conn);
            }
        }
    }
    return 0;
}

