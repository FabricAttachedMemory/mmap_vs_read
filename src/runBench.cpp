#include <ctime>
#include <cmath>
#include <stdio.h>
#include <fstream>
#include <iostream>
#include <unistd.h>
#include "sys/sysinfo.h"
#include <sys/resource.h>

#include <benchmark/benchmark.h>
#include "../headers/readMmap.h"
#include "../headers/readBlock.h"
#include "../headers/measures.h"

using namespace std;

struct BenchData {
    string name;
    long Vram; //virtual memory
    long PHram; //physical memory
    double runtime;
};

string FILE_PATH = "";

BenchData bench_the_mark(BaseRead* reader){
    // double vm, rss;
    Measures::MemoryState memState;
    Measures MeasuresObj;
    BenchData data;


    MeasuresObj.StartTimer();
    reader->read(false);
    double runtime = MeasuresObj.StopTimer();
    memState = MeasuresObj.GetMemoryUsed();
    

    data.name = reader->GetName();
    data.PHram = memState.physicalMem;
    data.Vram = memState.virtualMem;
    data.runtime = runtime;

    return data;
}//bench_the_mark


BenchData mmap_test(){
    MmapRead* mmapReader = new MmapRead(FILE_PATH);
    BenchData data = bench_the_mark(mmapReader);

    delete mmapReader;
    return data;
}//mmap_test


BenchData block_test(){
    BlockRead* blockReader = new BlockRead(FILE_PATH);
    BenchData data = bench_the_mark(blockReader);

    delete blockReader;
    return data;
}//block_test


void updateStateData(benchmark::State& state, BenchData& data){
    state.counters["Vram"] = data.Vram;
    state.counters["PHram"] = data.PHram;
}

static void BM_Mmap(benchmark::State& state){
    BenchData data;
    for (auto _ : state){ //do not use "while keep running". this is the way by creator's recommendations.
        data = mmap_test();
    }
    updateStateData(state, data);
}//BM_Mmap


static void BM_Block(benchmark::State& state){
    BenchData data;
    for (auto _ : state){ //do not use "while keep running". this is the way by creator's recommendations.
        data = block_test();
    }
    updateStateData(state, data);
}//BM_Mmap



BENCHMARK(BM_Mmap)->Unit(benchmark::kMillisecond)->UseRealTime()->Complexity(benchmark::oN);
BENCHMARK(BM_Block)->Unit(benchmark::kMillisecond)->UseRealTime()->Complexity(benchmark::oN);


int main(int argc, char * argv[]){
    FILE_PATH = argv[1];

    benchmark::Initialize(&argc, argv);
    benchmark::RunSpecifiedBenchmarks();

    return 0;
}//run