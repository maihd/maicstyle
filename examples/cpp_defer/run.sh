EXEDIR="$(dirname -- "${BASH_SOURCE[0]}")"
OUTPATH=$EXEDIR/cpp_defer

# echo $EXEDIR

clang++ $EXEDIR/main.cpp -o $OUTPATH

$OUTPATH

rm -f $OUTPATH