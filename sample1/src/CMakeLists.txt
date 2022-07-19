set(BinName "bin")
add_executable(${BinName})

pico_generate_pio_header(${BinName} ${CMAKE_CURRENT_LIST_DIR}/pio0_sm0.pio)
#pico_generate_pio_header(${BinName} ${CMAKE_CURRENT_LIST_DIR}/pio0_sm1.pio)
#pico_generate_pio_header(${BinName} ${CMAKE_CURRENT_LIST_DIR}/pio0_sm2.pio)
#pico_generate_pio_header(${BinName} ${CMAKE_CURRENT_LIST_DIR}/pio0_sm3.pio)

target_sources(${BinName} PRIVATE myapp.c)

pico_enable_stdio_usb(${BinName} 1)
pico_enable_stdio_uart(${BinName} 1)

target_link_libraries(${BinName} PRIVATE pico_stdlib hardware_pio)
pico_add_extra_outputs(${BinName})
