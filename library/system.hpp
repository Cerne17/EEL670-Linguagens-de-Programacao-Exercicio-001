#pragma once

#include <ctime>
#include <stdexcept>
#include <string>
#include <vector>

#include "dtos.hpp"
#include "reading.hpp"
#include "station.hpp"
#include "types.hpp"

using stations = std::vector<Station>;

class System
{
private:
  id p_id;
  timestamp p_created_at;
  timestamp p_updated_at;

  std::string p_name;
  stations p_stations;
  int p_total_stations;

public:
  id get_id();
  timestamp get_created_at();
  std::string get_name();
  stations get_stations();
  int get_total_stations();

  Station get_station_by_id(id station_identifier);
  Station get_station_by_name(std::string station_name);

  ResponseStatus set_id(id identifier);
  ResponseStatus set_name(std::string name);
  ResponseStatus set_total_stations(int total_stations);
  ResponseStatus insert_station(CreateStationDto new_station);
  ResponseStatus remove_station_by_id(id identifier);
  ResponseStatus update_station_by_id(id identifier,
                                      UpdateStationDto update_station_obj);

  ReadingResponseDto get_reading(ReadingRequestDto get_reading_dto);

  void on_notify();

  System(id identifier, std::string name)
    : p_created_at(time(NULL))
    , p_total_stations(0)
  {
    if (set_id(identifier) != SUCCESS || set_name(name) != SUCCESS)
    {
      throw std::invalid_argument("System: invalid constructor arguments");
    }
  }
};
