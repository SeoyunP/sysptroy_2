#include "game_state.h"
#include <time.h> 
#include <stdio.h>
#include <string.h>

void initialize_game_state(GameState *state) {
    state->current_room = ROOM_PALLADION_TEMPLE;
    state->game_over = false;
    state->game_clear = false;
    state->hint_uses_remaining = 3; 
    state->start_time = time(NULL);
    state->time_limit_minutes = 15;

    for (int i = 0; i < MAX_ITEMS; i++) {
        state->inventory[i] = 0;
    }

    memset(&state->puzzles, 0, sizeof(state->puzzles));

    state->puzzles.papyrus_fragments_collected = 0;
    state->puzzles.notes_collected = 0;
    state->puzzles.guards_choice_presented = false;
    state->puzzles.siren_song_attempted = false;
}

bool has_item(const GameState *state, Item item_id) {
    if (item_id <= ITEM_NONE || item_id >= MAX_ITEMS) {
        return false;
    }
    return state->inventory[item_id] > 0;
}

void add_item_to_inventory(GameState *state, Item item_id) {
    if (item_id > ITEM_NONE && item_id < MAX_ITEMS) {
        state->inventory[item_id]++;
        printf("'%s'을(를) 획득했습니다.\n", get_item_name(item_id));
    }
}

void remove_item_from_inventory(GameState *state, Item item_id) {
    if (item_id > ITEM_NONE && item_id < MAX_ITEMS && state->inventory[item_id] > 0) {
        state->inventory[item_id]--;
        printf("'%s'을(를) 사용했습니다.\n", get_item_name(item_id));
    }
}

const char* get_item_name(Item item_id) {
    switch (item_id) {
        case ITEM_TORCH: return "횃불";
        case ITEM_PAPYRUS_FRAGMENT: return "파피루스 조각";
        case ITEM_PALLADIUM: return "팔라디온";
        case ITEM_ESCAPE_KEY: return "탈출 열쇠";
        case ITEM_ROBE: return "로브";
        case ITEM_WOODEN_BAT: return "나무 방망이";
        case ITEM_SLEEPING_POWDER: return "수면 가루";
        case ITEM_NOTE_A: return "쪽지 A";
        case ITEM_NOTE_B: return "쪽지 B";
        case ITEM_NOTE_C: return "쪽지 C";
        default: return "알 수 없는 아이템";
    }
}

const char* get_room_name(RoomID room_id) {
    switch (room_id) {
        case ROOM_PALLADION_TEMPLE: return "팔라디온 신전";
        case ROOM_TROJAN_HORSE: return "트로이 목마 야영지";
        case ROOM_TROY_PALACE_FRONT: return "트로이 궁전 성문 앞";
        default: return "알 수 없는 장소";
    }
}

void display_inventory(const GameState *state) {
    printf("\n--- 인벤토리 ---\n");
    bool empty = true;
    for (int i = 1; i < MAX_ITEMS; i++) { 
        if (state->inventory[i] > 0) {
            printf("- %s (%d개)\n", get_item_name(i), state->inventory[i]);
            empty = false;
        }
    }
    if (empty) {
        printf("인벤토리가 비어 있습니다.\n");
    }
    printf("------------------\n");
}

void set_game_over(GameState *state, bool over) {
    state->game_over = over;
}

void set_game_clear(GameState *state, bool clear) {
    state->game_clear = clear;
}

void set_puzzle_solved(bool *flag_ptr) {
    *flag_ptr = true;
}