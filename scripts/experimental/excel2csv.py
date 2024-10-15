import argparse
import os
import openpyxl

import pandas as pd
import numpy as np

from tqdm import tqdm


def save_as_csv(input_file: str):
    """将xlsx文件中的部分内容转换为csv文件

    Parameters
    ----------
    input_file : str
        输入文件路径 (xlsx文件)
    """
    # 输出目录设定为当前文件所在目录
    out_dir = os.path.dirname(__file__)

    # 将部分内容转换为csv文件
    sut_csvf = os.path.join(out_dir, "sut.csv")  # SUT相关信息
    mr_csvf = os.path.join(out_dir, "mr.csv")  # LLM生成的MR相关信息

    # 读取xlsx文件中的SUT相关信息
    df = pd.read_excel(input_file, engine="openpyxl", sheet_name="Setup", usecols="H:M", skiprows=2, nrows=37)
    df.to_csv(sut_csvf, index=False)
    print(f"{sut_csvf} is saved.")

    # 读取xlsx文件中的MR相关信息
    sut_lst = df["SUT"].tolist()
    sut_lst = ["ACMS"]
    df = pd.DataFrame()
    for sut in tqdm(sut_lst, desc="Reading MR information of original template", ncols=100):

        # 读取gpt-3.5-turbo-1106在Original模板下生成的MR信息
        tmp0 = pd.DataFrame({"SUT": [sut] * 40, "LLM": ["gpt-3.5-turbo-1106"] * 40, "Template": ["Original"] * 40})
        tmp1 = pd.read_excel(input_file, engine="openpyxl", sheet_name=sut, usecols="B", skiprows=1, nrows=40)
        tmp2 = pd.read_excel(input_file, engine="openpyxl", sheet_name=sut, usecols="D:J", skiprows=1, nrows=40)
        tmp3 = pd.read_excel(input_file, engine="openpyxl", sheet_name=sut, usecols="L:M", skiprows=1, nrows=40)
        tab = pd.concat([tmp0, tmp1, tmp2, tmp3], axis=1)
        for col in tab.columns:
            tab.rename(columns={col: str(col)}, inplace=True)
        df = pd.concat([df, tab], axis=0)

        # 读取gpt-4-1106-preview在Original模板下生成的MR信息
        tmp0 = pd.DataFrame({"SUT": [sut] * 40, "LLM": ["gpt-4-1106-preview"] * 40, "Template": ["Original"] * 40})
        tmp1 = pd.read_excel(input_file, engine="openpyxl", sheet_name=sut, usecols="B", skiprows=46, nrows=40)
        tmp2 = pd.read_excel(input_file, engine="openpyxl", sheet_name=sut, usecols="D:J", skiprows=46, nrows=40)
        tmp3 = pd.read_excel(input_file, engine="openpyxl", sheet_name=sut, usecols="L:M", skiprows=46, nrows=40)
        tab = pd.concat([tmp0, tmp1, tmp2, tmp3], axis=1)
        for col in tab.columns:
            tab.rename(columns={col: str(col)}, inplace=True)
        df = pd.concat([df, tab], axis=0)

    # 读取消融实验相关数据
    sut_lst = ["Boyer", "Bsearch2", "QuickSort", "shortest_path"]
    for sut in tqdm(sut_lst, desc="Reading MR information of Prompt-C/S/I", ncols=100):
        # 3.5, Prompt-C
        tmp0 = pd.DataFrame({"SUT": [sut] * 40, "LLM": ["gpt-3.5-turbo-1106"] * 40, "Template": ["Prompt-C"] * 40})
        tmp1 = pd.read_excel(input_file, engine="openpyxl", sheet_name=sut, usecols="P", skiprows=1, nrows=40)
        tmp2 = pd.read_excel(input_file, engine="openpyxl", sheet_name=sut, usecols="R:X", skiprows=1, nrows=40)
        tmp3 = pd.read_excel(input_file, engine="openpyxl", sheet_name=sut, usecols="Z", skiprows=1, nrows=40)
        tmp4 = pd.DataFrame({"NEW": [-1] * 40})
        tab = pd.concat([tmp0, tmp1, tmp2, tmp3, tmp4], axis=1)
        for col in tab.columns:
            tab.rename(columns={col: col.split(".")[0]}, inplace=True)
        df = pd.concat([df, tab], axis=0)

        # 3.5, Prompt-S
        tmp0 = pd.DataFrame({"SUT": [sut] * 40, "LLM": ["gpt-3.5-turbo-1106"] * 40, "Template": ["Prompt-S"] * 40})
        tmp1 = pd.read_excel(input_file, engine="openpyxl", sheet_name=sut, usecols="AC", skiprows=1, nrows=40)
        tmp2 = pd.read_excel(input_file, engine="openpyxl", sheet_name=sut, usecols="AE:AK", skiprows=1, nrows=40)
        tmp3 = pd.read_excel(input_file, engine="openpyxl", sheet_name=sut, usecols="AM", skiprows=1, nrows=40)
        tmp4 = pd.DataFrame({"NEW": [-1] * 40})
        tab = pd.concat([tmp0, tmp1, tmp2, tmp3, tmp4], axis=1)
        for col in tab.columns:
            tab.rename(columns={col: col.split(".")[0]}, inplace=True)
        df = pd.concat([df, tab], axis=0)

        # 3.5, Prompt-I
        tmp0 = pd.DataFrame({"SUT": [sut] * 40, "LLM": ["gpt-3.5-turbo-1106"] * 40, "Template": ["Prompt-I"] * 40})
        tmp1 = pd.read_excel(input_file, engine="openpyxl", sheet_name=sut, usecols="AP", skiprows=1, nrows=40)
        tmp2 = pd.read_excel(input_file, engine="openpyxl", sheet_name=sut, usecols="AR:AX", skiprows=1, nrows=40)
        tmp3 = pd.read_excel(input_file, engine="openpyxl", sheet_name=sut, usecols="AZ", skiprows=1, nrows=40)
        tmp4 = pd.DataFrame({"NEW": [-1] * 40})
        tab = pd.concat([tmp0, tmp1, tmp2, tmp3, tmp4], axis=1)
        for col in tab.columns:
            tab.rename(columns={col: col.split(".")[0]}, inplace=True)
        df = pd.concat([df, tab], axis=0)

        # 4, Prompt-C
        tmp0 = pd.DataFrame({"SUT": [sut] * 40, "LLM": ["gpt-4-1106-preview"] * 40, "Template": ["Prompt-C"] * 40})
        tmp1 = pd.read_excel(input_file, engine="openpyxl", sheet_name=sut, usecols="P", skiprows=1, nrows=40)
        tmp2 = pd.read_excel(input_file, engine="openpyxl", sheet_name=sut, usecols="R:X", skiprows=1, nrows=40)
        tmp3 = pd.read_excel(input_file, engine="openpyxl", sheet_name=sut, usecols="Z", skiprows=1, nrows=40)
        tmp4 = pd.DataFrame({"NEW": [-1] * 40})
        tab = pd.concat([tmp0, tmp1, tmp2, tmp3, tmp4], axis=1)
        for col in tab.columns:
            tab.rename(columns={col: col.split(".")[0]}, inplace=True)
        df = pd.concat([df, tab], axis=0)

        # 4, Prompt-S
        tmp0 = pd.DataFrame({"SUT": [sut] * 40, "LLM": ["gpt-4-1106-preview"] * 40, "Template": ["Prompt-C"] * 40})
        tmp1 = pd.read_excel(input_file, engine="openpyxl", sheet_name=sut, usecols="AC", skiprows=1, nrows=40)
        tmp2 = pd.read_excel(input_file, engine="openpyxl", sheet_name=sut, usecols="AE:AK", skiprows=1, nrows=40)
        tmp3 = pd.read_excel(input_file, engine="openpyxl", sheet_name=sut, usecols="AM", skiprows=1, nrows=40)
        tmp4 = pd.DataFrame({"NEW": [-1] * 40})
        tab = pd.concat([tmp0, tmp1, tmp2, tmp3, tmp4], axis=1)
        for col in tab.columns:
            tab.rename(columns={col: col.split(".")[0]}, inplace=True)
        df = pd.concat([df, tab], axis=0)

        # 4, Prompt-I
        tmp0 = pd.DataFrame({"SUT": [sut] * 40, "LLM": ["gpt-4-1106-preview"] * 40, "Template": ["Prompt-C"] * 40})
        tmp1 = pd.read_excel(input_file, engine="openpyxl", sheet_name=sut, usecols="AP", skiprows=1, nrows=40)
        tmp2 = pd.read_excel(input_file, engine="openpyxl", sheet_name=sut, usecols="AR:AX", skiprows=1, nrows=40)
        tmp3 = pd.read_excel(input_file, engine="openpyxl", sheet_name=sut, usecols="AZ", skiprows=1, nrows=40)
        tmp4 = pd.DataFrame({"NEW": [-1] * 40})
        tab = pd.concat([tmp0, tmp1, tmp2, tmp3, tmp4], axis=1)
        for col in tab.columns:
            tab.rename(columns={col: col.split(".")[0]}, inplace=True)
        df = pd.concat([df, tab], axis=0)

    # 因为是从多个sheet中读取的数据，所以需要重置索引
    df.reset_index(drop=True, inplace=True)

    # fmt:off
    df.rename(columns={
        "ID": "mr_id",
        "1": "rand_res1",
        "2": "rand_res2",
        "3": "rand_res3",
        "4": "rand_res4",
        "5": "rand_res5",
        "MANUAL": "manual_res",
        "FINAL": "is_correct",
        "TYPE": "is_legal",
        "NEW": "is_extra"
    }, inplace=True)
    # fmt:on

    # 删掉is_legal为空值的行, 此类行只是占位置用的, LLM没有生成对应ID的MR
    del_indexes = df[df["is_legal"].isnull()].index
    df.drop(del_indexes, inplace=True)

    for index, row in df.iterrows():
        if row["is_legal"] == "Illegal":
            df.at[index, "is_legal"] = 0
        else:
            df.at[index, "is_legal"] = 1

    # 将指定列的空的单元格填充为-1
    cols = ["rand_res1", "rand_res2", "rand_res3", "rand_res4", "rand_res5", "manual_res", "is_correct", "is_extra"]
    for col in cols:
        df[col] = df[col].fillna(-1).astype(int)

    # 保存为csv文件
    df.to_csv(mr_csvf, index=True)
    print(f"{mr_csvf} is saved.")


if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    parser.add_argument("--input", type=str, required=True, help="Input file (.xlsx)")
    args = parser.parse_args()

    save_as_csv(args.input)
