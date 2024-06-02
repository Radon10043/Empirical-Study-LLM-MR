import openai
import marko, json
import random, time
import argparse, os, re

from marko.md_renderer import MarkdownRenderer
from typing import Any

# openai.log = "debug"
with open("api_key.txt") as f:
    openai.api_key = f.read()
openai.api_base = "https://api.chatanywhere.com.cn/v1"


def main(sut_name: str, spec_path: str, input_dir: str, output_dir: str, model: str):
    # 获取所有要判断的MRs, 存储至列表
    mr_list = list()
    for root, dirs, files in os.walk(input_dir):
        for file in files:
            with open(os.path.join(root, file), "r", encoding="utf-8") as f:
                mr_list.append(f.read())

    # 获取规格说明
    spec = str()
    with open(spec_path, "r", encoding="utf-8") as f:
        spec = f.read()

    # 获取prompt模板, 将模板与规格说明进行组合, 生成prompt
    prompt_path = os.path.join(os.path.dirname(__file__), "prompt.md")
    prompt = str()
    with open(prompt_path, "r", encoding="utf-8") as f:
        prompt = f.read()
    prompt.replace("[specification]", spec)

    # 开始判断MRs的正确性和类别, 返回对应的结果
    msgs = list()
    msgs.append({"role": "system", "content": prompt})
    for mr in mr_list:
        msgs.append({"role": "user", "content": mr})

        # 获取LLM的回复
        response = openai.ChatCompletion.create(model=model, messages=msgs, stream=True)

        # 流式输出LLM的回复
        for event in response:
            if event["choices"][0]["finish_reason"] == "stop":
                break
            for delta_k, delta_v in event["choices"][0]["delta"].items():
                print(delta_v, end="")

    # 将结果保存至指定路径
    pass


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="通过大模型判断MR是否正确")
    parser.add_argument("--name", type=str, help="被测对象的名称", required=True)
    parser.add_argument("--spec", type=str, help="被测对象的规格说明文件路径", required=True)
    parser.add_argument("--input", type=str, help="存放蜕变关系的根目录", required=True)
    parser.add_argument("--output", type=str, default=os.path.dirname(__file__), help="输出文件路径")
    parser.add_argument("--model", type=str, default="gpt-4o", help="使用的模型名称")
    args = parser.parse_args()

    main(args.name, args.spec, args.input, args.output, args.model)
