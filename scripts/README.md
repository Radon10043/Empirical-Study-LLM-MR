# scripts

This folder stores the scripts that used in the empirical study, including the script for instructing LLM to perform MR identification, the script for extracting MR candidates (MRCs) from LLM's output. The following is a description of some important files:

|       File        | Description                                                                                                                       |
| :---------------: | :-------------------------------------------------------------------------------------------------------------------------------- |
|     `chat.py`     | The script for instructing LLM to perform MR identification.                                                                      |
| `extract_code.py` | The script for extracting code blocks from a markdown file. In the empirical study, it is used to extract MRCs from LLM's output. |
| `LOC_counter.py`  | The scripts for counting the total lines of code for a function (include function it calls) in a py file.                         |
| `resumt_chat.py`  | The script that continues to talk to the LLM based on an input json file。                                                        |
|   `run-win.bat`   | The script for MR identification for all software under test (Windows).                                                           |
|  `run-linxu.sh`   | The script for MR identification for all software under test (Linux).                                                             |