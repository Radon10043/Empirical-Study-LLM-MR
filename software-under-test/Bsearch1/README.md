# Dependencies

## cmake

version 3.13.4

[https://github.com/Kitware/CMake](https://github.com/Kitware/CMake)

```sh
wget https://github.com/Kitware/CMake/releases/download/v3.13.4/cmake-3.13.4.tar.gz
tar zxvf cmake-3.13.4.tar.gz
cd cmake-3.13.4
sudo ./bootstrap
sudo make
sudo make install
```

## gtest

[https://github.com/google/googletest](https://github.com/google/googletest)

```sh
wget https://github.com/google/googletest/archive/refs/tags/v1.14.0.tar.gz
tar zxvf v1.14.0.tar.gz
cd googletest-1.14.0
mkdir build && cd build
cmake ..
make
sudo make install
```

# Run

## Run specified test case

```sh
build/test/GPT4Test --gtest_filter=TrueReturn/BSearchParamTest.20/* > testcases.output.txt
```