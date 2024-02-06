# FileCompressor
A basic file compressor that uses Huffman compression.

## Dependency
- [CMake](https://cmake.org/)
- [g++](https://gcc.gnu.org/)
- [Boost](https://www.boost.org/)

## Building
```shell
git clone https://github.com/leofracca/FileCompressor
cd FileCompressor
mkdir build
cd build
cmake ..
make
```

## Usage
```shell
./fileCompressor path/to/input/file OPTION [path/to/output/file]
```

### Example
```shell
# Compress the file foo.txt
# (it automatically generates the output file foo.txt.compressed,
# since no output file is given)
./fileCompressor foo.txt -c
```

```shell
# Decompress the file foo.txt.compressed and generate bar.txt
./fileCompressor foo.txt.compressed -d bar.txt
```

For a list of all possible options use
```shell
./fileCompressor -h
```

## Documentation
```shell
make docs
```

## References
- [Stanford University](https://web.stanford.edu/class/archive/cs/cs106b/cs106b.1186/yeah/huffman/Huffman_YEAH.pdf)
- [Huffman Coding](https://en.wikipedia.org/wiki/Huffman_coding)
