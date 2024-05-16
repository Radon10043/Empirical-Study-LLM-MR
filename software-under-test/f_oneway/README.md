# f_oneway

python 3.8.3

# Test

Run specified test:

```sh
python tests/GPT3D5_test.py -k test2_
```

Run all tests of GPT3D5, each test is repeated 5 times:

```sh
for i in {1..40}; do ./run.sh GPT3D5 MR$i 5; done | tee testcases.validate.md
```

Run all tests of GPT4, each test is repeated 5 times:

```sh
for i in {2..41}; do ./run.sh GPT4 MR$i 5; done | tee testcases.validate.md
```