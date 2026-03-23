// generated from rosidl_generator_py/resource/_idl_support.c.em
// with input from aura_msgs:msg/SwarmState.idl
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
#include "aura_msgs/msg/detail/swarm_state__struct.h"
#include "aura_msgs/msg/detail/swarm_state__functions.h"

#include "rosidl_runtime_c/primitives_sequence.h"
#include "rosidl_runtime_c/primitives_sequence_functions.h"

// Nested array functions includes
#include "aura_msgs/msg/detail/drone_state__functions.h"
// end nested array functions include
ROSIDL_GENERATOR_C_IMPORT
bool builtin_interfaces__msg__time__convert_from_py(PyObject * _pymsg, void * _ros_message);
ROSIDL_GENERATOR_C_IMPORT
PyObject * builtin_interfaces__msg__time__convert_to_py(void * raw_ros_message);
bool aura_msgs__msg__drone_state__convert_from_py(PyObject * _pymsg, void * _ros_message);
PyObject * aura_msgs__msg__drone_state__convert_to_py(void * raw_ros_message);

ROSIDL_GENERATOR_C_EXPORT
bool aura_msgs__msg__swarm_state__convert_from_py(PyObject * _pymsg, void * _ros_message)
{
  // check that the passed message is of the expected Python class
  {
    char full_classname_dest[38];
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
    assert(strncmp("aura_msgs.msg._swarm_state.SwarmState", full_classname_dest, 37) == 0);
  }
  aura_msgs__msg__SwarmState * ros_message = _ros_message;
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
  {  // num_drones_total
    PyObject * field = PyObject_GetAttrString(_pymsg, "num_drones_total");
    if (!field) {
      return false;
    }
    assert(PyLong_Check(field));
    ros_message->num_drones_total = (uint8_t)PyLong_AsUnsignedLong(field);
    Py_DECREF(field);
  }
  {  // num_drones_active
    PyObject * field = PyObject_GetAttrString(_pymsg, "num_drones_active");
    if (!field) {
      return false;
    }
    assert(PyLong_Check(field));
    ros_message->num_drones_active = (uint8_t)PyLong_AsUnsignedLong(field);
    Py_DECREF(field);
  }
  {  // num_hubs
    PyObject * field = PyObject_GetAttrString(_pymsg, "num_hubs");
    if (!field) {
      return false;
    }
    assert(PyLong_Check(field));
    ros_message->num_hubs = (uint8_t)PyLong_AsUnsignedLong(field);
    Py_DECREF(field);
  }
  {  // num_leaves
    PyObject * field = PyObject_GetAttrString(_pymsg, "num_leaves");
    if (!field) {
      return false;
    }
    assert(PyLong_Check(field));
    ros_message->num_leaves = (uint8_t)PyLong_AsUnsignedLong(field);
    Py_DECREF(field);
  }
  {  // mission_state
    PyObject * field = PyObject_GetAttrString(_pymsg, "mission_state");
    if (!field) {
      return false;
    }
    assert(PyLong_Check(field));
    ros_message->mission_state = (uint8_t)PyLong_AsUnsignedLong(field);
    Py_DECREF(field);
  }
  {  // coverage_percent
    PyObject * field = PyObject_GetAttrString(_pymsg, "coverage_percent");
    if (!field) {
      return false;
    }
    assert(PyFloat_Check(field));
    ros_message->coverage_percent = (float)PyFloat_AS_DOUBLE(field);
    Py_DECREF(field);
  }
  {  // coverage_quality
    PyObject * field = PyObject_GetAttrString(_pymsg, "coverage_quality");
    if (!field) {
      return false;
    }
    assert(PyFloat_Check(field));
    ros_message->coverage_quality = (float)PyFloat_AS_DOUBLE(field);
    Py_DECREF(field);
  }
  {  // avg_throughput_mbps
    PyObject * field = PyObject_GetAttrString(_pymsg, "avg_throughput_mbps");
    if (!field) {
      return false;
    }
    assert(PyFloat_Check(field));
    ros_message->avg_throughput_mbps = (float)PyFloat_AS_DOUBLE(field);
    Py_DECREF(field);
  }
  {  // avg_latency_ms
    PyObject * field = PyObject_GetAttrString(_pymsg, "avg_latency_ms");
    if (!field) {
      return false;
    }
    assert(PyFloat_Check(field));
    ros_message->avg_latency_ms = (float)PyFloat_AS_DOUBLE(field);
    Py_DECREF(field);
  }
  {  // packet_loss_percent
    PyObject * field = PyObject_GetAttrString(_pymsg, "packet_loss_percent");
    if (!field) {
      return false;
    }
    assert(PyFloat_Check(field));
    ros_message->packet_loss_percent = (float)PyFloat_AS_DOUBLE(field);
    Py_DECREF(field);
  }
  {  // mesh_connected
    PyObject * field = PyObject_GetAttrString(_pymsg, "mesh_connected");
    if (!field) {
      return false;
    }
    assert(PyBool_Check(field));
    ros_message->mesh_connected = (Py_True == field);
    Py_DECREF(field);
  }
  {  // backhaul_connected
    PyObject * field = PyObject_GetAttrString(_pymsg, "backhaul_connected");
    if (!field) {
      return false;
    }
    assert(PyBool_Check(field));
    ros_message->backhaul_connected = (Py_True == field);
    Py_DECREF(field);
  }
  {  // drones
    PyObject * field = PyObject_GetAttrString(_pymsg, "drones");
    if (!field) {
      return false;
    }
    PyObject * seq_field = PySequence_Fast(field, "expected a sequence in 'drones'");
    if (!seq_field) {
      Py_DECREF(field);
      return false;
    }
    Py_ssize_t size = PySequence_Size(field);
    if (-1 == size) {
      Py_DECREF(seq_field);
      Py_DECREF(field);
      return false;
    }
    if (!aura_msgs__msg__DroneState__Sequence__init(&(ros_message->drones), size)) {
      PyErr_SetString(PyExc_RuntimeError, "unable to create aura_msgs__msg__DroneState__Sequence ros_message");
      Py_DECREF(seq_field);
      Py_DECREF(field);
      return false;
    }
    aura_msgs__msg__DroneState * dest = ros_message->drones.data;
    for (Py_ssize_t i = 0; i < size; ++i) {
      if (!aura_msgs__msg__drone_state__convert_from_py(PySequence_Fast_GET_ITEM(seq_field, i), &dest[i])) {
        Py_DECREF(seq_field);
        Py_DECREF(field);
        return false;
      }
    }
    Py_DECREF(seq_field);
    Py_DECREF(field);
  }

  return true;
}

ROSIDL_GENERATOR_C_EXPORT
PyObject * aura_msgs__msg__swarm_state__convert_to_py(void * raw_ros_message)
{
  /* NOTE(esteve): Call constructor of SwarmState */
  PyObject * _pymessage = NULL;
  {
    PyObject * pymessage_module = PyImport_ImportModule("aura_msgs.msg._swarm_state");
    assert(pymessage_module);
    PyObject * pymessage_class = PyObject_GetAttrString(pymessage_module, "SwarmState");
    assert(pymessage_class);
    Py_DECREF(pymessage_module);
    _pymessage = PyObject_CallObject(pymessage_class, NULL);
    Py_DECREF(pymessage_class);
    if (!_pymessage) {
      return NULL;
    }
  }
  aura_msgs__msg__SwarmState * ros_message = (aura_msgs__msg__SwarmState *)raw_ros_message;
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
  {  // num_drones_total
    PyObject * field = NULL;
    field = PyLong_FromUnsignedLong(ros_message->num_drones_total);
    {
      int rc = PyObject_SetAttrString(_pymessage, "num_drones_total", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // num_drones_active
    PyObject * field = NULL;
    field = PyLong_FromUnsignedLong(ros_message->num_drones_active);
    {
      int rc = PyObject_SetAttrString(_pymessage, "num_drones_active", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // num_hubs
    PyObject * field = NULL;
    field = PyLong_FromUnsignedLong(ros_message->num_hubs);
    {
      int rc = PyObject_SetAttrString(_pymessage, "num_hubs", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // num_leaves
    PyObject * field = NULL;
    field = PyLong_FromUnsignedLong(ros_message->num_leaves);
    {
      int rc = PyObject_SetAttrString(_pymessage, "num_leaves", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // mission_state
    PyObject * field = NULL;
    field = PyLong_FromUnsignedLong(ros_message->mission_state);
    {
      int rc = PyObject_SetAttrString(_pymessage, "mission_state", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // coverage_percent
    PyObject * field = NULL;
    field = PyFloat_FromDouble(ros_message->coverage_percent);
    {
      int rc = PyObject_SetAttrString(_pymessage, "coverage_percent", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // coverage_quality
    PyObject * field = NULL;
    field = PyFloat_FromDouble(ros_message->coverage_quality);
    {
      int rc = PyObject_SetAttrString(_pymessage, "coverage_quality", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // avg_throughput_mbps
    PyObject * field = NULL;
    field = PyFloat_FromDouble(ros_message->avg_throughput_mbps);
    {
      int rc = PyObject_SetAttrString(_pymessage, "avg_throughput_mbps", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // avg_latency_ms
    PyObject * field = NULL;
    field = PyFloat_FromDouble(ros_message->avg_latency_ms);
    {
      int rc = PyObject_SetAttrString(_pymessage, "avg_latency_ms", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // packet_loss_percent
    PyObject * field = NULL;
    field = PyFloat_FromDouble(ros_message->packet_loss_percent);
    {
      int rc = PyObject_SetAttrString(_pymessage, "packet_loss_percent", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // mesh_connected
    PyObject * field = NULL;
    field = PyBool_FromLong(ros_message->mesh_connected ? 1 : 0);
    {
      int rc = PyObject_SetAttrString(_pymessage, "mesh_connected", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // backhaul_connected
    PyObject * field = NULL;
    field = PyBool_FromLong(ros_message->backhaul_connected ? 1 : 0);
    {
      int rc = PyObject_SetAttrString(_pymessage, "backhaul_connected", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // drones
    PyObject * field = NULL;
    size_t size = ros_message->drones.size;
    field = PyList_New(size);
    if (!field) {
      return NULL;
    }
    aura_msgs__msg__DroneState * item;
    for (size_t i = 0; i < size; ++i) {
      item = &(ros_message->drones.data[i]);
      PyObject * pyitem = aura_msgs__msg__drone_state__convert_to_py(item);
      if (!pyitem) {
        Py_DECREF(field);
        return NULL;
      }
      int rc = PyList_SetItem(field, i, pyitem);
      (void)rc;
      assert(rc == 0);
    }
    assert(PySequence_Check(field));
    {
      int rc = PyObject_SetAttrString(_pymessage, "drones", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }

  // ownership of _pymessage is transferred to the caller
  return _pymessage;
}
