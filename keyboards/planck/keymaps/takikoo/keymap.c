/* Copyright 2015-2021 Jack Humbert
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
#include "keymap_swedish.h"
#include "sendstring_swedish.h"

enum planck_layers {
  _QWERTY,
  _NEXT,
  _GAME,
  _LOWER,
  _RAISE,
  _GAMELOW,
  _ADJUST,
  _MOV,
  _NUM,
  _EXTRA
};

enum planck_keycodes {
  QWERTY = SAFE_RANGE,
  NEXT,
  GAME,
  TD,
  VILL,
  TILDE,
  CMNT,
  BACKLIT
};

#define CTL_ESC CTL_T(KC_ESC)

#define LOWER  MO(_LOWER)
#define RAISE  MO(_RAISE)
#define BS_LOW LT(_LOWER, KC_BSPC)
#define ENT_RS LT(_RAISE, KC_ENT)
#define SPCMOV LT(_MOV, KC_SPC)
#define SPCNUM LT(_NUM, KC_SPC)
#define TABEXT LT(_EXTRA, KC_TAB)
#define ZCTRL  LCTL_T(KC_Z)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Qwerty
 * ,-----------------------------------------------------------------------------------.
 * |TabExt|   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  | Bksp |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | C-Esc|   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   Ö  |  Ä   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Shift|  *Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   -  |Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Hyper| Meh  | Alt  | GUI  |Lower |SpcNum|SpcMov|Raise | Left | Down |  Up  |Right |
 * `-----------------------------------------------------------------------------------'
 *  TabNum - Tab when tapped, NUM layer when held
 *  C-Esc - CTRL when held, ESC when tapped
 *  SpaceMove - Space when tapped, MOVE layer when held
 *  *Z - Z when tapped, Ctrl when held
 */
[_QWERTY] = LAYOUT_planck_grid(
    TABEXT,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
    CTL_ESC, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    SE_ODIA, SE_ADIA,
    KC_LSFT, ZCTRL,   KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    SE_COMM, SE_DOT,  SE_MINS, KC_ENT ,
    KC_HYPR, KC_MEH, KC_LALT, KC_LGUI, BS_LOW,   SPCNUM,  SPCMOV,  ENT_RS,  KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT
),

/* Next (Trying new layouts)
 * ,-----------------------------------------------------------------------------------.
 * |TabNum|   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  |   Å  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | C-Esc|   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   Ö  |   Ä  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   -  |Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |Leader| Meh  | Alt  | GUI  |Lower |  SpaceMove  |Raise | Left | Down |  Up  |Right |
 * `-----------------------------------------------------------------------------------'
 */

[_NEXT] = LAYOUT_planck_grid(
    TABEXT,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    SE_ARNG,
    CTL_ESC, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    SE_ODIA, SE_ADIA,
    KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    SE_COMM, SE_DOT,  SE_MINS, KC_ENT ,
    KC_LEAD, KC_MEH,  KC_LALT, KC_LGUI, BS_LOW,  SPCNUM,  SPCMOV,  ENT_RS,  KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT
),

#define GLOW   MO(_GAMELOW)
#define SpLow  LM(_GAMELOW, MOD_LCTL | KC_SPC)

/* GAME
 * ,-----------------------------------------------------------------------------------.
 * |   1  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  | Bksp |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | C-Esc|   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   Ö  |  Ä   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   -  |Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Alt  |   4  |   3  |   2  |G-Low |    Space    |QWERTY| Left | Down |  Up  |Right |
 * `-----------------------------------------------------------------------------------'
 *  C-Esc - CTRL when held, ESC when tapped
 *  Lower and Raise are flipped
 */
[_GAME] = LAYOUT_planck_grid(
    KC_1,     KC_Q,  KC_W,  KC_E,  KC_R,   KC_T,    KC_Y,    KC_U,   KC_I,     KC_O,     KC_P,     KC_BSPC,
    CTL_ESC,  KC_A,  KC_S,  KC_D,  KC_F,   KC_G,    KC_H,    KC_J,   KC_K,     KC_L,     SE_ODIA,  SE_ADIA,
    KC_LSFT,  KC_Z,  KC_X,  KC_C,  KC_V,   KC_B,    KC_N,    KC_M,   SE_COMM,  SE_DOT,   SE_MINS,  KC_ENT ,
    KC_LALT,  KC_4,  KC_3,  KC_2,  GLOW,   KC_SPC,  KC_SPC,   QWERTY,  KC_LEFT,  KC_DOWN,  KC_UP,    KC_RGHT
),

/* Lower
 * ,-----------------------------------------------------------------------------------.
 * |   @  |   !  |   "  |   #  |   $  |   %  |   &  |   /  |   (  |   )  |   =  |  \   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Del  |      |   £  |   €  |   ¤  |      |      |   ?  |   [  |   ]  |   $  |  *   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |   *  |   {  |   }  |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_LOWER] = LAYOUT_planck_grid(
    SE_AT,   SE_EXLM, SE_DQUO, SE_HASH, SE_DLR,  SE_PERC, SE_AMPR, SE_SLSH, SE_LPRN, SE_RPRN, SE_EQL,  SE_BSLS,
    KC_DEL,  _______, SE_PND,  SE_EURO, SE_CURR, _______, _______, SE_QUES, SE_LBRC, SE_RBRC, SE_DLR,  SE_ASTR,
    _______, _______, _______, _______, _______, _______, _______, SE_ASTR, SE_LCBR, SE_RCBR, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
),

/* Raise
 * ,-----------------------------------------------------------------------------------.
 * |   ^  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | Del  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Del  | PIPE | TILD |   <  |   >  |      |      |   +  |   `  |   å  |      |  '   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_RAISE] = LAYOUT_planck_grid(
    SE_CIRC, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_DEL ,
    KC_DEL,  SE_PIPE, SE_TILD, SE_LABK, SE_RABK, _______, _______, SE_PLUS, SE_GRV,  SE_ARNG, _______, SE_QUOT,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
),

/* Lower - Game
 * ,-----------------------------------------------------------------------------------.
 * |      |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      | VILL |      |      |  DEL |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_GAMELOW] = LAYOUT_planck_grid(
    XXXXXXX, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    XXXXXXX,
    _______, VILL,    XXXXXXX, XXXXXXX, KC_DEL,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
),

/* Adjust (Lower + Raise)
 * ,-----------------------------------------------------------------------------------.
 * | Reset|Qwerty| RGB+ | Bri+ |      |      |      | Vol- | Play | Vol+ | Mute | GAME |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      | NEXT | RGB- | Bri- | MOUS1| MOUS2| MOUSL| MOUSD| MOUSU| MOUSR|      |PrtScr|
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      | RGB  |RGBMOD|AudTog|      |      |      | ACC0 | ACC1 | ACC2 |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |EEP-Rs|      |      |      |******|             |******|      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_ADJUST] = LAYOUT_planck_grid(
    RESET,   QWERTY,  RGB_VAI, KC_BRIU, _______, _______, _______, KC_VOLD, KC_MPLY, KC_VOLU, KC_MUTE, GAME,
    _______, NEXT,    RGB_VAD, KC_BRID, KC_BTN1, KC_BTN2, KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R, _______, KC_PSCR,
    _______, RGB_TOG, RGB_MOD, AU_TOG,  _______, _______, _______, KC_ACL0, KC_ACL1, KC_ACL2, _______, _______,
    EEP_RST, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
),

#define C_PGUP C(KC_PGUP)
#define C_PGDN C(KC_PGDN)
#define COMNT C(SE_QUOT)

/* MOV
 * ,-----------------------------------------------------------------------------------.
 * |      |      |      | Alt  |      | PgUp | CIns |C_PGUP|      |C_PGDN| SIns |      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Bksp | Home | End  | Shift| Ctrl |PgDown| Left | Down |  Up  | Right| Del  |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |      |      | COMNT|      | CAPS |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |******| Enter|      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 *
 * - Y outputs Control + Insert
 * - P outputs Shift + Insert
 * - U outputs Control + PageUp
 * - P outputs Control + PageDown
 * - COMNT shortcut to comment code
 */
[_MOV] = LAYOUT_planck_grid(
        XXXXXXX , XXXXXXX , XXXXXXX , KC_LALT , XXXXXXX , KC_PGUP , C(KC_INS) , C_PGUP  , XXXXXXX , C_PGDN   , S(KC_INS) , XXXXXXX,
        KC_BSPC , KC_HOME , KC_END  , KC_LSFT , KC_LCTL , KC_PGDN , KC_LEFT   , KC_DOWN , KC_UP   , KC_RIGHT , KC_DEL    , XXXXXXX,
        _______ , XXXXXXX , XXXXXXX , COMNT   , XXXXXXX , KC_CAPS , XXXXXXX   , XXXXXXX , XXXXXXX , XXXXXXX  , XXXXXXX   , _______,
        _______ , _______ , _______ , _______ , XXXXXXX , XXXXXXX , _______   , KC_ENT  , _______ , _______  , _______   , _______
        ),

#define CtrlK C(KC_K)
/* NUM
 * ,-----------------------------------------------------------------------------------.
 * |      |      |C_PGUP| CtrlK|C_PGDN|  TD  |      |   7  |   8  |   9  |   *  | Del  |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |      |      | CMNT | TILDE| Bksp |   4  |   5  |   6  |   +  |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |      |      |      |      |      | Enter|   1  |   2  |   3  |   -  |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      | **** |      |   0  |   ,  |   .  |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_NUM] = LAYOUT_planck_grid(
        XXXXXXX , XXXXXXX , C_PGUP  , CtrlK   , C_PGDN  , TD      , XXXXXXX , KC_7 , KC_8    , KC_9    , KC_PAST , KC_DEL  ,
        XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , CMNT    , TILDE   , KC_BSPC , KC_4 , KC_5    , KC_6    , KC_PPLS , XXXXXXX ,
        _______ , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , KC_ENT  , KC_1 , KC_2    , KC_3    , KC_PMNS , XXXXXXX ,
        XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , _______ , XXXXXXX , KC_0 , KC_COMM ,KC_DOT   , XXXXXXX , XXXXXXX
        ),

/* EXTRA
 * ,-----------------------------------------------------------------------------------.
 * | **** |  F1  |  F2  |  F3  |  F4  |  F5  |      |      |      |      |      |      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |  F6  |  F7  |  F8  |  F9  |  F10 |      |      |      |      |      |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |      |      |      |  F11 |  F12 |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_EXTRA] = LAYOUT_planck_grid(
        _______ , KC_F1   , KC_F2   , KC_F3   , KC_F4   , KC_F5   , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX ,
        XXXXXXX , KC_F6   , KC_F7   , KC_F8   , KC_F9   , KC_F10  , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX ,
        XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , KC_F11  , KC_F12  , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX ,
        XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX
        ),

};

layer_state_t layer_state_set_user(layer_state_t state) {
  return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        print("mode just switched to qwerty and this is a huge string\n");
        set_single_persistent_default_layer(_QWERTY);
      }
      return false;
      break;
    case NEXT:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_NEXT);
      }
      return false;
      break;
    case GAME:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_GAME);
      }
      return false;
      break;
    case TD:
      if (record->event.pressed) {
        SEND_STRING("td[]");
        tap_code(KC_LEFT);
      }
      return false;
      break;
    case VILL:
      if (record->event.pressed) {
        SEND_STRING(SS_LCTL("a") SS_DELAY(100) SS_LSFT("q"));
      }
      return false;
      break;
    case TILDE:
      if (record->event.pressed) {
        SEND_STRING("~");
        tap_code(KC_SPC);
      }
      return false;
      break;
    case CMNT:
      if (record->event.pressed) {
        SEND_STRING("``````");
      }
      return false;
      break;
    case BACKLIT:
      if (record->event.pressed) {
        register_code(KC_RSFT);
        #ifdef BACKLIGHT_ENABLE
          backlight_step();
        #endif
        #ifdef KEYBOARD_planck_rev5
          writePinLow(E6);
        #endif
      } else {
        unregister_code(KC_RSFT);
        #ifdef KEYBOARD_planck_rev5
          writePinHigh(E6);
        #endif
      }
      return false;
      break;
  }
  return true;
}
 
LEADER_EXTERNS();

void matrix_scan_user(void) {
    LEADER_DICTIONARY() {
        leading = false;
        leader_end();

        SEQ_ONE_KEY(KC_T) {
          SEND_STRING("td[]");
          tap_code(KC_LEFT);
        }

        SEQ_TWO_KEYS(KC_G, KC_D) {
            SEND_STRING("git diff");
            tap_code(KC_ENT);
        }

        SEQ_TWO_KEYS(KC_G, KC_C) {
            SEND_STRING("git commit ");
        }

        SEQ_TWO_KEYS(KC_G, KC_S) {
            SEND_STRING("git status");
            tap_code(KC_ENT);
        }

        SEQ_TWO_KEYS(KC_G, KC_P) {
            SEND_STRING("git push");
        }

        SEQ_THREE_KEYS(KC_G, KC_F, KC_P) {
            SEND_STRING("git push --force-with-lease");
        }

        // Caps-lock
        SEQ_TWO_KEYS(KC_TAB, KC_TAB) {
            tap_code16(KC_CAPS);
        }
    }
}
