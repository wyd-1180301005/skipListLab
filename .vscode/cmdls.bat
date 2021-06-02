@echo on
@REM echo processing cmdls.bat

@echo off
@REM 开启延时访问
setlocal EnableDelayedExpansion
@REM 运行cmake
cmake -S skipListLab -B skipLabBuild
set cmake_success=false
set build_success=false
set ctest_success=false
if !errorlevel!==0 (
    set cmake_success=true
) else (
    set  cmake_success=false
)
@REM 如果第一步cmake成功,则进行构建
if !cmake_success!==true (
    echo building:
    cmake --build skipLabBuild
    if !errorlevel!==0 (
        set build_success=true
    ) else (
        set build_success=false
    )
    @REM 只有在构建成功的情况下才会进行测试
    if !build_success!==true (
        echo testing:
        cd ".\skipLabBuild\"
        ctest
        if !errorlevel!==0 (
            echo test_success
            set ctest_success=true
        ) else (
            echo test_fail
            set ctest_success=false
        )
        @REM 只有在ctest出现错误的情况下才会进行错误报告的打印
        if !ctest_success!==false (
            echo evaluating:
            type Testing\\Temporary\\LastTest.log
        )
    )
)

@REM @echo on
@REM echo end:processing cmdls.bat

