@echo off

if [%1]==[] (set /A numLoop = 100) else (set /A numLoop = %1)
if [%2]==[] (set /A doComp = 1) else (set /A doComp = %2)

if %doComp% equ 1 (
    echo Compiling main, GenTemplate, solution_slow ...

    g++ -std=c++17 GenTemplate.cc -o GenTemplate
    g++ -std=c++17 main.cc -o main
    g++ -std=c++17 solution_slow.cc -o solution_slow

    echo Done compiling.
)

set "diff_found="

for /l %%x in (1, 1, %numLoop%) do (
    echo %%x
    GenTemplate > input.in
    main < input.in > output.out 
    solution_slow < input.in > output2.out

    rem add \f after "fc" to ignore trailing whitespaces and to convert
    rem multiple whitespaces into one space
    fc output.out output2.out > diagnostics
    if errorlevel 1 (
        set "diff_found=y"
        goto :break
    )
)

:break

if defined diff_found (
    echo A difference has been found.
    echo Input: 
    type input.in
    echo.
    echo.

    echo Output:
    type output.out
    echo.

    echo Expected:
    type output2.out
    echo.
) else (
    echo All Tests Passed 
)

del input.in
del output.out
del output2.out