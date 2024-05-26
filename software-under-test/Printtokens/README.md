# Printtokens

python 3.8.3

# Run tests

For GPT3.5:

```sh
for i in {1..40}; do ./run.sh GPT3D5 MR$i 5; done | tee testcases.validate.md
```

For GPT4:

```sh
for i in {1..40}; do ./run.sh GPT4 MR$i 5; done | tee testcases.validate.md
```