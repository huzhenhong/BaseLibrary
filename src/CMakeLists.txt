
set(Target ${This})

message("")
message(STATUS "Start building : " ${Target})

# 设置包含路径
include_directories(${ROOT_DIR}/src/include)

# 添加当前文件夹下所有文件为源文件

aux_source_directory(./logger LOGGERT_SRCS)
aux_source_directory(./util UTIL_SRCS)
message("LOGGERT_SRCS: " ${LOGGERT_SRCS})
message("UTIL_SRCS: " ${UTIL_SRCS})

set(SRCS
        ${LOGGERT_SRCS}
        ${UTIL_SRCS}
        )

message("SRCS: " ${SRCS})

# option(WIN32 True)
option(LIBRARY_EXPORT True)

if(WIN32)

endif()

# 生成动态库
add_library(${Target} SHARED ${SRCS})
target_link_libraries(${Target} stdc++fs)
# 设置库版本，VERSION代表库版本，SOVERSION代表API版本
# set_target_properties(${Target}_shared PROPERTIES VERSION 1.0 SOVERSION 1.0)  
# set_target_properties(${Target}_shared PROPERTIES OUTPUT_NAME ${Target}) # 仍然以工程名输出

# set_target_properties(${Target} PROPERTIES PUBLIC_HEADER ${ROOT_DIR}/src/include/BaseInclude.h)  
# set_target_properties(${Target} PROPERTIES PUBLIC_HEADER ${ROOT_DIR}/src/include/Logger.h)  
# set_target_properties(${Target} PROPERTIES PUBLIC_HEADER ${ROOT_DIR}/src/util/Util.h)  


target_compile_definitions(${Target}
        PRIVATE
        LIBRARY_EXPORT
        PUBLIC
        INTERFACE)

target_compile_options(${Target}
        PRIVATE
        # -D_GLIBCXX_USE_CXX11_ABI=0
        PUBLIC
        INTERFACE)


set_target_properties(${Target}
    PROPERTIES
    LINKER_LANGUAGE           "CXX"
)

# add_library((${This}_static STATIC ${SRCS})
# set_target_properties(${This}_static PROPERTIES OUTPUT_NAME ${This}) # 仍然以工程名输出
# set_target_properties(${This}_static PROPERTIES VERSION 1.0 SOVERSION 1.0)

# 安装生成的动态库
set(CMAKE_INSTALL_PREFIX ${ROOT_DIR}/install)

install(TARGETS ${Target}
        EXPORT ${Target}Tagets
        RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX}/bin
        LIBRARY DESTINATION ${CMAKE_INSTALL_PREFIX}/lib
        ARCHIVE DESTINATION ${CMAKE_INSTALL_PREFIX}/lib
        # PUBLIC_HEADER DESTINATION ${ROOT_DIR}/interface
        )

# 安装头文件
install(DIRECTORY ${ROOT_DIR}/src/include DESTINATION ${CMAKE_INSTALL_PREFIX})

# 将目标文件可导出文件
install(EXPORT ${Target}Tagets DESTINATION ${ROOT_DIR}/cmake)

# 生成 ${Target}Config.cmake
configure_file(${ROOT_DIR}/config/${Target}Config.cmake.in ${ROOT_DIR}/cmake/${Target}Config.cmake)
install(FILES ${ROOT_DIR}/cmake/${Target}Config.cmake DESTINATION ${CMAKE_INSTALL_PREFIX}/cmake)


message(STATUS "Stop building : " ${Target} "\n")