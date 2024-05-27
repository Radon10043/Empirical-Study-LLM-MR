# grep

python 3.8.3

## Build grep

```shell
cd src
./build.sh
```

## Run tests

For GPT3.5:

```shell
for i in {1..3}; do ./run.sh example MR$i 5; done | tee testcases.validate.md
```

For GPT3.5:

```shell
for i in {4..43}; do ./run.sh GPT3D5 MR$i 5; done | tee testcases.validate.md
```