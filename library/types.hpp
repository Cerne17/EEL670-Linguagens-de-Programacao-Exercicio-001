#pragma once

#include <ctime>

enum ReadingType
{
  TEMPERATURE,
  HUMIDITY,
  NONE
};

enum ResponseStatus
{
  SUCCESS,
  ERROR
};

using id = int;
using timestamp = time_t;
