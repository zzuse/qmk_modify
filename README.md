# qmk_modify
## winry25
### mostly tap dance configure
```c++
/* tap
 *CAPS        ______________________________     LOCK/LAYER
 *   `------>/1/ESC/ F1_2/ F2_3/F4_4 /5/DEL/--------'
 *          /-----/-----/-----/-----/-----/
 *         /TAB/Q/  W  /  E  /  R  /  T  /
 *        /-----/-----/-----/-----/-----/
 *       /  A  /  S  /  D  /  F  /  G  /
 *      /-----/-----/-----/-----/-----/
 *     / LSFT/  Z  /  X  /  C  / V/B /
 *    /-----/-----/-----/-----/-----/
 *   /HO/EN/Ctrl / Opt / CMD /Space/
 *  -------------------------------
 */
  [WASD_LAYER] = LAYOUT( TD(ESC_1),   TD(F1_2),  TD(F2_3),  TD(F4_4), TD(F5_5),
                         TD(TAB_Q),   KC_W,          KC_E,    KC_R,   KC_T,
                          KC_A,       KC_S,          KC_D,    KC_F,   KC_G,
                           KC_LSFT,   KC_Z,          KC_X,    KC_C,   KC_V,
                         TD(HOME_END),KC_LCTL,       KC_LOPT, LCMD_T(KC_B),KC_SPACE),
/* hold
 *            ______________________________
 *           /CON_A/CON_D/     /SHIFT/     /
 *          /-----/-----/-----/-----/-----/
 *         /RGBTg/RGBM+/Brig+/RGSPI/     /
 *        /-----/-----/-----/-----/-----/
 *       /     /     /TD(1)/     /     /
 *      /-----/-----/-----/-----/-----/
 *     /     /     /     /     /     /
 *    /-----/-----/-----/-----/-----/
 *   / COPY/     /     /     /PASTE/
 *  -------------------------------
 */
  [FUNC_LAYER] = LAYOUT(CONDA_ACTIVATE,CONDA_DEACTIVATE, _______,      KC_LSFT, _______,
                               RGB_TOG,         RGB_MOD, RGB_VAI,      RGB_SPI, _______,
                               _______,         _______, TD(QUO_LAYER),_______, _______,
                               _______,         _______, _______,      _______, _______,
                                  COPY,         _______, _______,      _______, PASTE),

/* double tap
 */
  [GAME_LAYER] = LAYOUT(  KC_TAB,       _______,  _______,  _______, TD(QUO_LAYER),
                         _______,       _______,  KC_W,     _______, _______,
                         _______,       KC_A,     KC_S,     KC_D,    _______,
                         KC_LSFT,       _______,  _______,  _______, _______,
                         _______,       _______,  _______,  _______, KC_SPACE),

/* triple tap
 *            _______________________________
 *           /  1  /     /  X  /      /  4  /
 *          /-----/-----/-----/ -----/-----/
 *         /  2  /     /  Z  /      /  5  /
 *        /-----/-----/-----/ -----/-----/
 *       /  D  /     /TD(1)/      /  6  /
 *      /-----/-----/-----/ -----/-----/
 *     /     /     /     /      /     /
 *    /-----/-----/-----/ -----/-----/
 *   /     /     /     /      /     /
 *  --------------------------------
*/
```
## ymdk09
