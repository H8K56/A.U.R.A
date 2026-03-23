// generated from rosidl_generator_py/resource/_idl_support.c.em
// with input from aura_msgs:msg/WeatherZone.idl
// generated code does not contain a copyright notice
#define NPY_NO_DEPRECATED_API NPY_1_7_API_VERSION
#include <Python.h>
#include <stdbool.h>
#ifndef _WIN32
# pragma GCC diagnostic push
# pragma GCC diagnostic ignored "-Wunused-function"
#endif
#include "numpy/ndarrayobject.h"
#ifndef _WIN32
# pragma GCC diagnostic pop
#endif
#include "rosidl_runtime_c/visibility_control.h"
#include "aura_msgs/msg/detail/weather_zone__struct.h"
#include "aura_msgs/msg/detail/weather_zone__functions.h"

ROSIDL_GENERATOR_C_IMPORT
bool builtin_interfaces__msg__time__convert_from_py(PyObject * _pymsg, void * _ros_message);
ROSIDL_GENERATOR_C_IMPORT
PyObject * builtin_interfaces__msg__time__convert_to_py(void * raw_ros_message);
ROSIDL_GENERATOR_C_IMPORT
bool geometry_msgs__msg__point__convert_from_py(PyObject * _pymsg, void * _ros_message);
ROSIDL_GENERATOR_C_IMPORT
PyObject * geometry_msgs__msg__point__convert_to_py(void * raw_ros_message);
ROSIDL_GENERATOR_C_IMPORT
bool builtin_interfaces__msg__time__convert_from_py(PyObject * _pymsg, void * _ros_message);
ROSIDL_GENERATOR_C_IMPORT
PyObject * builtin_interfaces__msg__time__convert_to_py(void * raw_ros_message);
ROSIDL_GENERATOR_C_IMPORT
bool builtin_interfaces__msg__time__convert_from_py(PyObject * _pymsg, void * _ros_message);
ROSIDL_GENERATOR_C_IMPORT
PyObject * builtin_interfaces__msg__time__convert_to_py(void * raw_ros_message);

ROSIDL_GENERATOR_C_EXPORT
bool aura_msgs__msg__weather_zone__convert_from_py(PyObject * _pymsg, void * _ros_message)
{
  // check that the passed message is of the expected Python class
  {
    char full_classname_dest[40];
    {
      char * class_name = NULL;
      char * module_name = NULL;
      {
        PyObject * class_attr = PyObject_GetAttrString(_pymsg, "__class__");
        if (class_attr) {
          PyObject * name_attr = PyObject_GetAttrString(class_attr, "__name__");
          if (name_attr) {
            class_name = (char *)PyUnicode_1BYTE_DATA(name_attr);
            Py_DECREF(name_attr);
          }
          PyObject * module_attr = PyObject_GetAttrString(class_attr, "__module__");
          if (module_attr) {
            module_name = (char *)PyUnicode_1BYTE_DATA(module_attr);
            Py_DECREF(module_attr);
          }
          Py_DECREF(class_attr);
        }
      }
      if (!class_name || !module_name) {
        return false;
      }
      snprintf(full_classname_dest, sizeof(full_classname_dest), "%s.%s", module_name, class_name);
    }
    assert(strncmp("aura_msgs.msg._weather_zone.WeatherZone", full_classname_dest, 39) == 0);
  }
  aura_msgs__msg__WeatherZone * ros_message = _ros_message;
  {  // timestamp
    PyObject * field = PyObject_GetAttrString(_pymsg, "timestamp");
    if (!field) {
      return false;
    }
    if (!builtin_interfaces__msg__time__convert_from_py(field, &ros_message->timestamp)) {
      Py_DECREF(field);
      return false;
    }
    Py_DECREF(field);
  }
  {  // zone_id
    PyObject * field = PyObject_GetAttrString(_pymsg, "zone_id");
    if (!field) {
      return false;
    }
    assert(PyLong_Check(field));
    ros_message->zone_id = PyLong_AsUnsignedLong(field);
    Py_DECREF(field);
  }
  {  // center
    PyObject * field = PyObject_GetAttrString(_pymsg, "center");
    if (!field) {
      return false;
    }
    if (!geometry_msgs__msg__point__convert_from_py(field, &ros_message->center)) {
      Py_DECREF(field);
      return false;
    }
    Py_DECREF(field);
  }
  {  // radius_meters
    PyObject * field = PyObject_GetAttrString(_pymsg, "radius_meters");
    if (!field) {
      return false;
    }
    assert(PyFloat_Check(field));
    ros_message->radius_meters = (float)PyFloat_AS_DOUBLE(field);
    Py_DECREF(field);
  }
  {  // min_altitude
    PyObject * field = PyObject_GetAttrString(_pymsg, "min_altitude");
    if (!field) {
      return false;
    }
    assert(PyFloat_Check(field));
    ros_message->min_altitude = (float)PyFloat_AS_DOUBLE(field);
    Py_DECREF(field);
  }
  {  // max_altitude
    PyObject * field = PyObject_GetAttrString(_pymsg, "max_altitude");
    if (!field) {
      return false;
    }
    assert(PyFloat_Check(field));
    ros_message->max_altitude = (float)PyFloat_AS_DOUBLE(field);
    Py_DECREF(field);
  }
  {  // weather_type
    PyObject * field = PyObject_GetAttrString(_pymsg, "weather_type");
    if (!field) {
      return false;
    }
    assert(PyLong_Check(field));
    ros_message->weather_type = (uint8_t)PyLong_AsUnsignedLong(field);
    Py_DECREF(field);
  }
  {  // severity
    PyObject * field = PyObject_GetAttrString(_pymsg, "severity");
    if (!field) {
      return false;
    }
    assert(PyFloat_Check(field));
    ros_message->severity = (float)PyFloat_AS_DOUBLE(field);
    Py_DECREF(field);
  }
  {  // wind_speed_ms
    PyObject * field = PyObject_GetAttrString(_pymsg, "wind_speed_ms");
    if (!field) {
      return false;
    }
    assert(PyFloat_Check(field));
    ros_message->wind_speed_ms = (float)PyFloat_AS_DOUBLE(field);
    Py_DECREF(field);
  }
  {  // wind_direction_rad
    PyObject * field = PyObject_GetAttrString(_pymsg, "wind_direction_rad");
    if (!field) {
      return false;
    }
    assert(PyFloat_Check(field));
    ros_message->wind_direction_rad = (float)PyFloat_AS_DOUBLE(field);
    Py_DECREF(field);
  }
  {  // signal_attenuation_db
    PyObject * field = PyObject_GetAttrString(_pymsg, "signal_attenuation_db");
    if (!field) {
      return false;
    }
    assert(PyFloat_Check(field));
    ros_message->signal_attenuation_db = (float)PyFloat_AS_DOUBLE(field);
    Py_DECREF(field);
  }
  {  // no_fly
    PyObject * field = PyObject_GetAttrString(_pymsg, "no_fly");
    if (!field) {
      return false;
    }
    assert(PyBool_Check(field));
    ros_message->no_fly = (Py_True == field);
    Py_DECREF(field);
  }
  {  // start_time
    PyObject * field = PyObject_GetAttrString(_pymsg, "start_time");
    if (!field) {
      return false;
    }
    if (!builtin_interfaces__msg__time__convert_from_py(field, &ros_message->start_time)) {
      Py_DECREF(field);
      return false;
    }
    Py_DECREF(field);
  }
  {  // end_time
    PyObject * field = PyObject_GetAttrString(_pymsg, "end_time");
    if (!field) {
      return false;
    }
    if (!builtin_interfaces__msg__time__convert_from_py(field, &ros_message->end_time)) {
      Py_DECREF(field);
      return false;
    }
    Py_DECREF(field);
  }
  {  // is_active
    PyObject * field = PyObject_GetAttrString(_pymsg, "is_active");
    if (!field) {
      return false;
    }
    assert(PyBool_Check(field));
    ros_message->is_active = (Py_True == field);
    Py_DECREF(field);
  }

  return true;
}

ROSIDL_GENERATOR_C_EXPORT
PyObject * aura_msgs__msg__weather_zone__convert_to_py(void * raw_ros_message)
{
  /* NOTE(esteve): Call constructor of WeatherZone */
  PyObject * _pymessage = NULL;
  {
    PyObject * pymessage_module = PyImport_ImportModule("aura_msgs.msg._weather_zone");
    assert(pymessage_module);
    PyObject * pymessage_class = PyObject_GetAttrString(pymessage_module, "WeatherZone");
    assert(pymessage_class);
    Py_DECREF(pymessage_module);
    _pymessage = PyObject_CallObject(pymessage_class, NULL);
    Py_DECREF(pymessage_class);
    if (!_pymessage) {
      return NULL;
    }
  }
  aura_msgs__msg__WeatherZone * ros_message = (aura_msgs__msg__WeatherZone *)raw_ros_message;
  {  // timestamp
    PyObject * field = NULL;
    field = builtin_interfaces__msg__time__convert_to_py(&ros_message->timestamp);
    if (!field) {
      return NULL;
    }
    {
      int rc = PyObject_SetAttrString(_pymessage, "timestamp", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // zone_id
    PyObject * field = NULL;
    field = PyLong_FromUnsignedLong(ros_message->zone_id);
    {
      int rc = PyObject_SetAttrString(_pymessage, "zone_id", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // center
    PyObject * field = NULL;
    field = geometry_msgs__msg__point__convert_to_py(&ros_message->center);
    if (!field) {
      return NULL;
    }
    {
      int rc = PyObject_SetAttrString(_pymessage, "center", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // radius_meters
    PyObject * field = NULL;
    field = PyFloat_FromDouble(ros_message->radius_meters);
    {
      int rc = PyObject_SetAttrString(_pymessage, "radius_meters", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // min_altitude
    PyObject * field = NULL;
    field = PyFloat_FromDouble(ros_message->min_altitude);
    {
      int rc = PyObject_SetAttrString(_pymessage, "min_altitude", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // max_altitude
    PyObject * field = NULL;
    field = PyFloat_FromDouble(ros_message->max_altitude);
    {
      int rc = PyObject_SetAttrString(_pymessage, "max_altitude", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // weather_type
    PyObject * field = NULL;
    field = PyLong_FromUnsignedLong(ros_message->weather_type);
    {
      int rc = PyObject_SetAttrString(_pymessage, "weather_type", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // severity
    PyObject * field = NULL;
    field = PyFloat_FromDouble(ros_message->severity);
    {
      int rc = PyObject_SetAttrString(_pymessage, "severity", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // wind_speed_ms
    PyObject * field = NULL;
    field = PyFloat_FromDouble(ros_message->wind_speed_ms);
    {
      int rc = PyObject_SetAttrString(_pymessage, "wind_speed_ms", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // wind_direction_rad
    PyObject * field = NULL;
    field = PyFloat_FromDouble(ros_message->wind_direction_rad);
    {
      int rc = PyObject_SetAttrString(_pymessage, "wind_direction_rad", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // signal_attenuation_db
    PyObject * field = NULL;
    field = PyFloat_FromDouble(ros_message->signal_attenuation_db);
    {
      int rc = PyObject_SetAttrString(_pymessage, "signal_attenuation_db", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // no_fly
    PyObject * field = NULL;
    field = PyBool_FromLong(ros_message->no_fly ? 1 : 0);
    {
      int rc = PyObject_SetAttrString(_pymessage, "no_fly", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // start_time
    PyObject * field = NULL;
    field = builtin_interfaces__msg__time__convert_to_py(&ros_message->start_time);
    if (!field) {
      return NULL;
    }
    {
      int rc = PyObject_SetAttrString(_pymessage, "start_time", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // end_time
    PyObject * field = NULL;
    field = builtin_interfaces__msg__time__convert_to_py(&ros_message->end_time);
    if (!field) {
      return NULL;
    }
    {
      int rc = PyObject_SetAttrString(_pymessage, "end_time", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // is_active
    PyObject * field = NULL;
    field = PyBool_FromLong(ros_message->is_active ? 1 : 0);
    {
      int rc = PyObject_SetAttrString(_pymessage, "is_active", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }

  // ownership of _pymessage is transferred to the caller
  return _pymessage;
}
