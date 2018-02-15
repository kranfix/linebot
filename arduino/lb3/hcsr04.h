/* A library to handle HC-SR04 sensor
 * Author: Frank Moreno
 */

typedef struct {
  int trigger;
  int echo;
  int isActive; // bool
} hcsr04_t;

hcsr04_t hcsr04_CreateAndBegin(int trigger, int echo);
hcsr04_t hcsr04_new(int trigger, int echo);
void hcsr04_begin(hcsr04_t * hc);
float hcsr04_loop(hcsr04_t * hc);
