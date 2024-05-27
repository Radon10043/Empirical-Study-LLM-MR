# TCAS

python 3.8.3

# Run tests

For exmaple:

```sh
for i in {1..4}; do ./run.sh example MR$i 5; done | tee testcases.validate.md
```

For GPT3.5:

```sh
for i in {5..44}; do ./run.sh GPT3D5 MR$i 5; done | tee testcases.validate.md
```

For GPT4:

```sh
for i in {5..44}; do ./run.sh GPT4 MR$i 5; done | tee testcases.validate.md
```