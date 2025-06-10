#include "utils/utils.h"
#include <stdio.h>
#include <stdlib.h> 
#include <string.h> 
#include <stdbool.h>
#include <time.h>   

#include "game_state.h"
#include "command_parser.h"
#include "rooms/rooms.h" 

void game_intro() {
    clear_screen();
    print_delay("눈을 떠보니 당신은 방탈출 게임 안에 들어와있습니다.\n", 30);
    print_delay("15분 이내에 목표를 전부 수행하여 이 곳에서 탈출하도록 하세요.\n",30);
    printf("→enter 입력\n");
    getchar();

    clear_screen();
    print_delay("트로이의 왕자 파리스는 사랑과 미의 여신 아프로디테의 도움으로 그리스 연합 장군의 아내 헬레네를 납치했습니다. 그로 인해 트로이 전쟁이 발생하였습니다. 당신은 트로이와 그리스의 전쟁이 한창인 현재, 오디세우스의 동료입니다. 그리스 편에서 헬레네를 되찾고 전쟁이 끝나도록 도와봅시다. 건투를 빕니다!\n", 30);
    printf("→enter 입력\n");
    getchar(); 
}

int main() {
    srand(time(NULL));
    GameState game_state;
    initialize_game_state(&game_state);

    game_intro();

    while (!game_state.game_over && !game_state.game_clear) {
        switch (game_state.current_room) {
            case ROOM_PALLADION_TEMPLE:
                play_room1(&game_state);
                break;
            case ROOM_TROJAN_HORSE:
                play_room2(&game_state);
                break;
            case ROOM_TROY_PALACE_FRONT:
                play_room3(&game_state);
                break;
            default:
                printf("알 수 없는 방 ID입니다. 게임을 종료합니다.\n");
                set_game_over(&game_state, true);
                break;
        }

        if (game_state.game_over || game_state.game_clear) {
            break;
        }

        printf("\n무엇을 하시겠습니까? ");
        char input[256];
        if (fgets(input, sizeof(input), stdin) == NULL) {
            printf("입력 오류!\n");
            break;
        }
        input[strcspn(input, "\n")] = 0;

        char verb[50];
        char noun[200];
        parse_command(input, verb, noun);

        execute_command(&game_state, verb, noun);
    }

    if (game_state.game_clear) {
        printf("\n🎉 트로이 함락 성공! 당신은 게임을 클리어했습니다.\n");
    } else {
        printf("\n게임 오버! 다음에 다시 시도해보세요.\n");
    }

    return 0;
}
