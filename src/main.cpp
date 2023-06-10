/*
  Stockfish, a UCI chess playing engine derived from Glaurung 2.1
  Copyright (C) 2004-2022 The Stockfish developers (see AUTHORS file)

  Stockfish is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  Stockfish is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <iostream>

#include "bitboard.h"
#include "endgame.h"
#include "piece.h"
#include "position.h"
#include "psqt.h"
#include "search.h"
#include "syzygy/tbprobe.h"
#include "thread.h"
#include "tt.h"
#include "uci.h"
#include "variant.h"
#include "xboard.h"

using namespace Stockfish;

/**
 * @brief The main function for the Stockfish chess engine.
 *
 * This function initializes various components of the Stockfish engine,
 * including the UCI interface, search threads, and various data structures.
 * It then enters the main UCI loop, where it waits for commands from the
 * user interface. After the UCI loop exits, it cleans up and exits.
 *
 * @param argc The number of command-line arguments.
 * @param argv The command-line arguments.
 * @return 0 on successful execution.
 */
int main(int argc, char* argv[])
{
    std::cout << engine_info() << std::endl;

    pieceMap.init();
    variants.init();
    CommandLine::init(argc, argv);
    UCI::init(Options);
    Tune::init();
    PSQT::init(variants.find(Options["UCI_Variant"])->second);
    Bitboards::init();
    Position::init();
    Bitbases::init();
    Endgames::init();
    Threads.set(size_t(Options["Threads"]));
    Search::clear();  // After threads are up
    Eval::NNUE::init();

    UCI::loop(argc, argv);

    Threads.set(0);
    variants.clear_all();
    pieceMap.clear_all();
    delete XBoard::stateMachine;
    return 0;
}
