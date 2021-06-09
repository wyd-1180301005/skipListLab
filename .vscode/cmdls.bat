@REM 使用utf-8格式存取文件
chcp 65001

@echo on
echo processing cmdls.bat

@echo off
@REM 开启延时访问
setlocal EnableDelayedExpansion
@REM 选择编译选项
set CMAKE_CONFIG_TYPE=%3
@REM 运行cmake
cmake -S %1 -B %2
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
    set log_file_name=log_build.txt
    cmake --build %2 --config %3 > !log_file_name!
    echo end building:
    if !errorlevel!==0 (
        set build_success=true
    ) else (
        set build_success=false
    )

    @REM 只有在构建失败的情况下才会进行输出
    set /a has_error=0
    if !build_success!==false (
        @REM 将log输出到终端中
        echo output build log
        set dir=''
        set level=''
        set code=''
        set msg=''
        set /a count=0

        for /f "tokens=1-3,* delims=:" %%M in ('findstr /r /x  /c:".*error.*" log_build.txt') do (
            set /a has_error=1
            set /a count=!count!+1
            echo %%M:%%N:%%O: !count!
            echo %%P
        )
        for /f "tokens=1-3,* delims=:" %%M in ('findstr /r /x  /c:".*warning.*" log_build.txt') do (
            set /a has_error=1
            set /a count=!count!+1
            echo %%M:%%N:%%O: !count!
            echo %%P
        )
    )
    @REM 只有在构建成功或者只有warning没有error的情况下才会进行测试
    if !build_success!==false  (
        if !has_error! GTR 0 (
            goto END_BAT
        )
    )
    echo testing:
    cd %2
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
        @REM 将log输出到终端中
        cd Testing/Temporary
        set test_log_name=LastTest.log
        set dir=''
        set level=''
        set code=''
        set msg=''
        set /a count=0
        for /f "tokens=1-2,* delims= "  %%G in ('findstr /r /x  /c:".*error.*" !test_log_name!')  do (
            set dir=%%G
            set level=%%H
            set msg=%%I
            set /a count=!count!+1
            echo !dir! !level! "!count!"
            echo !msg!
        )
    )
)

:END_BAT

@echo on
echo end:processing cmdls.bat


       