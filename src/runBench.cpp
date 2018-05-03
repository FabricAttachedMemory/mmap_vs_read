#include <list>
#include <ctime>
#include <stdio.h>
#include <fstream>
#include <iostream>
#include <unistd.h>
#include "sys/sysinfo.h"
#include <sys/resource.h>

#include <benchmark/benchmark.h>
#include "../headers/readMmap.h"
#include "../headers/readBlock.h"

using namespace std;


string FILE_PATH = "";

struct BenchData {
    string name;
    long vram;
    long dram;
    double runtime;
};

list<BenchData> RESULTS;

/*
Source: https://stackoverflow.com/questions/669438/how-to-get-memory-usage-at-run-time-in-c
*/
void process_mem_usage(double& vm_usage, double& resident_set)
{
   using std::ios_base;
   using std::ifstream;
   using std::string;

   vm_usage     = 0.0;
   resident_set = 0.0;

   // 'file' stat seems to give the most reliable results
   //
   ifstream stat_stream("/proc/self/stat",ios_base::in);    

   // dummy vars for leading entries in stat that we don't care about
   //
   string pid, comm, state, ppid, pgrp, session, tty_nr;
   string tpgid, flags, minflt, cminflt, majflt, cmajflt;
   string utime, stime, cutime, cstime, priority, nice;
   string O, itrealvalue, starttime;

   // the two fields we want
   //
   unsigned long vsize;
   long rss;

   stat_stream >> pid >> comm >> state >> ppid >> pgrp >> session >> tty_nr
               >> tpgid >> flags >> minflt >> cminflt >> majflt >> cmajflt
               >> utime >> stime >> cutime >> cstime >> priority >> nice
               >> O >> itrealvalue >> starttime >> vsize >> rss; // don't care about the rest

   stat_stream.close();

   long page_size_kb = sysconf(_SC_PAGE_SIZE) / 1024; // in case x86-64 is configured to use 2MB pages
   vm_usage     = vsize / 1024.0;
   resident_set = rss * page_size_kb;
}//process_mem_usage



BenchData bench_the_mark(BaseRead* reader){
    double vm, rss;
    BenchData data;

    double startTime = clock();
    reader->read(false);
    double endTime = clock();
    process_mem_usage(vm, rss);

    // cout << "VM: " << vm << "; RSS: " << rss << endl;

    double runtime = (endTime - startTime) / double(CLOCKS_PER_SEC);
    data.name = reader->GetName();
    data.dram = rss;
    data.vram = vm;
    data.runtime = runtime;

    return data;
}//bench_the_mark


BenchData mmap_test(){
    MmapRead* mmapReader = new MmapRead(FILE_PATH);
    BenchData data = bench_the_mark(mmapReader);
    // cout << "Mmap time: " << runtime << endl;
    RESULTS.push_front(data);
    delete mmapReader;
    return data;
}//mmap_test


BenchData block_test(){
    BlockRead* blockReader = new BlockRead(FILE_PATH);
    BenchData data = bench_the_mark(blockReader);
    RESULTS.push_back(data);
    // cout << "Mmap time: " << runtime << endl;
    delete blockReader;
    return data;
}//block_test


void updateStateData(benchmark::State& state, BenchData& data){
    state.counters["Runtime(Raw)"] = data.runtime;
    state.counters["VRAM"] = data.vram;
    state.counters["DRAM"] = data.dram;
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
/*
BENCHMARK(Mmap_vs_Read, MmapRead, 1, 1){
    mmap_test();
}//benchmark mmapread


BENCHMARK(Mmap_vs_Read, BlockRead, 1, 1){
    block_test();
}//benchmark blockread
*/


void showResults(){
    cout << "name | runtime | vram | dram " << endl; 
    for (auto const& i : RESULTS) {
        cout << i.name << " | " <<
            i.runtime << " | " <<
            i.vram << " | " <<
            i.dram << endl;
    }//for
}//ShowResults


int main(int argc, char * argv[]){
    FILE_PATH = argv[1];

    benchmark::Initialize(&argc, argv);
    benchmark::RunSpecifiedBenchmarks();

    return 0;
}//run