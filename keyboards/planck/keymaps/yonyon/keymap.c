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
  _LOWER,
  _RAISE,
  _ADJUST,
  _MOV,
  _NUM,
  _EXTRA
};

#include "yonyon-dance.h"

enum planck_keycodes {
  QWERTY = SAFE_RANGE,
  BACKLIT,
  RV_AL,
  RV_AR
};

#define CTL_ESC CTL_T(KC_ESC)

#define LOWER  MO(_LOWER)
#define RAISE  MO(_RAISE)
#define BS_LOW LT(_LOWER, KC_BSPC)
#define ENT_RS LT(_RAISE, KC_ENT)
#define SPCMOV LT(_MOV, KC_SPC)
#define SPCNUM LT(_NUM, KC_SPC)
#define TABEXT LT(_EXTRA, KC_TAB)
#define TABNUM LT(_NUM, KC_TAB)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Qwerty
 * ,-----------------------------------------------------------------------------------.
 * |TabExt|   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  |  Å   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | C-Esc|   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   Ö  |  Ä   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   -  |Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | LCTL | Alt  | GUI  | GUI  |Lower |SpcNum|SpcMov|Raise |DM1Ply|DM2Ply|DM1Rec|DM2Rec|
 * `-----------------------------------------------------------------------------------'
 *  C-Esc - CTRL when held, ESC when tapped
 *  SpaceMove - Space when tapped, MOVE layer when held
 */
[_QWERTY] = LAYOUT_planck_grid(
    TABEXT,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    SE_ARNG,
    TD(QUOT_LAYR), KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    SE_ODIA, SE_ADIA,
    KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    SE_COMM, SE_DOT,  SE_MINS, KC_ENT ,
    KC_LCTL, KC_LALT, KC_LGUI, KC_LGUI, BS_LOW,  SPCNUM,  SPCMOV,  ENT_RS,  DM_PLY1, DM_PLY2, DM_REC1, DM_REC2
),

/* Lower
 * ,-----------------------------------------------------------------------------------.
 * |   @  |   !  |   "  |   #  |   $  |   %  |   &  |   /  |   (  |   )  |   =  |  \   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Del  |   @  |   £  |   €  |   ¤  |      |      |   ?  |   [  |   ]  |   $  |  *   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |   *  |   {  |   }  |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_LOWER] = LAYOUT_planck_grid(
    SE_AT,   SE_EXLM, SE_DQUO, SE_HASH, SE_DLR,  SE_PERC, SE_AMPR, SE_SLSH, SE_LPRN, SE_RPRN, SE_EQL,  SE_BSLS,
    KC_DEL,  SE_AT,   SE_PND,  SE_EURO, SE_CURR, _______, _______, SE_QUES, SE_LBRC, SE_RBRC, SE_DLR,  SE_ASTR,
    _______, _______, _______, _______, _______, _______, _______, SE_ASTR, SE_LCBR, SE_RCBR, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
),

/* Raise
 * ,-----------------------------------------------------------------------------------.
 * |   ^  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | Del  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Del  | PIPE | TILD |   <  |   >  |      |      |   +  |   `  |   å  |   '  |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |   ´  |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_RAISE] = LAYOUT_planck_grid(
    SE_CIRC, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_DEL ,
    KC_DEL,  SE_PIPE, SE_TILD, SE_LABK, SE_RABK, _______, _______, SE_PLUS, SE_GRV,  SE_ARNG, SE_QUOT, XXXXXXX,
    _______, _______, _______, _______, _______, _______, _______, _______, SE_ACUT, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
),

/* Adjust (Lower + Raise)
 * ,-----------------------------------------------------------------------------------.
 * |      |Qwerty| RGB+ | Bri+ |      |      |      | Vol- | Play | Vol+ | Mute |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      | RGB- | Bri- | MOUS1| MOUS2| MOUSL| MOUSD| MOUSU| MOUSR|      |PrtScr|
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      | RGB  |RGBMOD|AudTog|      |      |      | ACC0 | ACC1 | ACC2 |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |EEP-Rs|      |      |      |******|             |******|      |      |      | Reset|
 * `-----------------------------------------------------------------------------------'
 */
[_ADJUST] = LAYOUT_planck_grid(
    _______,  QWERTY, RGB_VAI, KC_BRIU, _______, _______, _______, KC_VOLD, KC_MPLY, KC_VOLU, KC_MUTE, _______,
    _______, _______, RGB_VAD, KC_BRID, KC_BTN1, KC_BTN2, KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R, _______, KC_PSCR,
    _______, RGB_TOG, RGB_MOD, AU_TOG,  _______, _______, _______, KC_ACL0, KC_ACL1, KC_ACL2, _______, _______,
    EEP_RST, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, RESET
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
 * |      |      |C_PGUP| CtrlK|C_PGDN|      |      |   7  |   8  |   9  |   *  | Del  |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |      |      | CMNT | TILDE| Bksp |   4  |   5  |   6  |   +  |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |      |      |      |      |      | Enter|   1  |   2  |   3  |   -  |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      | **** |      |   0  |   ,  |   .  |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_NUM] = LAYOUT_planck_grid(
        XXXXXXX , XXXXXXX , C_PGUP  , CtrlK   , C_PGDN  , XXXXXXX , XXXXXXX , KC_7 , KC_8    , KC_9    , KC_PAST , KC_DEL  ,
        TD(QUOT_LAYR) , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , KC_BSPC , KC_4 , KC_5    , KC_6    , KC_PPLS , XXXXXXX ,
        XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , KC_ENT  , KC_1 , KC_2    , KC_3    , KC_PMNS , XXXXXXX ,
        XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , _______ , XXXXXXX , KC_0 , KC_COMM ,KC_DOT   , XXXXXXX , XXXXXXX
        ),

/* EXTRA
 * ,-----------------------------------------------------------------------------------.
 * | **** |  F1  |  F2  |  F3  |  F4  |  F5  |      |      |      |      |      |      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |  F6  |  F7  |  F8  |  F9  |  F10 |      |RV_AL |RV_AR |      |      |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |      |      |      |  F11 |  F12 |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_EXTRA] = LAYOUT_planck_grid(
        _______ , KC_F1   , KC_F2   , KC_F3   , KC_F4   , KC_F5   , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX ,
        XXXXXXX , KC_F6   , KC_F7   , KC_F8   , KC_F9   , KC_F10  , XXXXXXX , RV_AL   , RV_AR   , XXXXXXX , XXXXXXX , XXXXXXX ,
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
    case RV_AL:
      if (record->event.pressed) {
        SEND_STRING("A" SS_DELAY(500) "L");
      }
      return false;
      break;
    case RV_AR:
      if (record->event.pressed) {
        SEND_STRING("A" SS_DELAY(500) "R");
      }
      return false;
      break;
  }
  return true;
}

// Determine the current tap dance state
td_state_t cur_dance(qk_tap_dance_state_t *state) {
    if (state->count == 1) {
        if (!state->pressed) return TD_SINGLE_TAP;
        else return TD_SINGLE_HOLD;
    } else if (state->count == 2) return TD_DOUBLE_TAP;
    else return TD_UNKNOWN;
}

// Initialize tap structure associated with example tap dance key
static td_tap_t ql_tap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

// Functions that control what our tap dance key does
void ql_finished(qk_tap_dance_state_t *state, void *user_data) {
    ql_tap_state.state = cur_dance(state);
    switch (ql_tap_state.state) {
        case TD_SINGLE_TAP:
            tap_code(KC_QUOT);
            break;
        case TD_SINGLE_HOLD:
            layer_on(_NUM);
            break;
        case TD_DOUBLE_TAP:
            // Check to see if the layer is already set
            if (layer_state_is(_NUM)) {
                // If already set, then switch it off
                layer_off(_NUM);
            } else {
                // If not already set, then switch the layer on
                layer_on(_NUM);
            }
            break;
        default:
            break;
    }
}

void ql_reset(qk_tap_dance_state_t *state, void *user_data) {
    // If the key was held down and now is released then switch off the layer
    if (ql_tap_state.state == TD_SINGLE_HOLD) {
        layer_off(_NUM);
    }
    ql_tap_state.state = TD_NONE;
}

// Associate our tap dance key with its functionality
qk_tap_dance_action_t tap_dance_actions[] = {
    [QUOT_LAYR] = ACTION_TAP_DANCE_FN_ADVANCED_TIME(NULL, ql_finished, ql_reset, 275)
};
