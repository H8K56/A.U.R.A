// generated from rosidl_generator_py/resource/_idl_support.c.em
// with input from aura_msgs:msg/MissionStatus.idl
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
#include "aura_msgs/msg/detail/mission_status__struct.h"
#include "aura_msgs/msg/detail/mission_status__functions.h"

#include "rosidl_runtime_c/string.h"
#include "rosidl_runtime_c/string_functions.h"

#include "rosidl_runtime_c/primitives_sequence.h"
#include "rosidl_runtime_c/primitives_sequence_functions.h"

ROSIDL_GENERATOR_C_IMPORT
bool builtin_interfaces__msg__time__convert_from_py(PyObject * _pymsg, void * _ros_message);
ROSIDL_GENERATOR_C_IMPORT
PyObject * builtin_interfaces__msg__time__convert_to_py(void * raw_ros_message);

ROSIDL_GENERATOR_C_EXPORT
bool aura_msgs__msg__mission_status__convert_from_py(PyObject * _pymsg, void * _ros_message)
{
  // check that the passed message is of the expected Python class
  {
    char full_classname_dest[44];
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
    assert(strncmp("aura_msgs.msg._mission_status.MissionStatus", full_classname_dest, 43) == 0);
  }
  aura_msgs__msg__MissionStatus * ros_message = _ros_message;
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
  {  // mission_id
    PyObject * field = PyObject_GetAttrString(_pymsg, "mission_id");
    if (!field) {
      return false;
    }
    assert(PyUnicode_Check(field));
    PyObject * encoded_field = PyUnicode_AsUTF8String(field);
    if (!encoded_field) {
      Py_DECREF(field);
      return false;
    }
    rosidl_runtime_c__String__assign(&ros_message->mission_id, PyBytes_AS_STRING(encoded_field));
    Py_DECREF(encoded_field);
    Py_DECREF(field);
  }
  {  // phase
    PyObject * field = PyObject_GetAttrString(_pymsg, "phase");
    if (!field) {
      return false;
    }
    assert(PyLong_Check(field));
    ros_message->phase = (uint8_t)PyLong_AsUnsignedLong(field);
    Py_DECREF(field);
  }
  {  // progress_percent
    PyObject * field = PyObject_GetAttrString(_pymsg, "progress_percent");
    if (!field) {
      return false;
    }
    assert(PyFloat_Check(field));
    ros_message->progress_percent = (float)PyFloat_AS_DOUBLE(field);
    Py_DECREF(field);
  }
  {  // elapsed_time_sec
    PyObject * field = PyObject_GetAttrString(_pymsg, "elapsed_time_sec");
    if (!field) {
      return false;
    }
    assert(PyFloat_Check(field));
    ros_message->elapsed_time_sec = (float)PyFloat_AS_DOUBLE(field);
    Py_DECREF(field);
  }
  {  // estimated_remaining_sec
    PyObject * field = PyObject_GetAttrString(_pymsg, "estimated_remaining_sec");
    if (!field) {
      return false;
    }
    assert(PyFloat_Check(field));
    ros_message->estimated_remaining_sec = (float)PyFloat_AS_DOUBLE(field);
    Py_DECREF(field);
  }
  {  // coverage_achieved
    PyObject * field = PyObject_GetAttrString(_pymsg, "coverage_achieved");
    if (!field) {
      return false;
    }
    assert(PyFloat_Check(field));
    ros_message->coverage_achieved = (float)PyFloat_AS_DOUBLE(field);
    Py_DECREF(field);
  }
  {  // network_quality
    PyObject * field = PyObject_GetAttrString(_pymsg, "network_quality");
    if (!field) {
      return false;
    }
    assert(PyFloat_Check(field));
    ros_message->network_quality = (float)PyFloat_AS_DOUBLE(field);
    Py_DECREF(field);
  }
  {  // connections_established
    PyObject * field = PyObject_GetAttrString(_pymsg, "connections_established");
    if (!field) {
      return false;
    }
    assert(PyLong_Check(field));
    ros_message->connections_established = PyLong_AsUnsignedLong(field);
    Py_DECREF(field);
  }
  {  // data_transferred_mb
    PyObject * field = PyObject_GetAttrString(_pymsg, "data_transferred_mb");
    if (!field) {
      return false;
    }
    assert(PyLong_Check(field));
    ros_message->data_transferred_mb = PyLong_AsUnsignedLong(field);
    Py_DECREF(field);
  }
  {  // active_alerts
    PyObject * field = PyObject_GetAttrString(_pymsg, "active_alerts");
    if (!field) {
      return false;
    }
    {
      PyObject * seq_field = PySequence_Fast(field, "expected a sequence in 'active_alerts'");
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
      if (!rosidl_runtime_c__String__Sequence__init(&(ros_message->active_alerts), size)) {
        PyErr_SetString(PyExc_RuntimeError, "unable to create String__Sequence ros_message");
        Py_DECREF(seq_field);
        Py_DECREF(field);
        return false;
      }
      rosidl_runtime_c__String * dest = ros_message->active_alerts.data;
      for (Py_ssize_t i = 0; i < size; ++i) {
        PyObject * item = PySequence_Fast_GET_ITEM(seq_field, i);
        if (!item) {
          Py_DECREF(seq_field);
          Py_DECREF(field);
          return false;
        }
        assert(PyUnicode_Check(item));
        PyObject * encoded_item = PyUnicode_AsUTF8String(item);
        if (!encoded_item) {
          Py_DECREF(seq_field);
          Py_DECREF(field);
          return false;
        }
        rosidl_runtime_c__String__assign(&dest[i], PyBytes_AS_STRING(encoded_item));
        Py_DECREF(encoded_item);
      }
      Py_DECREF(seq_field);
    }
    Py_DECREF(field);
  }
  {  // alert_severities
    PyObject * field = PyObject_GetAttrString(_pymsg, "alert_severities");
    if (!field) {
      return false;
    }
    if (PyObject_CheckBuffer(field)) {
      // Optimization for converting arrays of primitives
      Py_buffer view;
      int rc = PyObject_GetBuffer(field, &view, PyBUF_SIMPLE);
      if (rc < 0) {
        Py_DECREF(field);
        return false;
      }
      Py_ssize_t size = view.len / sizeof(uint8_t);
      if (!rosidl_runtime_c__uint8__Sequence__init(&(ros_message->alert_severities), size)) {
        PyErr_SetString(PyExc_RuntimeError, "unable to create uint8__Sequence ros_message");
        PyBuffer_Release(&view);
        Py_DECREF(field);
        return false;
      }
      uint8_t * dest = ros_message->alert_severities.data;
      rc = PyBuffer_ToContiguous(dest, &view, view.len, 'C');
      if (rc < 0) {
        PyBuffer_Release(&view);
        Py_DECREF(field);
        return false;
      }
      PyBuffer_Release(&view);
    } else {
      PyObject * seq_field = PySequence_Fast(field, "expected a sequence in 'alert_severities'");
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
      if (!rosidl_runtime_c__uint8__Sequence__init(&(ros_message->alert_severities), size)) {
        PyErr_SetString(PyExc_RuntimeError, "unable to create uint8__Sequence ros_message");
        Py_DECREF(seq_field);
        Py_DECREF(field);
        return false;
      }
      uint8_t * dest = ros_message->alert_severities.data;
      for (Py_ssize_t i = 0; i < size; ++i) {
        PyObject * item = PySequence_Fast_GET_ITEM(seq_field, i);
        if (!item) {
          Py_DECREF(seq_field);
          Py_DECREF(field);
          return false;
        }
        assert(PyLong_Check(item));
        uint8_t tmp = (uint8_t)PyLong_AsUnsignedLong(item);

        memcpy(&dest[i], &tmp, sizeof(uint8_t));
      }
      Py_DECREF(seq_field);
    }
    Py_DECREF(field);
  }
  {  // drones_operational
    PyObject * field = PyObject_GetAttrString(_pymsg, "drones_operational");
    if (!field) {
      return false;
    }
    assert(PyLong_Check(field));
    ros_message->drones_operational = (uint8_t)PyLong_AsUnsignedLong(field);
    Py_DECREF(field);
  }
  {  // drones_degraded
    PyObject * field = PyObject_GetAttrString(_pymsg, "drones_degraded");
    if (!field) {
      return false;
    }
    assert(PyLong_Check(field));
    ros_message->drones_degraded = (uint8_t)PyLong_AsUnsignedLong(field);
    Py_DECREF(field);
  }
  {  // drones_failed
    PyObject * field = PyObject_GetAttrString(_pymsg, "drones_failed");
    if (!field) {
      return false;
    }
    assert(PyLong_Check(field));
    ros_message->drones_failed = (uint8_t)PyLong_AsUnsignedLong(field);
    Py_DECREF(field);
  }

  return true;
}

ROSIDL_GENERATOR_C_EXPORT
PyObject * aura_msgs__msg__mission_status__convert_to_py(void * raw_ros_message)
{
  /* NOTE(esteve): Call constructor of MissionStatus */
  PyObject * _pymessage = NULL;
  {
    PyObject * pymessage_module = PyImport_ImportModule("aura_msgs.msg._mission_status");
    assert(pymessage_module);
    PyObject * pymessage_class = PyObject_GetAttrString(pymessage_module, "MissionStatus");
    assert(pymessage_class);
    Py_DECREF(pymessage_module);
    _pymessage = PyObject_CallObject(pymessage_class, NULL);
    Py_DECREF(pymessage_class);
    if (!_pymessage) {
      return NULL;
    }
  }
  aura_msgs__msg__MissionStatus * ros_message = (aura_msgs__msg__MissionStatus *)raw_ros_message;
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
  {  // mission_id
    PyObject * field = NULL;
    field = PyUnicode_DecodeUTF8(
      ros_message->mission_id.data,
      strlen(ros_message->mission_id.data),
      "replace");
    if (!field) {
      return NULL;
    }
    {
      int rc = PyObject_SetAttrString(_pymessage, "mission_id", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // phase
    PyObject * field = NULL;
    field = PyLong_FromUnsignedLong(ros_message->phase);
    {
      int rc = PyObject_SetAttrString(_pymessage, "phase", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // progress_percent
    PyObject * field = NULL;
    field = PyFloat_FromDouble(ros_message->progress_percent);
    {
      int rc = PyObject_SetAttrString(_pymessage, "progress_percent", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // elapsed_time_sec
    PyObject * field = NULL;
    field = PyFloat_FromDouble(ros_message->elapsed_time_sec);
    {
      int rc = PyObject_SetAttrString(_pymessage, "elapsed_time_sec", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // estimated_remaining_sec
    PyObject * field = NULL;
    field = PyFloat_FromDouble(ros_message->estimated_remaining_sec);
    {
      int rc = PyObject_SetAttrString(_pymessage, "estimated_remaining_sec", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // coverage_achieved
    PyObject * field = NULL;
    field = PyFloat_FromDouble(ros_message->coverage_achieved);
    {
      int rc = PyObject_SetAttrString(_pymessage, "coverage_achieved", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // network_quality
    PyObject * field = NULL;
    field = PyFloat_FromDouble(ros_message->network_quality);
    {
      int rc = PyObject_SetAttrString(_pymessage, "network_quality", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // connections_established
    PyObject * field = NULL;
    field = PyLong_FromUnsignedLong(ros_message->connections_established);
    {
      int rc = PyObject_SetAttrString(_pymessage, "connections_established", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // data_transferred_mb
    PyObject * field = NULL;
    field = PyLong_FromUnsignedLong(ros_message->data_transferred_mb);
    {
      int rc = PyObject_SetAttrString(_pymessage, "data_transferred_mb", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // active_alerts
    PyObject * field = NULL;
    size_t size = ros_message->active_alerts.size;
    rosidl_runtime_c__String * src = ros_message->active_alerts.data;
    field = PyList_New(size);
    if (!field) {
      return NULL;
    }
    for (size_t i = 0; i < size; ++i) {
      PyObject * decoded_item = PyUnicode_DecodeUTF8(src[i].data, strlen(src[i].data), "replace");
      if (!decoded_item) {
        return NULL;
      }
      int rc = PyList_SetItem(field, i, decoded_item);
      (void)rc;
      assert(rc == 0);
    }
    assert(PySequence_Check(field));
    {
      int rc = PyObject_SetAttrString(_pymessage, "active_alerts", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // alert_severities
    PyObject * field = NULL;
    field = PyObject_GetAttrString(_pymessage, "alert_severities");
    if (!field) {
      return NULL;
    }
    assert(field->ob_type != NULL);
    assert(field->ob_type->tp_name != NULL);
    assert(strcmp(field->ob_type->tp_name, "array.array") == 0);
    // ensure that itemsize matches the sizeof of the ROS message field
    PyObject * itemsize_attr = PyObject_GetAttrString(field, "itemsize");
    assert(itemsize_attr != NULL);
    size_t itemsize = PyLong_AsSize_t(itemsize_attr);
    Py_DECREF(itemsize_attr);
    if (itemsize != sizeof(uint8_t)) {
      PyErr_SetString(PyExc_RuntimeError, "itemsize doesn't match expectation");
      Py_DECREF(field);
      return NULL;
    }
    // clear the array, poor approach to remove potential default values
    Py_ssize_t length = PyObject_Length(field);
    if (-1 == length) {
      Py_DECREF(field);
      return NULL;
    }
    if (length > 0) {
      PyObject * pop = PyObject_GetAttrString(field, "pop");
      assert(pop != NULL);
      for (Py_ssize_t i = 0; i < length; ++i) {
        PyObject * ret = PyObject_CallFunctionObjArgs(pop, NULL);
        if (!ret) {
          Py_DECREF(pop);
          Py_DECREF(field);
          return NULL;
        }
        Py_DECREF(ret);
      }
      Py_DECREF(pop);
    }
    if (ros_message->alert_severities.size > 0) {
      // populating the array.array using the frombytes method
      PyObject * frombytes = PyObject_GetAttrString(field, "frombytes");
      assert(frombytes != NULL);
      uint8_t * src = &(ros_message->alert_severities.data[0]);
      PyObject * data = PyBytes_FromStringAndSize((const char *)src, ros_message->alert_severities.size * sizeof(uint8_t));
      assert(data != NULL);
      PyObject * ret = PyObject_CallFunctionObjArgs(frombytes, data, NULL);
      Py_DECREF(data);
      Py_DECREF(frombytes);
      if (!ret) {
        Py_DECREF(field);
        return NULL;
      }
      Py_DECREF(ret);
    }
    Py_DECREF(field);
  }
  {  // drones_operational
    PyObject * field = NULL;
    field = PyLong_FromUnsignedLong(ros_message->drones_operational);
    {
      int rc = PyObject_SetAttrString(_pymessage, "drones_operational", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // drones_degraded
    PyObject * field = NULL;
    field = PyLong_FromUnsignedLong(ros_message->drones_degraded);
    {
      int rc = PyObject_SetAttrString(_pymessage, "drones_degraded", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // drones_failed
    PyObject * field = NULL;
    field = PyLong_FromUnsignedLong(ros_message->drones_failed);
    {
      int rc = PyObject_SetAttrString(_pymessage, "drones_failed", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }

  // ownership of _pymessage is transferred to the caller
  return _pymessage;
}
