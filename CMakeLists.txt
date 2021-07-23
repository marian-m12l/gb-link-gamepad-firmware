cmake_minimum_required(VERSION 3.13)
# initialize the SDK based on PICO_SDK_PATH
# note: this must happen before project()
include(pico_sdk_import.cmake)
project(gbgamepad)
 
pico_sdk_init()

add_executable(gbgamepad)

pico_generate_pio_header(gbgamepad ${CMAKE_CURRENT_LIST_DIR}/pio/secondary.pio)

target_include_directories(gbgamepad PRIVATE ${CMAKE_CURRENT_LIST_DIR})

target_sources(gbgamepad PRIVATE
        main.c

        usb_descriptors.c

        # PIO components
        pio/pio_secondary.c
        )
        
target_link_libraries(gbgamepad PRIVATE pico_stdlib hardware_pio tinyusb_device tinyusb_board)
pico_add_extra_outputs(gbgamepad)

