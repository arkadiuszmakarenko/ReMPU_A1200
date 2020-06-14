//#include <stdint.h>
#include <inttypes.h>
//#include <stdbool.h>

#define KEY_PRESSED_MAX 10
typedef struct {
	uint8_t lami;
	uint8_t lalt;
	uint8_t lshift;
	uint8_t ctrl;
	uint8_t rami;
	uint8_t ralt;
	uint8_t rshift;
	uint8_t keys[KEY_PRESSED_MAX];
} keyboard_code_t;


extern void amikb_startup(void);
extern void amikb_process(keyboard_code_t *data);
extern void amikb_notify(const char *notify);
extern void amikb_gpio_init(void);
extern void amikb_ready(int isready);
extern bool amikb_reset_check(void);
extern void amikb_reset(void);

