/*
This is the c configuration file for the keymap

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

#pragma once

#ifdef RGBLIGHT_ENABLE
//#    define RGBLIGHT_EFFECT_BREATHING
//#    define RGBLIGHT_EFFECT_RAINBOW_MOOD
//#    define RGBLIGHT_EFFECT_RAINBOW_SWIRL
//#    define RGBLIGHT_EFFECT_SNAKE
//#    define RGBLIGHT_EFFECT_KNIGHT
//#    define RGBLIGHT_EFFECT_CHRISTMAS
//#    define RGBLIGHT_EFFECT_STATIC_GRADIENT
//#    define RGBLIGHT_EFFECT_RGB_TEST
//#    define RGBLIGHT_EFFECT_ALTERNATING
//#    define RGBLIGHT_EFFECT_TWINKLE
#endif

#define TAP_CODE_DELAY 5

#define POINTING_DEVICE_AUTO_MOUSE_ENABLE
#define AUTO_MOUSE_DEFAULT_LAYER 2

// スクロールスナップ無効化
#define KEYBALL_SCROLLSNAP_ENABLE 0

// デフォルトスクロール速度変更
#define KEYBALL_SCROLL_DIV_DEFAULT 5 // スクロール速度 (default: 4)

// OLED自動消灯時間 [ms]
#define OLED_TIMEOUT 20000 // ミリ秒

// // レイヤーロックのタイムアウト
// #define LAYER_LOCK_IDLE_TIMEOUT 30000  // Turn off after 60 seconds.

// shiftのダブルタップで大文字入力
// #define DOUBLE_TAP_SHIFT_TURNS_ON_CAPS_WORD
// 左右shift同時押しで大文字入力
// #define BOTH_SHIFTS_TURNS_ON_CAPS_WORD
