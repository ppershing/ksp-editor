echo "<font color='yellow'> <h2> Welcome to testing session </h2> </font>"

SHOW_DIFF=0
if [ "$1" == "--fulllog" ]; then
    SHOW_DIFF=1
    shift
fi
echo "<p><font color='yellow'> Test parameters I'm using now are: '$*', "
echo "full_log_enabled: $SHOW_DIFF </font></p>"

for infile in *.in; do
    echo "<p><font color='yellow'> ********* "
    echo "Testing $infile ******** </font><br>"

    base=`basename $infile .in`
    outfile=$base.out
    echo -n "<font color='yellow'> running... </font> <pre>"
    ./wrapper $* ./program -i$infile -o$base.tst
    echo "</pre>"

    if [ "$?" -ne 0 ]; then
        echo -n "<font color='red'> ****** Program ended unexpectedly "
        echo "at input $base </font>"
        exit 1
    fi;
    echo "<font color='yellow'> program exitted normally"
    echo "checking output for validity...</font><br>"

    if [ $SHOW_DIFF -ne 0 ]; then
        diff $base.tst $base.out > $base.diff;
        DIFFRES=$?
        echo "<font color='yellow'> Diff: </font><pre> "
        cat $base.diff | sed 's/</≪/' \
                | sed 's/>/≫/' \
                | sed 's/&/∝/';
        echo "</pre>";
    else
        diff $base.tst $base.out > /dev/null
        DIFFRES=$?
    fi
    if [ "$DIFFRES" -ne 0 ]; then
        echo -n "<font color='red'> **** The output of testcase "
        echo " $base is not correct </font>"
        exit 1
    fi;
    echo "<font color='green'> OK, empty diff </font>"
    echo "</p>"
done
echo "<font color='green'> Everything seems to be OK, accepting </font>"
exit 0;
