
#ifndef HID_DESCRIPTOR_H_
#define HID_DESCRIPTOR_H_

#include "common/tusb_common.h"
#include "device/usbd.h"


// Gamepad Report Descriptor with 8 buttons
#define REPORT_DESC_GAMEPAD(...)                   \
    HID_USAGE_PAGE(HID_USAGE_PAGE_DESKTOP),                \
    HID_USAGE(HID_USAGE_DESKTOP_GAMEPAD),              \
    HID_COLLECTION(HID_COLLECTION_APPLICATION),        \
        __VA_ARGS__                                        \
            HID_USAGE_PAGE(HID_USAGE_PAGE_BUTTON),         \
        HID_USAGE_MIN(1),                                  \
        HID_USAGE_MAX(8),                                 \
        HID_LOGICAL_MIN(0),                                \
        HID_LOGICAL_MAX(1),                                \
        HID_REPORT_COUNT(8),                              \
        HID_REPORT_SIZE(1),                                \
        HID_INPUT(HID_DATA | HID_VARIABLE | HID_ABSOLUTE), \
    HID_COLLECTION_END


#endif /* HID_DESCRIPTOR_H_ */
