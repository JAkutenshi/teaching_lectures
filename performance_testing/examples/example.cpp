#include "benchmark.h"
#include <vector>

static void escape(void *p) {
    asm volatile ("" : : "g"(p) : "memory");
}

static void clobber() {
    asm volatile ("" : : : "memory");
}

static void bm_create(benchmark::State &state) {
    while (state.KeepRunning()) {
// heaptrack allocation; uncomment for heaptrack test
//        std::vector<int> *v = new std::vector<int>(1000);
        std::vector<int> v;  // perf example; comment for heaptrack
        escape(&v);
        (void) v;            // perf example; comment for heaptrack
// heaptrack free; uncomment for heaptrack test
//        delete v;
    }
}
BENCHMARK(bm_create);

static void bm_reserve(benchmark::State &state) {
    while (state.KeepRunning()) {
        std::vector<int> v;
        v.reserve(1);
        escape(v.data());
    }
}
BENCHMARK(bm_reserve);

static void bm_push_back(benchmark::State &state) {
    while (state.KeepRunning()) {
        std::vector<int> v;
        escape(v.data());
        v.push_back(42);
        clobber();
    }
}
BENCHMARK(bm_push_back);

BENCHMARK_MAIN();

