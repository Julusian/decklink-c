cmake_minimum_required(VERSION 3.10)
project(decklink_c)

set(CMAKE_CXX_STANDARD 14)

set(SOURCES
        include/common.h
        include/decklink_c.h
        include/device.h
        include/display_mode.h
        include/enums.h
        include/frame.h
        include/iterator.h
        include/types.h

        src/decklink_api.h
        src/device.cpp
        src/display_mode.cpp
        src/frame.cpp
        src/iterator.cpp
        src/types.h

        interop/Linux/include/DeckLinkAPI.h
        #        interop/Linux/include/DeckLinkAPI_v7_1.h
        #        interop/Linux/include/DeckLinkAPI_v7_3.h
        #        interop/Linux/include/DeckLinkAPI_v7_6.h
        #        interop/Linux/include/DeckLinkAPI_v7_9.h
        #        interop/Linux/include/DeckLinkAPI_v8_0.h
        #        interop/Linux/include/DeckLinkAPI_v8_1.h
        #        interop/Linux/include/DeckLinkAPI_v9_2.h
        #        interop/Linux/include/DeckLinkAPI_v9_9.h
        #        interop/Linux/include/DeckLinkAPI_v10_2.h
        #        interop/Linux/include/DeckLinkAPI_v10_4.h
        #        interop/Linux/include/DeckLinkAPI_v10_5.h
        #        interop/Linux/include/DeckLinkAPI_v10_6.h
        #        interop/Linux/include/DeckLinkAPI_v10_9.h
        #        interop/Linux/include/DeckLinkAPI_v10_11.h
        interop/Linux/include/DeckLinkAPIConfiguration.h
        #        interop/Linux/include/DeckLinkAPIConfiguration_v10_2.h
        #        interop/Linux/include/DeckLinkAPIConfiguration_v10_4.h
        #        interop/Linux/include/DeckLinkAPIConfiguration_v10_5.h
        #        interop/Linux/include/DeckLinkAPIConfiguration_v10_9.h
        #        interop/Linux/include/DeckLinkAPIConfiguration_v10_11.h
        interop/Linux/include/DeckLinkAPIDeckControl.h
        interop/Linux/include/DeckLinkAPIDiscovery.h
        interop/Linux/include/DeckLinkAPIDispatch.cpp
        interop/Linux/include/DeckLinkAPIModes.h
        interop/Linux/include/DeckLinkAPITypes.h
        interop/Linux/include/DeckLinkAPIVersion.h
        interop/Linux/include/LinuxCOM.h
        )

include_directories(.)
add_library(decklink_c STATIC ${SOURCES})

target_link_libraries(decklink_c dl pthread)

add_subdirectory(examples)

install(TARGETS decklink_c DESTINATION .)
