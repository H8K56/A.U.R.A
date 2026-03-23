// generated from rosidl_generator_py/resource/_idl_support.c.em
// with input from aura_msgs:srv/GetNetworkStatus.idl
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
#include "aura_msgs/srv/detail/get_network_status__struct.h"
#include "aura_msgs/srv/detail/get_network_status__functions.h"


ROSIDL_GENERATOR_C_EXPORT
bool aura_msgs__srv__get_network_status__request__convert_from_py(PyObject * _pymsg, void * _ros_message)
{
  // check that the passed message is of the expected Python class
  {
    char full_classname_dest[59];
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
    assert(strncmp("aura_msgs.srv._get_network_status.GetNetworkStatus_Request", full_classname_dest, 58) == 0);
  }
  aura_msgs__srv__GetNetworkStatus_Request * ros_message = _ros_message;
  {  // include_coverage_map
    PyObject * field = PyObject_GetAttrString(_pymsg, "include_coverage_map");
    if (!field) {
      return false;
    }
    assert(PyBool_Check(field));
    ros_message->include_coverage_map = (Py_True == field);
    Py_DECREF(field);
  }
  {  // include_link_details
    PyObject * field = PyObject_GetAttrString(_pymsg, "include_link_details");
    if (!field) {
      return false;
    }
    assert(PyBool_Check(field));
    ros_message->include_link_details = (Py_True == field);
    Py_DECREF(field);
  }

  return true;
}

ROSIDL_GENERATOR_C_EXPORT
PyObject * aura_msgs__srv__get_network_status__request__convert_to_py(void * raw_ros_message)
{
  /* NOTE(esteve): Call constructor of GetNetworkStatus_Request */
  PyObject * _pymessage = NULL;
  {
    PyObject * pymessage_module = PyImport_ImportModule("aura_msgs.srv._get_network_status");
    assert(pymessage_module);
    PyObject * pymessage_class = PyObject_GetAttrString(pymessage_module, "GetNetworkStatus_Request");
    assert(pymessage_class);
    Py_DECREF(pymessage_module);
    _pymessage = PyObject_CallObject(pymessage_class, NULL);
    Py_DECREF(pymessage_class);
    if (!_pymessage) {
      return NULL;
    }
  }
  aura_msgs__srv__GetNetworkStatus_Request * ros_message = (aura_msgs__srv__GetNetworkStatus_Request *)raw_ros_message;
  {  // include_coverage_map
    PyObject * field = NULL;
    field = PyBool_FromLong(ros_message->include_coverage_map ? 1 : 0);
    {
      int rc = PyObject_SetAttrString(_pymessage, "include_coverage_map", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // include_link_details
    PyObject * field = NULL;
    field = PyBool_FromLong(ros_message->include_link_details ? 1 : 0);
    {
      int rc = PyObject_SetAttrString(_pymessage, "include_link_details", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }

  // ownership of _pymessage is transferred to the caller
  return _pymessage;
}

#define NPY_NO_DEPRECATED_API NPY_1_7_API_VERSION
// already included above
// #include <Python.h>
// already included above
// #include <stdbool.h>
// already included above
// #include "numpy/ndarrayobject.h"
// already included above
// #include "rosidl_runtime_c/visibility_control.h"
// already included above
// #include "aura_msgs/srv/detail/get_network_status__struct.h"
// already included above
// #include "aura_msgs/srv/detail/get_network_status__functions.h"

#include "rosidl_runtime_c/primitives_sequence.h"
#include "rosidl_runtime_c/primitives_sequence_functions.h"
#include "rosidl_runtime_c/string.h"
#include "rosidl_runtime_c/string_functions.h"

bool aura_msgs__msg__network_metrics__convert_from_py(PyObject * _pymsg, void * _ros_message);
PyObject * aura_msgs__msg__network_metrics__convert_to_py(void * raw_ros_message);

ROSIDL_GENERATOR_C_EXPORT
bool aura_msgs__srv__get_network_status__response__convert_from_py(PyObject * _pymsg, void * _ros_message)
{
  // check that the passed message is of the expected Python class
  {
    char full_classname_dest[60];
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
    assert(strncmp("aura_msgs.srv._get_network_status.GetNetworkStatus_Response", full_classname_dest, 59) == 0);
  }
  aura_msgs__srv__GetNetworkStatus_Response * ros_message = _ros_message;
  {  // success
    PyObject * field = PyObject_GetAttrString(_pymsg, "success");
    if (!field) {
      return false;
    }
    assert(PyBool_Check(field));
    ros_message->success = (Py_True == field);
    Py_DECREF(field);
  }
  {  // metrics
    PyObject * field = PyObject_GetAttrString(_pymsg, "metrics");
    if (!field) {
      return false;
    }
    if (!aura_msgs__msg__network_metrics__convert_from_py(field, &ros_message->metrics)) {
      Py_DECREF(field);
      return false;
    }
    Py_DECREF(field);
  }
  {  // overall_health
    PyObject * field = PyObject_GetAttrString(_pymsg, "overall_health");
    if (!field) {
      return false;
    }
    assert(PyFloat_Check(field));
    ros_message->overall_health = (float)PyFloat_AS_DOUBLE(field);
    Py_DECREF(field);
  }
  {  // issues
    PyObject * field = PyObject_GetAttrString(_pymsg, "issues");
    if (!field) {
      return false;
    }
    {
      PyObject * seq_field = PySequence_Fast(field, "expected a sequence in 'issues'");
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
      if (!rosidl_runtime_c__String__Sequence__init(&(ros_message->issues), size)) {
        PyErr_SetString(PyExc_RuntimeError, "unable to create String__Sequence ros_message");
        Py_DECREF(seq_field);
        Py_DECREF(field);
        return false;
      }
      rosidl_runtime_c__String * dest = ros_message->issues.data;
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

  return true;
}

ROSIDL_GENERATOR_C_EXPORT
PyObject * aura_msgs__srv__get_network_status__response__convert_to_py(void * raw_ros_message)
{
  /* NOTE(esteve): Call constructor of GetNetworkStatus_Response */
  PyObject * _pymessage = NULL;
  {
    PyObject * pymessage_module = PyImport_ImportModule("aura_msgs.srv._get_network_status");
    assert(pymessage_module);
    PyObject * pymessage_class = PyObject_GetAttrString(pymessage_module, "GetNetworkStatus_Response");
    assert(pymessage_class);
    Py_DECREF(pymessage_module);
    _pymessage = PyObject_CallObject(pymessage_class, NULL);
    Py_DECREF(pymessage_class);
    if (!_pymessage) {
      return NULL;
    }
  }
  aura_msgs__srv__GetNetworkStatus_Response * ros_message = (aura_msgs__srv__GetNetworkStatus_Response *)raw_ros_message;
  {  // success
    PyObject * field = NULL;
    field = PyBool_FromLong(ros_message->success ? 1 : 0);
    {
      int rc = PyObject_SetAttrString(_pymessage, "success", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // metrics
    PyObject * field = NULL;
    field = aura_msgs__msg__network_metrics__convert_to_py(&ros_message->metrics);
    if (!field) {
      return NULL;
    }
    {
      int rc = PyObject_SetAttrString(_pymessage, "metrics", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // overall_health
    PyObject * field = NULL;
    field = PyFloat_FromDouble(ros_message->overall_health);
    {
      int rc = PyObject_SetAttrString(_pymessage, "overall_health", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // issues
    PyObject * field = NULL;
    size_t size = ros_message->issues.size;
    rosidl_runtime_c__String * src = ros_message->issues.data;
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
      int rc = PyObject_SetAttrString(_pymessage, "issues", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }

  // ownership of _pymessage is transferred to the caller
  return _pymessage;
}
