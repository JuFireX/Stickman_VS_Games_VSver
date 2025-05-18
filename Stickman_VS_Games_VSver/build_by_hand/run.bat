cd ..
g++ -Wall -Wextra -g3 *.cpp -o handle_build/game.exe
if %errorlevel% neq 0 goto end
:end
