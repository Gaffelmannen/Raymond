# Raymond - The raytracer
A very simple Raytracer..


## Build it
To build the application run the Makefile.

```
make
```


## Test it
Raymond use the Catch2 test framework. The tests are arranged for each class.

Syntax
```
make test TEST_SRC=tests/test_<CLASS_NAME>.cpp
```

An example to test the class material run the command below.
```
make test TEST_SRC=tests/test_material.cpp
```


## Run it
To run the program call the executable created in the "Build it" step.

```
./raymond
```
