g++ check.cpp -o check
for (( i = 1; i < 22; i++ )); do
    echo "checking data $i"
    ./check < ../data/$i.in 
done
