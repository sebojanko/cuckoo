#!/bin/bash

make

# Creates data and runs all benchmarks.
# Saves data in the /data dir, stores results in /results.

mkdir data
./kmergen 10 50000 data/10_50k_extracted.txt gen
./kmergen 10 1000000 data/10_1mil_extracted.txt gen
./kmergen 20 1000000 data/20_1mil_extracted.txt gen
./kmergen 50 1000000 data/50_1mil_extracted.txt gen
./kmergen 100 1000000 data/100_1mil_extracted.txt gen
./kmergen 200 1000000 data/200_1mil_extracted.txt gen
./kmergen 10 5000 data/10_5k_random.txt gen
./kmergen 10 500000 data/10_500k_random.txt gen
./kmergen 20 500000 data/20_500k_random.txt gen
./kmergen 50 500000 data/50_500k_random.txt gen
./kmergen 100 500000 data/100_500k_random.txt gen
./kmergen 200 500000 data/200_500k_random.txt gen

mkdir results
./benchmark data/10_50k_extracted.txt data/10_5k_random.txt results/output_10_50k_5k.txt
./benchmark data/10_1mil_extracted.txt data/10_500k_random.txt results/output_10_1M_500k.txt
./benchmark data/20_1mil_extracted.txt data/20_500k_random.txt results/output_20_1M_500k.txt
./benchmark data/50_1mil_extracted.txt data/50_500k_random.txt results/output_50_1M_500k.txt
./benchmark data/100_1mil_extracted.txt data/100_500k_random.txt results/output_100_1M_500k.txt
./benchmark data/200_1mil_extracted.txt data/200_500k_random.txt results/output_100_1M_500k.txt
