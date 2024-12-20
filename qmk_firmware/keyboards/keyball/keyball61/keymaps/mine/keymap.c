/*
Copyright 2022 @Yowkees
Copyright 2022 MURAOKA Taro (aka KoRoN, @kaoriya)

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

#include "quantum.h"

// 自作キーコード
enum custom_keycodes {
    LT_LCTL_SPC = SAFE_RANGE, // Tap/Hold: IME/Layer1 
};

static bool layer_1_active = false;
static uint16_t lt_timer;


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case LT_LCTL_SPC: // Tap/Hold: IME/Layer1
            if (record->event.pressed) {
                // キーを押した時
                layer_1_active = true;
                layer_on(1);  // レイヤー1をオン
                lt_timer = timer_read();
                return false;
            } else {
                // キーを離した時
                layer_1_active = false;
                layer_off(1); // レイヤー1をオフ
                
                if (timer_elapsed(lt_timer) < TAPPING_TERM) {
                    // タップした場合（素早く押し離した場合）
                    tap_code16(LCTL(KC_SPACE));
                }
                return false;
            }
            break;
    }
    return true;
}

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT_universal(
    KC_GRV , KC_1   , KC_2   , KC_3        , KC_4       , KC_5  ,                               KC_6   , KC_7   , KC_8   , KC_9   , KC_0         , KC_EQL ,
    KC_TAB , KC_Q   , KC_W   , KC_E        , KC_R       , KC_T  ,                               KC_Y   , KC_U   , KC_I   , KC_O   , KC_P         , KC_MINS,
    KC_LSFT, KC_A   , KC_S   , KC_D        , KC_F       , KC_G  ,                               KC_H   , KC_J   , KC_K   , KC_L   , KC_SCLN      , KC_QUOT,
    KC_LCTL, KC_Z   , KC_X   , KC_C        , KC_V       , KC_B  , LT(3,KC_LBRC), LT(3,KC_RBRC), KC_N   , KC_M   , KC_COMM, KC_DOT , LT(2,KC_SLSH), KC_RSFT,
    MO(2)  , KC_LWIN, KC_LALT, LT(1,KC_ESC), LT_LCTL_SPC, KC_SPC, MO(2)        , KC_ENT       , KC_BSPC, KC_NO  , KC_NO  , KC_NO  , LT(1,KC_BSLS), KC_RCTL
  ),

  [1] = LAYOUT_universal(
    _______, KC_F1  , KC_F2, KC_F3 , KC_F4  , KC_F5  ,                   KC_F6  , KC_F7  ,  KC_F8   ,  KC_F9   , KC_F10 , KC_F11 ,
    _______, KC_PSLS, KC_7 , KC_8  , KC_9   , KC_PPLS,                   KC_LBRC, KC_RBRC,S(KC_LBRC),S(KC_RBRC), KC_PSCR, KC_F12 ,
    _______, _______, KC_4 , KC_5  , KC_6   , KC_PMNS,                   KC_LEFT, KC_DOWN,  KC_UP   ,  KC_RGHT , _______, _______,
    _______, _______, KC_1 , KC_2  , KC_3   , KC_PENT, KC_PAST, KC_DEL , S(KC_9), S(KC_0),  _______ , _______  , _______, _______,
    _______, _______, KC_0 , KC_DOT, _______, _______, _______, _______, _______, _______,  _______ , _______  , _______, _______
  ),

  [2] = LAYOUT_universal(
    _______, KC_1   , KC_2   , KC_3        , KC_4   , KC_5   ,                                KC_6      , KC_7      , KC_8    , KC_9    , KC_0    , KC_EQL ,
    _______, KC_Q   , KC_W   , KC_BRID     , KC_BRIU, KC_T   ,                                CPI_D1K   , CPI_D100  , CPI_I100, CPI_I1K , SCRL_DVD, KC_MINS,
    _______, _______, KC_MUTE, KC_VOLD     , KC_VOLU, KC_G   ,                                AML_TO    , KC_BTN1   , SCRL_MO , KC_BTN2 , SCRL_DVI, _______,
    _______, _______, KC_X   , KC_C        , KC_V   , KC_B   , LT(3,KC_LBRC), LT(3,KC_RBRC) , A(KC_RGHT), A(KC_LEFT), KC_BTN3 , KC_NO   , KC_NO   , _______,
    _______, _______, KC_LALT, LT(1,KC_ESC), _______, _______, _______      , _______       , _______   , _______   , _______ , _______ , _______ , _______
  ),

  [3] = LAYOUT_universal(
      KC_GRV ,   KC_1 ,   KC_2 ,   KC_3 ,   KC_4 ,   KC_5 ,                    KC_6 ,   KC_7 ,   KC_8 ,   KC_9 ,   KC_0 , KC_F12 ,
    S(KC_GRV), S(KC_1), S(KC_2), S(KC_3), S(KC_4), S(KC_5),                  S(KC_6), S(KC_7), S(KC_8), S(KC_9), S(KC_0), S(KC_EQL) ,
      KC_GRV ,   KC_1 ,   KC_2 ,   KC_3 ,   KC_4 ,   KC_5 ,                    KC_6 ,   KC_7 ,   KC_8 ,   KC_9 ,   KC_0 , KC_EQL ,
    _______  ,   KC_F1,   KC_F2,   KC_F3,   KC_F4,  KC_F5 , _______, _______,  KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10, KC_MINS ,
    _______  , _______, _______, _______, _______, _______, _______, _______,_______, _______, _______, _______,  KC_F11, S(KC_MINS)
  ),
};
// clang-format on

layer_state_t layer_state_set_user(layer_state_t state) {
    // Auto enable scroll mode when the highest layer is 3
    keyball_set_scroll_mode(get_highest_layer(state) == 3);
    return state;
}

#ifdef OLED_ENABLE

#    include "lib/oledkit/oledkit.h"

void oledkit_render_info_user(void) {
    keyball_oled_render_keyinfo();
    keyball_oled_render_ballinfo();
    keyball_oled_render_layerinfo();
}
#endif
