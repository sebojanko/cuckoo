# cuckoo
An implementation of the Cuckoo filter from the paper: "Cuckoo Filter: Practically Better Than Bloom" by Bin Fan, David G. Andersen, Michael Kaminsky and Michael D. Mitzenmache. (https://www.cs.cmu.edu/~dga/papers/cuckoo-conext2014.pdf)

This project is part of the Bioinformatics course of the Faculty of Electrical Engineering and Computing, University of Zagreb. (https://www.fer.unizg.hr/en/course/bio)

### Quick start
To compile, generate all files, and run the benchmarks, simply run:

`bash run.sh`

which will generate all the input files in the `/data` directory, and store all results in the `/results` directory.


### Compiling

Run `make` in the root folder then run `cuckoo`

### Running unit tests

Run `make test` in the root folder to create binary.
Run `./test <fasta_input_file>` to run all tests.
Without the input file, some tests are not run.


### Generating input data

Run `make gen` to compile the KMer Generator.
Use the Generator to create input files of either random k-mers or k-mers extracted from a file.
#### Usage:
`./kmergen <len> <iterations> <outputFile> <type> [inputFile]`

`<type>` is 'gen' (for generating random k-mers) or 'ext' (for extraction from [inputFile])
  
#### Example:
`./kmergen 20 1000000 generated_1M_20mer.txt gen`

This generates one million random 20-mers and writes them to input.txt.


### Running performance analysis

Run `make bench` to create the benchmark program.
#### Usage:
`./benchmark <for_insertion> <non_existing_for_FP> <output_file>`

The first argument is the file containing k-mers for insertion into the Cuckoo filter. One k-mer per line, lines must be separated by the newline character.
The second argument are k-mers that are not found in the first file. These k-mers are used to check for false positives. The format of the file is the same as the first one.
The output is written to the output file.

## Authors
* Sebastian Janko - [sebojanko](https://github.com/sebojanko)
* David Lozić - [cizl](https://github.com/cizl)
* Luka Markušić - [mark2185](https://github.com/mark2185)
