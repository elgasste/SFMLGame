#pragma once

#define WIN32_LEAN_AND_MEAN

#include <memory>
#include <string>
#include <vector>
#include <map>
#include <queue>
#include <math.h>

// this must be included before Windows.h, or there will be errors!
#include <SFML/Graphics.hpp>

#include <Windows.h>
#include <timeapi.h>
#include <chrono>
#include <thread>

#include "StringTable.h"

#define NAMESPACE          SFMLGame
#define NAMESPACE_BEGIN    namespace NAMESPACE {
#define NAMESPACE_END      }
