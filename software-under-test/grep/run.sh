#!/bin/bash

# $1: 哪个测试文件夹
# $2: 哪个MR
# $3: 重复几次

for ((i=1; i<=$3; i++)); do
    echo "# $2.py"
    python test/$1/$2.py > testcases.output.txt 2>&1
    ret=$?
    if [ $ret -eq 0 ]; then
        echo "$2.py Test $i success  "
    else
        echo "$2.py Test $i failed  "
        exit 1
    fi

    count=$(cat testcases.output.txt | grep "Ran 1000" | wc -l)
    if [ $count -eq 0 ]; then
        echo "Oops, maybe something wrong when testing $2.py? Please check it."
    fi

    echo ""
done