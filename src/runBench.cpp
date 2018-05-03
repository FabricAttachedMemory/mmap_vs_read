#include <ctime>
#include <stdio.h>
#include <fstream>
#include <iostream>
#include "sys/sysinfo.h"
#include <sys/resource.h>

#include "../hayai/hayai.hpp" // https://github.com/nickbruun/hayai
#include <benchmark/benchmark.h>
#include "../h/readMmap.h"
#include "../h/readBlock.h"

using namespace std;


string FILE_PATH = "";


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



float bench_the_mark(BaseRead* reader){
    double vm, rss;

    int startTime = clock();
    reader->read();
    int endTime = clock();
    process_mem_usage(vm, rss);

    cout << "VM: " << vm << "; RSS: " << rss << endl;

    return (endTime - startTime) / double(CLOCKS_PER_SEC);
}//bench_the_mark


void mmap_test(){
    MmapRead* mmapReader = new MmapRead(FILE_PATH);
    float runtime = bench_the_mark(mmapReader);
    cout << "Mmap time: " << runtime << endl;
    delete mmapReader;
}//mmap_test


void block_test(){
    BlockRead* blockReader = new BlockRead(FILE_PATH);
    float runtime = bench_the_mark(blockReader);
    cout << "Mmap time: " << runtime << endl;
    delete blockReader;
}//block_test


static void BM_Mmap(benchmark::State& state){
    for (auto _ : state) //do not use "while keep running". this is the way by creator's recommendations.
        mmap_test();
}//BM_Mmap


static void BM_Block(benchmark::State& state){
    for (auto _ : state) //do not use "while keep running". this is the way by creator's recommendations.
        block_test();
}//BM_Mmap



BENCHMARK(BM_Mmap)->Unit(benchmark::kMillisecond)->UseRealTime();;
BENCHMARK(BM_Block)->Unit(benchmark::kMillisecond)->UseRealTime();;
/*
BENCHMARK(Mmap_vs_Read, MmapRead, 1, 1){
    mmap_test();
}//benchmark mmapread


BENCHMARK(Mmap_vs_Read, BlockRead, 1, 1){
    block_test();
}//benchmark blockread
*/



int main(int argc, char * argv[]){
    FILE_PATH = argv[1];
    // FILE_PATH = "../test.data";
    benchmark::Initialize(&argc, argv);
    benchmark::RunSpecifiedBenchmarks();

    cout << "\n -- Runing Raw --" << endl;

    mmap_test();
    block_test();

    /*  
    std::filebuf fb;
    fb.open ("logs/bench.log",std::ios::out);
    std::ostream os(&fb);
    
    // Set up the main runner.
    hayai::ConsoleOutputter consoleOutputter;
    hayai::JsonOutputter jsoner(os);
    hayai::Benchmarker::AddOutputter(jsoner);
    hayai::Benchmarker::RunAllTests();
    */
    return 0;
}//run