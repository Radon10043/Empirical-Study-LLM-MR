"""
Author: Radon
Date: 2024-01-11 19:31:12
LastEditors: Radon
LastEditTime: 2024-09-09 15:40:52
Description: 从md文件中提取代码片段
"""
import argparse, os, marko

from marko.md_renderer import MarkdownRenderer


def extract(md_file: str, out_dir: str):
    # 使用MarkdownRenderer构造一个MarkDown实例
    md_instance = marko.Markdown(renderer=MarkdownRenderer)

    # 读取markdown文件原始内容, 存入md_text
    md_text = str()
    with open(md_file, mode="r", encoding="utf-8") as f:
        md_text = f.read()

    # 解析markdown文件
    md_ast = md_instance.parse(md_text)

    # 代码文件路径
    code_file = os.path.basename(md_file)
    code_file = os.path.splitext(md_file)[0] + ".code.txt"
    code_file = os.path.join(out_dir, code_file)
    f = open(code_file, mode="w", encoding="utf-8")

    # 遍历AST, 获取代码片段, 写入文件
    for child in md_ast.children:
        child_type = child.get_type()
        if child_type == "FencedCode":
            code_list = md_instance.render(child).split("\n")
            code_list.pop(0)  # 去掉第一行的```xxx
            code_list.pop(-2)  # 去掉最后的```
            code_snippet = "\n".join(code_list)  # 合成代码片段
            f.write(code_snippet)

    f.close()
    print(f"{code_file} finish!")


def check_valid(args: argparse.Namespace) -> bool:
    """检查输入参数是否合法

    Parameters
    ----------
    args : argparse.Namespace
        命令行参数

    Returns
    -------
    bool
        输入参数是否合法
    """
    for file in args.input:
        if not os.path.exists(file):
            print(f"{file}不存在")
            return False
        if not file.endswith(".md"):
            print(f"{file}不是md文件")
            return False
    return True


if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    parser.add_argument("-i", "--input", nargs="*", type=str, required=True, help="markdown文件, 可输入多个")
    parser.add_argument("-o", "--outdir", type=str, required=False, help="输出文件夹")
    args = parser.parse_args()

    # 检查命令行参数是否合法
    if not check_valid(args):
        exit(1)

    # 遍历所有md文件, 提取代码片段
    for md_file in args.input:
        # 如果没有指定输出文件夹, 则默认为md文件所在文件夹
        out_dir = args.outdir
        if out_dir is None:
            out_dir = os.path.dirname(md_file)

        # 提取代码片段
        extract(md_file, out_dir)
