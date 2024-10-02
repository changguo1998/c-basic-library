INC="$(pwd)/../include"
SRC="$(pwd)/../src"

echo $INC
echo $SRC

gcc -c $SRC/DateTime.c -o DateTime.a -I $INC
gcc -c $SRC/test_DateTime.c -o test_DateTime.a -I $INC
gcc DateTime.a test_DateTime.a -o test_DateTime.exe
rm DateTime.a test_DateTime.a
./test_DateTime.exe
