# Advent of Code

## Description
This template is inspired by https://github.com/fspoettel/advent-of-code-rust. The goal is to reduce the amount of overhead for solving Advent of Code challenges in C++. You don't have to worry about manually editing CMakeLists or your filesystem. For more information, see [starting a new day](#Starting-a-new-day).

## Building
Click "Use this template" and create your repository, then clone and build. This project depends on gtest and libcurl, which will be downloaded and built automatically via vcpkg.

**Important note:** this project uses submodules to make initializing vcpkg easier and to force a stable build of third party dependencies. Please use the `--recurse-submodules` when cloning. If you forgot to do this for the clone, you can also `git submodule update --init --recursive`.

```sh
git clone --recurse-submodules ...
cd ...
mkdir build && cd build
cmake ../
cmake --build .
```

### perl dependency
There is perl dependency for Linux users that is not retrieved by vcpkg. If you see CMake errors about IPC or perl, please get perl from your package manager.

## Enabling downloading inputs
`StartNewDay` will download your input for you, but in order to do that, it needs your session cookie. Login to https://adventofcode.com, press F12, and find your session token. On Firefox, this is located under the "Storage" tab then the "Cookies" menu. Paste the value into a file in the "inputs" subdirectory in a file called ".adventofcode.session".

Note that inputs *should not* be maintained by version control. This is already setup in the gitignore.

## Starting a new day
Run `StartNewDay` to download input and create the boilerplate code. From your build directory:

```sh
cd bin
./StartNewDay 1 # add boiler-plate CMake and stub code and download inputs
cmake --build ../
```

"1.cpp" and the accompanying CMakeLists will be added. CMake should be run after running `StartNewDay` to pick up the new source file.

Additionally, the year and day can be omitted to use the current year and day. If it's not December yet, the previous year will be used. Assuming today is Christmas:
```sh
./StartNewDay # uses 25 as the day and the current year
```

### Input files
In addition to generating boiler plate for solving the day's problem, the input and sample input are downloaded as well. These files are placed in the "inputs" subdirectory of the root project directory. If you're using Visual Studio, these files should show up under the days project target.

## Implementing your solution
Stub code will be added, so all you have to do is fill in the blanks:

```cpp
namespace
{
    struct Solver : public ACSolver
    {
        Answer solvePartOne() override
        {
            // The day's input will be stored in the member mInput. Other useful utility functions are provided, see Utilities.hpp.
            const auto ii = util::ContainerTo<int64_t>(mInput);

            // Solve part one.
            return std::accumulate(ii.begin(), ii.end(), 1, std::multiplies<>());
        }
    // ...
}

// ...

TEST(day_1, part_1)
{
    // This part needs no changes.
    const auto answer = CreateSolver(false).solvePartOne();
    ASSERT_NE(answer, std::nullopt);

    // Once you know the answer, put it here and uncomment. This isn't strictly necessary.
    EXPECT_EQ(*answer, 1337);

    // This part also needs no changes. Assuming the previous assertion does not fail, your answer should be printed.
    std::cout << "part one: " << *answer << std::endl;
}
```

## Running tests
Solutions are implemented using gtest and are automatically added to ctest. Therefore, running your solution can be accomplished in a couple ways.

### ctest
ctest can be used to run an arbitrary set of days and parts. Note that, unless `--test-dir` is used, you must be in the top-level build directory as opposed to the "bin" subdirectory.
```sh
ctest --test-dir build/Debug # run all tests from two directories above our build
cd build/Debug
ctest # run all tests (all days)
ctest -R part_1 # run part one from all tests
ctest -R day_1 # run all parts from day one
ctest -R day_1.part_1 # run part one from day one
ctest -R day_1.sample_part_1 # run sample part one
```

### gtest
If gtest is used, you can only run one day at a time, otherwise the same flexibility exists.
```sh
cd build/Debug/bin
./day1 # run all parts from day one
./day1 --gtest_filter=day_1.part_1 # run part one
./day1 --gtest_filter=*sample_part_1 # use a wild card and run sample part one
```

## Planned updates
In an effort to further mimic https://github.com/fspoettel/advent-of-code-rust, I am writing a cli interface for AoC, which takes inspiration from https://github.com/scarvalhojr/aoc-cli. While some of that functionality is complete, the product as a whole is not. This repo is a minimum viable solution for solving AoC challenges in a convenient package, but I plan on removing overlapping functionality from this project and relying on the new cli interface. If you're interested, [check it out here](https://github.com/jonathondgebhardt/aoc-cli-cpp).
