#ifndef COMMAND_PARSER_H
#define COMMAND_PARSER_H

#include <stdbool.h>
#include "game_state.h" 

typedef struct {
    const char *verb;
    bool (*func)(GameState *state, const char *verb, const char *noun);
    const char *description;
} Command;


void parse_command(const char *input, char *verb_buf, char *noun_buf);
bool execute_command(GameState *state, const char *verb, const char *noun);

#endif
