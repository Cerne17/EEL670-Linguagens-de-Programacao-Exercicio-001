#pragma once

#include "types.hpp"

#include <ctime>
#include <stdexcept>

class Reading
{
private:
  id p_id;
  timestamp p_timestamp;
  double p_measure;
  ReadingType p_reading_type;

public:
  id get_id();
  timestamp get_timestamp();
  double get_measure();
  ReadingType get_reading_type();

  ResponseStatus set_id(id identifier);
  ResponseStatus set_timestamp(timestamp time);
  ResponseStatus set_measure(double measure);
  ResponseStatus set_reading_type(ReadingType reading_type);

  Reading(id identifier,
          timestamp time,
          double measure,
          ReadingType reading_type)
  {
    if (set_id(identifier) != SUCCESS
        || set_timestamp(time) != SUCCESS
        || set_measure(measure) != SUCCESS
        || set_reading_type(reading_type) != SUCCESS)
    {
      throw std::invalid_argument("Reading: invalid constructor arguments");
    }
  }
};
