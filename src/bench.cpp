#include "bench.h"

void StartBenchmark(SearchThread& st) {
    SearchInfo& info = st.info;

    info.depth    = 6;
    info.time_set = false;

    uint64_t nodes        = 0;
    uint64_t count        = 0;
    uint64_t time_elapsed = 0;

    // Inspired from Koivisto

    for (auto& fen : bench_fens) {
        st.applyFen(fen);

        auto start = now();
        iterative_deepening<false>(st);
        auto end = now();

        count++;
        nodes += st.nodes;
        time_elapsed += (end - start);

        printf("Position [%2d] -> cp %5d move %5s nodes %11lld nps %d", int(count), int(info.score),
               uci::moveToSan(st.board, st.bestmove).c_str(), nodes,
               static_cast<int>(1000.0f * nodes / (time_elapsed + 1)));
        std::cout << std::endl;
    }

    printf("Finished: nodes %38lld nps %d\n", static_cast<uint64_t>(nodes),
           static_cast<int>(1000.0f * nodes / (time_elapsed + 1)));
    std::cout << std::flush;
}