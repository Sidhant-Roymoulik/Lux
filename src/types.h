#pragma once

#include "chess.hpp"

using namespace chess;

#define NAME "Lux"
#define AUTHOR "Sidhant Roymoulik"

using Ply   = int16_t;
using Score = int32_t;
using Hash  = uint64_t;

const Ply MAX_DEPTH = 100;
const Ply MAX_PLY   = 100;