#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "rooms.h" // For room function declarations
#include "../game_state.h"
#include "../utils/utils.h"

void play_room3(GameState *game_state) {
    static bool initial_entry = true;

    if (initial_entry) {
        clear_screen();
        print_delay("무사히 동료들과 트로이 목마에 합류했습니다.\n", 30);
        print_delay("목마 안에서 꼬박 하루를 보내고, 드디어 적진의 한가운데로 향할 차례입니다.\n", 30);
        print_delay("안에 타고 있던 동료들 중 하나가 필요할 때 사용하라며 당신에게 수면 가루를 건넵니다.\n", 30);
        
        // 수면 가루 획득 메시지 출력 및 아이템 획득 로직
        if (!game_state->puzzles.sleeping_powder_obtained) {
            add_item_to_inventory(game_state, ITEM_SLEEPING_POWDER);
            game_state->puzzles.sleeping_powder_obtained = true;
        }
        print_delay("성공적으로 트로이 목마에서 내려 보면, 눈 앞에 보이는 광장은 조용하고 사람들은 술에 취해 자고 있네요.\n", 30);
        print_delay("주변을 둘러보려면 'look around'를 입력하세요.\n", 30);
        initial_entry = false;
    }
    // Room 3 loop logic is handled by command_parser.c based on user input
}