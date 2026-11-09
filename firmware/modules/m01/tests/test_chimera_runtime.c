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

    printf("PASS: ProcessCommand\n");

    return 0;
}