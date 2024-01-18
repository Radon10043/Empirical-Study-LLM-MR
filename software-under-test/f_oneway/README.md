# f_oneway

python 3.8.3

# Test

Run specified test:

```sh
python tests/GPT3D5_test.py -k test2_
```

Run all test cases of GPT3D5_test, each test case is repeated five times:

```sh
for i in {2..41}; do ./run.sh GPT3D5_test test$i 5; done | tee testcases.validate.md
```