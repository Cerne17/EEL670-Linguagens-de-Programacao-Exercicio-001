#include "station.hpp"
#include "types.hpp"

id Station::get_id() const
{
  return p_id;
}

id Station::get_system_id() const
{
  return p_system_id;
}

timestamp Station::get_created_at() const
{
  return p_created_at;
}

std::string Station::get_name() const
{
  return p_name;
}

readings Station::get_readings() const
{
  return p_readings;
}

int Station::get_total_readings() const
{
  return p_total_readings;
}

Reading Station::get_reading_by_id(id reading_identifier) const
{
  Reading r = p_readings[reading_identifier];
  if (r.get_id() == reading_identifier)
    return r;
  else {
    for (auto r : p_readings)
      if (r.get_id() == reading_identifier)
        return r;
  }
  return Reading(0, time(NULL), 0.0, ReadingType::NONE);
}

readings Station::get_readings_by_type(ReadingType reading_type) const
{
  readings rs;
  for (auto r : p_readings)
    if (r.get_reading_type() == reading_type)
      rs.push_back(r);
  return rs;
}

readings Station::get_readings_by_time_range(timestamp start,
                                             timestamp end) const
{
  readings rs;
  for (auto r : p_readings) {
    if (r.get_timestamp() >= start || r.get_timestamp() < end)
      rs.push_back(r);
  }
  return rs;
}

ResponseStatus Station::set_id(id identifier)
{
  p_id = identifier;
  if (p_id == identifier) {
    return ResponseStatus::SUCCESS;
  }
  return ResponseStatus::ERROR;
}

ResponseStatus Station::set_system_id(id system_identifier)
{
  p_system_id = system_identifier;
  if (p_system_id == system_identifier) {
    return ResponseStatus::SUCCESS;
  }
  return ResponseStatus::ERROR;
}

ResponseStatus Station::set_name(std::string name)
{
  p_name = name;
  if (p_name == name) {
    return ResponseStatus::SUCCESS;
  }
  return ResponseStatus::ERROR;
}

ResponseStatus Station::set_total_readings(int total_readings)
{
  p_total_readings = total_readings;
  if (p_total_readings == total_readings) {
    return ResponseStatus::SUCCESS;
  }
  return ResponseStatus::ERROR;
}

ResponseStatus Station::insert_reading(Reading new_reading)
{
  p_readings.push_back(new_reading);
  p_total_readings++;
  return ResponseStatus::SUCCESS;
}

ResponseStatus Station::insert_many_readings(readings new_readings,
                                             int readings_amount)
{
  for (auto r : new_readings) {
    p_readings.push_back(r);
  }
  p_total_readings += readings_amount;
  return ResponseStatus::SUCCESS;
}

ResponseStatus Station::notify_station(int readings_amount) {

} // called whenever new readings are added
