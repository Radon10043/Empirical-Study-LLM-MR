"""
Author: Radon
Date: 2023-12-06 15:26:45
LastEditors: Radon
LastEditTime: 2023-12-07 15:24:33
Description: Hi, say something
"""
import openai
import marko

from marko.md_renderer import MarkdownRenderer

# openai.log = "debug"
with open("api_key.txt") as f:
    openai.api_key = f.read()
openai.api_base = "https://api.chatanywhere.com.cn/v1"


def gpt_3p5_turbo(list_prompt: list):
    """向gpt-3.5-turbo发送信息, 让其识别蜕变关系并生成单元测试用例代码

    Parameters
    ----------
    list_prompt : list
        提示词列表

    Notes
    -----
    _description_
    """
    msgs = list()  # 聊天记录列表

    for prompt in list_prompt:
        # 将提示词加入列表, 以让gpt记住历史聊天内容
        msgs.append({"role": "user", "content": prompt})

        # 获取gpt的回复内容, 加入到answer中
        answer = str()
        response = openai.ChatCompletion.create(model="gpt-3.5-turbo", messages=msgs, stream=True)
        print("ChatGPT: ", end="")

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

    # 将聊天内容输出到文件
    with open("gpt3.5turbo.md", mode="w") as f:
        for msg in msgs:
            f.write("#### " + msg["role"] + "\n\n")
            f.write(msg["content"] + "\n\n")
    print("Finish!")


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


def read_prompt(prompt_path: str) -> list:
    """解析存储了提示词的文件, 并返回存有提示词内容的列表

    Parameters
    ----------
    prompt_path : str
        存储提示内容的文件路径

    Returns
    -------
    list
        村粗提示词内容的列表

    Notes
    -----
    _description_
    """
    # 由于使用render函数会默认呈现为HTML的文本, 因此构造一个MarkDown实例, 使用MarkdownRenderer, 使AST可呈现为md文本
    md_instance = marko.Markdown(renderer=MarkdownRenderer)

    # 读取markdown文件的原始内容, 存入md_text
    md_text = str()
    with open(prompt_path) as f:
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
            # 如果存在非空行节点, 加入list_prompt
            if not is_all_blank(sub_document):
                list_prompt.append(md_instance.render(sub_document).lstrip("\n"))
            sub_document.children = []

        # 如果不是标题, 将节点加入到sub_document中
        else:
            sub_document.children.append(child)

    # 为防止遗漏最后一段, 判断结尾的paragraph是否全为BlankLine, 如果不是, 加入到list_prompt中
    if not is_all_blank(sub_document):
        list_prompt.append(md_instance.render(sub_document))

    # 为了保证蜕变关系生成的数量至少有50个, 反复重复最后一个提示词, 直到list_prompt的长度到达30
    while len(list_prompt) < 30:
        list_prompt.append(list_prompt[-1])

    return list_prompt


if __name__ == "__main__":
    # TODO: args
    prompt_path = "prompt.md"

    list_prompt = read_prompt(prompt_path)
    gpt_3p5_turbo(list_prompt)
