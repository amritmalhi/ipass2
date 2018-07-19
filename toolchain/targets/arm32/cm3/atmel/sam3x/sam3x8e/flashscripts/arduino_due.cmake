find_program(bossac "bossac" HINTS ${flash_program_path})
if(NOT bossac)
	message([warning] "bossac not found.This program is nessecery to flash the Arduino Due chip. Please install this program and add it to your path or set flash_program_path in your CMakeLists.txt before continuing.")
endif()
if(MSYS OR MINGW)
	set(DEVICE_LOCATION
		"COM3"
		CACHE STRING
		"Serial device name"
	)
else(MSYS OR MINGW)
	set(DEVICE_LOCATION
		"ttyACM0"
		CACHE STRING
		"Serial device name"
	)
endif(MSYS OR MINGW)

if(bossac)
    if(MSYS OR MINGW)
        add_custom_target(flash DEPENDS ${PROJECT_NAME}.bin
                COMMAND ${bossac} -p${DEVICE_LOCATION} -Ufalse -e -w -v -b ${PROJECT_NAME}.bin -R
                # ^ erease -> write -> verify -> boot -> reset
        )
    else(MSYS OR MINGW)
        add_custom_target(flash DEPENDS ${PROJECT_NAME}.bin
                COMMAND stty 1200 -F /dev/${DEVICE_LOCATION}
                COMMAND ${bossac} -p ${DEVICE_LOCATION} -U false -e -w -v -b ${PROJECT_NAME}.bin -R
                # ^ erease -> write -> verify -> boot -> reset
        )
    endif(MSYS OR MINGW)
endif()
