# scripts

This folder stores the scripts that used in the empirical study, including the script for instructing LLM to perform MR identification, the script for extracting MR candidates (MRCs) from LLM's output. The following is a description of each script.

## chat.py

- **Summary:** The script for instructing LLM to perform MR identification. The results of interaction with LLM will be saved in a json file and md file, respectively.
- **Input(s):**
  - *--template (Required):* The path of prompt template file (markdown). Examples of prompt templates are shown under `data/template`.
  - *--spec (Required):* The path of specification file (markdown) of Software Under Test. Examples of the specification are shown in the folder `data/specification`.
  - *--demo (Required):* A markdown file containing the Initial Codified MR(s). Examples are shown in the folder `data/demo`
  - *--model (Required):* LLM for performing MR identification.
  - *--name:* Name of Software Under Test.
  - *--count:* The maximum number of queries (default: 50).
  - *--output:* The target directory for saving query content, the default is where chat.py is located.
- **Output(s):**
  - A json file and a markdown file, both of which save results of LLM queries.
- **Example:**
```sh
python chat.py --template ./data/template/prompt.template.md \
               --spec ./data/specification/specification.Bsearch2.md \
               --demo ./data/demo/demo.Bsearch2.md \
               --model gpt-4-1106-preview \
               --name Bsearch2
```

## extract_code.py

- **Summary:** The script for extracting code blocks from a markdown file. In the empirical study, it is used to extract MRCs from LLM's output.
- **Input(s):**
  - *--input (Required):* The path of markdown file. The script will parse it into an abstract syntax tree and extract code blocks.
  - *--outdir:* The target directory for saving the extraction results. Default is the directory where extract_code.py is located.
- **Output(s):**
  - A txt file that saves all code blocks from the input markdown file.
- **Example:**
```sh
python extract_code.py --input /path/to/gpt-4-1106-preview.Bsearch2.md
```

## LOC_counter.py

- **Summary:** The scripts for counting the total lines of code for a function (include function it calls) in a py file.
- **Input(s):**
  - *--filepath (Required):* The path of the file to be analyzed.
  - *--func (Required):* The name of the function to be analyzed.
- **Output(s):**
  - The total number of lines of code in the function (including functions it calls).
- **Example:**
```sh
python LOC_counter.py --filepath /path/to/software-under-test/rotate/venv/Lib/site-packages/scipy/ndimage/_interpolation.py" \
                      --func rotate
```

## resume_chat.py

- **Summary:** The script that continues to talk to the LLM based on an input json. During the process of LLM query, the script may exit early due to network problems and not satisfying the stop condition. Users can use this script to continue the query based on the previous query records.
- **Input(s):**
  - *--json (Reuqired):* JSON file path that saving query records.
  - *--model (Reuqired):* The name of LLM to be quired, e.g., *gpt-4-1106-preview*.
  - *--count:* Maximum number of times to continue querying (default: 50).
- **Output(s):**
  - Same as `chat.py`.
- **Example:**
```sh
python resume_chat.py --json gpt-4-1106-preview.Bsearch2.json \
                      --model gpt-4-1106-preview \
                      --count 20
```

## run-win.bat

- **Summary:** The script for MR identification for all Software Under Test (for Windows).
- **Input(s):** N/A
- **Output(s):** MR identification results for all Software Under Test using LLM
- **Example:**
```powershell
.\\run-windows.bat
```

## run-linux.sh
- **Summary:** The script for MR identification for all Software Under Test (for Linux).
- **Input(s):** N/A
- **Output(s):** MR identification results for all Software Under Test using LLM
- **Example:**
```sh
./run-linux.sh
```