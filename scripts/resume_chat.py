"""
Author: Radon
Date: 2024-01-02 21:07:30
LastEditors: Radon
LastEditTime: 2024-12-19 16:33:07
Description: Hi, say something
"""
import openai
import argparse, json
import random, time
import os, re
import traceback

# openai.log = "debug"
with open("api_key.txt") as f:
    openai.api_key = f.read()
with open*("api_base.txt") as f:
    openai.api_base = f.read()

def resume_chat(json_path: str, resume_cnt: int, gpt_name: str):
    """基于之前的聊天内容继续进行聊天

    Parameters
    ----------
    json_path : str
        聊天记录json文件路径
    resume_cnt : int
        继续进行聊天的最大次数
    gpt_name : str
        要使用的gpt系大模型名称
    """

    msgs = json.load(open(json_path))

    # 读取最后一次user的内容
    index = len(msgs) - 1
    while index >= 0:
        if msgs[index]["role"] == "user":
            break
        index -= 1

    # 避免非user的情况
    if index < 0:
        print("聊天记录中没有user!")
        return

    # 最后一次user的内容作为提示词
    prompt = msgs[index]["content"]

    # 继续聊天...
    while resume_cnt > 0:
        msgs.append({"role": "user", "content": prompt})

        # 随机休息几秒, 防止报错
        time.sleep(random.randint(1, 5))

        try:
            # 获取gpt的回复内容, 加入到answer中
            answer = str()
            response = openai.ChatCompletion.create(model=gpt_name, messages=msgs, stream=True)
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

            # 如果输出内容中有Metamorphic Relation 55, 跳出循环
            search_result = re.search("(Metamorphic Relation 45|MR45)", answer, flags=re.IGNORECASE)
            if not search_result is None:
                break

        except BaseException as e:
            # 如果出现了错误, 弹出刚刚加入的提示, 下标-1, 并休息一段时间后再开始
            msgs.pop()
            print("出现错误:", e)
            traceback.print_exc()

            # 随机休息一段时间后再继续
            sleep_time = random.randint(60, 600)
            while sleep_time > 0:
                sleep_time -= 1
                print("休息一下后再继续... %d秒" % sleep_time, end="\r")
                time.sleep(1)
            print()

        resume_cnt -= 1

    fn = os.path.splitext(json_path)[0] + ".update"
    print("Writing to the " + fn + ".md ... ", end="")
    with open(os.path.join(fn + ".md"), mode="w", encoding="utf-8") as f:
        for msg in msgs:
            f.write("#### " + msg["role"] + "\n\n")
            f.write(msg["content"] + "\n\n")
    print("finish!")

    # 将聊天内容同时保存至json文件
    print("Writing to the " + fn + ".json ... ", end="")
    with open(os.path.join(fn + ".json"), mode="w", encoding="utf-8") as f:
        json.dump(msgs, f, indent=4)
    print("finish!")


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="自动向大模型发送提示并输出内容至markdown文件")
    parser.add_argument("-j", "--json", required=True, help="聊天记录json文件路径")
    parser.add_argument("-c", "--count", type=int, default=50, help="继续聊天次数")
    parser.add_argument("-m", "--model", required=True, help="要使用的大模型")
    args = parser.parse_args()

    json_path = args.json
    resumt_cnt = args.count
    gpt_name = args.model

    resume_chat(json_path, resumt_cnt, gpt_name)
