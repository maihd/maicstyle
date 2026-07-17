EXEDIR="$(dirname -- "${BASH_SOURCE[0]}")"
OUTPATH=$EXEDIR/cpp_defer_2

# echo $EXEDIR

clang++ $EXEDIR/main.cpp -o $OUTPATH -fno-exceptions -fno-unwind-tables -fno-rtti -std=c++11

$OUTPATH

rm -f $OUTPATH