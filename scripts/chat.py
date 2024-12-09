"""
Author: Radon
Date: 2023-12-06 15:26:45
LastEditors: Radon
LastEditTime: 2024-09-08 19:37:29
Description: Hi, say something
"""

import openai
import marko, json
import random, time
import argparse, os, re

from marko.md_renderer import MarkdownRenderer
from typing import Any

# openai.log = "debug"
with open("api_key.txt") as f:
    openai.api_key = f.read()
with open*("api_base.txt") as f:
    openai.api_base = f.read()


def get_cur_time() -> str:
    """获取当前时间

    Returns
    -------
    str
        返回当前时间, 格式为"年月日时分秒"

    Notes
    -----
    _description_
    """
    cur_time = time.strftime("%Y%m%d%H%M%S", time.localtime(time.time()))
    return cur_time


def chat_with_gpt(list_prompt: list, gpt_name: str, output_dir: str, max_chat_count: int, sut_name: str):
    """向GPT系的大模型发送信息, 让其识别蜕变关系并生成单元测试用例代码

    Parameters
    ----------
    list_prompt : list
        提示词列表
    output_dir : str
        聊天内容要输出到的目录
    max_chat_count : int
        最大聊天次数
    sut_name : str
        被测对象的名称
    gpt_name : str
        进行聊天的gpt系模型名称

    Notes
    -----
    _description_
    """
    msgs = list()  # 聊天记录列表

    i = 0
    while list_prompt[i][0] == "system":
        msgs.append({"role": "system", "content": list_prompt[i][1]})
        i += 1

    while i < max_chat_count:
        # 将提示词加入列表, 以让gpt记住历史聊天内容
        if i < len(list_prompt):
            role = list_prompt[i][0]
            prompt = list_prompt[i][1]
        else:
            role = list_prompt[-1][0]
            prompt = list_prompt[-1][1]
        msgs.append({"role": role, "content": prompt})

        # 随机休息几秒, 防止报错
        time.sleep(random.randint(1, 5))

        try:
            # 获取gpt的回复内容, 加入到answer中
            answer = str()
            response = openai.ChatCompletion.create(model=gpt_name, messages=msgs, stream=True)
            print("ChatGPT\n--------------")

            for event in response:
                if event["choices"][0]["finish_reason"] == "stop":
                    answer += "\n\n"
                    print("\n\n")
                    break
                for delta_k, delta_v in event["choices"][0]["delta"].items():
                    if delta_k == "role":
                        continue
                    print(delta_v, end="")
                    answer += delta_v

            # 将answer加入msgs, 以让gpt记住历史聊天内容
            msgs.append({"role": "assistant", "content": answer})

            # 如果输出内容中有Metamorphic Relation 45或MR45, 跳出循环
            search_result = re.search("(Metamorphic Relation 45|MR45)", answer, flags=re.IGNORECASE)
            if not search_result is None:
                break

        except BaseException as e:
            # 如果出现了错误, 弹出刚刚加入的提示, 下标-1, 并休息一段时间后再开始
            msgs.pop()
            i -= 1
            print("出现错误:", e)

            # 随机休息一段时间后再继续
            sleep_time = random.randint(60, 600)
            try:
                while sleep_time > 0:
                    sleep_time -= 1
                    print("休息一下后再继续... %d秒" % sleep_time, end="\r")
                    time.sleep(1)
            except KeyboardInterrupt:
                print("KeyboardInterrupt, exit!")
                break
            print()

        i += 1

    # 获取当前时间
    cur_time = get_cur_time()

    # 将聊天内容输出到文件
    fn_base = gpt_name + "." + sut_name + "." + cur_time

    print("Writing to the " + fn_base + ".md ... ", end="")
    with open(os.path.join(output_dir, fn_base + ".md"), mode="w", encoding="utf-8") as f:
        for msg in msgs:
            f.write("#### " + msg["role"] + "\n\n")
            f.write(msg["content"] + "\n\n")
    print("finish!")

    # 将聊天内容同时保存至json文件
    print("Writing to the " + fn_base + ".json ... ", end="")
    with open(os.path.join(output_dir, fn_base + ".json"), mode="w", encoding="utf-8") as f:
        json.dump(msgs, f, indent=4)
    print("finish!")


def is_all_blank(document: marko.block.Document) -> bool:
    """判断document的子集里是否全为空行

    Parameters
    ----------
    document : marko.block.Document
        存储了markdown内容的结点

    Returns
    -------
    bool
        document的children中是否全为BlankLine

    Notes
    -----
    _description_
    """
    b_all_blank = True
    for child in document.children:
        if child.get_type() != "BlankLine":
            b_all_blank = False
            break
    return b_all_blank


def read_prompt(template_path: str, spec_path: str, demo_path: str, **kwargs: Any) -> list:
    """读取模板文件, 规格说明文件, 已编码的初始MR文件, 并返回prompt的列表

    Parameters
    ----------
    template_path : str
        模板文件路径 (markdown)
    spec_path : str
        规格说明文件路径 (markdown)
    demo_path : str
        存储已编码MR的文件路径 (markdown)
    kwargs: Any
        其他参数

    Returns
    -------
    list
        _description_
    """
    # 由于使用render函数会默认呈现为HTML的文本, 因此构造一个MarkDown实例, 使用MarkdownRenderer, 使AST可呈现为md文本
    md_instance = marko.Markdown(renderer=MarkdownRenderer)

    # 读取template, spec, demo文件的原始内容, 组合并存入md_text
    template_text = str()
    spec_text = str()
    demo_text = str()
    with open(template_path, encoding="utf-8") as f:
        template_text = f.read()
    with open(spec_path, encoding="utf-8") as f:
        spec_text = f.read()
    with open(demo_path, encoding="utf-8") as f:
        demo_text = f.read()
    md_text = template_text.replace("[specification]", spec_text).replace("[demo]", demo_text)

    # 如果模板里有[sut_name], 将其替换为sut_name, 消融实验nospec里会用到
    md_text = md_text.replace("[sut_name]", kwargs["sut_name"])

    # 解析markdown文件
    md_ast = md_instance.parse(md_text)

    list_prompt = list()  # 存储prompt的列表
    sub_document = marko.block.Document()  # 存储markdown文件AST子节点的列表
    role = "system"  # 用于存储当前提示词的角色, 默认为系统

    # 遍历AST, 获取文本
    for child in md_ast.children:
        # 获取child类型
        child_type = child.get_type()

        # FIXME: 现在没有对markdown的注释作判断, 可能会向list_prompt中多加内容
        # 如果是标题, 根据情况决定是否要将sub_document转换为文本并加入list_prompt, 并更新角色信息
        if child_type == "Heading":

            # 判断sub_document中的节点是否都是空行的节点, 如果都是空行的节点就不加到list_prompt里了
            if not is_all_blank(sub_document):
                list_prompt.append((role, md_instance.render(sub_document).lstrip("\n")))

            # 如果存在非空行节点, 加入list_prompt
            sub_document.children = []

            # 更新角色信息
            role = child.children[0].children

        # 如果不是标题, 将节点加入到sub_document中
        else:
            sub_document.children.append(child)

    # 为防止遗漏最后一段, 判断结尾的paragraph是否全为BlankLine, 如果不是, 加入到list_prompt中
    if not is_all_blank(sub_document):
        list_prompt.append((role, md_instance.render(sub_document).lstrip("\n")))

    return list_prompt


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="自动向大模型发送提示并输出内容至markdown文件")
    parser.add_argument("--template", required=True, help="prompt模板文件路径, 需要是markdown文件.")
    parser.add_argument("--spec", required=True, help="被测对象的规格说明文件路径, 需要是markdown文件.")
    parser.add_argument("--demo", required=True, help="存有已编码的初始MR的markdown文件.")
    parser.add_argument("--model", required=True, help="要使用的大模型")
    parser.add_argument("--name", default="", help="SUT名称.")
    parser.add_argument("--count", type=int, default=50, help="最大聊天次数")
    parser.add_argument("--output", default="", help="聊天内容输出目录, 默认当前工作目录下")
    args = parser.parse_args()

    template_path = args.template
    spec_path = args.spec
    demo_path = args.demo
    max_chat_count = args.count
    model_name = args.model
    sut_name = args.name
    output_dir = args.output

    if output_dir == "":
        output_dir = os.path.dirname(__file__)

    list_prompt = read_prompt(template_path, spec_path, demo_path, sut_name=sut_name)
    chat_with_gpt(list_prompt, model_name, output_dir, max_chat_count, sut_name)
