@ECHO OFF

REM Constant definition.
SET PROGRAM_FILE_NAME=program

REM The directory containing this file.
SET EXDIR=%~dp0

REM Clear screen.
CLS

REM Check if source file exists?
IF NOT EXIST %EXDIR%%PROGRAM_FILE_NAME%.cpp (
  ECHO ERROR: ^'%PROGRAM_FILE_NAME%.cpp^' not found.
  GOTO ENDEX
)

REM Compile source file.
ECHO ^-^> g++ %EXDIR%%PROGRAM_FILE_NAME%.cpp -o %EXDIR%%PROGRAM_FILE_NAME%.exe
g++ %EXDIR%%PROGRAM_FILE_NAME%.cpp -o %EXDIR%%PROGRAM_FILE_NAME%.exe

REM Check if executable file exists?
IF NOT EXIST %EXDIR%%PROGRAM_FILE_NAME%.exe (
  ECHO ERROR: ^'%PROGRAM_FILE_NAME%.exe^' not found.
  GOTO ENDEX
)

REM Clear screen.
CLS

REM Run executable file.
%EXDIR%%PROGRAM_FILE_NAME%.exe

REM Remove executable file.
DEL %EXDIR%%PROGRAM_FILE_NAME%.exe

REM Clear screen.
CLS

:ENDEX
exit /b 0
