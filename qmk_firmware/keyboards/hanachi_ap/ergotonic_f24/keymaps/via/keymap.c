/* Copyright 2022 hanachi-ap
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include QMK_KEYBOARD_H
#include "quantum.h"

// Defines names for use in layer keycodes and the keymap
enum layer_names {
    _BASE,
    _L1,
    _L2,
    _L3,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT( 
	KC_ESC,	   KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,                      KC_Y,   KC_U,   KC_I,   KC_O,   KC_P,     KC_EQL,
	KC_TAB,    KC_A,   KC_S,   KC_D,   KC_F,   KC_G,                      KC_H,   KC_J,   KC_K,   KC_L,   KC_SCLN,  KC_MINS,
	KC_LSFT,   KC_Z,   KC_X,   KC_C,   KC_V,    KC_B,  KC_DEL,    KC_LGUI,KC_N,   KC_M,   KC_COMM,KC_DOT, KC_SLSH,  KC_BSLS,
    SWIN(KC_S),        KC_LALT, LT(_L1,KC_SPC),KC_SPC,KC_LCTL, SFT_T(KC_BSPC), LT(_L2,KC_ENT), MO(_L1), MO(_L3),    KC_ENT
    ),

    [_L1] = LAYOUT(
	KC_GRV,  S(KC_1),S(KC_2),S(KC_3),S(KC_4),S(KC_5),                  S(KC_6),S(KC_7),S(KC_8),S(KC_9), S(KC_0), S(KC_EQL),
	_______,   KC_1,   KC_2,   KC_3,   KC_4,   KC_5,                    KC_6,   KC_7,   KC_8,   KC_9,   KC_0,    S(KC_MINS),
	_______,  KC_LCBR,KC_RCBR,KC_LBRC,KC_RBRC,KC_TILD, _______,  _______,KC_LPRN,KC_RPRN,KC_COMM,KC_DOT, KC_SLSH, KC_PIPE,
    _______,                   _______,_______,_______,_______,  _______,_______, _______, _______,                 _______
    ),
    [_L2] = LAYOUT(
	_______,  KC_F1,  KC_F2,  KC_F3,  KC_F4,  KC_F5,                     KC_PGUP, KC_NO,    KC_UP,  KC_NO,   KC_NO, KC_NO, 
	_______,  KC_F6,  KC_F7,  KC_F8,  KC_F9,  KC_F10,                    KC_PGDN, KC_LEFT,  KC_DOWN,KC_RIGHT,KC_NO, KC_NO,
	_______,  KC_F11, KC_F12, KC_F13, KC_F14, KC_F15,  _______,  _______,KC_HOME, KC_END,   KC_NO,  KC_NO,   KC_NO, KC_NO,
    _______,                   _______,_______,_______,_______,  _______,_______, _______, _______,                 _______
    ),

    [_L3] = LAYOUT(
	XXXXXXX,   UG_TOGG, UG_VALU,UG_VALD,AS_ON,AS_OFF,                    XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,
	XXXXXXX,   UG_NEXT,UG_SATU,UG_SATD,AS_UP,AS_DOWN,                    XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,
	XXXXXXX,   UG_PREV,UG_HUEU,UG_HUED,XXXXXXX,AS_RPT,XXXXXXX,  XXXXXXX, XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,
    UG_TOGG,                   _______,_______,_______,_______,  _______,_______, _______, _______,              _______
    )    
};

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [_BASE] ={ ENCODER_CCW_CW(KC_WH_L, KC_WH_R), ENCODER_CCW_CW(KC_C, KC_D), ENCODER_CCW_CW(KC_E, KC_F), ENCODER_CCW_CW(KC_G, KC_H) },
    [_L1] =  { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_C, KC_D), ENCODER_CCW_CW(KC_E, KC_F), ENCODER_CCW_CW(KC_G, KC_H) },
    [_L2] =  { ENCODER_CCW_CW(KC_WH_D, KC_WH_U), ENCODER_CCW_CW(KC_C, KC_D), ENCODER_CCW_CW(KC_E, KC_F), ENCODER_CCW_CW(KC_G, KC_H) },
    [_L3] =  { ENCODER_CCW_CW(UG_VALD, UG_VALU), ENCODER_CCW_CW(KC_C, KC_D), ENCODER_CCW_CW(KC_E, KC_F), ENCODER_CCW_CW(KC_G, KC_H) },
};
#endif
