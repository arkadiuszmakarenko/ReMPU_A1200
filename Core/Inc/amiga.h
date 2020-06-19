
#include <inttypes.h>
#include "keyboard.h"




extern void amikb_startup(void);
extern void amikb_process(keyboard_t *data);
extern void amikb_gpio_init(void);
extern bool amikb_reset_check(void);
extern void amikb_reset(void);

