"""
Author: Radon
Date: 2023-12-06 15:26:45
LastEditors: Radon
LastEditTime: 2023-12-07 14:06:34
Description: Hi, say something
"""
import openai
import marko

from marko.md_renderer import MarkdownRenderer

# openai.log = "debug"
openai.api_key = ""
openai.api_base = "https://api.chatanywhere.com.cn/v1"


def main():
    """向ChatGPT发送信息并进行聊天"""
    msgs = list()  # 提问列表
    turn = 0  # 当前是第几个聊天
    max_turn = 30  # 最大聊天次数

    while turn < max_turn:
        # 将提问内容加入列表, 以让AI记住历史聊天内容
        print("(%d/%d)请输入内容:" % (turn + 1, max_turn), end="")
        question = input()
        msgs.append({"role": "user", "content": question})

        try:
            response = openai.ChatCompletion.create(model="gpt-3.5-turbo", messages=msgs, stream=True)
            print("ChatGPT: ", end="")
            for event in response:
                if event["choices"][0]["finish_reason"] == "stop":
                    print("\n\n")
                    break
                for delta_k, delta_v in event["choices"][0]["delta"].items():
                    if delta_k == "role":
                        continue
                    print(delta_v, end="")
            turn += 1
        except BaseException as e:
            print("Openai API 出现异常: ", e)


def read_prompt():
    # 由于使用render函数会默认呈现为HTML的文本, 因此构造一个MarkDown实例, 使用MarkdownRenderer, 使AST可呈现为md文本
    md_instance = marko.Markdown(renderer=MarkdownRenderer)

    # 读取markdown文件的原始内容, 存入md_text
    md_text = str()
    with open("prompt.md") as f:
        md_text = f.read()

    # 解析markdown文件
    md_ast = md_instance.parse(md_text)

    list_prompt = list()  # 存储prompt的列表
    sub_document = marko.block.Document()  # 存储markdown文件AST子节点的列表

    # 遍历AST, 获取文本
    for child in md_ast.children:
        # 获取child类型
        child_type = child.get_type()

        # FIXME: 现在没有对markdown的注释作判断, 可能会向list_prompt中多加内容
        # 如果是标题, 根据情况决定是否要将sub_document转换为文本并加入list_prompt
        if child_type == "Heading":

            # 判断sub_document中的节点是否都是空行的节点, 如果都是空行的节点就不加到list_prompt里了
            b_all_blank = True
            for sub_child in sub_document.children:
                if sub_child.get_type() != "BlankLine":
                    b_all_blank = False
                    break

            # 如果存在非空行节点, 加入list_prompt
            if not b_all_blank:
                list_prompt.append(md_instance.render(sub_document))

            # 清空sub_document
            sub_document.children = []

        # 如果不是标题, 将节点加入到sub_document中
        else:
            sub_document.children.append(child)

    with open("tmp.txt", mode="w") as f:
        for text in list_prompt:
            f.write(text)
            f.write("--------------------\n\n")

    print("Please check.")


if __name__ == "__main__":
    read_prompt()
    # main()
