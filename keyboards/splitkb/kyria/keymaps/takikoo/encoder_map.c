#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
    [_QWERTY] = { ENCODER_CCW_CW(UC_STAB, UC_TAB)    ,  ENCODER_CCW_CW(KC_PGUP, KC_PGDN)                    },
    [_LOWER]  = { ENCODER_CCW_CW(KC_LEFT, KC_RIGHT)  ,  ENCODER_CCW_CW(KC_KB_VOLUME_DOWN, KC_KB_VOLUME_UP)  },
    [_RAISE]  = { ENCODER_CCW_CW(S(KC_F3), KC_F3)    ,  ENCODER_CCW_CW(KC_LEFT, KC_RIGHT)                    },
    [_NAV]    = { ENCODER_CCW_CW(KC_LEFT, KC_RIGHT)  ,  ENCODER_CCW_CW(KC_RIGHT, KC_LEFT)                   },
    [_NUM]    = { ENCODER_CCW_CW(KC_LEFT, KC_RIGHT)  ,  ENCODER_CCW_CW(C(KC_Z), C(KC_Y))                    },
};
#endif
