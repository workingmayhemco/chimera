#include "chimera_commands.h"
#include <string.h>

ChimeraCommand ChimeraCommands_Parse(const char *command)
{
    if (strcmp(command, "PING") == 0)
    {
        return CHIMERA_CMD_PING;
    }
    else if (strcmp(command, "HELP") == 0)
    {
        return CHIMERA_CMD_HELP;
    }
    else if (strcmp(command, "STATUS") == 0)
    {
        return CHIMERA_CMD_STATUS;
    }
    
    return CHIMERA_CMD_UNKNOWN;
}