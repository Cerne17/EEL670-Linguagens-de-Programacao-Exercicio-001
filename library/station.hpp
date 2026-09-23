#pragma once

#include "reading.hpp"
#include "system.hpp"
#include "types.hpp"

#include <ctime>
#include <stdexcept>
#include <string>
#include <vector>

using readings = std::vector<Reading>;

class Station
{
private:
  id p_id;
  id p_system_id;
  System system;
  timestamp p_created_at;
  timestamp p_updated_at;

  std::string p_name;
  readings p_readings;
  int p_total_readings;

public:
  id get_id() const;
  id get_system_id() const;
  timestamp get_created_at() const;
  std::string get_name() const;
  readings get_readings() const;
  int get_total_readings() const;

  Reading get_reading_by_id(id reading_identifier) const;
  readings get_readings_by_type(ReadingType reading_type) const;
  readings get_readings_by_time_range(timestamp start, timestamp end) const;

  ResponseStatus set_id(id identifier);
  ResponseStatus set_system_id(id system_identifier);
  ResponseStatus set_name(std::string name);
  ResponseStatus set_total_readings(int total_readings);

  ResponseStatus insert_reading(Reading new_reading);
  ResponseStatus insert_many_readings(readings new_readings,
                                      int readings_amount);
  ResponseStatus notify_station(
    int readings_amount); // called whenever new readings are added

  Station(id identifier, id system_identifier, std::string name)
    : p_total_readings(0)
    , p_created_at(time(NULL))
  {
    if (set_id(identifier) != SUCCESS ||
        set_system_id(system_identifier) != SUCCESS ||
        set_name(name) != SUCCESS) {
      throw std::invalid_argument("Station: invalid constructor arguments");
    }
  }
};
