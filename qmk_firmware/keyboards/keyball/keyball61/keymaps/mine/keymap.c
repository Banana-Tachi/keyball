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

#include "./custom_oled.h"
#include "./layer_lock.h"

// 自作キーコード
enum custom_keycodes {
    LT_LCTL_SPC = SAFE_RANGE, // Tap/Hold: IME/Layer1 
    LLOCK,
};

static bool layer_1_active = false;
static uint16_t lt_timer;


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (!process_layer_lock(keycode, record, LLOCK)) {
        return false;
    }
    switch (keycode) {
        case LT_LCTL_SPC:
            if (record->event.pressed) {
                // キーを押した時
                if (!is_layer_locked(1)) {  // レイヤー1がロックされていない場合のみ
                    layer_1_active = true;
                    layer_on(1);  // レイヤー1をオン
                }
                lt_timer = timer_read();
                return false;
            } else {
                // キーを離した時
                if (!is_layer_locked(1)) {  // レイヤー1がロックされていない場合のみ
                    layer_1_active = false;
                    layer_off(1); // レイヤー1をオフ
                }
                
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
    KC_LCTL, KC_LWIN, KC_LALT, LT(1,KC_ESC), LT_LCTL_SPC, KC_SPC, MO(2)        , KC_ENT       , KC_BSPC, KC_NO  , KC_NO  , KC_NO  , LT(1,KC_BSLS), KC_RCTL
  ),

  [1] = LAYOUT_universal(
    _______, KC_F1  , KC_F2, KC_F3 , KC_F4  , KC_F5  ,                   KC_F6  , KC_F7  ,  KC_F8   ,  KC_F9   , KC_F10 , KC_F11 ,
    _______, KC_PSLS, KC_7 , KC_8  , KC_9   , KC_PPLS,                   KC_LBRC, KC_RBRC,S(KC_LBRC),S(KC_RBRC), KC_PSCR, KC_F12 ,
    _______, _______, KC_4 , KC_5  , KC_6   , KC_PMNS,                   KC_LEFT, KC_DOWN,  KC_UP   ,  KC_RGHT , _______, _______,
    _______, _______, KC_1 , KC_2  , KC_3   , KC_PENT, KC_PAST, KC_DEL , S(KC_9), S(KC_0),  _______ , _______  , _______, _______,
    LLOCK  , _______, KC_0 , KC_DOT, _______, _______, _______, _______, _______, _______,  _______ , _______  , _______, _______
  ),

  [2] = LAYOUT_universal(
    _______, KC_1   , KC_2   , KC_3        , KC_4   , KC_5   ,                                KC_6      , KC_7      , KC_8    , KC_9    , KC_0    , KC_EQL ,
    _______, KC_Q   , KC_W   , KC_BRID     , KC_BRIU, KC_T   ,                                CPI_D1K   , CPI_D100  , CPI_I100, CPI_I1K , SCRL_DVD, KC_MINS,
    _______, _______, KC_MUTE, KC_VOLD     , KC_VOLU, KC_G   ,                                AML_TO    , KC_BTN1   , SCRL_MO , KC_BTN2 , SCRL_DVI, _______,
    _______, _______, KC_X   , KC_C        , KC_V   , KC_B   , LT(3,KC_LBRC), LT(3,KC_RBRC) , A(KC_RGHT), A(KC_LEFT), KC_BTN3 , KC_NO   , KC_NO   , _______,
    LLOCK  , _______, KC_LALT, LT(1,KC_ESC), _______, _______, _______      , _______       , _______   , _______   , _______ , _______ , _______ , _______
  ),

  [3] = LAYOUT_universal(
      KC_GRV ,   KC_1 ,   KC_2 ,   KC_3 ,   KC_4 ,   KC_5 ,                    KC_6 ,   KC_7 ,   KC_8 ,   KC_9 ,   KC_0 , KC_F12 ,
    S(KC_GRV), S(KC_1), S(KC_2), S(KC_3), S(KC_4), S(KC_5),                  S(KC_6), S(KC_7), S(KC_8), S(KC_9), S(KC_0), S(KC_EQL) ,
      KC_GRV ,   KC_1 ,   KC_2 ,   KC_3 ,   KC_4 ,   KC_5 ,                    KC_6 ,   KC_7 ,   KC_8 ,   KC_9 ,   KC_0 , KC_EQL ,
    _______  ,   KC_F1,   KC_F2,   KC_F3,   KC_F4,  KC_F5 , _______, _______,  KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10, KC_MINS ,
    LLOCK    , _______, _______, _______, _______, _______, _______, _______,_______, _______, _______, _______,  KC_F11, S(KC_MINS)
  ),
};
// clang-format on

layer_state_t layer_state_set_user(layer_state_t state) {
    // Auto enable scroll mode when the highest layer is 3
    keyball_set_scroll_mode(get_highest_layer(state) == 3);
    return state;
}


//
// oled系
//
#ifdef OLED_ENABLE

#    include "lib/oledkit/oledkit.h"

// 向き変更
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    if (is_keyboard_master()) {
        return OLED_ROTATION_270;
    }
    return rotation;
}

static const char LFSTR_ON[] PROGMEM = "\xB2\xB3";
static const char LFSTR_OFF[] PROGMEM = "\xB4\xB5";

static char to_1x(uint8_t x) {
    x &= 0x0f;
    return x < 10 ? x + '0' : x + 'a' - 10;
}
static const char *format_num(int16_t num, uint8_t width) {
    static char buf[5];
    char *p = &buf[sizeof(buf) - 1];
    *p = '\0';
    
    uint16_t n = num < 0 ? -num : num;
    do {
        *--p = (n % 10) + '0';
        n /= 10;
        width--;
    } while (n > 0 && p > buf);
    
    if (num < 0 && p > buf) {
        *--p = '-';
        width--;
    }
    
    while (width > 0 && p > buf) {
        *--p = ' ';
        width--;
    }
    
    return p;
}

void my_oled_keyinfo(void) {
    // "Key" Label
    oled_write_P(PSTR("Key\n "), false);
    // Row and column
    oled_write_char('\xB8', false);
    oled_write_char(to_1x(keyball.last_pos.row), false);
    oled_write_char('\xB9', false);
    oled_write_char(to_1x(keyball.last_pos.col), false);
    // Keycode
    oled_write_P(PSTR(" \xBA\xBB"), false);
    oled_write_char(to_1x(keyball.last_kc >> 4), false);
    oled_write_char(to_1x(keyball.last_kc), false);
    // Pressing keys
    oled_write_char(' ', false);
    oled_write_char(keyball.pressing_keys[0], false);
    oled_write_char(keyball.pressing_keys[1], false);
    oled_write_char(keyball.pressing_keys[2], false);
    oled_write_char(keyball.pressing_keys[3], false);
}

void my_oled_ballinfo(void) {
    // 1st line, "Ball" label, mouse x, y, h, and v.
    oled_write_P(PSTR("Ball\n "), false);
    if(keyball.scroll_mode){
        oled_write(format_num(keyball.last_mouse.h, 4), false);
        oled_write_char(' ', false);
        oled_write(format_num(keyball.last_mouse.v, 4), false);
    }else{
        oled_write(format_num(keyball.last_mouse.x, 4), false);
        oled_write_char(' ', false);
        oled_write(format_num(keyball.last_mouse.y, 4), false);
    }

    // 2nd line, empty label and CPI
    oled_write_char(' ', false);
    oled_write(format_num(keyball_get_cpi(),3) + 1, false);
    oled_write_P(PSTR("00"), false);

    // indicate scroll divider:
    oled_write_P(PSTR(" \xC0\xC1 "), false);
    oled_write_char('0' + keyball_get_scroll_div(), false);
    oled_write_P(PSTR(" \xBE\xBF"), false);
    // indicate scroll mode: on/off
    oled_write_P(keyball.scroll_mode ? LFSTR_ON : LFSTR_OFF, false);
    // pointing device auto mouse
    oled_write_P(PSTR(" \xC2\xC3"), false);
    oled_write_P(get_auto_mouse_enable() ? LFSTR_ON : LFSTR_OFF, false);
}

void my_oled_layerinfo(void) {
    const char *img;
    if      (is_caps_word_on())  img = img_S;
    else if (is_layer_locked(0)) img = img_0_box;
    else if (is_layer_locked(1)) img = img_1_box;
    else if (is_layer_locked(2)) img = img_2_box;
    else if (is_layer_locked(3)) img = img_3_box;
    else {
        static const char *const layer_imgs[] = {img_0, img_1, img_2, img_3};
        img = layer_imgs[get_highest_layer(layer_state)];
    }
    oled_write_raw_P(img, sizeof(img_0)); // 全ての画像は同じサイズと仮定
}

void oledkit_render_info_user(void) {
    // keyball_oled_render_keyinfo();
    // keyball_oled_render_ballinfo();
    // keyball_oled_render_layerinfo();
    my_oled_keyinfo();
    my_oled_ballinfo();
    my_oled_layerinfo();
}
#endif
