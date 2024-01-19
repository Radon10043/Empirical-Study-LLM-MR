#!/bin/bash

main() {
    # 跑几次测试, 查看测试结果
    echo -e "# Test $2\n"
    for ((i = 1; i <= $3; i++)); do
        $CUR_DIR/venv/Scripts/python $CUR_DIR/test/$1.py -k $2"_" > testcases.output.txt 2>&1
        if [ $? -eq 0 ]; then
            echo -e "$2 Test $i success  "
        else
            echo -e "$2 Test $i failed  "
            break
        fi
    done
    echo ""

    # 查看测试结果输出行数, 如果没出现1000, 可能是哪里写错了, 需要进行检查
    count=$(cat testcases.output.txt | grep 1000 | wc -l)
    if [ $count -lt 1 ]; then
        echo -e "Oops, maybe there are something wrong when testing $2, please check it.\n"
    fi
}

check() {
    # 查看对应的MR是否存在
    count=$(cat test/$1.py | grep "$2(" | wc -l)
    if [ $count -eq 0 ]; then
        echo "$2 not exist in $1"
        exit 1
    fi

    # 都存在的话, 通过检查
}

# $1 要运行的py文件名称, 默认会去./test/下面找
# $2 MR的编号, 通常是test[x], x是数字
# $3 要运行的次数
CUR_DIR=$(dirname $0)
cd $CUR_DIR
check $1 $2
main $1 $2 $3