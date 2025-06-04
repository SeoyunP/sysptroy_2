#ifndef GAME_STATE_H
#define GAME_STATE_H

#include <stdbool.h>
#include <time.h> // time_t, time 함수를 위해 필요

// 아이템 목록
typedef enum {
    ITEM_NONE = 0,
    ITEM_TORCH,                 // 횃불 (Room 1)
    ITEM_PAPYRUS_FRAGMENT,      // 파피루스 조각 (Room 1)
    ITEM_PALLADIUM,             // 팔라디온 (Room 1)
    ITEM_ESCAPE_KEY,            // 탈출 열쇠 (Room 1)
    ITEM_ROBE,                  // 로브 (Room 2)
    ITEM_WOODEN_BAT,            // 나무 방망이 (Room 2)
    ITEM_SLEEPING_POWDER,       // 수면 가루 (Room 3, 동료에게 받음)
    ITEM_NOTE_A,                // 쪽지 A (Room 3)
    ITEM_NOTE_B,                // 쪽지 B (Room 3)
    ITEM_NOTE_C,                // 쪽지 C (Room 3)
    MAX_ITEMS
} Item;

// 방 ID 목록
typedef enum {
    ROOM_PALLADION_TEMPLE = 1, // 팔라디온 신전 (Room 1)
    ROOM_TROJAN_HORSE,         // 트로이 목마 야영지 (Room 2)
    ROOM_TROY_PALACE_FRONT     // 트로이 궁전 성문 앞 (Room 3)
} RoomID;

// 퍼즐 상태를 저장하는 구조체
typedef struct {
    // --- Room 1 퍼즐: 팔라디온 신전 ---
    int papyrus_fragments_collected;        // 파피루스 조각 수 (3개)
    bool papyrus_riddle_revealed;           // 파피루스 수수께끼 ('가장 아름다운 여신에게') 힌트 획득 여부
    bool torch_placed_on_aphrodite;         // 횃불이 아프로디테 벽화에 꽂혔는지 여부
    bool helene_password_revealed;          // '헬레네' 암호가 벽돌에서 드러났는지 여부
    bool palladium_obtained;                // 팔라디온 획득 여부
    bool room1_exit_key_obtained;           // Room 1 탈출 열쇠 획득 여부

    // --- Room 2 퍼즐: 트로이 목마 ---
    bool has_robe;                          // 로브 획득 여부 (중복 아이템 획득 방지용)
    bool has_wooden_bat;                    // 나무 방망이 획득 여부 (중복 아이템 획득 방지용)
    bool robe_equipped;                     // 로브 착용 여부
    bool guard1_hint_obtained;              // 경비병 1 (친절한 병사) 힌트 (방망이 사용법, 오디세우스) 획득 여부
    bool guard2_quiz_hint_given;            // 경비병 2 (까다로운 병사) 퀴즈 힌트 ('트로이를 무너뜨릴 여신') 제공 여부
    bool guard2_quiz_solved;                // 경비병 2 퀴즈 해결 여부
    bool trojan_horse_banged;               // 트로이 목마를 두드렸는지 여부 (2회)
    bool trojan_horse_password_entered;     // 트로이 목마 암호 입력 여부 ('ODYSSEUS')

    // --- Room 3 퍼즐: 트로이 궁전 ---
    bool sleeping_powder_obtained;          // 수면 가루 획득 여부
    bool guards_defeated_by_powder;         // 경비병이 수면 가루로 제압되었는지 여부
    int notes_collected;                    // 쪽지 획득 수 (3개)
    bool gear_hint_revealed;                // 쪽지 조합으로 기어 힌트 획득 여부
    bool gear_puzzle_solved;                // 기어 퍼즐 해결 여부
    
    bool guards_choice_presented; // Room 3: 경비병 선택지 제시 여부
    bool siren_song_attempted;    // Room 3: 세이렌 노래 시도 여부

} PuzzleFlags;


// 게임 상태 구조체
typedef struct {
    RoomID current_room;
    bool game_over;
    bool game_clear;
    int inventory[MAX_ITEMS]; // 인벤토리 (각 아이템의 수량)
    PuzzleFlags puzzles;

    time_t start_time;         // 게임 시작 시간
    int time_limit_minutes;    // 게임 제한 시간 (분 단위)

    int hint_uses_remaining; // 힌트 사용 횟수 (선택 사항, 여기선 사용 안함)
} GameState;

// 함수 선언
void initialize_game_state(GameState *state);
bool has_item(const GameState *state, Item item_id);
void add_item_to_inventory(GameState *state, Item item_id);
void remove_item_from_inventory(GameState *state, Item item_id);
const char* get_item_name(Item item_id);
const char* get_room_name(RoomID room_id);
void display_inventory(const GameState *state);
void set_game_over(GameState *state, bool over);
void set_game_clear(GameState *state, bool clear);

// 퍼즐 플래그를 설정하는 유틸리티 함수
// 이 함수는 단순히 *flag_ptr = true; 를 수행합니다.
void set_puzzle_solved(bool *flag_ptr);


#endif // GAME_STATE_H
