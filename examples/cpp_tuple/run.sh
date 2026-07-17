EXEDIR="$(dirname -- "${BASH_SOURCE[0]}")"
OUTPATH=$EXEDIR/tuple

# echo $EXEDIR

clang++ $EXEDIR/main.cpp -o $OUTPATH -fno-exceptions -fno-unwind-tables -fno-rtti -std=c++17

$OUTPATH

rm -f $OUTPATH