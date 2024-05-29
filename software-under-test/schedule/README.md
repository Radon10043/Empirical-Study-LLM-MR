# Schedule

python 3.8.3

## Run tests

For example:

```sh
for i in {1..2}; do ./run.sh example MR$i 5; done | tee testcases.validate.md
```

For GPT3.5:

```sh
for i in {3..42}; do ./run.sh GPT3D5 MR$i 5; done | tee testcases.validate.md
```

For GPT4:

```sh
for i in {1..33}; do ./run.sh GPT4 MR$i 5; done | tee testcases.validate.md
```