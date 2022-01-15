#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "pico/util/queue.h"
#include "pico/stdlib.h"
#include "bsp/board.h"
#include "tusb.h"
#include "usb_descriptors.h"


// Where we begin our GPIO pins.
#define GPIO_OFFSET 2

/* Blink pattern
 * - 250 ms  : device not mounted
 * - 1000 ms : device mounted
 * - 2500 ms : device is suspended
 */
enum  {
  BLINK_NOT_MOUNTED = 250,
  BLINK_MOUNTED = 1000,
  BLINK_SUSPENDED = 2500,
};

static uint32_t blink_interval_ms = BLINK_NOT_MOUNTED;

queue_t keysend_queue;

typedef struct {
  uint8_t keycode[6];
} keysend_task_t;

void led_blinking_task(void);
void hid_task(void);
void keysend_task(void);

/*------------- MAIN -------------*/
int main(void)
{
  board_init();
  tusb_init();

  queue_init(&keysend_queue, sizeof(keysend_task_t), 8);

  for (uint8_t i=0; i < 5; i++) {
    gpio_init(i+GPIO_OFFSET);
    gpio_set_dir(i+GPIO_OFFSET, GPIO_OUT);
    printf("Initializing GPIO %d\n", i+GPIO_OFFSET);
  }

  while (1)
  {
    tud_task(); // tinyusb device task
    led_blinking_task();

    hid_task();
    keysend_task();
  }

  return 0;
}

//--------------------------------------------------------------------+
// Device callbacks
//--------------------------------------------------------------------+

// Invoked when device is mounted
void tud_mount_cb(void)
{
  blink_interval_ms = BLINK_MOUNTED;
}

// Invoked when device is unmounted
void tud_umount_cb(void)
{
  blink_interval_ms = BLINK_NOT_MOUNTED;
}

// Invoked when usb bus is suspended
// remote_wakeup_en : if host allow us  to perform remote wakeup
// Within 7ms, device must draw an average of current less than 2.5 mA from bus
void tud_suspend_cb(bool remote_wakeup_en)
{
  (void) remote_wakeup_en;
  blink_interval_ms = BLINK_SUSPENDED;
}

// Invoked when usb bus is resumed
void tud_resume_cb(void)
{
  blink_interval_ms = BLINK_MOUNTED;
}

//--------------------------------------------------------------------+
// USB HID
//--------------------------------------------------------------------+

bool btnstate[5] = { false };
bool prevbtnstate[5] = { false };

void hid_task(void)
{
  // Poll every 10ms
  const uint32_t interval_ms = 30;
  static uint32_t start_ms = 0;

  if ( board_millis() - start_ms < interval_ms) return; // not enough time
  start_ms += interval_ms;

  bool btn = false;

  for (uint8_t i=0; i < 5; i++) {
    btnstate[i] = gpio_get(i+GPIO_OFFSET);
    if (btnstate[i]) btn = true;
    /*if (btn) printf("Got Button State\n");*/
  }
    if (btnstate[0]) {
      printf("BTN 0 MOD Down\n");

      // Audio Follows
      if(btnstate[1] && !prevbtnstate[1]){
        keysend_task_t keycode_item = { .keycode = { 0 } };
        keycode_item.keycode[0] = HID_KEY_SCROLL_LOCK;
        queue_try_add(&keysend_queue, &keycode_item);
        queue_try_add(&keysend_queue, &keycode_item);
        keycode_item.keycode[0] = HID_KEY_F5;
        queue_try_add(&keysend_queue, &keycode_item);
      }
      // Audio Current
      if(btnstate[2] && !prevbtnstate[2]){
        keysend_task_t keycode_item = { .keycode = { 0 } };
        keycode_item.keycode[0] = HID_KEY_SCROLL_LOCK;
        queue_try_add(&keysend_queue, &keycode_item);
        queue_try_add(&keysend_queue, &keycode_item);
        keycode_item.keycode[0] = HID_KEY_A;
        queue_try_add(&keysend_queue, &keycode_item);
      }
      // USB Follows
      if(btnstate[3] && !prevbtnstate[3]){
        keysend_task_t keycode_item = { .keycode = { 0 } };
        keycode_item.keycode[0] = HID_KEY_SCROLL_LOCK;
        queue_try_add(&keysend_queue, &keycode_item);
        queue_try_add(&keysend_queue, &keycode_item);
        keycode_item.keycode[0] = HID_KEY_F7;
        queue_try_add(&keysend_queue, &keycode_item);
      }
      // USB Current
      if(btnstate[4] && !prevbtnstate[4]){
        keysend_task_t keycode_item = { .keycode = { 0 } };
        keycode_item.keycode[0] = HID_KEY_SCROLL_LOCK;
        queue_try_add(&keysend_queue, &keycode_item);
        queue_try_add(&keysend_queue, &keycode_item);
        keycode_item.keycode[0] = HID_KEY_U;
        queue_try_add(&keysend_queue, &keycode_item);
      }
    } else {
      // normal switching.
      // Switch to head 1
      if(btnstate[1] && !prevbtnstate[1]){
        keysend_task_t keycode_item = { .keycode = { 0 } };
        keycode_item.keycode[0] = HID_KEY_SCROLL_LOCK;
        queue_try_add(&keysend_queue, &keycode_item);
        queue_try_add(&keysend_queue, &keycode_item);
        keycode_item.keycode[0] = HID_KEY_1;
        queue_try_add(&keysend_queue, &keycode_item);
      }
      // Switch to head 2
      if(btnstate[2] && !prevbtnstate[2]){
        keysend_task_t keycode_item = { .keycode = { 0 } };
        keycode_item.keycode[0] = HID_KEY_SCROLL_LOCK;
        queue_try_add(&keysend_queue, &keycode_item);
        queue_try_add(&keysend_queue, &keycode_item);
        keycode_item.keycode[0] = HID_KEY_2;
        queue_try_add(&keysend_queue, &keycode_item);
      }
      // Switch to head 3
      if(btnstate[3] && !prevbtnstate[3]){
        keysend_task_t keycode_item = { .keycode = { 0 } };
        keycode_item.keycode[0] = HID_KEY_SCROLL_LOCK;
        queue_try_add(&keysend_queue, &keycode_item);
        queue_try_add(&keysend_queue, &keycode_item);
        keycode_item.keycode[0] = HID_KEY_3;
        queue_try_add(&keysend_queue, &keycode_item);
      }
      // Switch to head 4
      if(btnstate[4] && !prevbtnstate[4]){
        keysend_task_t keycode_item = { .keycode = { 0 } };
        keycode_item.keycode[0] = HID_KEY_SCROLL_LOCK;
        queue_try_add(&keysend_queue, &keycode_item);
        queue_try_add(&keysend_queue, &keycode_item);
        keycode_item.keycode[0] = HID_KEY_4;
        queue_try_add(&keysend_queue, &keycode_item);
      }
    }
  for (int i=0;i<5; i++){
    prevbtnstate[i] = btnstate[i];
  }
}

static bool has_keyboard_key = false;
const uint32_t send_interval_ms = 50;
static uint32_t send_start_ms = 0;

void keysend_task(void) {

  if ( board_millis() - send_start_ms < send_interval_ms) return; // not enough time
  send_start_ms += send_interval_ms;
  
  if ( tud_hid_n_ready(ITF_NUM_KEYBOARD) ) {
    // if the key is down, our next interval will be a keyup send.
    if (has_keyboard_key) {
      tud_hid_n_keyboard_report(ITF_NUM_KEYBOARD, 0, 0, NULL);
      has_keyboard_key = false;
    } else {

      keysend_task_t keycode;
      if (!queue_try_remove(&keysend_queue, &keycode)) return;
      tud_hid_n_keyboard_report(ITF_NUM_KEYBOARD, 0, 0, keycode.keycode);
      has_keyboard_key = true;
    }
  }
}

// Invoked when received SET_PROTOCOL request
// protocol is either HID_PROTOCOL_BOOT (0) or HID_PROTOCOL_REPORT (1)
void tud_hid_set_protocol_cb(uint8_t instance, uint8_t protocol)
{
  (void) instance;
  (void) protocol;

  // nothing to do since we use the same compatible boot report for both Boot and Report mode.
  // TOOD set a indicator for user
}

// Invoked when sent REPORT successfully to host
// Application can use this to send the next report
// Note: For composite reports, report[0] is report ID
void tud_hid_report_complete_cb(uint8_t instance, uint8_t const* report, uint8_t len)
{
  (void) instance;
  (void) report;
  (void) len;

  // nothing to do
}

// Invoked when received GET_REPORT control request
// Application must fill buffer report's content and return its length.
// Return zero will cause the stack to STALL request
uint16_t tud_hid_get_report_cb(uint8_t instance, uint8_t report_id, hid_report_type_t report_type, uint8_t* buffer, uint16_t reqlen)
{
  // TODO not Implemented
  (void) instance;
  (void) report_id;
  (void) report_type;
  (void) buffer;
  (void) reqlen;

  return 0;
}

// Invoked when received SET_REPORT control request or
// received data on OUT endpoint ( Report ID = 0, Type = 0 )
void tud_hid_set_report_cb(uint8_t instance, uint8_t report_id, hid_report_type_t report_type, uint8_t const* buffer, uint16_t bufsize)
{
  (void) report_id;

  // keyboard interface
  if (instance == ITF_NUM_KEYBOARD)
  {
    // Set keyboard LED e.g Capslock, Numlock etc...
    if (report_type == HID_REPORT_TYPE_OUTPUT)
    {
      // bufsize should be (at least) 1
      if ( bufsize < 1 ) return;

      uint8_t const kbd_leds = buffer[0];

      if (kbd_leds & KEYBOARD_LED_CAPSLOCK)
      {
        // Capslock On: disable blink, turn led on
        blink_interval_ms = 0;
        board_led_write(true);
      }else
      {
        // Caplocks Off: back to normal blink
        board_led_write(false);
        blink_interval_ms = BLINK_MOUNTED;
      }
    }
  }
}

//--------------------------------------------------------------------+
// BLINKING TASK
//--------------------------------------------------------------------+
// Used for a status message.  
// Final version might be using a LED that's off the board, so we can mount it in the case.
void led_blinking_task(void)
{
  static uint32_t start_ms = 0;
  static bool led_state = false;

  // blink is disabled
  if (!blink_interval_ms) return;

  // Blink every interval ms
  if ( board_millis() - start_ms < blink_interval_ms) return; // not enough time
  start_ms += blink_interval_ms;

  board_led_write(led_state);
  led_state = 1 - led_state; // toggle
}
