
ADD_COMPILE_DEFINITIONS(__MODUS_TARGET_SDL2_AUDIO__=true)
ADD_COMPILE_DEFINITIONS(__MODUS_TARGET_DESKTOP_CONTROLS__=true)
ADD_COMPILE_DEFINITIONS(__MODUS_TARGET_DESKTOP_DISPLAY__=true)
ADD_COMPILE_DEFINITIONS(LIBXMP_CORE_PLAYER=true)

FILE(GLOB_RECURSE TESTS "${CREATIVE_ENGINE_PATH}/test/src/tests/*.cpp")
ADD_EXECUTABLE(test
        ${CREATIVE_ENGINE_PATH}/test/src/main.cpp
        ${CREATIVE_ENGINE_PATH}/test/src/test.h
        ${TESTS}
        ${CREATIVE_ENGINE_SOURCE_FILES}
        ${CREATIVE_ENGINE_PATH}/test/src/Resources.bin
        )

TARGET_INCLUDE_DIRECTORIES( test PUBLIC
        ${CREATIVE_ENGINE_INCLUDE_DIRS}
        ${SDL2_INCLUDE_DIRS}
        ${CREATIVE_ENGINE_PATH}/test/src
        )

TARGET_LINK_LIBRARIES(test ${SDL2_LIBRARIES})