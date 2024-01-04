#!/bin/bash

main() {
    # 跑几次测试, 查看测试结果
    echo "Testing ..."
    for ((i = 1; i <= $3; i++)); do
        $CUR_DIR/build/test/$1 --gtest_filter=TrueReturn/GetRangeParamTest.$2/* >testcases.output.txt
        if [ $? -eq 0 ]; then
            echo "$2 Test $i success"
        else
            echo "$2 Test $i failed"
            break
        fi
    done
}

check() {
    # 查看对应的MR是否存在
    count=$(cat test/$1.cpp | grep "$2)" | wc -l)
    if [ $count -eq 0 ]; then
        echo "$2 not exist in $1"
        exit 1
    fi

    # 都存在的话, 通过检查
}

# $1 哪个测试
# $2 第几个MR
# $3 跑几次
CUR_DIR=$(dirname $0)
cd $CUR_DIR
check $1 $2
main $1 $2 $3
