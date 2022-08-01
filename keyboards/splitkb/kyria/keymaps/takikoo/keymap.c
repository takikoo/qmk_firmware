/* Copyright 2019 Thomas Baart <thomas@splitkb.com>
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


uint16_t copy_paste_timer;

enum layers {
    _QWERTY = 0,
    _GAME,
    _COLEMAK_DH,
    _LOWER,
    _RAISE,
    _NAV,
    _FUNCTION,
    _NUM,
    _GAMELOW,
    _ADJUST,
};

enum custom_keycodes {
    KC_CCCV = SAFE_RANGE,
    TD,
    VILL,
    TILDE,
    CMNT,
    MK_BRC,
    MK_SQT,
    MK_CBR,
    MK_PRN,
    MK_COL,
    UC_TAB,
    UC_STAB,
};

enum combos {
  AB_ESC,
  DTC_COL,
  JK_BRC,
  KL_SQT,
  IO_PRN,
  UI_CBR,
  QW_SFT,
};

const uint16_t PROGMEM ab_combo[] = {KC_A, KC_B, COMBO_END};
const uint16_t PROGMEM dtc_combo[] = {SE_DOT, SE_COMM, COMBO_END};
const uint16_t PROGMEM jk_combo[] = {KC_J, KC_K, COMBO_END};
const uint16_t PROGMEM kl_combo[] = {KC_K, KC_L, COMBO_END};
const uint16_t PROGMEM io_combo[] = {KC_I, KC_O, COMBO_END};
const uint16_t PROGMEM ui_combo[] = {KC_U, KC_I, COMBO_END};
const uint16_t PROGMEM qw_combo[] = {KC_Q, KC_W, COMBO_END};

combo_t key_combos[COMBO_COUNT] = {
  [AB_ESC]  = COMBO(ab_combo, KC_ESC),
  [DTC_COL] = COMBO(dtc_combo, SE_COLN),
  [JK_BRC]  = COMBO(jk_combo, MK_BRC),
  [KL_SQT]  = COMBO(kl_combo, MK_SQT),
  [IO_PRN]  = COMBO(io_combo, MK_PRN),
  [UI_CBR]  = COMBO(ui_combo, MK_CBR),
  [QW_SFT]  = COMBO(qw_combo, KC_LSFT)
};

// Aliases for readability
#define QWERTY   DF(_QWERTY)
#define COLEMAK  DF(_COLEMAK_DH)
#define GAME     DF(_GAME)

#define BS_LOW   LT(_LOWER, KC_BSPC)
#define ENT_RS   LT(_RAISE, KC_ENT)
#define NAV      MO(_NAV)
#define SPCNAV   LT(_NAV, KC_SPC)
#define TABNUM   LT(_NUM, KC_TAB)
#define FKEYS    MO(_FUNCTION)
#define ADJUST   MO(_ADJUST)
#define GLow     MO(_GAMELOW)
#define SpLow    LM(_GAMELOW, MOD_LCTL | KC_SPC)

#define CTL_ESC  MT(MOD_LCTL, KC_ESC)
#define CTL_QUOT MT(MOD_RCTL, KC_QUOTE)
#define ALT_ENT  MT(MOD_LALT, KC_ENT)

#define C_PGUP C(KC_PGUP)
#define C_PGDN C(KC_PGDN)
#define YANK   C(KC_INS)
#define PASTE  S(KC_INS)
#define COMNT  C(SE_QUOT)
#define DUPLIC C(S(KC_D))
#define CtrlK  C(KC_K)
#define SCtrlK S(C(KC_K))

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/*
 * Base Layer: QWERTY
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |  Tab   |   Q  |   W  |   E  |   R  |   T  |                              |   Y  |   U  |   I  |   O  |   P  |  Bksp  |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |Ctrl/Esc|   A  |   S  |   D  |   F  |   G  |                              |   H  |   J  |   K  |   L  |   Ö  |   Ä    |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * | LShift |   Z  |   X  |   C  |   V  |   B  | GAME | CCCV |  |F-keys| LEAD |   N  |   M  |   ,  |   .  |   -  |  Enter |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |Adjust| LAlt | Bksp/|NumSpc| LGUI |  | MEH  |SpcNav|Enter/| RGUI | Menu |
 *                        |      |      | Lower|      |      |  |      |      | Raise|      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_QWERTY] = LAYOUT(
     KC_TAB  , KC_Q ,  KC_W   ,  KC_E  ,   KC_R ,   KC_T ,                                        KC_Y,   KC_U ,   KC_I ,   KC_O  , KC_P   , KC_BSPC,
     CTL_ESC , KC_A ,  KC_S   ,  KC_D  ,   KC_F ,   KC_G ,                                        KC_H,   KC_J ,   KC_K ,   KC_L  , SE_ODIA, SE_ADIA,
     KC_LSFT , KC_Z ,  KC_X   ,  KC_C  ,   KC_V ,   KC_B , GAME   ,KC_CCCV,     FKEYS  , KC_LEAD, KC_N,   KC_M ,   SE_COMM, SE_DOT, SE_MINS, KC_ENT,
                                ADJUST , KC_LALT,  BS_LOW, TABNUM ,KC_LGUI,     KC_MEH , SPCNAV , ENT_RS, KC_RGUI, KC_MUTE
    ),

/*
 * Base Layer: Colemak DH
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |  Tab   |   Q  |   W  |   F  |   P  |   B  |                              |   J  |   L  |   U  |   Y  | ;  : |  Bksp  |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |Ctrl/Esc|   A  |   R  |   S  |   T  |   G  |                              |   M  |   N  |   E  |   I  |   O  |Ctrl/' "|
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * | LShift |   Z  |   X  |   C  |   D  |   V  |QWERTY|      |  |F-keys| LEAD |   K  |   H  | ,  < | . >  | /  ? | RShift |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |Adjust| LGUI | LAlt/| Space| Nav  |  | Sym  | Space| AltGr| RGUI | Menu |
 *                        |      |      | Enter|      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_COLEMAK_DH] = LAYOUT(
     KC_TAB  , KC_Q ,  KC_W   ,  KC_F  ,   KC_P ,   KC_B ,                                        KC_J,   KC_L ,  KC_U ,   KC_Y ,SE_ODIA, KC_BSPC,
     CTL_ESC , KC_A ,  KC_R   ,  KC_S  ,   KC_T ,   KC_G ,                                        KC_M,   KC_N ,  KC_E ,   KC_I ,  KC_O , CTL_QUOT,
     KC_LSFT , KC_Z ,  KC_X   ,  KC_C  ,   KC_D ,   KC_V , QWERTY ,XXXXXXX,     FKEYS  , KC_LEAD,  KC_K,   KC_H ,SE_COMM, SE_DOT ,SE_SLSH, KC_RSFT,
                                ADJUST , KC_LALT,  BS_LOW, TABNUM ,KC_LGUI,     KC_MEH , SPCNAV , ENT_RS, KC_RGUI, KC_MUTE
    ),

/*
 * Base Layer: GAME
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |  Tab   |   Q  |   W  |   E  |   R  |   T  |                              |   Y  |   U  |   I  |   O  |   P  |  Bksp  |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |Ctrl/Esc|   A  |   S  |   D  |   F  |   G  |                              |   H  |   J  |   K  |   L  |   Ö  |   Ä    |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * | LShift |   Z  |   X  |   C  |   V  |   B  |QWERTY|      |  |F-keys|      |   N  |   M  |   ,  |   .  |   -  |  Enter |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |Adjust| LGUI | LAlt/| SpLow| GLow |  | Sym  | Space| AltGr| RGUI | Menu |
 *                        |      |      | Enter|      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_GAME] = LAYOUT(
     KC_TAB  , KC_Q ,  KC_W   ,  KC_E  ,   KC_R ,   KC_T ,                                        KC_Y,   KC_U ,  KC_I ,   KC_O ,  KC_P , KC_BSPC,
     CTL_ESC , KC_A ,  KC_S   ,  KC_D  ,   KC_F ,   KC_G ,                                        KC_H,   KC_J ,  KC_K ,   KC_L ,SE_ODIA, SE_ADIA,
     KC_LSFT , KC_Z ,  KC_X   ,  KC_C  ,   KC_V ,   KC_B , QWERTY,XXXXXXX,     FKEYS  , XXXXXXX, KC_N,   KC_M ,SE_COMM, SE_DOT ,SE_MINS, KC_ENT,
                                ADJUST , KC_LGUI, ALT_ENT, SpLow ,GLow   ,     _______, KC_SPC ,KC_RALT, KC_RGUI, KC_MUTE
    ),

/*
 * Lower layer
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |   @    |   !  |   "  |   #  |   $  |   %  |                              |   &  |   /  |   (  |   )  |   =  |   \    |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |   @    |   !  |   "  |   #  |   $  |   %  |                              |   @  |   ?  |   [  |   ]  |   $  |  *     |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * |        |      |   £  |   €  |   @  |   ¤  |      |      |  |      |      |      |   *  |   {  |   }  |      |        |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_LOWER] = LAYOUT(
      SE_AT  , SE_EXLM, SE_DQUO, SE_HASH, SE_DLR,  SE_PERC,                                     SE_AMPR, SE_SLSH, SE_LPRN, SE_RPRN, SE_EQL,  SE_BSLS,
      SE_AT  , SE_EXLM, SE_DQUO, SE_HASH, SE_DLR,  SE_PERC,                                       SE_AT, SE_QUES, SE_LBRC, SE_RBRC, SE_DLR , SE_ASTR,
      _______, _______,  SE_PND, SE_EURO,  SE_AT,  SE_CURR, _______, _______, _______, _______, _______, SE_ASTR, SE_LCBR, SE_RCBR, _______, _______,
                                 _______, _______, _______, _______, XXXXXXX, _______, _______, _______, _______, KC_MUTE
    ),

/*
 * Raise layer
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |    ^   |   1  |   2  |   3  |   4  |   5  |                              |   6  |   7  |   8  |   9  |   0  |   Del  |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |   Del  | PIPE | TILD |   <  |   >  |      |                              |   '  |   +  |   `  |   å  |      |        |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * |        |      |      |      | PIPE |      | COLE |      |  |      |      |      |      |   ´  |      |      |        |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        | |>|| |      |      |      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_RAISE] = LAYOUT(
      SE_CIRC, KC_1   ,  KC_2,   KC_3   , KC_4   , KC_5   ,                                     KC_6   , KC_7   , KC_8   , KC_9   , KC_0   , KC_DEL ,
      KC_DEL,  SE_PIPE, SE_TILD, SE_LABK, SE_RABK, _______,                                     SE_QUOT, SE_PLUS, SE_GRV , SE_ARNG, _______, XXXXXXX,
      _______, _______, _______, _______, SE_PIPE, _______, COLEMAK, _______, _______, _______, _______, SE_ASTR, SE_LCBR, SE_RCBR, _______, _______,
                                 KC_MPLY, _______, _______, _______, _______, XXXXXXX, _______, _______, _______, _______
    ),

/*
 * Nav Layer: Media, navigation
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |        |      |      | Alt  |      | PgUp |                              | Yank |C_PGUP|      |C_PGDN| Paste|        |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |  Bksp  | Home | End  | Shift| Ctrl | PgDn |                              |  ←   |   ↓  |   ↑  |   →  | Del  |        |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * |        | Ctrl |      |      | COMNT|DUPLIC|      |      |  |      |      |      | Yank |      | Paste|      | PrtSc  |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_NAV] = LAYOUT(
      XXXXXXX, XXXXXXX, XXXXXXX, KC_LALT, XXXXXXX, KC_PGUP,                                     YANK   , C_PGUP,  XXXXXXX, C_PGDN , PASTE  , XXXXXXX,
      KC_BSPC, KC_HOME, KC_END , KC_LSFT, KC_LCTL, KC_PGDN,                                     KC_LEFT, KC_DOWN, KC_UP  , KC_RGHT, KC_DEL , XXXXXXX,
      _______, KC_LCTL, XXXXXXX, COMNT  , DUPLIC , XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, YANK,    PASTE  , XXXXXXX, XXXXXXX, KC_PSCR,
                                 _______, XXXXXXX, XXXXXXX, _______, _______, _______, _______, _______, _______, _______
    ),

/*
 * Function Layer: Function keys
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |        |  F9  | F10  | F11  | F12  |      |                              |      |      |      |      |      |        |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |        |  F5  |  F6  |  F7  |  F8  |      |                              |      | Shift| Ctrl |  Alt |  GUI |        |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * |        |  F1  |  F2  |  F3  |  F4  |      |      |      |  |      |      |      |      |      |      |      |        |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_FUNCTION] = LAYOUT(
      _______,  KC_F9 ,  KC_F10,  KC_F11,  KC_F12, _______,                                     _______, _______, _______, _______, _______, _______,
      _______,  KC_F5 ,  KC_F6 ,  KC_F7 ,  KC_F8 , _______,                                     _______, KC_RSFT, KC_RCTL, KC_LALT, KC_RGUI, _______,
      _______,  KC_F1 ,  KC_F2 ,  KC_F3 ,  KC_F4 , _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
                                 _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),

/*
 * Function Layer: Numpad
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |        |      |C_PGUP|      |C_PGDN|  TD  |                              | CtrlK|  7   |  8   |  9   |  *   |  Del   |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |        |      |SAltTb|      | AltTb| TILDE|                              | Bksp |  4   |  5   |  6   |  +   |   ,    |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * |        |      |      |      | CMNT |      |      |      |  |      |SCtrlK| Enter|  1   |  2   |  3   |  -   |        |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |      |      |      |      |      |  |      |      |  0   |  .   |      |
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_NUM] = LAYOUT(
      _______, _______, C_PGUP , _______, C_PGDN , TD     ,                                      CtrlK , KC_7   , KC_8   , KC_9   , KC_PAST, KC_DEL ,
      _______, _______, UC_STAB, _______, UC_TAB , TILDE  ,                                     KC_BSPC, KC_4   , KC_5   , KC_6   , KC_PPLS, SE_COMM,
      _______, _______, _______, _______, CMNT   , _______, _______, _______, _______, SCtrlK , _______, KC_1   , KC_2   , KC_3   , KC_PMNS, _______,
                                 _______, _______, _______, _______, _______, _______, _______, KC_0   , SE_DOT , _______
    ),

/*
 * Lower layer for Game layer
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |        |   1  |   2  |   3  |   4  |   5  |                              |   6  |   7  |   8  |   9  |   0  |        |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |        | VILL |      |      |      |  DEL |                              |      |      |      |      |      |        |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |      |  |      |      |      |      |      |      |      |        |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_GAMELOW] = LAYOUT(
      XXXXXXX, KC_1   , KC_2   , KC_3   , KC_4   , KC_5   ,                                     KC_6   , KC_7   , KC_8   , KC_9   , KC_0   , XXXXXXX,
      _______, VILL   , XXXXXXX, XXXXXXX, KC_DEL , XXXXXXX,                                     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
      _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                                 XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
    ),

/*
 * Adjust Layer: Default layer settings, RGB
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |        |      |      |QWERTY|      |      |                              |      |      |      |      |      |        |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |        |      |      |GAME  |      |      |                              | TOG  | SAI  | HUI  | VAI  | MOD  |        |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |      |  |      |      |      | SAD  | HUD  | VAD  | RMOD |        |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_ADJUST] = LAYOUT(
      _______, _______, _______, QWERTY , _______, _______,                                    _______, _______, _______, _______,  _______, _______,
      _______, _______, _______, GAME   , _______, _______,                                    RGB_TOG, RGB_SAI, RGB_HUI, RGB_VAI,  RGB_MOD, _______,
      _______, _______, _______, _______, _______, _______,_______, _______, _______, _______, _______, RGB_SAD, RGB_HUD, RGB_VAD, RGB_RMOD, _______,
                                 _______, _______, _______,_______, _______, _______, _______, _______, _______, _______
    ),

};
// clang-format on

bool is_alt_tab_active = false;
uint16_t alt_tab_timer = 0;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
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
    case MK_PRN:
      if (record->event.pressed) {
        SEND_STRING("()");
        tap_code(KC_LEFT);
      }
      return false;
      break;
    case MK_BRC:
      if (record->event.pressed) {
        SEND_STRING("[]");
        tap_code(KC_LEFT);
      }
      return false;
      break;
    case MK_SQT:
      if (record->event.pressed) {
        SEND_STRING("''");
        tap_code(KC_LEFT);
      }
      return false;
      break;
    case MK_CBR:
      if (record->event.pressed) {
        SEND_STRING("{}");
        tap_code(KC_LEFT);
      }
      return false;
      break;
    case TILDE:
      if (record->event.pressed) {
        SEND_STRING("~");
      }
      return false;
      break;
    case CMNT:
      if (record->event.pressed) {
        SEND_STRING("```");
      }
      return false;
      break;
    case KC_CCCV:  // One key copy/paste
      if (record->event.pressed) {
        copy_paste_timer = timer_read();
      } else {
        if (timer_elapsed(copy_paste_timer) > TAPPING_TERM) {  // Hold, copy
          tap_code16(LCTL(KC_C));
        } else { // Tap, paste
          tap_code16(LCTL(KC_V));
        }
      }
      break;
    case UC_TAB:
      if (record->event.pressed) {
        if (!is_alt_tab_active) {
          is_alt_tab_active = true;
          register_code(KC_LALT);
        }
        alt_tab_timer = timer_read();
        tap_code16(KC_TAB);
      }
      break;
    case UC_STAB:
      if (record->event.pressed) {
        if (!is_alt_tab_active) {
          is_alt_tab_active = true;
          register_code(KC_LALT);
        }
        alt_tab_timer = timer_read();
        tap_code16(S(KC_TAB));
      }
      break;
  }
  return true;
}

LEADER_EXTERNS();
void matrix_scan_user(void) {
    if (is_alt_tab_active) {
        if (timer_elapsed(alt_tab_timer) > 500) {
            unregister_code(KC_LALT);
            is_alt_tab_active = false;
        }
    }

    LEADER_DICTIONARY() {
        leading = false;
        leader_end();

        SEQ_ONE_KEY(KC_F) { // Contains XPATH
            SEND_STRING("contains(@class,'')"  SS_TAP(X_LEFT) SS_TAP(X_LEFT));
        }
        SEQ_ONE_KEY(KC_C) { // Inline Code
            SEND_STRING("`` " SS_TAP(X_LEFT) SS_TAP(X_LEFT));
        }
        SEQ_ONE_KEY(KC_Q) { // Windows screenshot
            SEND_STRING(SS_LGUI("\nS"));
        }
    }
}

#include "oled.c"
#include "encoder_map.c"
