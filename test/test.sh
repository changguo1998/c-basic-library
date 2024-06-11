INC="$(pwd)/../include"
SRC="$(pwd)/../src"

echo $INC
echo $SRC

gcc -c $SRC/DateTime.c -o DateTime.a -I $INC
gcc -c $SRC/test.c -o test.a -I $INC
gcc DateTime.a test.a -o test.exe
rm DateTime.a test.a
./test.exe
