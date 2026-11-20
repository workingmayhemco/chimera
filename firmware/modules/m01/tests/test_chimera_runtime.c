/*
SPDX-FileCopyrightText: 2026 Working Mayhem
SPDX-License-Identifier: Apache-2.0
*/

#include <assert.h>
#include <stdio.h>
#include <string.h>

#include "chimera_runtime.h"

int main(void)
{
    char response[128];
    int ret;

    ret = ProcessCommand("PING", 0U, response, sizeof(response));
    assert(ret >= 0 && (size_t)ret < sizeof(response));
    assert(strcmp(response, "PONG\r\n") == 0);

    ret = ProcessCommand("HELP", 0, response, sizeof(response));
    assert(ret >= 0 && (size_t)ret < sizeof(response));
    assert(strcmp(response, "Available commands: PING, HELP, STATUS\r\n") == 0);

    ret = ProcessCommand("UNKNOWN", 0, response, sizeof(response));
    assert(ret >= 0 && (size_t)ret < sizeof(response));
    assert(strcmp(response, "UNKNOWN COMMAND\r\n") == 0);

    ret = ProcessCommand("STATUS", 3675000, response, sizeof(response));
    assert(ret >= 0 && (size_t)ret < sizeof(response));
    assert(strcmp(response, "UPTIME: 01:01:15\r\n") == 0);

    char small_response[8];

    ret = ProcessCommand(
        "STATUS",
        3675000U,
        small_response,
        sizeof(small_response)
    );

    assert(ret >= (int)sizeof(small_response));

    char small_response2[6];

    ret = ProcessCommand(
        "PING",
        0U,
        small_response2,
        sizeof(small_response2)
    );

    assert(ret == 6);
    assert(ret >= (int)sizeof(small_response2));
    assert(strcmp(small_response2, "PONG\r") == 0);

    char exact_response[7];

    ret = ProcessCommand(
        "PING",
        0U,
        exact_response,
        sizeof(exact_response)
    );

    assert(ret == 6);
    assert((size_t)ret < sizeof(exact_response));
    assert(strcmp(exact_response, "PONG\r\n") == 0);

    printf("PASS: ProcessCommand\n");

    return 0;
}