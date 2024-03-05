cmake_minimum_required(VERSION 3.12)
#set(PICO_SDK_PATH C:/DEV/SDK)
set(CMAKE_C_STANDARD 11)
set(PICO_PLATFORM rp2040)
#set(PICO_COMPILER pico_arm_gcc)
#set(CMAKE_BUILD_TYPE Release)
set(PICO_BOARD pico)
#add_executable(Pioasm IMPORTED)
#set_property(TARGET Pioasm PROPERTY IMPORTED_LOCATION C:/DEV/SDK/tools/pioasm/pioasm.exe)
#set(Pioasm_FOUND 1)
#add_executable(ELF2UF2 IMPORTED)
#set_property(TARGET ELF2UF2 PROPERTY IMPORTED_LOCATION C:/DEV/SDK/tools/elf2uf2/elf2uf2.exe)
#set(ELF2UF2_FOUND 1)
include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)
project(project_name)
pico_sdk_init()
add_executable(project_name
		main.c
	)
target_include_directories(${PROJECT_NAME}
    PRIVATE
        ${PROJECT_SOURCE_DIR}
        ${PROJECT_SOURCE_DIR}/src
        ${PROJECT_SOURCE_DIR}/inc
)
target_link_libraries(project_name
		pico_stdlib
	)
target_compile_definitions(project_name PRIVATE
		TUD_OPT_RP2040_USB_DEVICE_UFRAME_FIX=0
		PICO_CLOCK_AJDUST_PERI_CLOCK_WITH_SYS_CLOCK=1
	)
pico_enable_stdio_usb(project_name 1)
pico_enable_stdio_uart(project_name 0)
pico_add_extra_outputs(project_name)
