echo "<font color='yellow'> Welcome to testing session"
echo "Test parameters I'm using now are '$*' </font>"

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
    diff $base.tst $base.out;
    if [ "$?" -ne 0 ]; then
        echo -n "<font color='red'> **** The output of testcase "
        echo " $base is not correct </font>"
        exit 1
    fi;
done
echo "<font color='green'> Everything seems to be OK, accepting </font>"
exit 0;
