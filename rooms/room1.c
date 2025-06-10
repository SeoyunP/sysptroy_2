#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "rooms.h"
#include "../game_state.h"
#include "../utils/utils.h"

void play_room1(GameState *game_state) {
    (void)game_state;
    static bool initial_entry = true;

    if (initial_entry) {
        clear_screen();
        print_delay("이곳은...\n", 30);
        print_delay("트로이 성의 심장부, 아테나 여신을 모시는 신전의 깊숙한 밀실.\n", 30);
        print_delay("당신은 트로이의 불패 신화를 지탱하는 수호신 상, 팔라디온을 훔치러 잠입했습니다.\n", 30);
        print_delay("어둠 속에서 신전 특유의 신성함과 서늘함이 동시에 느껴집니다.\n", 30);
        print_delay("주변을 둘러보려면 'look around'를 입력하세요.\n", 30);
        initial_entry = false;
    }
}
