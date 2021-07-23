
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "bsp/board.h"
#include "tusb.h"
#include <stdio.h>
#include <string.h>
#include "tusb.h"
#include "hardware/pio.h"


#include "pio/pio_secondary.h"
//--------------------------------------------------------------------+
// MACRO CONSTANT TYPEDEF PROTYPES
//--------------------------------------------------------------------+




//------------- prototypes -------------//
void hid_task(void);

/*------------- MAIN -------------*/

pio_secondary_inst_t secondary = {
        .pio = pio1,
        .sm = 0
};


#define PIN_SCK 0
#define PIN_SIN 1
#define PIN_SOUT 2


struct report
{
    uint8_t buttons;
} report;


int main(void)
{
  uint secondary_prog_offs = pio_add_program(secondary.pio, &secondary_program);
  secondary_program_init(secondary.pio, secondary.sm, secondary_prog_offs, PIN_SCK, PIN_SIN, PIN_SOUT);
  

  tusb_init();

  while (1)
  {
    tud_task(); // tinyusb device task
    hid_task();
  }

  return 0;
}

//--------------------------------------------------------------------+
// Device callbacks
//--------------------------------------------------------------------+

// Invoked when device is mounted
void tud_mount_cb(void)
{
}

// Invoked when device is unmounted
void tud_umount_cb(void)
{
}

// Invoked when usb bus is suspended
// remote_wakeup_en : if host allow us  to perform remote wakeup
// Within 7ms, device must draw an average of current less than 2.5 mA from bus
void tud_suspend_cb(bool remote_wakeup_en)
{
  (void) remote_wakeup_en;
}

// Invoked when usb bus is resumed
void tud_resume_cb(void)
{
}

//--------------------------------------------------------------------+
// USB HID
//--------------------------------------------------------------------+

// Invoked when received GET_REPORT control request
// Application must fill buffer report's content and return its length.
// Return zero will cause the stack to STALL request
uint16_t tud_hid_get_report_cb(uint8_t index, uint8_t report_id, hid_report_type_t report_type, uint8_t *buffer, uint16_t reqlen)
{
    (void)report_id;
    (void)report_type;
    (void)buffer;
    (void)reqlen;

    return 0;
}

// Invoked when received SET_REPORT control request or
// received data on OUT endpoint ( Report ID = 0, Type = 0 )
void tud_hid_set_report_cb(uint8_t index, uint8_t report_id, hid_report_type_t report_type, uint8_t const *buffer, uint16_t bufsize)
{
    // echo back anything we received from host
    tud_hid_report(0, buffer, bufsize);
}



//--------------------------------------------------------------------+
// USB HID
//--------------------------------------------------------------------+
void hid_task(void)
{
  // Is data available on PIO ?
  if (pio_secondary_available(&secondary)) {
    // Read byte
    uint8_t rx;
    pio_secondary_read8(&secondary, &rx, 1);
    
    // Send HID report
    report.buttons = rx;

    // Remote wakeup
    if (tud_suspended())
    {
        // Wake up host if we are in suspend mode
        // and REMOTE_WAKEUP feature is enabled by host
        tud_remote_wakeup();
    }

    if (tud_hid_ready())
    {
        tud_hid_n_report(0x00, 0x01, &report, sizeof(report));
    }
  }
}
