/*
Copyright 2021 andys8 <andys8@users.noreply.github.com>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#include QMK_KEYBOARD_H
#include "sendstring_german.h"

// feature 1: Macro using send string
enum custom_keycodes {
    CONDA_ACTIVATE= SAFE_RANGE,
    CONDA_DEACTIVATE,
    GIT_COMMIT,
    COPY,
    PASTE,
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
#ifdef CONSOLE_ENABLE
    uprintf("KL: kc: 0x%04X, col: %u, row: %u, pressed: %b, time: %u, interrupt: %b, count: %u\n", keycode, record->event.key.col, record->event.key.row, record->event.pressed, record->event.time, record->tap.interrupted, record->tap.count);
    uprintf("rgblight: mode: %u, hue: %u, sat: %u, val: %u, speed: %u\n", rgblight_get_mode(), rgblight_get_hue(), rgblight_get_sat(), rgblight_get_val(), rgblight_get_speed());
#endif
    switch (keycode) {
        case CONDA_ACTIVATE:
            if (record->event.pressed) {
                SEND_STRING("conda activate cling\n");
            }
            break;
        case CONDA_DEACTIVATE:
            if (record->event.pressed) {
                SEND_STRING("conda deactivate\n");
            }
            break;
        case GIT_COMMIT:
            if (record->event.pressed) {
                SEND_STRING("git commit -a\n");
            }
            break;
        case COPY:
            if (record->event.pressed) {
                tap_code16(G(KC_C));
            }
            break;
        case PASTE:
            if (record->event.pressed) {
                tap_code16(G(KC_V));
            }
            break;
    }
    return true;
};

// feature 2: tap dance
typedef enum {
    TD_NONE,
    TD_UNKNOWN,
    TD_SINGLE_TAP,
    TD_SINGLE_HOLD,
    TD_DOUBLE_TAP,
    TD_DOUBLE_HOLD,
    TD_DOUBLE_SINGLE_TAP, // Send two single taps
    TD_TRIPLE_TAP,
    TD_TRIPLE_HOLD
} td_state_t;

typedef struct {
    bool is_press_action;
    td_state_t state;
} td_tap_t;

enum {
    TAB_1,
    QUO_LAYER,
    VIM_J_H,
    SOME_OTHER_DANCE,
};

td_state_t cur_dance(tap_dance_state_t *state);
void x_finished(tap_dance_state_t *state, void *user_data);
void x_reset(tap_dance_state_t *state, void *user_data);
void ql_finished(tap_dance_state_t *state, void *user_data);
void ql_reset(tap_dance_state_t *state, void *user_data);
void j_finished(tap_dance_state_t *state, void *user_data);
void j_reset(tap_dance_state_t *state, void *user_data);

td_state_t cur_dance(tap_dance_state_t *state) {
    if(state->count == 1) {
        if(state->interrupted || !state->pressed) return TD_SINGLE_TAP;
        else return TD_SINGLE_HOLD;
    } else if (state->count == 2) {
        if(state->interrupted) return TD_DOUBLE_SINGLE_TAP;
        else if (state->pressed) return TD_DOUBLE_HOLD;
        else return TD_DOUBLE_TAP;
    }
    if(state->count == 3) {
        if(state->interrupted || !state->pressed) return TD_TRIPLE_TAP;
        else return TD_TRIPLE_HOLD;
    } else return TD_UNKNOWN;
}

static td_tap_t x_tap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

static td_tap_t ql_tap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

static td_tap_t j_tap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

tap_dance_action_t tap_dance_actions[] = {
    [TAB_1]     = ACTION_TAP_DANCE_FN_ADVANCED(NULL, x_finished, x_reset),
    [QUO_LAYER] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, ql_finished, ql_reset),
    [VIM_J_H]   = ACTION_TAP_DANCE_FN_ADVANCED(NULL, j_finished, j_reset),
};

// feature 3: key override
//const key_override_t dot_key_override =
//    ko_make_basic(MOD_MASK_SHIFT, KC_DOT, KC_QUES);
//
//const key_override_t** key_overrides = (const key_override_t*[]){
//    &dot_key_override,
//    NULL
//};

// feature 4: combo
// enum combos {
//     A_12D,
// };
// const uint16_t PROGMEM a12d_combo[] = {KC_1, KC_2, KC_D, COMBO_END};
//
// combo_t key_combos[COMBO_COUNT] = {
//     [A_12D]   = COMBO(a12d_combo, KC_A),
// };
/*bool process_combo_key_release(uint16_t combo_index, combo_t *combo, uint8_t key_index, uint16_t keycode) {
    uprintf("Combo release: kc: 0x%04X, index: %u, combo_index %u\n", keycode, key_index, combo_index );
    return true;
}*/

// layouts
enum layer_names {
    WASD_LAYER,
    FUNC_LAYER,
    MUSIC_LAYER,
    VIM_LAYER,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* tap
 *            _______________________________
 *           /1/TAB/  2  /  3  /4/F4 /  5  /
 *          /-----/-----/-----/-----/-----/
 *         /  Q  /  W  /  E  /  R  /  T  /
 *        /-----/-----/-----/-----/-----/
 *       /  A  /  S  /  D  /  F  /  G  /
 *      /-----/-----/-----/-----/-----/
 *     /LSFT /  Z  /  X  /  C  / V/B /
 *    /-----/-----/-----/-----/-----/
 *   /HO/EN/Ctrl /Optio/ CMD /Space/
 *  -------------------------------
 */
  [WASD_LAYER] = LAYOUT(        TD(TAB_1),   KC_2,          KC_3,    KC_4,   LT(1, KC_5),
                                     KC_Q,   KC_W,          KC_E,    KC_R,   KC_T,
                                     KC_A,   KC_S,          KC_D,    KC_F,   KC_G,
                                  KC_LSFT,   KC_Z,          KC_X,    KC_C,   KC_V,
                                  KC_HOME,   KC_LCTL,       KC_LOPT, KC_LCMD,KC_SPACE),
/* hold
 *            ___________________
 *           /CON_A/CON_D/SHIFT/
 *          /-----/-----/-----/
 *         /RGBTg/RGBM+/Brig+/
 *        /-----/-----/-----/
 *       / COPY/TD(1)/PASTE/
 *      -------------------
 */
  [FUNC_LAYER] = LAYOUT(CONDA_ACTIVATE,CONDA_DEACTIVATE, _______,  _______, KC_LSFT,
                               RGB_TOG,         RGB_MOD, RGB_VAI,  RGB_SPI, _______,
                              _______,          _______,TD(QUO_LAYER),_______, _______,
                               _______,         _______,  _______,  _______, _______,
                                  COPY,         _______,  _______,  _______, PASTE),

/* double tap
 */
  [VIM_LAYER] = LAYOUT(  _______,         _______,  _______,  _______, _______,
                         _______,         _______,  _______,  _______, _______,
                         _______,         _______,TD(QUO_LAYER),_______, _______,
                         _______,         _______,  _______,  _______, _______,
                         _______,         _______,  _______,  _______, _______),

/* triple tap
 *            _______________________________
 *           /  1  /     /  X  /      /  4  /
 *          /-----/-----/-----/ -----/-----/
 *         /  2  /     /  Z  /      /  5  /
 *        /-----/-----/-----/ -----/-----/
 *       /  D  /     /TD(1)/      /  6  /
 *      /-----/-----/-----/ -----/-----/
 *     /     /     /     /      /     /
 *    /-----/-----/-----/ -----/-----/
 *   /     /     /     /      /     /
 *  --------------------------------
*/
  [MUSIC_LAYER] = LAYOUT(  KC_1,   _______,  KC_X,          _______, KC_4,
                           KC_2,   _______,  KC_Z,          _______, KC_5,
                           KC_D,   _______,  TD(QUO_LAYER), _______, KC_6,
                           _______,_______,  _______,       _______, _______,
                           _______,_______,  _______,       _______, _______),
};

// post init
void keyboard_post_init_user(void) {
    // 调用后初始化代码
    debug_enable=true;
    debug_matrix=true;
    rgblight_enable_noeeprom();
}

// below is tap dance callback methods
/*
 * Tap = Send Tab
 * Hold = Send 1
 * Double Tap = Send Escape
 * Double Tap and Hold = Send `
 * Triple Tap = Send KC_CAPS
 */
void x_finished(tap_dance_state_t *state, void *user_data) {
    x_tap_state.state = cur_dance(state);
    switch(x_tap_state.state) {
        case TD_SINGLE_TAP: register_code(KC_TAB);break;
        case TD_SINGLE_HOLD: register_code(KC_1); break;
        case TD_DOUBLE_TAP: register_code(KC_ESC); break;
        case TD_DOUBLE_HOLD: register_code(KC_GRAVE);break;
        case TD_DOUBLE_SINGLE_TAP: tap_code(KC_1);register_code(KC_1);break;
        case TD_TRIPLE_TAP: register_code(KC_CAPS);break;
        default: break;
    }
}

void x_reset(tap_dance_state_t *state, void *user_data) {
    switch (x_tap_state.state) {
        case TD_SINGLE_TAP: unregister_code(KC_TAB); break;
        case TD_SINGLE_HOLD: unregister_code(KC_1);break;
        case TD_DOUBLE_TAP: unregister_code(KC_ESC);break;
        case TD_DOUBLE_HOLD: unregister_code(KC_GRAVE);break;
        case TD_DOUBLE_SINGLE_TAP: unregister_code(KC_1);break;
        case TD_TRIPLE_TAP: unregister_code(KC_CAPS);break;
        default: break;
    }
    x_tap_state.state = TD_NONE;
}

/*
 * Tap = WASD LAYER
 * Hold = FUNC_LAYER
 * Double Tap = --- LAYER
 * Double Tap and Hold =
 * Triple Tap = MUSIC LAYER
 */
void ql_finished(tap_dance_state_t *state, void *user_data) {
    ql_tap_state.state = cur_dance(state);
    switch (ql_tap_state.state) {
        case TD_SINGLE_TAP:
            if(layer_state_is(WASD_LAYER)) {
                ;
            } else {
                layer_off(FUNC_LAYER);
                layer_off(VIM_LAYER);
                layer_off(MUSIC_LAYER);
                layer_on(WASD_LAYER);
            }
            break;
        case TD_SINGLE_HOLD:
            if(layer_state_is(FUNC_LAYER)) {
                ;
            } else {
                layer_off(VIM_LAYER);
                layer_off(WASD_LAYER);
                layer_off(MUSIC_LAYER);
                layer_on(FUNC_LAYER);
            }
            break;
        case TD_DOUBLE_TAP:
            if(layer_state_is(VIM_LAYER)) {
                ;
            } else {
                layer_off(WASD_LAYER);
                layer_off(FUNC_LAYER);
                layer_off(MUSIC_LAYER);
                layer_on(VIM_LAYER);
            }
            break;
        case TD_TRIPLE_TAP:
            if(layer_state_is(MUSIC_LAYER)) {
                ;
            } else {
                layer_off(WASD_LAYER);
                layer_off(FUNC_LAYER);
                layer_off(VIM_LAYER);
                layer_on(MUSIC_LAYER);
            }
        default:
            break;
    }
}

void ql_reset(tap_dance_state_t *state, void *user_data) {
    ql_tap_state.state = TD_NONE;
}

void j_finished(tap_dance_state_t *state, void *user_data) {
    j_tap_state.state = cur_dance(state);
    switch(j_tap_state.state) {
        case TD_SINGLE_TAP: register_code(KC_J);break;
        case TD_SINGLE_HOLD: register_code(KC_H); break;
        case TD_DOUBLE_HOLD: register_code(KC_J);break;
        default: break;
    }
}

void j_reset(tap_dance_state_t *state, void *user_data) {
    switch (j_tap_state.state) {
        case TD_SINGLE_TAP: unregister_code(KC_J); break;
        case TD_SINGLE_HOLD: unregister_code(KC_H);break;
        case TD_DOUBLE_HOLD: unregister_code(KC_J);break;
        default: break;
    }
    j_tap_state.state = TD_NONE;
}
