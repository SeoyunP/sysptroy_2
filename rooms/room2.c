#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "rooms.h"
#include "../game_state.h"
#include "../utils/utils.h"

void play_room2(GameState *game_state) {
    (void)game_state;
    static bool initial_entry = true;

    if (initial_entry) {
        clear_screen();
        print_delay("당신은 성공적으로 팔라디온을 탈취했습니다.\n", 30);
        print_delay("이번엔 동료들과 합류하기 위해 경비병에게 도움을 얻어 트로이 목마에 올라타야 합니다.\n", 30);
        print_delay("밤은 충분히 어둡고, 성 바깥의 야영지에는 두 명의 그리스 군 경비병이 보입니다.\n", 30);
        print_delay("과연 성공적으로 잠입할 수 있을까요?\n", 30);
        print_delay("주변을 둘러보려면 'look around'를 입력하세요.\n", 30);
        initial_entry = false;
    }
}
