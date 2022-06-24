g++ gen.cpp -o gen
g++ std.cpp -o std
for (( i = 22; i < 43; i++ )); do
    echo "generating data $i"
    ./gen > ../data/$i.in
    ./std < ../data/$i.in > ../data/$i.ans
done
