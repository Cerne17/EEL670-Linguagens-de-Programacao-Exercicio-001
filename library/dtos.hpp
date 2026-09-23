#pragma once

#include "reading.hpp"
#include "types.hpp"

#include <string>
#include <vector>

using readings = std::vector<Reading>;

struct CreateStationDto
{
  id identifier;
  id system_identifier;
  std::string name;
};

struct UpdateStationDto
{
  std::string name;
  readings readings;
  int total_readings;
};

struct ReadingRequestDto
{
  id station_id;
  id reading_id;
};

struct ReadingResponseDto
{
  id reading_id;
  id station_id;
  ReadingType reading_type;
  timestamp reading_datetime;
  double measure;
};
