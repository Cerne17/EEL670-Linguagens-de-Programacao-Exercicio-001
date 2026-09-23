#include "reading.hpp"
#include "types.hpp"

id Reading::get_id()
{
  return p_id;
}
timestamp Reading::get_timestamp()
{
  return p_timestamp;
}
double Reading::get_measure()
{
  return p_measure;
}
ReadingType Reading::get_reading_type()
{
  return p_reading_type;
}

ResponseStatus Reading::set_id(id identifier)
{
  p_id = identifier;
  if (p_id == identifier)
    return ResponseStatus::SUCCESS;
  return ResponseStatus::ERROR;
}

ResponseStatus Reading::set_timestamp(timestamp time)
{
  p_timestamp = time;
  if (p_timestamp == time)
    return ResponseStatus::SUCCESS;
  return ResponseStatus::ERROR;
}

ResponseStatus Reading::set_measure(double measure)
{
  p_measure = measure;
  if (p_measure == measure)
    return ResponseStatus::SUCCESS;
  return ResponseStatus::ERROR;
}

ResponseStatus Reading::set_reading_type(ReadingType reading_type)
{
  p_reading_type = reading_type;
  if (p_reading_type == reading_type)
    return ResponseStatus::SUCCESS;
  return ResponseStatus::ERROR;
}
