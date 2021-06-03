@REM 使用utf-8格式存取文件
chcp 65001

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
    cls
    echo building:
    set log_file_name=log_build.txt
    cmake --build skipLabBuild > !log_file_name!
    if !errorlevel!==0 (
        set build_success=true
    ) else (
        set build_success=false
    )
    @REM 只有在构建成功的情况下才会进行测试
    if !build_success!==true (
        cls
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
            pause
            cls
        )
    ) else (
    cls
    @REM 将log输出到终端中
    set dir=''
    set level=''
    set code=''
    set msg=''
    set /a count=0
    for /f "tokens=1-3,* delims= "  %%G in ('findstr /r /x  /c:".*error.*" log_build.txt')  do (
        set dir=%%G
        set level=%%H
        set code=%%I
        set msg=%%J
        set /a count=!count!+1
        echo !dir! !level! !count!
        echo !code! !msg!
    )
    set /a count=0
    for /f "tokens=1-3,* delims= "  %%G in ('findstr /r /x  /c:".*warning.*" log_build.txt')  do (
        set dir=%%G
        set level=%%H
        set code=%%I
        set msg=%%J
        set /a count=!count!+1
        echo !dir! !level! !count!
        echo !code! !msg!
    )
    pause
    cls
    )
)

@echo on
echo end:processing cmdls.bat

