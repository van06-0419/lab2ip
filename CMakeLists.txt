cmake_minimum_required(VERSION 3.10)
project(ip_filter_project)

# 设置C++14标准（保持不变）
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# -------------------------- 优化GTest下载与配置 --------------------------
include(FetchContent)
# 增加下载超时（300秒），避免网络慢导致下载失败
set(FETCHCONTENT_DOWNLOAD_TIMEOUT 300)

FetchContent_Declare(
  googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
  DOWNLOAD_EXTRACT_TIMESTAMP TRUE  # 解决CMP0135警告
)

# 显式配置：启用GTest目标生成（部分版本需手动开启）
set(INSTALL_GTEST OFF CACHE BOOL "" FORCE)  # 不安装GTest到系统，仅项目内使用
set(BUILD_GMOCK OFF CACHE BOOL "" FORCE)    # 仅构建GTest（无需GMock）
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)  # Windows运行时库兼容

# 强制重新下载（清除旧缓存干扰）
FetchContent_GetProperties(googletest)
if(NOT googletest_POPULATED)
  FetchContent_Populate(googletest)  # 手动触发下载和构建
  add_subdirectory(${googletest_SOURCE_DIR} ${googletest_BINARY_DIR} EXCLUDE_FROM_ALL)
endif()

# 包含项目自身头文件目录（保持不变）
include_directories(include)

# 构建主程序（保持不变）
add_executable(ip_filter
    src/main.cpp
    src/ip_filter.cpp
)

# -------------------------- 构建测试程序（兼容目标名称） --------------------------
add_executable(ip_filter_test
    test/ip_filter_test.cpp
    src/ip_filter.cpp  # 复用核心逻辑
)

# 链接GTest：优先使用GTest::GTest，若不存在则用gtest（兼容不同版本）
if(TARGET GTest::GTest AND TARGET GTest::Main)
    target_link_libraries(ip_filter_test PRIVATE GTest::GTest GTest::Main)
else()
    # 兼容旧目标名称（gtest/gtest_main）
    target_link_libraries(ip_filter_test PRIVATE gtest gtest_main)
endif()

# 确保测试程序能找到GTest头文件（部分场景需手动指定）
target_include_directories(ip_filter_test PRIVATE
    ${googletest_SOURCE_DIR}/googletest/include
)