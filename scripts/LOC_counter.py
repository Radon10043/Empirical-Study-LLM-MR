"""
Author: Radon
Date: 2024-03-26 13:06:03
LastEditors: Radon
LastEditTime: 2024-03-26 13:09:31
Description: 用于统计目标函数及其调用的函数的LOC总和, 需要注意函数中的注释与空行的内容也被统计了, 所以结果可能会有些不准确
"""

import os
import ast
import queue
import argparse


def get_callees(root: ast.FunctionDef) -> list:
    """获取指定函数调用的所有函数名称

    Parameters
    ----------
    root : ast.FunctionDef
        指定函数的AST根节点

    Returns
    -------
    list
        该函数调用的所有函数名称
    """
    callees = list()
    q = queue.Queue()
    q.put(root)

    # 采用广序遍历的方式获取调用的函数名称
    while not q.empty():
        node = q.get()
        attrs = vars(node).keys()

        # 如果属性中有body, 证明该节点是一个复合语句, 需要将其子节点加入队列
        if "body" in attrs:
            for child in node.body:
                q.put(child)

        # 如果属性中有value, 证明该节点可能表示了函数调用, 查看调用的函数名称
        if "value" in attrs and isinstance(node.value, ast.Call):
            try:
                if "attr" in vars(node.value.func).keys():
                    callees.append(node.value.func.attr)
                else:
                    callees.append(node.value.func.id)
            except:
                pass

    return callees


def main(filepath: str, func: str) -> int:
    """获取指定文件中指定函数及其调用的函数的LOC总和

    Parameters
    ----------
    filepath : str
        文件路径
    func : str
        函数名称

    Returns
    -------
    int
        目标函数及其调用的函数的LOC总和
    """
    # 获取文件所在根目录路径
    dir = os.path.dirname(filepath)

    # 获取目录下所有的.py文件路径
    files = list()
    for file in os.listdir(dir):
        if file.endswith(".py"):
            files.append(os.path.join(dir, file))

    # 获取根目录下所有py文件中的函数和对应的AST节点
    func_dict = dict()
    for file in files:
        f = open(file, encoding="UTF-8")
        tree = ast.parse(f.read())
        f.close()
        for node in ast.walk(tree):
            if isinstance(node, ast.FunctionDef):
                func_dict[node.name] = node

    # 初始化广度优先搜索队列, 访问集合, 行数统计等变量
    q = queue.Queue()
    root = func_dict[func]
    visit = set()
    cnt = 0

    # 基于目标函数进行广序遍历, 统计目标函数和它调用的函数的LOC总和
    q.put(root)
    while not q.empty():
        node = q.get()
        if node in visit:
            continue
        visit.add(node)
        cnt += node.end_lineno - node.lineno + 1

        # 获取callee的AST节点, 加入队列
        callees = get_callees(node)
        for callee in callees:
            if callee in func_dict.keys():
                q.put(func_dict[callee])

    return cnt


if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    parser.add_argument("--filepath", type=str, help="The path of the file to be analyzed.", required=True)
    parser.add_argument("--func", type=str, help="The name of the function to be analyzed.", required=True)

    filepath = parser.parse_args().filepath
    func = parser.parse_args().func
    loc = main(filepath, func)
    print("FILE:", filepath, "\nFUNC:", func, "\nLOC:", loc, sep=" ")
