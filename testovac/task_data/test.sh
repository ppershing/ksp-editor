echo "<font color='yellow'> Welcome to testing session"

SHOW_DIFF=0
if [ "$1" == "--fulllog" ]; then
    SHOW_DIFF=1
    shift
fi
echo "Test parameters I'm using now are '$*', full_log: $SHOW_DIFF </font>"

for infile in *.in; do
    echo ""
    echo "<font color='yellow'> ********* Testing $infile ******** </font>"
    base=`basename $infile .in`
    outfile=$base.out
    ./wrapper $* ./program -i$infile -o$base.tst
    if [ "$?" -ne 0 ]; then
        echo -n "<font color='red'> ****** Program ended unexpectedly "
        echo "at input $base </font>"
        exit 1
    fi;
    echo "<font color='yellow'> program exitted normally"
    echo "checking output for validity...</font>"

    if [ $SHOW_DIFF -ne 0 ]; then
        diff $base.tst $base.out > $base.diff;
        DIFFRES=$?
        cat $base.diff | sed 's/^</ <font color="red">mine:<\/font>/' \
                | sed 's/^>/ <font color="orange">correct:<\/font>/';
    else
        diff $base.tst $base.out > /dev/null
        DIFFRES=$?
    fi
    if [ "$DIFFRES" -ne 0 ]; then
        echo -n "<font color='red'> **** The output of testcase "
        echo " $base is not correct </font>"
        exit 1
    fi;
done
echo "<font color='green'> Everything seems to be OK, accepting </font>"
exit 0;
