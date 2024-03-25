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
    _MOUSE,
    _ADJUST,
};

enum custom_keycodes {
    TD = SAFE_RANGE,
    VILL,
    VILL5,
    GLHF,
    GG,
    OC,
    TILDE,
    CMNT,
    MK_BRC,
    MK_SQT,
    MK_CBR,
    MK_PRN,
    MK_COL,
};

enum combos {
  AB_ESC,
  DTC_COL,
  JK_BRC,
  KL_SQT,
  CM_CBR,
  UI_PRN,
  QW_SFT,
};

const uint16_t PROGMEM ab_combo[] = {KC_A, KC_B, COMBO_END};
const uint16_t PROGMEM dtc_combo[] = {SE_DOT, SE_COMM, COMBO_END};
const uint16_t PROGMEM jk_combo[] = {KC_J, KC_K, COMBO_END};
const uint16_t PROGMEM kl_combo[] = {KC_K, KC_L, COMBO_END};
const uint16_t PROGMEM cm_combo[] = {SE_COMM, KC_M, COMBO_END};
const uint16_t PROGMEM ui_combo[] = {KC_U, KC_I, COMBO_END};
const uint16_t PROGMEM qw_combo[] = {KC_Q, KC_W, COMBO_END};

combo_t key_combos[COMBO_COUNT] = {
  [AB_ESC]  = COMBO(ab_combo, KC_ESC),
  [DTC_COL] = COMBO(dtc_combo, SE_COLN),
  [JK_BRC]  = COMBO(jk_combo, MK_BRC),
  [KL_SQT]  = COMBO(kl_combo, MK_SQT),
  [CM_CBR]  = COMBO(cm_combo, MK_CBR),
  [UI_PRN]  = COMBO(ui_combo, MK_PRN),
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
#define MOUSE    LT(_MOUSE, KC_ESC)
#define GLow     LM(_GAMELOW, MOD_LCTL)
#define SpLow    LT(_GAMELOW, KC_SPC)
#define CTL_ESC  MT(MOD_LCTL, KC_ESC)
#define CTL_QUOT MT(MOD_RCTL, KC_QUOTE)
#define ALT_ENT  MT(MOD_LALT, KC_ENT)

// Mod Tap Home row
#define HM_A     LGUI_T(KC_A)
#define HM_S     LALT_T(KC_S)
#define HM_D     LCTL_T(KC_D)
#define HM_F     LSFT_T(KC_F)
#define HM_J     LSFT_T(KC_J)
#define HM_K     LCTL_T(KC_K)
#define HM_L     LALT_T(KC_L)
#define HM_ODIA  LGUI_T(SE_ODIA)

#define U_RDO KC_AGIN
#define U_UND KC_UNDO

#define C_PGUP C(KC_PGUP)
#define C_PGDN C(KC_PGDN)
#define CUT    C(KC_X)
#define YANK   C(KC_INS)
#define PASTE  S(KC_INS)
#define COMNT  C(SE_QUOT)
#define DLINE  C(KC_D)
#define DUPLIC C(S(KC_D))
#define CtrlK  C(KC_K)
#define SCtrlK S(C(KC_K))
#define B_BACK A(KC_LEFT)
#define B_FWD  A(KC_RIGHT)

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/*
 * Base Layer: QWERTY
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |  Tab   |   Q  |   W  |   E  |   R  |   T  |                              |   Y  |   U  |   I  |   O  |   P  |   Å    |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |Ctrl/Esc|   A  |   S  |   D  |   F  |   G  |                              |   H  |   J  |   K  |   L  |   Ö  |   Ä    |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * | LShift |   Z  |   X  |   C  |   V  |   B  | GAME |CapsW |  |F-keys|CapsW |   N  |   M  |   ,  |   .  |   -  |  Enter |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |Adjust| LAlt | Bksp/|NumSpc| LGUI |  | MEH  |SpcNav|Enter/| RGUI | Menu |
 *                        |      |      | Lower|      |      |  |      |      | Raise|      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_QWERTY] = LAYOUT(
     KC_TAB   , KC_Q  ,  KC_W  ,  KC_E  , KC_R   ,  KC_T  ,                                     KC_Y   , KC_U   , KC_I   , KC_O   , KC_P   , SE_ARNG,
     CTL_ESC  , HM_A  ,  HM_S  ,  HM_D  , HM_F   ,  KC_G  ,                                     KC_H   , HM_J   , HM_K   , HM_L   , HM_ODIA, SE_ADIA,
     KC_LSFT  , KC_Z  ,  KC_X  ,  KC_C  , KC_V   ,  KC_B  , GAME   , CW_TOGG, FKEYS  , CW_TOGG, KC_N   , KC_M   , SE_COMM, SE_DOT , SE_MINS, KC_ENT ,
                                  ADJUST, KC_LALT,  BS_LOW, TABNUM , MOUSE  , KC_MEH , SPCNAV , ENT_RS , KC_RGUI, KC_MUTE
    ),

/*
 * Base Layer: Colemak DH
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |  Tab   |   Q  |   W  |   F  |   P  |   B  |                              |   J  |   L  |   U  |   Y  | ;  : |  Bksp  |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |Ctrl/Esc|   A  |   R  |   S  |   T  |   G  |                              |   M  |   N  |   E  |   I  |   O  |Ctrl/' "|
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * | LShift |   Z  |   X  |   C  |   D  |   V  |QWERTY|      |  |F-keys|      |   K  |   H  | ,  < | . >  | /  ? | RShift |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |Adjust| LGUI | LAlt/| Space| Nav  |  | Sym  | Space| AltGr| RGUI | Menu |
 *                        |      |      | Enter|      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_COLEMAK_DH] = LAYOUT(
      KC_TAB   , KC_Q   , KC_W   , KC_F   , KC_P   , KC_B   ,                                     KC_J   , KC_L   , KC_U   , KC_Y   , SE_ODIA,SE_ARNG ,
      CTL_ESC  , KC_A   , KC_R   , KC_S   , KC_T   , KC_G   ,                                     KC_M   , KC_N   , KC_E   , KC_I   , KC_O   ,CTL_QUOT,
      KC_LSFT  , KC_Z   , KC_X   , KC_C   , KC_D   , KC_V   , QWERTY , XXXXXXX, FKEYS  , XXXXXXX, KC_K   , KC_H   , SE_COMM, SE_DOT , SE_SLSH,KC_RSFT ,
                                   ADJUST , KC_LALT, BS_LOW , TABNUM , KC_LGUI, KC_MEH , SPCNAV , ENT_RS , KC_RGUI, KC_MUTE
    ),

/*
 * Base Layer: GAME
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |  Tab   |   Q  |   W  |   E  |   R  |   T  |                              |   Y  |   U  |   I  |   O  |   P  |  Bksp  |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |Ctrl/Esc|   A  |   S  |   D  |   F  |   G  |                              |   H  |   J  |   K  |   L  |   Ö  |   Ä    |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * | LShift |   Z  |   X  |   C  |   V  |   B  |   1  |   2  |  |F-keys|      |   N  |   M  |   ,  |   .  |   -  |  Enter |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |  DEL | LGUI | LAlt/| SpLow| GLow |  | Sym  | Space| AltGr| RGUI | Menu |
 *                        |      |      | Enter|      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_GAME] = LAYOUT(
      KC_TAB   , KC_Q   , KC_W   , KC_E   , KC_R   , KC_T   ,                                     KC_Y   , KC_U   , KC_I   , KC_O   , KC_P   , KC_BSPC,
      CTL_ESC  , KC_A   , KC_S   , KC_D   , KC_F   , KC_G   ,                                     KC_H   , KC_J   , KC_K   , KC_L   , SE_ODIA, SE_ADIA,
      KC_LSFT  , KC_Z   , KC_X   , KC_C   , KC_V   , KC_B   , KC_1   , KC_2   , QWERTY , XXXXXXX, KC_N   , KC_M   , SE_COMM, SE_DOT , SE_MINS, KC_ENT ,
                                   KC_DEL , KC_LGUI, KC_LALT, SpLow  , GLow   , KC_MEH , KC_SPC , KC_RALT, KC_RGUI, KC_MUTE
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
 * |        |      | LGUI | Alt  |      | PgUp |                              | Yank |C_PGUP|      |C_PGDN| Paste|        |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |  Bksp  | Home | End  | Ctrl | Shift| PgDn |                              |  ←   |   ↓  |   ↑  |   →  | Del  |        |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * |        |      |      | COMNT|DUPLIC|      |      |      |  |      |      |      | Yank |      | Paste|      | PrtSc  |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_NAV] = LAYOUT(
      XXXXXXX, XXXXXXX, KC_LGUI, KC_LALT, XXXXXXX, KC_PGUP,                                     YANK   , C_PGUP,  B_FWD  , C_PGDN , PASTE  , XXXXXXX,
      KC_BSPC, KC_HOME, KC_END , KC_LCTL, KC_LSFT, KC_PGDN,                                     KC_LEFT, KC_DOWN, KC_UP  , KC_RGHT, KC_DEL , XXXXXXX,
      _______, XXXXXXX, DLINE  , COMNT  , DUPLIC , XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, YANK,    PASTE  , XXXXXXX, XXXXXXX, KC_PSCR,
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
      _______, _______, C_PGUP , B_BACK , C_PGDN , TD     ,                                     CtrlK  , KC_7   , KC_8   , KC_9   , KC_PAST, KC_DEL ,
      _______, _______, XXXXXXX, _______, XXXXXXX, TILDE  ,                                     KC_BSPC, KC_4   , KC_5   , KC_6   , KC_PPLS, SE_COMM,
      _______, _______, _______, _______, CMNT   , _______, _______, _______, _______, SCtrlK , _______, KC_1   , KC_2   , KC_3   , KC_PMNS, _______,
                                 _______, _______, _______, _______, _______, _______, _______, KC_0   , SE_DOT , _______
    ),

/*
 * Lower layer for Game layer
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |        |   1  |   2  |   3  |   4  |   5  |                              |   6  |   7  |   8  |   9  |   0  |        |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |        | VILL5|      |      |      |  DEL |                              |      |      |      |      |      |        |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |      |  |      |      |      |      |      |      |      |        |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_GAMELOW] = LAYOUT(
      XXXXXXX, KC_1   , KC_2   , KC_3   , KC_4   , KC_5   ,                                     KC_6   , KC_7   , KC_8   , KC_9   , KC_0   , XXXXXXX,
      _______, VILL5  , KC_3   , KC_2   , KC_1   , XXXXXXX,                                     OC     , GLHF   , GG     ,  XXXXXXX, XXXXXXX, XXXXXXX,
      _______, VILL   , XXXXXXX, XXXXXXX, KC_DEL , XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                                 XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
    ),

/*
 * Mouse layer
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |        |      |      |      |      |      |                              | REDO | PASTE| YANK | CUT  | UNDO |        |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |        | LGUI | LAlt | LCtrl|LShift|      |                              |  M←  |  M↓  |  M↑  |  M→  |      |        |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |      |  |      |      |  MS← |  MS↓ |  MS↑ |  MS→ |      |        |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |      |      |      |      |      |  |RClick|LClick|WClick|      |      |
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_MOUSE] = LAYOUT(

      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                                     U_RDO,   PASTE,   YANK,    CUT,     U_UND,   XXXXXXX,
      XXXXXXX, KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, XXXXXXX,                                     KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R, XXXXXXX, XXXXXXX,
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_WH_L, KC_WH_D, KC_WH_U, KC_WH_R, XXXXXXX, XXXXXXX,
                                 XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_BTN2, KC_BTN1, KC_BTN3, XXXXXXX, XXXXXXX
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

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case TD:
      if (record->event.pressed) {
        SEND_STRING("td[]");
        tap_code(KC_LEFT);
      }
      return false;
      break;
    case GLHF:
      if (record->event.pressed) {
        tap_code(KC_ENT);
        SEND_STRING(SS_DELAY(100) "*glhf!" SS_DELAY(100));
        tap_code(KC_ENT);
      }
      return false;
      break;
    case GG:
      if (record->event.pressed) {
        tap_code(KC_ENT);
        SEND_STRING(SS_DELAY(100) "*gg wp" SS_DELAY(100));
        tap_code(KC_ENT);
      }
      return false;
      break;
    case OC:
      if (record->event.pressed) {
        tap_code(KC_ENT);
        SEND_STRING(SS_DELAY(100) "*");
      }
      return false;
      break;
    case VILL:
      if (record->event.pressed) {
        SEND_STRING(SS_LCTL("a") SS_DELAY(100) "q");
      }
      return false;
      break;
    case VILL5:
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
  }
  return true;
}

#include "oled.c"
#include "encoder_map.c"
