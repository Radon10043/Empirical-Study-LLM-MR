import argparse
import os
import openpyxl

import pandas as pd
import seaborn as sns
import matplotlib.pyplot as plt
import matplotlib.gridspec as gridspec

from matplotlib import rcParams

openpyxl.reader.excel.warnings.simplefilter(action="ignore")

# ========== GLOBAL VARIABLES ==========
LOG_PATH = os.path.join(os.path.dirname(__file__), "debug.log")
# ======================================

# ============ PREPROCESSING ===========
if os.path.exists(LOG_PATH):
    os.remove(LOG_PATH)
# ======================================


def draw_legal_plots(excel_path: str, mr_sheet: str, out_dir: str):
    """画Legal Rate的折线图

    Parameters
    ----------
    excel_path : str
        EXCEL文件路径
    mr_sheet : str
        存储MR信息的工作表名称
    out_dir : str
        输出目录
    """
    # 读取数据
    df = pd.read_excel(excel_path, engine="openpyxl", sheet_name=mr_sheet)
    df = df[df["TEMPLATE"] == "Original"]

    # 计算Legal Rate
    plot_data = list()
    llms = df["LLM"].unique()
    suts = df["SUT"].unique()
    for llm in llms:
        for sut in suts:
            num_MRCs = df[(df["LLM"] == llm) & (df["SUT"] == sut)].shape[0]
            num_LMRCs = df[(df["LLM"] == llm) & (df["SUT"] == sut) & (df["TYPE"] != "Illegal")].shape[0]
            plot_data.append({"LLM": llm, "SUT": sut, "Legal Rate": num_LMRCs / num_MRCs * 100})

    # 整理要画图的数据, 数据按照LLM升序, Legal Rate降序排列
    plot_df = pd.DataFrame(plot_data)
    plot_df = plot_df.sort_values(by=["LLM", "Legal Rate"], ascending=[True, False])

    # 输出每个LLM的最低, 最高和总体合法率到日志文件
    with open(LOG_PATH, "a") as f:
        f.write("Messages from draw_legal_plots():\n")
        for llm in llms:
            num_all_MRCs = df[df["LLM"] == llm].shape[0]
            num_all_LMRCs = df[(df["LLM"] == llm) & (df["TYPE"] != "Illegal")].shape[0]
            f.write("%45s : %6s%%\n" % ("Lowest legal rate of " + llm, str(plot_df[plot_df["LLM"] == llm].tail(1)["Legal Rate"].values[0])))
            f.write("%45s : %6s%%\n" % ("Highest legal rate of " + llm, str(plot_df[plot_df["LLM"] == llm].head(1)["Legal Rate"].values[0])))
            f.write("%45s : %6.2f%%\n" % ("Overall legal rate of " + llm, round(num_all_LMRCs / num_all_MRCs * 100, 2)))
        f.write("\n\n")

    # 画折线图
    custom_palette = ["#3a86ff", "#808b96"]
    custom_markers = {"gpt-3.5-turbo-1106": "o", "gpt-4-1106-preview": "s"}
    custom_dashes = [(1, 0), (1, 0)]
    plt.figure(figsize=(15, 3))
    sns.lineplot(data=plot_df, x="SUT", y="Legal Rate", hue="LLM", style="LLM", markers=custom_markers, dashes=custom_dashes, palette=custom_palette)
    plt.xlabel("")
    plt.ylabel("$LR$ (\%)")
    plt.xticks(rotation=45, ha="right")
    plt.yticks(range(40, 101, 10))
    plt.tight_layout()

    legend = plt.legend(loc="lower left", labelspacing=0.1)
    for text in legend.get_texts():
        text.set_text(r"\textit{" + text.get_text() + r"}")

    # 保存图片
    plt.savefig(os.path.join(out_dir, "Legal_Rate.pdf"))
    print("Legal Rate plots saved.")


def draw_correct_plots(excel_path: str, mr_sheet: str, out_dir: str):
    """画Correct Rate的折线图

    Parameters
    ----------
    excel_path : str
        EXCEL文件路径
    mr_sheet : str
        存储MR信息的工作表名称
    out_dir : str
        输出目录
    """
    # 读取数据
    df = pd.read_excel(excel_path, engine="openpyxl", sheet_name=mr_sheet)
    df = df[df["TEMPLATE"] == "Original"]

    # 计算Correct Rate
    plot_data = list()
    llms = df["LLM"].unique()
    suts = df["SUT"].unique()
    for llm in llms:
        for sut in suts:
            num_MRCs = df[(df["LLM"] == llm) & (df["SUT"] == sut)].shape[0]
            num_CMRCs = df[(df["LLM"] == llm) & (df["SUT"] == sut) & (df["CORRECT"] == 1.0)].shape[0]
            plot_data.append({"LLM": llm, "SUT": sut, "Correct Rate": num_CMRCs / num_MRCs * 100})

    # 整理要画图的数据, 数据按照LLM升序, Correct Rate降序排列
    plot_df = pd.DataFrame(plot_data)
    plot_df = plot_df.sort_values(by=["LLM", "Correct Rate"], ascending=[True, False])

    # 输出每个LLM的最低, 最高和总体正确率到日志文件
    with open(LOG_PATH, "a") as f:
        f.write("Messages from draw_correct_plots():\n")
        for llm in llms:
            num_all_MRCs = df[df["LLM"] == llm].shape[0]
            num_all_CMRCs = df[(df["LLM"] == llm) & (df["CORRECT"] == 1.0)].shape[0]
            f.write("%45s : %6s%%\n" % ("Lowest correct rate of " + llm, str(plot_df[plot_df["LLM"] == llm].tail(1)["Correct Rate"].values[0])))
            f.write("%45s : %6s%%\n" % ("Highest correct rate of " + llm, str(plot_df[plot_df["LLM"] == llm].head(1)["Correct Rate"].values[0])))
            f.write("%45s : %6.2f%%\n" % ("Overall correct rate of " + llm, round(num_all_CMRCs / num_all_MRCs * 100, 2)))
        f.write("\n\n")

    # 画折线图
    custom_palette = ["#3a86ff", "#808b96"]
    custom_markers = {"gpt-3.5-turbo-1106": "o", "gpt-4-1106-preview": "s"}
    custom_dashes = [(1, 0), (1, 0)]
    plt.figure(figsize=(15, 3))
    sns.lineplot(data=plot_df, x="SUT", y="Correct Rate", hue="LLM", style="LLM", markers=custom_markers, dashes=custom_dashes, palette=custom_palette)
    plt.xlabel("")
    plt.ylabel("$CR$ (\%)")
    plt.xticks(rotation=45, ha="right")
    plt.yticks(range(0, 91, 10))
    plt.tight_layout()

    legend = plt.legend(loc="upper right", labelspacing=0.1)
    for text in legend.get_texts():
        text.set_text(r"\textit{" + text.get_text() + r"}")

    # 保存图片
    plt.savefig(os.path.join(out_dir, "Correct_Rate.pdf"))
    print("Correct Rate plots saved.")


def draw_innova_plots(excel_path: str, mr_sheet: str, out_dir: str):
    """画Innovative Rate的柱状图

    Parameters
    ----------
    excel_path : str
        EXCEL文件路径
    mr_sheet : str
        存储MR信息的工作表名称
    out_dir : str
        输出目录
    """
    df = pd.read_excel(excel_path, engine="openpyxl", sheet_name=mr_sheet)
    df = df[df["TEMPLATE"] == "Original"]

    # 计算Innovative Rate
    plot_data = list()
    llms = df["LLM"].unique()
    suts = df["SUT"].unique()
    for llm in llms:
        for sut in suts:
            num_MRCs = df[(df["LLM"] == llm) & (df["SUT"] == sut)].shape[0]
            num_EMRCs = df[(df["LLM"] == llm) & (df["SUT"] == sut) & (df["NEW"] == 1.0)].shape[0]
            plot_data.append({"LLM": llm, "SUT": sut, "Innovative Rate": num_EMRCs / num_MRCs * 100})

    # 整理要画图的数据, 数据按照LLM升序, Innovative Rate降序排列
    plot_df = pd.DataFrame(plot_data)
    plot_df = plot_df.sort_values(by=["LLM", "Innovative Rate"], ascending=[True, False])

    # 输出每个LLM的最低, 最高和总体创新率到日志文件
    with open(LOG_PATH, "a") as f:
        f.write("Messages from draw_innova_plots():\n")
        for llm in llms:
            num_all_MRCs = df[df["LLM"] == llm].shape[0]
            num_all_EMRCs = df[(df["LLM"] == llm) & (df["NEW"] == 1.0)].shape[0]
            f.write("%45s : %6s%%\n" % ("Lowest innovative rate of " + llm, str(plot_df[plot_df["LLM"] == llm].tail(1)["Innovative Rate"].values[0])))
            f.write("%45s : %6s%%\n" % ("Highest innovative rate of " + llm, str(plot_df[plot_df["LLM"] == llm].head(1)["Innovative Rate"].values[0])))
            f.write("%45s : %6.2f%%\n" % ("Overall innovative rate of " + llm, round(num_all_EMRCs / num_all_MRCs * 100, 2)))
        f.write("\n\n")

    # 画柱状图
    custom_palette = ["#000000", "#7f7f7f"]
    plt.figure(figsize=(15, 3))
    sns.barplot(data=plot_df, x="SUT", y="Innovative Rate", hue="LLM", palette=custom_palette)
    plt.xlabel("")
    plt.xticks(rotation=45, ha="right")
    plt.ylabel("$IR$ (\%)")
    plt.yticks(range(0, 81, 20))
    legend = plt.legend()
    plt.tight_layout()

    # 将legend里的字体调整为斜体
    for text in legend.get_texts():
        text.set_text(r"\textit{" + text.get_text() + r"}")

    # 保存图片
    plt.savefig(os.path.join(out_dir, "Innovative_Rate.pdf"))
    print("Innovative Rate plots saved.")


def draw_char_plots(excel_path: str, mr_sheet: str, sut_sheet: str, out_dir: str):
    """根据SUT的特征和LLM为其生成MR的合法率和准确率, 画盒图

    Parameters
    ----------
    excel_path : str
        EXCEL文件路径
    mr_sheet : str
        存储MR信息的信息所在的工作表名称
    sut_sheet : str
        存储sut信息的工作表名称
    out_dir : str
        输出目录
    """
    # 读取SUT信息
    sut_df = pd.read_excel(excel_path, engine="openpyxl", sheet_name=sut_sheet)

    # 读取MR信息
    mr_df = pd.read_excel(excel_path, engine="openpyxl", sheet_name=mr_sheet)
    mr_df = mr_df[mr_df["TEMPLATE"] == "Original"]

    llms = mr_df["LLM"].unique()
    suts = mr_df["SUT"].unique()
    metrics = ["Legal Rate", "Correct Rate"]

    # 根据LLM和SUT特征对所有的合法率和正确率进行分组
    plot_data = list()
    for llm in llms:
        for sut in suts:
            char = sut_df[sut_df["SUT"] == sut]["CHAR"].values[0]
            total_MRCs = mr_df[(mr_df["LLM"] == llm) & (mr_df["SUT"] == sut)].shape[0]
            legal_MRCs = mr_df[(mr_df["LLM"] == llm) & (mr_df["SUT"] == sut) & (mr_df["TYPE"] != "Illegal")].shape[0]
            correct_MRCs = mr_df[(mr_df["LLM"] == llm) & (mr_df["SUT"] == sut) & (mr_df["CORRECT"] == 1.0)].shape[0]
            plot_data.append({"LLM": llm, "SUT": sut, "CHAR": char, "Legal Rate": legal_MRCs / total_MRCs * 100, "Correct Rate": correct_MRCs / total_MRCs * 100})

    # 将数据转换为Dataframe格式
    plot_df = pd.DataFrame(plot_data)

    # 输出不同LLM在不同特征下的平均合法率和正确率到日志文件
    with open(LOG_PATH, "a") as f:
        f.write("Messages from draw_char_plots():\n")
        for llm in llms:
            for char in plot_df["CHAR"].unique():
                avg_legal_rate = plot_df[(plot_df["LLM"] == llm) & (plot_df["CHAR"] == char)]["Legal Rate"].mean()
                avg_correct_rate = plot_df[(plot_df["LLM"] == llm) & (plot_df["CHAR"] == char)]["Correct Rate"].mean()
                f.write("%55s : %6.2f%%\n" % ("Average legal rate of " + llm + " with " + char, round(avg_legal_rate, 2)))
                f.write("%55s : %6.2f%%\n" % ("Average correct rate of " + llm + " with " + char, round(avg_correct_rate, 2)))
        f.write("\n\n")

    # 画合法率和正确率的盒图
    rcParams["font.size"] = 16
    fig = plt.figure(figsize=(8, 3))
    gs = gridspec.GridSpec(1, len(llms) * len(metrics), figure=fig, left=0.07, bottom=0.25, right=0.95, top=0.95, wspace=0.7)
    for i, metric in enumerate(metrics):
        for j, llm in enumerate(llms):
            ax = fig.add_subplot(gs[i * len(metrics) + j])
            sns.boxplot(data=plot_df[plot_df["LLM"] == llm], x="CHAR", y=metric, hue="CHAR", showmeans=True, meanprops={"marker": "x", "markeredgecolor": "black"}, palette=["#FFFFFF", "#FFFFFF"], linecolor="black", ax=ax)
            sns.despine()
            ax.set_xlabel(r"\textit{" + llm + r"}")
            ax.set_xticklabels(ax.get_xticklabels(), rotation=15, ha="right")
            ax.set_ylabel("$LR$ (\%)" if metric == "Legal Rate" else "$CR$ (\%)")
            ax.set_ylim(0, 101)
            ax.yaxis.labelpad = -7
    rcParams["font.size"] = 12

    # 保存图片
    plt.tight_layout()
    plt.savefig(os.path.join(out_dir, "Characteristics.pdf"))
    print("Characteristics plots saved.")


def draw_freq_plots(excel_path: str, mr_sheet: str, sut_sheet: str, out_dir: str):
    """根据SUT的特征和LLM为其生成MR的合法率和准确率, 画盒图

    Parameters
    ----------
    excel_path : str
        EXCEL文件路径
    mr_sheet : str
        存储MR信息所在的工作表名称
    sut_sheet : str
        存储sut信息的工作表
    out_dir : str
        输出目录
    """
    # 读取SUT信息
    sut_df = pd.read_excel(excel_path, engine="openpyxl", sheet_name=sut_sheet)

    # 读取MR信息
    mr_df = pd.read_excel(excel_path, engine="openpyxl", sheet_name=mr_sheet)
    mr_df = mr_df[mr_df["TEMPLATE"] == "Original"]

    llms = mr_df["LLM"].unique()
    suts = mr_df["SUT"].unique()
    metrics = ["Legal Rate", "Correct Rate"]

    # 根据LLM和SUT使用频率对所有的合法率和正确率进行分组
    plot_data = list()
    for llm in llms:
        for sut in suts:
            freq = sut_df[sut_df["SUT"] == sut]["FREQ"].values[0]
            total_MRCs = mr_df[(mr_df["LLM"] == llm) & (mr_df["SUT"] == sut)].shape[0]
            legal_MRCs = mr_df[(mr_df["LLM"] == llm) & (mr_df["SUT"] == sut) & (mr_df["TYPE"] != "Illegal")].shape[0]
            correct_MRCs = mr_df[(mr_df["LLM"] == llm) & (mr_df["SUT"] == sut) & (mr_df["CORRECT"] == 1.0)].shape[0]
            plot_data.append({"LLM": llm, "SUT": sut, "FREQ": freq, "Legal Rate": legal_MRCs / total_MRCs * 100, "Correct Rate": correct_MRCs / total_MRCs * 100})

    # 将数据转换为Dataframe格式
    plot_df = pd.DataFrame(plot_data)

    # 输出不同LLM在不同频率下的平均合法率和正确率到日志文件
    with open(LOG_PATH, "a") as f:
        f.write("Messages from draw_freq_plots():\n")
        for llm in llms:
            for freq in plot_df["FREQ"].unique():
                avg_legal_rate = plot_df[(plot_df["LLM"] == llm) & (plot_df["FREQ"] == freq)]["Legal Rate"].mean()
                avg_correct_rate = plot_df[(plot_df["LLM"] == llm) & (plot_df["FREQ"] == freq)]["Correct Rate"].mean()
                f.write("%55s : %6.2f%%\n" % ("Average legal rate of " + llm + " with " + freq, round(avg_legal_rate, 2)))
                f.write("%55s : %6.2f%%\n" % ("Average correct rate of " + llm + " with " + freq, round(avg_correct_rate, 2)))
        f.write("\n\n")

    # 画合法率和正确率的盒图
    rcParams["font.size"] = 16
    fig = plt.figure(figsize=(8, 3))
    gs = gridspec.GridSpec(1, len(llms) * len(metrics), figure=fig, left=0.07, bottom=0.2, right=0.95, top=0.95, wspace=0.7)
    for i, metric in enumerate(metrics):
        for j, llm in enumerate(llms):
            ax = fig.add_subplot(gs[i * len(metrics) + j])
            sns.boxplot(data=plot_df[plot_df["LLM"] == llm], x="FREQ", y=metric, hue="FREQ", showmeans=True, meanprops={"marker": "x", "markeredgecolor": "black"}, palette=["#FFFFFF", "#FFFFFF"], linecolor="black", ax=ax)
            sns.despine()
            ax.set_xlabel(r"\textit{" + llm + r"}")
            ax.set_ylabel("$LR$ (\%)" if metric == "Legal Rate" else "$CR$ (\%)")
            ax.set_ylim(0, 101)
            ax.yaxis.labelpad = -7
    rcParams["font.size"] = 12

    # 保存图片
    plt.tight_layout()
    plt.savefig(os.path.join(out_dir, "Frequency.pdf"))
    print("Frequency plots saved.")


def draw_abala_plots(excel_path: str, mr_sheet: str, out_dir: str):
    """画消融实验的图 (柱状图)

    Parameters
    ----------
    excel_path : str
        存储MR信息的路径
    mr_sheet : str
        工作表名称
    out_dir : str
        输出目录
    """
    df = pd.read_excel(excel_path, engine="openpyxl", sheet_name=mr_sheet)
    llms = df[df["TEMPLATE"] != "Original"]["LLM"].unique()
    suts = df[df["TEMPLATE"] != "Original"]["SUT"].unique()
    templates = df["TEMPLATE"].unique()
    metrics = ["Legal Rate", "Correct Rate"]

    plot_data = list()
    for llm in llms:
        for sut in suts:
            for template in templates:
                total_MRCs = df[(df["LLM"] == llm) & (df["SUT"] == sut) & (df["TEMPLATE"] == template)].shape[0]
                legal_MRCs = df[(df["LLM"] == llm) & (df["SUT"] == sut) & (df["TEMPLATE"] == template) & (df["TYPE"] != "Illegal")].shape[0]
                correct_MRCs = df[(df["LLM"] == llm) & (df["SUT"] == sut) & (df["TEMPLATE"] == template) & (df["CORRECT"] == 1.0)].shape[0]
                plot_data.append({"LLM": llm, "SUT": sut, "TEMPLATE": template, "Legal Rate": legal_MRCs / total_MRCs * 100, "Correct Rate": correct_MRCs / total_MRCs * 100})

    # 画消融实验的图 (柱状图)
    rcParams["font.size"] = 14
    for llm in llms:

        # 画柱状图
        fig, axes = plt.subplots(1, len(llms), figsize=(9, 3))
        tmp_data = [data for data in plot_data if data["LLM"] == llm]
        for j, metric in enumerate(metrics):
            ax = axes[j]
            sns.barplot(data=pd.DataFrame(tmp_data), x="SUT", y=metric, hue="TEMPLATE", palette=["#0c0c0c", "#777777", "#cccccc", "#ffffff"], edgecolor="black", errorbar=None, ax=ax)
            sns.despine()
            ax.set_xlabel("")
            ax.set_ylabel("$LR$ (\%)" if metric == "Legal Rate" else "$CR$ (\%)")
            ax.set_ylim(0, 101)
            ax.set_yticks(range(0, 101, 20))
            ax.get_legend().remove()
            ax.set_xticklabels(ax.get_xticklabels(), rotation=15, ha="right")

        # 添加图例
        ax = axes[-1]
        handles, labels = ax.get_legend_handles_labels()
        item_dict = {"Original": r"\textit{Original}", "Prompt-C": r"\textit{Prompt\textsubscript{-C}}", "Prompt-S": r"\textit{Prompt\textsubscript{-S}}", "Prompt-I": r"\textit{Prompt\textsubscript{-I}}"}
        labels = [item_dict[label] for label in labels if label in item_dict.keys()]
        fig.legend(handles=handles, labels=labels, frameon=False, loc="lower center", ncol=len(labels))

        # 调整布局
        fig.tight_layout()
        fig.subplots_adjust(bottom=0.3)

        llm_abbrv = "".join(llm.split("-")[:2])
        plt.savefig(os.path.join(out_dir, f"Ablation_{llm_abbrv}.pdf"))
        print(f"Abala plots for {llm} saved.")

    rcParams["font.size"] = 12


def main(args: argparse.Namespace):
    """根据实验数据画图

    Parameters
    ----------
    args : argparse.Namespace
        命令行参数
    """
    excel_path = args.excel
    mr_sheet = args.mr_sheet
    sut_sheet = args.sut_sheet
    plots = args.plots
    out_dir = os.path.dirname(__file__)

    rcParams["text.usetex"] = True
    rcParams["font.family"] = "Times"
    rcParams["font.size"] = 12

    if plots == "legal" or plots == "all":
        draw_legal_plots(excel_path, mr_sheet, out_dir)

    if plots == "correct" or plots == "all":
        draw_correct_plots(excel_path, mr_sheet, out_dir)

    if plots == "innova" or plots == "all":
        draw_innova_plots(excel_path, mr_sheet, out_dir)

    if plots == "char" or plots == "all":
        draw_char_plots(excel_path, mr_sheet, sut_sheet, out_dir)

    if plots == "freq" or plots == "all":
        draw_freq_plots(excel_path, mr_sheet, sut_sheet, out_dir)

    if plots == "abla" or plots == "all":
        draw_abala_plots(excel_path, mr_sheet, out_dir)

    print("All done.")


if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    parser.add_argument("--excel", type=str, required=True, help="Path of excel file")
    parser.add_argument("--mr_sheet", type=str, required=True, help="Sheet name of mr data")
    parser.add_argument("--sut_sheet", type=str, required=True, help="Sheet name for sut data")
    parser.add_argument("--plots", type=str, choices=["legal", "correct", "innova", "char", "freq", "abla", "all"], default="all", help="plots to draw")
    args = parser.parse_args()
    main(args)
