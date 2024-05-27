# Schedule2

python 3.8.3

## Run tests

For example:

```shell
for i in {1..2}; do ./run.sh example MR$i 5; done | tee testcases.validate.md
```

For GPT3.5:

```shell
for i in {3..42}; do ./run.sh GPT3D5 MR$i 5; done | tee testcases.validate.md
```