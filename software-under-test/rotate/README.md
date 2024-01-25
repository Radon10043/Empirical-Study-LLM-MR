# Rotate

python 3.8.3

```sh
pip install -r requirements.txt
```

## Run tests

For GPT3.5:

```shell
for i in {2..41}; do ./run.sh GPT3D5 MR$i 5; done | tee testcases.validate.md
```