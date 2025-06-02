#ifndef COMMAND_PARSER_H
#define COMMAND_PARSER_H

#include <stdbool.h>
#include "game_state.h" // GameState 구조체 정의를 포함

// 명령어 구조체
typedef struct {
    const char *verb;
    bool (*func)(GameState *state, const char *verb, const char *noun);
    const char *description;
} Command;

// 명령어 파싱 및 실행 함수 선언
void parse_command(const char *input, char *verb_buf, char *noun_buf);
bool execute_command(GameState *state, const char *verb, const char *noun);

#endif // COMMAND_PARSER_H
