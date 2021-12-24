cmake_minimum_required(VERSION 3.12)

include(pico-sdk/pico_sdk_init.cmake)
project(l1kvm-remote C CXX ASM)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

pico_sdk_init()

add_executable(${PROJECT_NAME})

target_sources(${PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/main.c
  ${CMAKE_CURRENT_LIST_DIR}/usb_descriptors.c
)

target_include_directories(${PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}
  )

pico_add_extra_outputs(${PROJECT_NAME})

target_link_libraries(${PROJECT_NAME} PUBLIC
  pico_stdlib
  pico_multicore
  tinyusb_device
  tinyusb_board
)

#pico_auto_set_url(l1kvm-remote)
