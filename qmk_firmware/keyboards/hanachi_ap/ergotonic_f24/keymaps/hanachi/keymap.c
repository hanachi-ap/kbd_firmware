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
    SWIN(KC_S),        KC_LALT, LT(_L1,KC_SPC),KC_LNG9,KC_LCTL, SFT_T(KC_BSPC), LT(_L2,KC_ENT), MO(_L1), MO(_L3),    KC_ENT
    ),

    [_L1] = LAYOUT(
	KC_GRV,  S(KC_1),S(KC_2),S(KC_3),S(KC_4),S(KC_5),                  S(KC_6),S(KC_7),S(KC_8),S(KC_9), S(KC_0), S(KC_EQL),
	_______,   KC_1,   KC_2,   KC_3,   KC_4,   KC_5,                    KC_6,   KC_7,   KC_8,   KC_9,   KC_0,    S(KC_MINS),
	_______,  KC_LCBR,KC_RCBR,KC_LBRC,KC_RBRC,KC_TILD, _______,  _______,KC_QUOT,KC_DQT,KC_COMM,KC_DOT, KC_SLSH, KC_PIPE,
    _______,                   _______,_______,_______,_______,  _______,_______, _______, _______,                   _______
    ),
    [_L2] = LAYOUT(
	_______,  KC_F1,  KC_F2,  KC_F3,  KC_F4,  KC_F5,                     KC_PGUP, S(KC_LEFT),KC_UP, S(KC_RIGHT),SWIN(KC_S),KC_NO, 
	KC_CAPS,  KC_F6,  KC_F7,  KC_F8,  KC_F9,  KC_F10,                    KC_PGDN, KC_LEFT,  KC_DOWN,KC_RIGHT,   KC_NO,  KC_NO,
	_______,  KC_F11, KC_F12, KC_F13, KC_F14, KC_F15,  _______,  _______,KC_HOME, KC_END,   KC_NO,KC_NO, KC_NO, KC_NO,
    _______,                   _______,_______,KC_F17,KC_F14,  _______,_______, _______, _______,                      _______
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

/* 親指でキーを押さえている間、IMEをONにし、離すと確定&IME OFFとなる 
   使用中のIME側とキー定義を合わせる(google imputと組み合わせるといい感じに動作)
     KC_F14:IME ON, KC_F15:変換,  KC_F16:確定, KC_F17:IME OFF
   Tapしたときの入力コードはお好みで
*/
static bool lang_key_pressed = false;
static bool lang_mode = false;
static uint16_t lang_pressed_time = 0;

bool process_record_user(uint16_t keycode, keyrecord_t* record) {

    switch (keycode)
    {
    case KC_LNG9:
        if (record->event.pressed)
        {
            lang_pressed_time = record->event.time;
            lang_key_pressed = true;
        }
        else
        {
            if (lang_key_pressed && (TIMER_DIFF_16(record->event.time, lang_pressed_time) <= TAP_MOD_DELAY))
            {
                // TAPPING_TERM以下でリリースされたら単発キーとして処理
                tap_code(KC_SPC);
                lang_mode = false;
            }
            else if (lang_mode)
            {
                // IME ON状態ならモードを直接入力に
                tap_code(KC_F15); // 入力中の文字列がある場合は変換
                tap_code(KC_F16); // 変換中の文字列を確定
                tap_code(KC_F17); // IMEをOFF
                lang_mode = false;
            }
            lang_key_pressed = false;
        }
        return false;
        break;
    default:
        // LANGキーが押されている間に他のキーが押されたら
        if (lang_key_pressed) {
            tap_code(KC_F14); // IME ON
            lang_mode = true;
        }
        lang_key_pressed = false;
    }
    return true;
}

#define INTERVAL_SEC  (100)
void prupuru(void) {
    report_mouse_t mouse_report = {0};
    mouse_report.x =   1;
    host_mouse_send(&mouse_report);
    mouse_report.x =  -1 ;
    host_mouse_send(&mouse_report);
}
bool delta = true;
uint16_t last_timer_c;
int interval_sec = 0;
void matrix_scan_user() {
    if (delta) {
        if ( timer_elapsed(last_timer_c) > 1000) {
            interval_sec++;
            last_timer_c = timer_read();
        }
        if (interval_sec  > INTERVAL_SEC) {
            prupuru();
            interval_sec = 0;
        }
    }
}
