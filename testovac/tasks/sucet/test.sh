echo "Test parameters: $*"

for infile in *.in; do
    echo ""
    echo "********* Testing $infile ********"
    base=`basename $infile .in`
    outfile=$base.out
    ./wrapper $* ./program -i$infile -o$base.tst
    if [ "$?" -ne 0 ]; then
        echo ">>>> Program ended unexpectedly at case $base"
        exit 1
    fi;
    diff $base.tst $base.out;
    if [ "$?" -ne 0 ]; then
        echo ">>>> The output of case $base is not correct"
        exit 1
    fi;
done
exit 0;
