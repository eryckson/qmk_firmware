/* Copyright 2019
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

// begin encoder handler: https://www.reddit.com/r/olkb/comments/9jzbg1/help_with_rotary_encoder_code/e8elobo/

// wait DELAY ms before unregistering media keys
#define MEDIA_KEY_DELAY 15

// ref:
void encoder_update_user(uint8_t index, bool clockwise) {
  uint16_t held_keycode_timer = timer_read();

  switch(biton32(layer_state)){
    case 2:
      if (clockwise) {
        register_code(KC_MNXT);
        while (timer_elapsed(held_keycode_timer) < MEDIA_KEY_DELAY) {
          // no-op
        }
        unregister_code(KC_MNXT);
      } else {
        register_code(KC_MPRV);
        while (timer_elapsed(held_keycode_timer) < MEDIA_KEY_DELAY) {
          // no-op
        }
        unregister_code(KC_MPRV);
      }
      break;
    case 1:
      if (clockwise) {
        tap_code(KC_WH_D);
      } else {
        tap_code(KC_WH_U);
      }
      break;
    default:
      if (clockwise) {
        register_code(KC_VOLU);
        while (timer_elapsed(held_keycode_timer) < MEDIA_KEY_DELAY) {
          // no-op
        }
        unregister_code(KC_VOLU);
      } else {
        register_code(KC_VOLD);
        while (timer_elapsed(held_keycode_timer) < MEDIA_KEY_DELAY) {
          // no-op
        }
        unregister_code(KC_VOLD);
      }
      break;
  }
}

// end encoder handler

enum layers {
  _QWERTY = 0,
  _LOWER,
  _RAISE,
  _ADJUST,
};

#define LOWER  MO(_LOWER)
#define RAISE  MO(_RAISE)
#define ADJUST MO(_ADJUST)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Qwerty
 * ,------------------------------------------------------------------------------------.
 * | Esc   |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  | Bksp |
 * |-------+------+------+------+------+-------------+------+------+------+------+------|
 * | Tab   |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  |  "   |
 * |-------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift |   Z  |   X  |  C   |   V  |   B  |   N  |   M  |   ,  |   .  |   /  |Enter |
 * |-------+------+------+------+------+------+------+------+------+------+------+------|
 * |  Play | Ctrl | GUI  | Alt  |Lower | Space| Space|Raise | Left | Down |  Up  |Right |
 * `-----------------------------------------------------------------------------------'
 */
[_QWERTY] = LAYOUT_ortho_4x12( \
  KC_ESC,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC, \
  KC_TAB,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, \
  KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_ENT , \
  KC_MPLY, KC_LCTL, KC_LGUI, KC_LALT, LOWER,   KC_SPC,  KC_SPC,  RAISE,   KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT \
),

/* Lower
 * ,-----------------------------------------------------------------------------------.
 * |   ~  |   !  |   @  |   #  |   $  |   %  |   ^  |   &  |   *  |   (  |   )  | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Del  | All  | Save |      | Find |      |      |   _  |   +  |  {   |   }  |  |   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      | Undo | Cut  | Copy |Paste |      |      |      |      |      |      |Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Mute |      |      |      |      |             |      | Home | PgDn | PgUp | End  |
 * `-----------------------------------------------------------------------------------'
 */
[_LOWER] = LAYOUT_ortho_4x12( \
  KC_TILD, KC_EXLM,         KC_AT,    KC_HASH, KC_DLR,     KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_BSPC, \
  KC_DEL,  LCTL(KC_A), LCTL(KC_S),    _______, LCTL(KC_F), _______, _______, KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_PIPE, \
  _______, LCTL(KC_Z), LCTL(KC_X), LCTL(KC_C), LCTL(KC_V), _______, _______, _______, _______, _______, _______, _______, \
  KC_MUTE,    _______,    _______,    _______,    _______, _______, _______, _______, KC_HOME, KC_PGUP, KC_PGDOWN, KC_END \
),

/* Raise
 * ,-----------------------------------------------------------------------------------.
 * |   `  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Caps |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |   -  |   =  |   [  |   ]  |  \   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |      |      |      |      |Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Mute |      |      |      |      |             |      | Prev | Vol- | Vol+ | Next |
 * `-----------------------------------------------------------------------------------'
 */
[_RAISE] = LAYOUT_ortho_4x12( \
  KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC, \
  KC_CAPS, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, KC_BSLS, \
  _______, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  _______, _______, _______, _______, _______, \
  KC_MUTE, _______, _______, _______, _______, _______, _______, _______, KC_MPRV, KC_VOLD, KC_VOLU, KC_MNXT \
),

/* Adjust (Lower + Raise)
 * ,-----------------------------------------------------------------------------------.
 * |      | Reset|      |      |      |      |      |      |      |      |      |  Del |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_ADJUST] =  LAYOUT_ortho_4x12( \
  _______, RESET,   _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_DEL, \
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,\
  _______, _______, RGB_TOG, RGB_MOD, _______, _______, _______, _______, _______, _______, _______, _______,\
  _______, BL_TOGG, BL_INC,  BL_DEC , _______, _______, _______, _______, _______, _______, _______, _______ \
)
};

layer_state_t layer_state_set_user(layer_state_t state) {
  return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}
