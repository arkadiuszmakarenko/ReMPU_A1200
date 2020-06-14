#include <stdint.h>
#include <inttypes.h>
#include <stdbool.h>


#define KEY_PRESSED_MAX 10


typedef struct {
	uint8_t lami;
	uint8_t lalt;
	uint8_t lshf;
	uint8_t ctrl;
	uint8_t rami;
	uint8_t ralt;
	uint8_t rshf;
	uint16_t keys[KEY_PRESSED_MAX];
} keyboard_t;




int * Read_Keyboard(void);

