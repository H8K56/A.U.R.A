// generated from rosidl_generator_py/resource/_idl_support.c.em
// with input from aura_msgs:msg/CoverageGoal.idl
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
#include "aura_msgs/msg/detail/coverage_goal__struct.h"
#include "aura_msgs/msg/detail/coverage_goal__functions.h"

ROSIDL_GENERATOR_C_IMPORT
bool builtin_interfaces__msg__time__convert_from_py(PyObject * _pymsg, void * _ros_message);
ROSIDL_GENERATOR_C_IMPORT
PyObject * builtin_interfaces__msg__time__convert_to_py(void * raw_ros_message);
ROSIDL_GENERATOR_C_IMPORT
bool geometry_msgs__msg__point__convert_from_py(PyObject * _pymsg, void * _ros_message);
ROSIDL_GENERATOR_C_IMPORT
PyObject * geometry_msgs__msg__point__convert_to_py(void * raw_ros_message);

ROSIDL_GENERATOR_C_EXPORT
bool aura_msgs__msg__coverage_goal__convert_from_py(PyObject * _pymsg, void * _ros_message)
{
  // check that the passed message is of the expected Python class
  {
    char full_classname_dest[42];
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
    assert(strncmp("aura_msgs.msg._coverage_goal.CoverageGoal", full_classname_dest, 41) == 0);
  }
  aura_msgs__msg__CoverageGoal * ros_message = _ros_message;
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
  {  // drone_id
    PyObject * field = PyObject_GetAttrString(_pymsg, "drone_id");
    if (!field) {
      return false;
    }
    assert(PyLong_Check(field));
    ros_message->drone_id = (uint8_t)PyLong_AsUnsignedLong(field);
    Py_DECREF(field);
  }
  {  // position
    PyObject * field = PyObject_GetAttrString(_pymsg, "position");
    if (!field) {
      return false;
    }
    if (!geometry_msgs__msg__point__convert_from_py(field, &ros_message->position)) {
      Py_DECREF(field);
      return false;
    }
    Py_DECREF(field);
  }
  {  // desired_arrival_time
    PyObject * field = PyObject_GetAttrString(_pymsg, "desired_arrival_time");
    if (!field) {
      return false;
    }
    assert(PyFloat_Check(field));
    ros_message->desired_arrival_time = PyFloat_AS_DOUBLE(field);
    Py_DECREF(field);
  }
  {  // formation_type
    PyObject * field = PyObject_GetAttrString(_pymsg, "formation_type");
    if (!field) {
      return false;
    }
    assert(PyLong_Check(field));
    ros_message->formation_type = (uint8_t)PyLong_AsUnsignedLong(field);
    Py_DECREF(field);
  }
  {  // priority
    PyObject * field = PyObject_GetAttrString(_pymsg, "priority");
    if (!field) {
      return false;
    }
    assert(PyFloat_Check(field));
    ros_message->priority = (float)PyFloat_AS_DOUBLE(field);
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
  {  // max_velocity
    PyObject * field = PyObject_GetAttrString(_pymsg, "max_velocity");
    if (!field) {
      return false;
    }
    assert(PyFloat_Check(field));
    ros_message->max_velocity = (float)PyFloat_AS_DOUBLE(field);
    Py_DECREF(field);
  }
  {  // required_throughput_mbps
    PyObject * field = PyObject_GetAttrString(_pymsg, "required_throughput_mbps");
    if (!field) {
      return false;
    }
    assert(PyFloat_Check(field));
    ros_message->required_throughput_mbps = (float)PyFloat_AS_DOUBLE(field);
    Py_DECREF(field);
  }
  {  // required_coverage_radius
    PyObject * field = PyObject_GetAttrString(_pymsg, "required_coverage_radius");
    if (!field) {
      return false;
    }
    assert(PyFloat_Check(field));
    ros_message->required_coverage_radius = (float)PyFloat_AS_DOUBLE(field);
    Py_DECREF(field);
  }

  return true;
}

ROSIDL_GENERATOR_C_EXPORT
PyObject * aura_msgs__msg__coverage_goal__convert_to_py(void * raw_ros_message)
{
  /* NOTE(esteve): Call constructor of CoverageGoal */
  PyObject * _pymessage = NULL;
  {
    PyObject * pymessage_module = PyImport_ImportModule("aura_msgs.msg._coverage_goal");
    assert(pymessage_module);
    PyObject * pymessage_class = PyObject_GetAttrString(pymessage_module, "CoverageGoal");
    assert(pymessage_class);
    Py_DECREF(pymessage_module);
    _pymessage = PyObject_CallObject(pymessage_class, NULL);
    Py_DECREF(pymessage_class);
    if (!_pymessage) {
      return NULL;
    }
  }
  aura_msgs__msg__CoverageGoal * ros_message = (aura_msgs__msg__CoverageGoal *)raw_ros_message;
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
  {  // drone_id
    PyObject * field = NULL;
    field = PyLong_FromUnsignedLong(ros_message->drone_id);
    {
      int rc = PyObject_SetAttrString(_pymessage, "drone_id", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // position
    PyObject * field = NULL;
    field = geometry_msgs__msg__point__convert_to_py(&ros_message->position);
    if (!field) {
      return NULL;
    }
    {
      int rc = PyObject_SetAttrString(_pymessage, "position", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // desired_arrival_time
    PyObject * field = NULL;
    field = PyFloat_FromDouble(ros_message->desired_arrival_time);
    {
      int rc = PyObject_SetAttrString(_pymessage, "desired_arrival_time", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // formation_type
    PyObject * field = NULL;
    field = PyLong_FromUnsignedLong(ros_message->formation_type);
    {
      int rc = PyObject_SetAttrString(_pymessage, "formation_type", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // priority
    PyObject * field = NULL;
    field = PyFloat_FromDouble(ros_message->priority);
    {
      int rc = PyObject_SetAttrString(_pymessage, "priority", field);
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
  {  // max_velocity
    PyObject * field = NULL;
    field = PyFloat_FromDouble(ros_message->max_velocity);
    {
      int rc = PyObject_SetAttrString(_pymessage, "max_velocity", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // required_throughput_mbps
    PyObject * field = NULL;
    field = PyFloat_FromDouble(ros_message->required_throughput_mbps);
    {
      int rc = PyObject_SetAttrString(_pymessage, "required_throughput_mbps", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // required_coverage_radius
    PyObject * field = NULL;
    field = PyFloat_FromDouble(ros_message->required_coverage_radius);
    {
      int rc = PyObject_SetAttrString(_pymessage, "required_coverage_radius", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }

  // ownership of _pymessage is transferred to the caller
  return _pymessage;
}
