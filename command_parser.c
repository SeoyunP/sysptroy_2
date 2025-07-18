#include "command_parser.h"
#include "game_state.h"
#include "utils/utils.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h> 
#include <time.h>

// =================================================================
bool handle_look(GameState *state, const char *verb, const char *noun);
bool handle_take(GameState *state, const char *verb, const char *noun);
bool handle_use(GameState *state, const char *verb, const char *noun);
bool handle_go(GameState *state, const char *verb, const char *noun);
bool handle_talk(GameState *state, const char *verb, const char *noun);
bool handle_knock(GameState *state, const char *verb, const char *noun);
bool handle_inventory(GameState *state, const char *verb, const char *noun);
bool handle_help(GameState *state, const char *verb, const char *noun);
bool handle_quit(GameState *state, const char *verb, const char *noun);
bool handle_combine(GameState *state, const char *verb, const char *noun);
bool handle_time(GameState *state, const char *verb, const char *noun);

// =================================================================
Command command_list[] = {
    {"look", handle_look, "주변을 둘러봅니다. (예: look around, look torch)"},
    {"take", handle_take, "아이템을 획득합니다. (예: take torch)"},
    {"pick", handle_take, "아이템을 획득합니다. (축약) (예: pick up torch)"},
    {"use", handle_use, "아이템을 사용합니다. (예: use key, use torch)"},
    {"open", handle_use, "무엇을 엽니다. (use로 대체 가능)"}, 
    {"go", handle_go, "특정 방향이나 장소로 이동합니다. (예: go north, go door)"},
    {"enter", handle_go, "무엇 안으로 들어갑니다. (go로 대체 가능)"},
    {"talk", handle_talk, "NPC와 대화합니다. (예: talk to guard 1)"},
    {"knock", handle_knock, "무엇을 두드립니다. (예: knock 2)"},
    {"inventory", handle_inventory, "현재 소지품을 확인합니다. (축약: i)"},
    {"i", handle_inventory, "인벤토리 (축약)."},
    {"help", handle_help, "사용 가능한 명령어 목록을 봅니다."},
    {"도움", handle_help, "도움말 (한글)."},
    {"quit", handle_quit, "게임을 종료합니다. (한글: 종료)"},
    {"종료", handle_quit, "게임 종료 (한글)."},
    {"combine", handle_combine, "여러 쪽지를 조합하여 힌트를 얻습니다. (예: combine notes)"},
    {"time", handle_time, "남은 제한 시간을 확인합니다."},
    {"시간", handle_time, "남은 제한 시간을 확인합니다. (한글)"}, 

    {NULL, NULL, NULL}
};

// =================================================================

// 사용자 입력
void parse_command(const char *input, char *verb_buf, char *noun_buf) {
    verb_buf[0] = '\0';
    noun_buf[0] = '\0';

    char temp_input[256];
    strncpy(temp_input, input, sizeof(temp_input) - 1);
    temp_input[sizeof(temp_input) - 1] = '\0';

    char *token = strtok(temp_input, " ");
    if (token != NULL) {
        //소문자로 변환
        for (int i = 0; token[i] != '\0'; i++) {
            verb_buf[i] = tolower((unsigned char)token[i]);
        }
        verb_buf[strlen(token)] = '\0';

        token = strtok(NULL, "");
        if (token != NULL) {
            int start = 0;
            while (isspace((unsigned char)token[start])) {
                start++;
            }
            int end = strlen(token) - 1;
            while (end >= start && isspace((unsigned char)token[end])) {
                end--;
            }
            if (end >= start) {
                strncpy(noun_buf, token + start, end - start + 1);
                noun_buf[end - start + 1] = '\0';
            }
            for (int i = 0; noun_buf[i] != '\0'; i++) {
                noun_buf[i] = tolower((unsigned char)noun_buf[i]);
            }
        }
    }
}

bool execute_command(GameState *state, const char *verb, const char *noun) {
    for (int i = 0; command_list[i].verb != NULL; i++) {
        if (strcmp(verb, command_list[i].verb) == 0) {
            return command_list[i].func(state, verb, noun);
        }
    }
    printf("알 수 없는 명령어입니다. 'help'를 입력하여 도움말을 보세요.\n");
    return false;
}

// =================================================================

bool handle_look(GameState *state, const char *verb, const char *noun) {
    (void)verb;
    if (strlen(noun) == 0 || strcmp(noun, "around") == 0) {
        switch (state->current_room) {
            case ROOM_PALLADION_TEMPLE:
                printf("\n--- 팔라디온 신전 도면 ---\n");
                printf("┌──────────┬───────┬──────────┐\n");
                printf("│          │       │          │\n");
                printf("│          └───────┘          │\n");
                printf("│                             │\n");
                printf("│                             │\n");
                printf("│          📃         🔥      │\n");
                printf("│          ┌───────┐          │\n");
                printf("│          │  제단 │    🔥    │\n");
                printf("│          └───────┘          │\n");
                printf("│        📃           🔥      │\n");
                printf("│    📃                       │\n");
                printf("└─────────────────────────────┘\n");
                printf("벽에 달린 세 개의 횃불, 중앙에 놓인 제단, 그리고 굳게 잠긴 문이 보입니다.\n");
                printf("바닥에 떨어져 있는 파피루스 조각 3개와, 왠지 불을 붙일 수 있을 것만 같은 횃불 3개가 보입니다.\n");
                printf("횃불을 보면 어쩐지 그림을 볼 수 있을 것도 같네요.\n");
                break;
            case ROOM_TROJAN_HORSE:
                printf("\n--- 트로이 목마 야영지 도면 ---\n");
                printf("┌─────────────────────────────┐\n");
                printf("│                             │\n");
                printf("│                             │\n");
                printf("│          🧥                 │\n");
                printf("│                             │\n");
                printf("│      💂    💂               │\n");
                printf("│      ┌───────┐              │\n");
                printf("│      │ 🐴    │              │\n");
                printf("│      └───────┘              │\n");
                printf("│                             │\n");
                printf("│                             │\n");
                printf("└─────────────────────────────┘\n");
                printf("정 중앙에 커다란 트로이 목마가 세워져 있고, 양쪽에 경비병 1번과 경비병 2번이 서로 떨어진 위치에 서 있습니다.\n");
                printf("근처 바닥에 로브와 나무 방망이가 떨어져 있습니다.\n");
                break;
            case ROOM_TROY_PALACE_FRONT:
                printf("\n--- 트로이 궁전 도면 ---\n");
                printf("┌───────────────────────────┐\n");
                printf("│───────────────────────────│\n");
                printf("│───────────────────────────│\n");
                printf("│          ┌────┐           │\n");
                printf("│          │기어│           │\n");
                printf("│          └────┘           │\n");
                printf("│  👮    🧑‍🌾                 │\n");
                printf("│                           │\n");
                printf("│                           │\n");
                printf("└───────────────────────────┘\n");
                printf("주변을 둘러봐도 성으로 가는 길 밖에 보이지 않네요. 흩어진 쪽지 3개가 보이는 듯합니다.\n");
                printf("성문 앞에는 두 경비병이 서 있습니다.\n");
                break;
        }
        return true;
    } else if (strcmp(noun, "torch") == 0) {
        if (state->current_room == ROOM_PALLADION_TEMPLE) {
            if (has_item(state, ITEM_TORCH) || state->puzzles.torch_placed_on_aphrodite) {
                   printf("3개의 횃불, 그 각각의 위에 아테나, 헤라, 아프로디테의 벽화가 보입니다.\n");
                   if (!state->puzzles.papyrus_riddle_revealed) {
                       printf("어느 벽화를 골라야 할지 모르겠군요..\n");
                   } else {
                       printf("'가장 아름다운 여신에게'라는 힌트를 고려하면, 아프로디테 벽화에 꽂아야 할 것 같습니다.\n");
                   }
            } else {
                   printf("횃불은 보이지 않습니다.\n");
            }
        } else {
            printf("이곳에는 횃불이 없습니다.\n");
        }
        return true;
    } else if (strcmp(noun, "altar") == 0 || strcmp(noun, "제단") == 0) {
        if (state->current_room == ROOM_PALLADION_TEMPLE) {
            printf("중앙에 오래된 제단이 놓여 있습니다. 표면에 알 수 없는 문양과 잠금 장치가 새겨져 있습니다.\n");
            if (state->puzzles.helene_password_revealed) {
                printf("튀어나온 벽돌의 '헬레네' 글자가 제단과 관련이 있을 것 같습니다.\n");
            }
        } else {
            printf("이곳에는 제단이 없습니다.\n");
        }
        return true;
    } else if (strcmp(noun, "trojan horse") == 0 || strcmp(noun, "목마") == 0) {
        if (state->current_room == ROOM_TROJAN_HORSE) {
            printf("거대한 트로이 목마가 눈앞에 서 있습니다. 별다른 입구는 보이지 않습니다. 독특한 방법으로 들어갈 수 있을 것 같습니다.\n");
            if (state->puzzles.guard1_hint_obtained) {
                printf("경비병이 목마 탈 때 방망이로 두 번 툭툭 두드리라고 했습니다.\n");
            }
        } else {
            printf("이곳에는 트로이 목마가 없습니다.\n");
        }
        return true;
    } else if (strcmp(noun, "gate") == 0 || strcmp(noun, "성문") == 0) {
        if (state->current_room == ROOM_TROY_PALACE_FRONT) {
            printf("견고한 성문이 당신의 앞을 가로막고 있습니다. 옆에는 복잡한 기어 조작 장치가 보입니다.\n");
            if (state->puzzles.guards_defeated_by_powder) {
                printf("경비병들이 쓰러져 성문 조작이 가능해 보입니다.\n");
            }
            if (state->puzzles.gear_hint_revealed) {
                printf("쪽지들을 조합해서 기어 조작 힌트를 얻었습니다.\n");
            }
        } else {
            printf("이곳에는 성문이 없습니다.\n");
        }
        return true;
    } else {
        printf("'%s'은(는) 둘러볼 수 없습니다.\n", noun);
        return false;
    }
}

bool handle_take(GameState *state, const char *verb, const char *noun) {
    (void)verb;

    if (strlen(noun) == 0) {
        printf("무엇을 획득할지 입력하세요. (예: take torch)\n");
        return false;
    }

    switch (state->current_room) {
        case ROOM_PALLADION_TEMPLE:
            if (strcmp(noun, "papyrus fragment") == 0 || strcmp(noun, "파피루스 조각") == 0) {
                if (state->puzzles.papyrus_fragments_collected < 3) {
                    add_item_to_inventory(state, ITEM_PAPYRUS_FRAGMENT);
                    state->puzzles.papyrus_fragments_collected++;
                    printf("오래된 파피루스 조각을 획득했습니다. (%d/3)\n", state->puzzles.papyrus_fragments_collected);
                    if (state->puzzles.papyrus_fragments_collected == 3 && !state->puzzles.papyrus_riddle_revealed) {
                        printf("모든 파피루스 조각을 모았습니다. 'combine notes' 명령어로 조합하여 힌트를 얻을 수 있을 것 같습니다.\n");
                    }
                    return true;
                } else {
                    printf("더 이상 파피루스 조각이 없습니다.\n");
                }
            } else if (strcmp(noun, "torch") == 0 || strcmp(noun, "횃불") == 0) {
                if (!has_item(state, ITEM_TORCH) && !state->puzzles.torch_placed_on_aphrodite) {
                    add_item_to_inventory(state, ITEM_TORCH);
                    printf("신전의 제단 옆에서 횃불을 획득했습니다.\n");
                    return true;
                } else if (state->puzzles.torch_placed_on_aphrodite) {
                    printf("횃불은 이미 벽면에 꽂혀 있습니다.\n");
                } else {
                    printf("이미 횃불을 가지고 있습니다.\n");
                }
            } else if (strcmp(noun, "palladium") == 0 || strcmp(noun, "팔라디온") == 0) {
                if (state->puzzles.palladium_obtained) {
                    printf("이미 팔라디온을 획득했습니다.\n");
                } else if (state->puzzles.helene_password_revealed) { // 헬레네 암호로 제단이 열린 상태
                    add_item_to_inventory(state, ITEM_PALLADIUM);
                    set_puzzle_solved(&state->puzzles.palladium_obtained);
                    printf("제단에서 팔라디온을 획득하였습니다. 팔라디온을 가져가자, 제단 아래에서 '탈출 열쇠'가 튀어나왔습니다!\n");
                    set_puzzle_solved(&state->puzzles.room1_exit_key_obtained); // 탈출 열쇠 자동 획득
                    add_item_to_inventory(state, ITEM_ESCAPE_KEY); // 탈출 열쇠 인벤토리에 추가
                    return true;
                } else {
                    printf("팔라디온은 아직 획득할 수 없습니다. 제단의 자물쇠를 풀어야 합니다.\n");
                }
            } else if (strcmp(noun, "escape key") == 0 || strcmp(noun, "탈출 열쇠") == 0) {
                if (state->puzzles.room1_exit_key_obtained && has_item(state, ITEM_ESCAPE_KEY)) {
                    printf("이미 탈출 열쇠를 가지고 있습니다.\n");
                } else if (state->puzzles.palladium_obtained) { 
                    printf("탈출 열쇠는 팔라디온 획득 시 이미 얻었습니다.\n");
                } else {
                    printf("탈출 열쇠는 아직 획득할 수 없습니다.\n");
                }
            } else {
                printf("'%s'은(는) 획득할 수 없습니다.\n", noun);
            }
            break;

        case ROOM_TROJAN_HORSE:
            if (strcmp(noun, "robe") == 0 || strcmp(noun, "로브") == 0) {
                if (!state->puzzles.has_robe) {
                    add_item_to_inventory(state, ITEM_ROBE);
                    set_puzzle_solved(&state->puzzles.has_robe);
                    printf("어두운 빛의 로브다. 로브 끝에 아주 작게 그리스 군의 신분을 나타내는 표식이 붙어 있다.\n");
                    return true;
                } else {
                    printf("이미 로브를 가지고 있습니다.\n");
                }
            } else if (strcmp(noun, "wooden bat") == 0 || strcmp(noun, "나무 방망이") == 0) {
                if (!state->puzzles.has_wooden_bat) {
                    add_item_to_inventory(state, ITEM_WOODEN_BAT);
                    set_puzzle_solved(&state->puzzles.has_wooden_bat);
                    printf("꽤 단단한 나무 방망이입니다. 사람도 충분히 기절시킬 수 있을 것 같습니다.\n");
                    return true;
                } else {
                    printf("이미 나무 방망이를 가지고 있습니다.\n");
                }
            } else {
                printf("'%s'은(는) 획득할 수 없습니다.\n", noun);
            }
            break;

        case ROOM_TROY_PALACE_FRONT:
            if (strcmp(noun, "note a") == 0 || strcmp(noun, "쪽지 a") == 0 ||
                strcmp(noun, "note b") == 0 || strcmp(noun, "쪽지 b") == 0 ||
                strcmp(noun, "note c") == 0 || strcmp(noun, "쪽지 c") == 0 ||
                strcmp(noun, "note") == 0 || strcmp(noun, "쪽지") == 0)
            {
                if (state->puzzles.notes_collected < 3) {
                    if (state->inventory[ITEM_NOTE_A] == 0 && (strcmp(noun, "note a") == 0 || strcmp(noun, "쪽지 a") == 0 || (strcmp(noun, "note") == 0 && state->puzzles.notes_collected == 0))) {
                        add_item_to_inventory(state, ITEM_NOTE_A);
                        state->puzzles.notes_collected++;
                        printf("흩어진 쪽지 A를 획득했습니다. (%d/3)\n", state->puzzles.notes_collected);
                    } else if (state->inventory[ITEM_NOTE_B] == 0 && (strcmp(noun, "note b") == 0 || strcmp(noun, "쪽지 b") == 0 || (strcmp(noun, "note") == 0 && state->puzzles.notes_collected == 1))) {
                        add_item_to_inventory(state, ITEM_NOTE_B);
                        state->puzzles.notes_collected++;
                        printf("흩어진 쪽지 B를 획득했습니다. (%d/3)\n", state->puzzles.notes_collected);
                    } else if (state->inventory[ITEM_NOTE_C] == 0 && (strcmp(noun, "note c") == 0 || strcmp(noun, "쪽지 c") == 0 || (strcmp(noun, "note") == 0 && state->puzzles.notes_collected == 2))) {
                        add_item_to_inventory(state, ITEM_NOTE_C);
                        state->puzzles.notes_collected++;
                        printf("흩어진 쪽지 C를 획득했습니다. (%d/3)\n", state->puzzles.notes_collected);
                    } else {
                        printf("'%s'은(는) 이미 획득했거나 존재하지 않습니다.\n", noun);
                        return false;
                    }

                    if (state->puzzles.notes_collected == 3 && !state->puzzles.gear_hint_revealed) {
                        printf("모든 쪽지를 모았습니다. 'combine notes' 명령어로 조합해 보세요.\n");
                    }
                    return true;
                } else {
                    printf("더 이상 쪽지가 없습니다.\n");
                }
            } else {
                printf("'%s'은(는) 획득할 수 없습니다.\n", noun);
            }
            break;

        default:
            printf("이 방에서는 '%s'을(를) 획득할 수 없습니다.\n", noun);
            break;
    }
    return false;
}

bool handle_use(GameState *state, const char *verb, const char *noun) {
    (void)verb;

    if (strlen(noun) == 0) {
        printf("무엇을 사용할지 입력하세요. (예: use key)\n");
        return false;
    }

    // ------------- Room 3: 경비병 선택지 특별 분기 -------------
    if (state->current_room == ROOM_TROY_PALACE_FRONT &&
        state->puzzles.guards_choice_presented &&
        !state->puzzles.guards_defeated_by_powder) {

        // 1. 방망이 선택
        if (strcmp(noun, "방망이") == 0 || strcmp(noun, "wooden bat") == 0) {
            printf("방망이로 경비병들을 공격했지만, 2명을 상대하기엔 너무 약했습니다!...\n");
            printf("결국 당신은 붙잡혀 게임 오버가 되었습니다.\n");
            state->game_over = true;
            return true;
        }
        // 2. 수면 가루 선택
        else if (strcmp(noun, "수면 가루") == 0 || strcmp(noun, "sleeping powder") == 0) {
            // switch-case 이동
        }
        // 3. 세이렌의 노래 선택
        else if (strcmp(noun, "세이렌의 노래") == 0 || strcmp(noun, "siren song") == 0) {
            printf("당신은 세이렌의 노래를 흉내냈지만, 경비병들은 아무런 반응도 보이지 않습니다.\n");
            printf("효과가 없었습니다.\n\n");
            state->puzzles.siren_song_attempted = true;
            printf("어떻게 하시겠습니까?\n");
            printf("1. 방망이로 경비병을 공격한다.\n");
            printf("2. 경비병에게 수면 가루를 사용한다.\n");
            return true;
        }
        else {
            printf("유효한 선택지가 아닙니다. (use 방망이 | use 수면 가루 | use 세이렌의 노래)\n");
            return false;
        }
    }

    switch (state->current_room) {
        case ROOM_PALLADION_TEMPLE:
            if (strcmp(noun, "torch") == 0 || strcmp(noun, "횃불") == 0) {
                if (has_item(state, ITEM_TORCH)) {
                    if (state->puzzles.papyrus_riddle_revealed) {
                        printf("횃불을 아프로디테의 벽화 아래 횃불걸이에 꽂았습니다.\n");
                        print_delay("쿠구궁, 하는 효과음과 함께 횃불 옆의 벽돌이 튀어나옵니다.\n", 30);
                        printf("튀어나온 벽돌에는 '헬레네'라고 적혀있네요.\n");
                        set_puzzle_solved(&state->puzzles.torch_placed_on_aphrodite);
                        set_puzzle_solved(&state->puzzles.helene_password_revealed);
                        remove_item_from_inventory(state, ITEM_TORCH);
                        return true;
                    } else {
                        printf("아직은 용도를 잘 모르겠습니다... 횃불을 보면 어쩐지 그림을 볼 수 있을 것 같은데.\n");
                    }
                } else {
                    printf("횃불을 가지고 있지 않습니다.\n");
                }
            } else if (strcmp(noun, "helene") == 0 || strcmp(noun, "헬레네") == 0) {
                if (state->puzzles.helene_password_revealed) {
                    if (!state->puzzles.palladium_obtained) {
                        printf("중앙 제단의 자물쇠에 '헬레네' 암호를 입력했습니다.\n");
                        set_puzzle_solved(&state->puzzles.palladium_obtained);
                        add_item_to_inventory(state, ITEM_PALLADIUM);
                        printf("재단이 열리며 팔라디온을 획득하였습니다. 열쇠 또한 같이 있군요! 열쇠를 챙겼습니다.\n");
                        set_puzzle_solved(&state->puzzles.room1_exit_key_obtained);
                        add_item_to_inventory(state, ITEM_ESCAPE_KEY);
                        return true;
                    } else {
                        printf("이미 제단의 자물쇠가 해제되었습니다.\n");
                    }
                } else {
                    printf("아직 이 암호를 사용할 때가 아닙니다. 제단의 비밀을 먼저 파헤쳐 보세요.\n");
                }
            } else if (strcmp(noun, "key") == 0 || strcmp(noun, "열쇠") == 0) {
                if (has_item(state, ITEM_ESCAPE_KEY)) {
                    printf("탈출 열쇠를 사용하여 굳게 잠긴 문을 열었습니다.\n");
                    printf("방을 탈출하였습니다. 어라.. 그러나 게임은 아직 끝나지 않았습니다..\n");
                    state->current_room = ROOM_TROJAN_HORSE;
                    return true;
                } else {
                    printf("탈출 열쇠를 가지고 있지 않습니다.\n");
                }
            } else {
                printf("'%s'은(는) 이곳에서 사용할 수 없습니다.\n", noun);
            }
            break;

        case ROOM_TROJAN_HORSE:
            if (strcmp(noun, "robe") == 0 || strcmp(noun, "로브") == 0) {
                if (has_item(state, ITEM_ROBE) && !state->puzzles.robe_equipped) {
                    set_puzzle_solved(&state->puzzles.robe_equipped);
                    printf("로브를 착용했습니다. 이제 경비병들에게 의심받지 않을 것 같습니다.\n");
                    remove_item_from_inventory(state, ITEM_ROBE);
                    return true;
                } else if (state->puzzles.robe_equipped) {
                    printf("이미 로브를 착용하고 있습니다.\n");
                } else {
                    printf("로브를 가지고 있지 않습니다.\n");
                }
            } else if (strcmp(noun, "aphrodite") == 0 || strcmp(noun, "아프로디테") == 0) {
                if (state->puzzles.robe_equipped && !state->puzzles.guard2_quiz_solved) {
                    printf("경비병에게 '아프로디테'라고 답했습니다. 경비병 2가 고개를 끄덕이며 말합니다:\n");
                    printf(" \"그래, 그럼 문 앞에 가서 두 번 툭툭 두드리고 암호를 말해. 들어갈 수 있을 거야.\"\n");
                    set_puzzle_solved(&state->puzzles.guard2_quiz_solved);
                    return true;
                } else if (state->puzzles.guard2_quiz_solved) {
                    printf("경비병 2는 이미 당신을 통과시켰습니다.\n");
                } else {
                    printf("아직 이 답을 사용할 때가 아닙니다. 경비병 2와 대화하고 로브를 착용해야 합니다.\n");
                }
            } else if (strcmp(noun, "odysseus") == 0 || strcmp(noun, "오디세우스") == 0) {
                if (state->puzzles.trojan_horse_banged && !state->puzzles.trojan_horse_password_entered) {
                    printf("트로이 목마를 고안한 사람으로 '오디세우스'를 말했습니다.\n");
                    printf("목마의 숨겨진 문이 천천히 열립니다. 안으로 진입합니다.\n");
                    set_puzzle_solved(&state->puzzles.trojan_horse_password_entered);
                    add_item_to_inventory(state, ITEM_SLEEPING_POWDER);
                    printf("안에 타고 있던 동료들 중 하나가 필요할 때 사용하라며 당신에게 수면 가루를 건넵니다.\n");
                    state->puzzles.sleeping_powder_obtained = true;
                    state->current_room = ROOM_TROY_PALACE_FRONT;
                    return true;
                } else if (state->puzzles.trojan_horse_password_entered) {
                    printf("이미 목마 안으로 진입했습니다.\n");
                } else {
                    printf("아직 이 암호를 사용할 때가 아닙니다. 먼저 목마를 두드려야 합니다.\n");
                }
            } else {
                printf("'%s'은(는) 이곳에서 사용할 수 없습니다.\n", noun);
            }
            break;

        case ROOM_TROY_PALACE_FRONT:
            if (strcmp(noun, "sleeping powder") == 0 || strcmp(noun, "수면 가루") == 0) {
                if (has_item(state, ITEM_SLEEPING_POWDER) && !state->puzzles.guards_defeated_by_powder) {
                    printf("경비병들을 향해 수면 가루를 뿌렸습니다! 두 경비가 조용히 쓰러집니다.\n");
                    printf("이제 성문 조작이 가능해 보입니다.\n");
                    set_puzzle_solved(&state->puzzles.guards_defeated_by_powder);
                    remove_item_from_inventory(state, ITEM_SLEEPING_POWDER);
                    return true;
                } else if (state->puzzles.guards_defeated_by_powder) {
                    printf("경비병들은 이미 쓰러져 있습니다.\n");
                } else {
                    printf("수면 가루를 가지고 있지 않습니다.\n");
                }
            } else if (strcmp(noun, "right arrow") == 0 || strcmp(noun, "오른쪽 화살표") == 0 ||
                       strcmp(noun, "left arrow") == 0 || strcmp(noun, "왼쪽 화살표") == 0 ||
                       strcmp(noun, "upper arrow") == 0 || strcmp(noun, "윗쪽 화살표") == 0) {
                if (state->puzzles.guards_defeated_by_powder && state->puzzles.gear_hint_revealed) {
                    static int gear_sequence_step = 0;
                    if (strcmp(noun, "left arrow") == 0 || strcmp(noun, "왼쪽 화살표") == 0) {
                        if (gear_sequence_step == 0) {
                            gear_sequence_step = 1;
                            printf("기어 장치에 왼쪽 화살표를 입력했습니다.\n");
                        } else {
                            printf("기어가 덜컥거리며 헛돌기 시작했다… 다시 시도해보자.\n");
                            gear_sequence_step = 0;
                        }
                    } else if (strcmp(noun, "right arrow") == 0 || strcmp(noun, "오른쪽 화살표") == 0) {
                        if (gear_sequence_step == 1) {
                            gear_sequence_step = 2;
                            printf("기어 장치에 오른쪽 화살표를 입력했습니다.\n");
                        } else {
                            printf("기어가 덜컥거리며 헛돌기 시작했다… 다시 시도해보자.\n");
                            gear_sequence_step = 0;
                        }
                    } else if (strcmp(noun, "upper arrow") == 0 || strcmp(noun, "윗쪽 화살표") == 0) {
                        if (gear_sequence_step == 2) {
                            printf("기어 장치에 윗쪽 화살표를 입력했습니다.\n");
                            printf("기어들이 완벽히 맞물리며 성문이 천천히 열린다...\n");
                            printf("은빛 달 아래, 트로이의 밤은 무너지고 있다.\n");
                            set_puzzle_solved(&state->puzzles.gear_puzzle_solved);
                            return true;
                        } else {
                            printf("기어가 덜컥거리며 헛돌기 시작했다… 다시 시도해보자.\n");
                            gear_sequence_step = 0;
                        }
                    } else {
                        printf("유효한 기어 조작 입력이 아닙니다. (예: use left arrow)\n");
                    }
                } else if (!state->puzzles.guards_defeated_by_powder) {
                    printf("경비병들 때문에 성문 조작 장치에 접근할 수 없습니다.\n");
                } else if (!state->puzzles.gear_hint_revealed) {
                    printf("기어 조작 힌트를 얻지 못했습니다. 쪽지를 조합해 보세요.\n");
                }
                return false;
            } else {
                printf("'%s'은(는) 이곳에서 사용할 수 없습니다.\n", noun);
            }
            break;

        default:
            printf("'%s'은(는) 사용할 수 없습니다.\n", noun);
            break;
    }
    return false;
}

bool handle_go(GameState *state, const char *verb, const char *noun) {
    (void)verb;
    if (strlen(noun) == 0) {
        printf("어디로 이동할지 입력하세요. (예: go north)\n");
        return false;
    }

    switch (state->current_room) {
        case ROOM_PALLADION_TEMPLE:
            if (strcmp(noun, "door") == 0 || strcmp(noun, "문") == 0) {
                if (has_item(state, ITEM_ESCAPE_KEY)) {
                    printf("탈출 열쇠를 사용하여 굳게 잠긴 문을 열었습니다.\n");
                    printf("방을 탈출하였습니다. 어라.. 그러나 게임은 아직 끝나지 않았습니다..\n");
                    state->current_room = ROOM_TROJAN_HORSE;
                    return true;
                } else {
                    printf("문은 굳게 잠겨 있습니다. 탈출 열쇠가 필요한 것 같습니다.\n");
                }
            } else if (strcmp(noun, "altar") == 0 || strcmp(noun, "제단") == 0) {
                printf("중앙 제단으로 이동했습니다. 제단의 자물쇠에 암호를 입력하려면 'use (암호)' 명령어를 사용하세요.\n");
                if (state->puzzles.helene_password_revealed && !state->puzzles.palladium_obtained) {
                    printf("튀어나온 벽돌의 '헬레네' 글자가 제단과 관련이 있을 것 같습니다.\n");
                }
                return true;
            } else {
                printf("이곳에서는 '%s'(으)로 이동할 수 없습니다.\n", noun);
            }
            break;
        case ROOM_TROJAN_HORSE:
            if (strcmp(noun, "trojan horse") == 0 || strcmp(noun, "목마") == 0) {
                printf("트로이 목마로 향했습니다.\n");
                if (!state->puzzles.trojan_horse_password_entered) {
                    printf("별다른 입구는 보이지 않습니다. 독특한 방법으로 들어갈 수 있을 것 같습니다.\n");
                    if (state->puzzles.guard1_hint_obtained) {
                        printf("경비병 1의 힌트: 방망이로 두 번 툭툭 두드려 보세요.\n");
                    }
                } else {
                    printf("목마 안으로 진입했습니다. 다음 방으로 이동합니다.\n");
                    add_item_to_inventory(state, ITEM_SLEEPING_POWDER);
                    printf("안에 타고 있던 동료들 중 하나가 필요할 때 사용하라며 당신에게 수면 가루를 건넵니다.\n");
                    state->puzzles.sleeping_powder_obtained = true;
                    state->current_room = ROOM_TROY_PALACE_FRONT;
                }
                return true;
            } else {
                printf("이곳에서는 '%s'(으)로 이동할 수 없습니다.\n", noun);
            }
            break;
        case ROOM_TROY_PALACE_FRONT:
            if (strcmp(noun, "gate") == 0 || strcmp(noun, "성문") == 0) {
                if (state->puzzles.gear_puzzle_solved) {
                    set_game_clear(state, true);
                    return true;
                } else {
                    printf("성문이 굳게 닫혀 있습니다. 성문 조작 장치를 작동시켜야 합니다.\n");
                }
            } else {
                printf("이곳에서는 '%s'(으)로 이동할 수 없습니다.\n", noun);
            }
            break;
    }
    return false;
}

bool handle_talk(GameState *state, const char *verb, const char *noun) {
    (void)verb; 
    if (strlen(noun) == 0) {
        printf("누구와 대화할지 입력하세요. (예: talk to guard 1)\n");
        return false;
    }

    if (state->current_room == ROOM_TROY_PALACE_FRONT) {
        if (strcmp(noun, "guards") == 0 || strcmp(noun, "경비병") == 0) {
            if (!state->puzzles.guards_defeated_by_powder) {
                state->puzzles.guards_choice_presented = true;
                printf("경비병 앞에 섰습니다. 어떻게 할까요?\n");
                printf("1. 방망이로 경비병을 공격한다.\n");
                printf("2. 경비병에게 수면 가루를 사용한다.\n");
                printf("3. 세이렌의 노래를 흉내낸다.\n");
                printf("아래 중 하나의 명령어를 입력해 보세요:\n");
                printf("use 방망이  |  use 수면 가루  |  use 세이렌의 노래\n");
                return true;
            } else {
                printf("경비병들은 이미 쓰러져 있습니다.\n");
                return true;
            }
        } else {
            printf("대화할 수 없는 대상입니다.\n");
            return false;
        }
    }

    if (state->current_room == ROOM_TROJAN_HORSE) {
        if (strcmp(noun, "to guard 1") == 0 || strcmp(noun, "guard 1") == 0 || strcmp(noun, "경비병 1") == 0) {
            printf("경비병 1: \"응? 거기 뭐 찾는 거야?\"\n");
            if (!state->puzzles.guard1_hint_obtained) {
                printf("경비병 1: \"방망이? 아, 목마 탈 때 쓰는 거야. 두 번만 가볍게 툭툭 두드리면 열릴 걸? 그리고 그 목마, 오디세우스가 만든 거라더군...\"\n");
                set_puzzle_solved(&state->puzzles.guard1_hint_obtained);
            }
            return true;
        } else if (strcmp(noun, "to guard 2") == 0 || strcmp(noun, "guard 2") == 0 || strcmp(noun, "경비병 2") == 0) {
            if (!state->puzzles.robe_equipped) {
                printf("경비병 2: \"이 추운 날씨에 맨몸으로? 감기 걸리겠다.\"\n");
            } else {
                if (!state->puzzles.guard2_quiz_solved) {
                    printf("경비병 2: \"그래, 목마 탈 사람 맞구먼. 그럼 질문 하나. 트로이를 무너뜨릴 여신의 이름은?\"\n");
                    printf("정답을 'use (여신 이름)' 형태로 입력해 보세요.\n");
                    set_puzzle_solved(&state->puzzles.guard2_quiz_hint_given);
                } else {
                    printf("경비병 2는 이미 당신을 통과시켰습니다.\n");
                }
            }
            return true;
        } else {
            printf("대화할 수 없는 대상입니다.\n");
        }
    } else {
        printf("이곳에는 대화할 상대가 없습니다.\n");
    }
    return false;
}


bool handle_knock(GameState *state, const char *verb, const char *noun) {
    (void)verb;
    if (strlen(noun) == 0) {
        printf("무엇을 두드릴지 입력하세요. (예: knock trojan horse)\n");
        return false;
    }

    if (state->current_room == ROOM_TROJAN_HORSE) {
        if (strcmp(noun, "2") == 0 || strcmp(noun, "twice") == 0 || strcmp(noun, "trojan horse 2") == 0) {
            if (has_item(state, ITEM_WOODEN_BAT)) {
                if (!state->puzzles.trojan_horse_banged) {
                    printf("나무 방망이로 트로이 목마를 두 번 툭툭 두드렸습니다. '쿵, 쿵' 소리가 울려 퍼졌습니다.\n");
                    printf("트로이 목마를 고안한 사람은 누구인가요? (use [이름]으로 답하세요)\n");
                    set_puzzle_solved(&state->puzzles.trojan_horse_banged);
                    return true;
                } else {
                    printf("이미 목마를 두드렸습니다. 이제 암호를 말해야 합니다.\n");
                }
            } else {
                printf("나무 방망이가 있어야 목마를 두드릴 수 있습니다.\n");
            }
        } else {
            printf("움직임이 없습니다. (예: knock 2)\n");
        }
    } else {
        printf("이곳에서는 두드릴 것이 없습니다.\n");
    }
    return false;
}

bool handle_inventory(GameState *state, const char *verb, const char *noun) {
    (void)verb;
    (void)noun;
    display_inventory(state);
    return true;
}

bool handle_help(GameState *state, const char *verb, const char *noun) {
    (void)state;
    (void)verb;
    (void)noun;

    printf("\n--- 사용 가능한 명령어 ---\n");
    for (int i = 0; command_list[i].verb != NULL; i++) {
        printf("- %s: %s\n", command_list[i].verb, command_list[i].description);
    }
    printf("-------------------------\n");
    return true;
}

bool handle_quit(GameState *state, const char *verb, const char *noun) {
    (void)verb;
    (void)noun;
    printf("게임을 종료합니다.\n");
    state->game_over = true;
    return true;
}

bool handle_combine(GameState *state, const char *verb, const char *noun) {
    (void)verb;
    if (strlen(noun) == 0 || strcmp(noun, "notes") == 0 || strcmp(noun, "쪽지") == 0) {
        if (state->current_room == ROOM_PALLADION_TEMPLE) {
            if (state->puzzles.papyrus_fragments_collected == 3 && !state->puzzles.papyrus_riddle_revealed) {
                printf("세 개의 파피루스 조각을 조합했습니다.\n");
                printf("조합된 파피루스에는 '가장 아름다운 여신에게 횃불을 바쳐라.'라는 문구가 적혀 있습니다.\n");
                set_puzzle_solved(&state->puzzles.papyrus_riddle_revealed);
                remove_item_from_inventory(state, ITEM_PAPYRUS_FRAGMENT);
                return true;
            } else if (state->puzzles.papyrus_riddle_revealed) {
                printf("이미 파피루스 조각을 조합했습니다.\n");
            } else {
                printf("파피루스 조각이 모두 모이지 않았습니다. (%d/3)\n", state->puzzles.papyrus_fragments_collected);
            }
        } else if (state->current_room == ROOM_TROY_PALACE_FRONT) {
             if (state->puzzles.notes_collected == 3 && !state->puzzles.gear_hint_revealed) {
                printf("흩어진 쪽지들을 조합했습니다.\n");
                printf("쪽지에는 '왼쪽, 오른쪽, 위쪽'이라는 기어 조작 순서가 적혀 있습니다.\n");
                set_puzzle_solved(&state->puzzles.gear_hint_revealed);
                remove_item_from_inventory(state, ITEM_NOTE_A);
                remove_item_from_inventory(state, ITEM_NOTE_B);
                remove_item_from_inventory(state, ITEM_NOTE_C);
                return true;
            } else if (state->puzzles.gear_hint_revealed) {
                printf("이미 쪽지들을 조합했습니다.\n");
            } else {
                printf("쪽지가 모두 모이지 않았습니다. (%d/3)\n", state->puzzles.notes_collected);
            }
        } else {
            printf("이곳에서는 조합할 것이 없습니다.\n");
        }
    } else {
        printf("무엇을 조합할지 입력하세요. (예: combine notes)\n");
    }
    return false;
}

bool handle_time(GameState *state, const char *verb, const char *noun) {
    (void)verb;
    (void)noun;

    time_t current_time = time(NULL);
    double elapsed_seconds = difftime(current_time, state->start_time);
    int elapsed_minutes = (int)(elapsed_seconds / 60);

    int remaining_minutes = state->time_limit_minutes - elapsed_minutes;

    if (remaining_minutes > 0) {
        printf("남은 시간: %d분 (총 %d분 중 %d분 경과)\n",
               remaining_minutes, state->time_limit_minutes, elapsed_minutes);
    } else {
        printf("시간이 초과되었습니다! 임무 실패...\n");
        state->game_over = true;
    }
    return true;
}