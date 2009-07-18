#include <string.h>
#include "pnet-error.h"

pnet_error_t *
pnet_error(const char *message)
{
    pnet_error_t *error;

    error = malloc(sizeof(pnet_error_t));
    if (!error)
        return NULL;

    strncpy(error->message, message, 128);
    error->code = -1; /* Meaning no error code was set. */

    return error;
}

pnet_error_t *
pnet_error1(const char *message, int16_t code)
{
    pnet_error_t *error;

    error = malloc(sizeof(pnet_error_t));
    if (!error)
        return NULL;

    strncpy(error->message, message, 128);
    error->code = code;

    return error;
}

