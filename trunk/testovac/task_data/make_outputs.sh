echo "generating outputs for all inputs"
echo "compiling program"
g++ solution.cpp -W -Wall -o solution
if [ "$?" -ne 0 ]; then
    echo "problem compiling solution"
    exit 1
fi;

echo "removing all outputs"
rm *.out

for infile in *.in; do
    echo ""
    echo "generating out for $infile"
    base=`basename $infile .in`
    outfile=$base.out
    ./solution <$infile >$base.out
    if [ "$?" -ne 0 ]; then
        echo -n "Problem generating output"
        echo "at input $base"
        exit 1
    fi;
done
echo "removing compiled solution"
rm solution
echo "all done"
exit 0;
