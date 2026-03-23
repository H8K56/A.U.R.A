# generated from rosidl_generator_py/resource/_idl.py.em
# with input from aura_msgs:srv/GetNetworkStatus.idl
# generated code does not contain a copyright notice


# Import statements for member types

import builtins  # noqa: E402, I100

import rosidl_parser.definition  # noqa: E402, I100


class Metaclass_GetNetworkStatus_Request(type):
    """Metaclass of message 'GetNetworkStatus_Request'."""

    _CREATE_ROS_MESSAGE = None
    _CONVERT_FROM_PY = None
    _CONVERT_TO_PY = None
    _DESTROY_ROS_MESSAGE = None
    _TYPE_SUPPORT = None

    __constants = {
    }

    @classmethod
    def __import_type_support__(cls):
        try:
            from rosidl_generator_py import import_type_support
            module = import_type_support('aura_msgs')
        except ImportError:
            import logging
            import traceback
            logger = logging.getLogger(
                'aura_msgs.srv.GetNetworkStatus_Request')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__srv__get_network_status__request
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__srv__get_network_status__request
            cls._CONVERT_TO_PY = module.convert_to_py_msg__srv__get_network_status__request
            cls._TYPE_SUPPORT = module.type_support_msg__srv__get_network_status__request
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__srv__get_network_status__request

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
        }


class GetNetworkStatus_Request(metaclass=Metaclass_GetNetworkStatus_Request):
    """Message class 'GetNetworkStatus_Request'."""

    __slots__ = [
        '_include_coverage_map',
        '_include_link_details',
    ]

    _fields_and_field_types = {
        'include_coverage_map': 'boolean',
        'include_link_details': 'boolean',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.BasicType('boolean'),  # noqa: E501
        rosidl_parser.definition.BasicType('boolean'),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        self.include_coverage_map = kwargs.get('include_coverage_map', bool())
        self.include_link_details = kwargs.get('include_link_details', bool())

    def __repr__(self):
        typename = self.__class__.__module__.split('.')
        typename.pop()
        typename.append(self.__class__.__name__)
        args = []
        for s, t in zip(self.__slots__, self.SLOT_TYPES):
            field = getattr(self, s)
            fieldstr = repr(field)
            # We use Python array type for fields that can be directly stored
            # in them, and "normal" sequences for everything else.  If it is
            # a type that we store in an array, strip off the 'array' portion.
            if (
                isinstance(t, rosidl_parser.definition.AbstractSequence) and
                isinstance(t.value_type, rosidl_parser.definition.BasicType) and
                t.value_type.typename in ['float', 'double', 'int8', 'uint8', 'int16', 'uint16', 'int32', 'uint32', 'int64', 'uint64']
            ):
                if len(field) == 0:
                    fieldstr = '[]'
                else:
                    assert fieldstr.startswith('array(')
                    prefix = "array('X', "
                    suffix = ')'
                    fieldstr = fieldstr[len(prefix):-len(suffix)]
            args.append(s[1:] + '=' + fieldstr)
        return '%s(%s)' % ('.'.join(typename), ', '.join(args))

    def __eq__(self, other):
        if not isinstance(other, self.__class__):
            return False
        if self.include_coverage_map != other.include_coverage_map:
            return False
        if self.include_link_details != other.include_link_details:
            return False
        return True

    @classmethod
    def get_fields_and_field_types(cls):
        from copy import copy
        return copy(cls._fields_and_field_types)

    @builtins.property
    def include_coverage_map(self):
        """Message field 'include_coverage_map'."""
        return self._include_coverage_map

    @include_coverage_map.setter
    def include_coverage_map(self, value):
        if __debug__:
            assert \
                isinstance(value, bool), \
                "The 'include_coverage_map' field must be of type 'bool'"
        self._include_coverage_map = value

    @builtins.property
    def include_link_details(self):
        """Message field 'include_link_details'."""
        return self._include_link_details

    @include_link_details.setter
    def include_link_details(self, value):
        if __debug__:
            assert \
                isinstance(value, bool), \
                "The 'include_link_details' field must be of type 'bool'"
        self._include_link_details = value


# Import statements for member types

# already imported above
# import builtins

import math  # noqa: E402, I100

# already imported above
# import rosidl_parser.definition


class Metaclass_GetNetworkStatus_Response(type):
    """Metaclass of message 'GetNetworkStatus_Response'."""

    _CREATE_ROS_MESSAGE = None
    _CONVERT_FROM_PY = None
    _CONVERT_TO_PY = None
    _DESTROY_ROS_MESSAGE = None
    _TYPE_SUPPORT = None

    __constants = {
    }

    @classmethod
    def __import_type_support__(cls):
        try:
            from rosidl_generator_py import import_type_support
            module = import_type_support('aura_msgs')
        except ImportError:
            import logging
            import traceback
            logger = logging.getLogger(
                'aura_msgs.srv.GetNetworkStatus_Response')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__srv__get_network_status__response
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__srv__get_network_status__response
            cls._CONVERT_TO_PY = module.convert_to_py_msg__srv__get_network_status__response
            cls._TYPE_SUPPORT = module.type_support_msg__srv__get_network_status__response
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__srv__get_network_status__response

            from aura_msgs.msg import NetworkMetrics
            if NetworkMetrics.__class__._TYPE_SUPPORT is None:
                NetworkMetrics.__class__.__import_type_support__()

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
        }


class GetNetworkStatus_Response(metaclass=Metaclass_GetNetworkStatus_Response):
    """Message class 'GetNetworkStatus_Response'."""

    __slots__ = [
        '_success',
        '_metrics',
        '_overall_health',
        '_issues',
    ]

    _fields_and_field_types = {
        'success': 'boolean',
        'metrics': 'aura_msgs/NetworkMetrics',
        'overall_health': 'float',
        'issues': 'sequence<string>',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.BasicType('boolean'),  # noqa: E501
        rosidl_parser.definition.NamespacedType(['aura_msgs', 'msg'], 'NetworkMetrics'),  # noqa: E501
        rosidl_parser.definition.BasicType('float'),  # noqa: E501
        rosidl_parser.definition.UnboundedSequence(rosidl_parser.definition.UnboundedString()),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        self.success = kwargs.get('success', bool())
        from aura_msgs.msg import NetworkMetrics
        self.metrics = kwargs.get('metrics', NetworkMetrics())
        self.overall_health = kwargs.get('overall_health', float())
        self.issues = kwargs.get('issues', [])

    def __repr__(self):
        typename = self.__class__.__module__.split('.')
        typename.pop()
        typename.append(self.__class__.__name__)
        args = []
        for s, t in zip(self.__slots__, self.SLOT_TYPES):
            field = getattr(self, s)
            fieldstr = repr(field)
            # We use Python array type for fields that can be directly stored
            # in them, and "normal" sequences for everything else.  If it is
            # a type that we store in an array, strip off the 'array' portion.
            if (
                isinstance(t, rosidl_parser.definition.AbstractSequence) and
                isinstance(t.value_type, rosidl_parser.definition.BasicType) and
                t.value_type.typename in ['float', 'double', 'int8', 'uint8', 'int16', 'uint16', 'int32', 'uint32', 'int64', 'uint64']
            ):
                if len(field) == 0:
                    fieldstr = '[]'
                else:
                    assert fieldstr.startswith('array(')
                    prefix = "array('X', "
                    suffix = ')'
                    fieldstr = fieldstr[len(prefix):-len(suffix)]
            args.append(s[1:] + '=' + fieldstr)
        return '%s(%s)' % ('.'.join(typename), ', '.join(args))

    def __eq__(self, other):
        if not isinstance(other, self.__class__):
            return False
        if self.success != other.success:
            return False
        if self.metrics != other.metrics:
            return False
        if self.overall_health != other.overall_health:
            return False
        if self.issues != other.issues:
            return False
        return True

    @classmethod
    def get_fields_and_field_types(cls):
        from copy import copy
        return copy(cls._fields_and_field_types)

    @builtins.property
    def success(self):
        """Message field 'success'."""
        return self._success

    @success.setter
    def success(self, value):
        if __debug__:
            assert \
                isinstance(value, bool), \
                "The 'success' field must be of type 'bool'"
        self._success = value

    @builtins.property
    def metrics(self):
        """Message field 'metrics'."""
        return self._metrics

    @metrics.setter
    def metrics(self, value):
        if __debug__:
            from aura_msgs.msg import NetworkMetrics
            assert \
                isinstance(value, NetworkMetrics), \
                "The 'metrics' field must be a sub message of type 'NetworkMetrics'"
        self._metrics = value

    @builtins.property
    def overall_health(self):
        """Message field 'overall_health'."""
        return self._overall_health

    @overall_health.setter
    def overall_health(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'overall_health' field must be of type 'float'"
            assert not (value < -3.402823466e+38 or value > 3.402823466e+38) or math.isinf(value), \
                "The 'overall_health' field must be a float in [-3.402823466e+38, 3.402823466e+38]"
        self._overall_health = value

    @builtins.property
    def issues(self):
        """Message field 'issues'."""
        return self._issues

    @issues.setter
    def issues(self, value):
        if __debug__:
            from collections.abc import Sequence
            from collections.abc import Set
            from collections import UserList
            from collections import UserString
            assert \
                ((isinstance(value, Sequence) or
                  isinstance(value, Set) or
                  isinstance(value, UserList)) and
                 not isinstance(value, str) and
                 not isinstance(value, UserString) and
                 all(isinstance(v, str) for v in value) and
                 True), \
                "The 'issues' field must be a set or sequence and each value of type 'str'"
        self._issues = value


class Metaclass_GetNetworkStatus(type):
    """Metaclass of service 'GetNetworkStatus'."""

    _TYPE_SUPPORT = None

    @classmethod
    def __import_type_support__(cls):
        try:
            from rosidl_generator_py import import_type_support
            module = import_type_support('aura_msgs')
        except ImportError:
            import logging
            import traceback
            logger = logging.getLogger(
                'aura_msgs.srv.GetNetworkStatus')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._TYPE_SUPPORT = module.type_support_srv__srv__get_network_status

            from aura_msgs.srv import _get_network_status
            if _get_network_status.Metaclass_GetNetworkStatus_Request._TYPE_SUPPORT is None:
                _get_network_status.Metaclass_GetNetworkStatus_Request.__import_type_support__()
            if _get_network_status.Metaclass_GetNetworkStatus_Response._TYPE_SUPPORT is None:
                _get_network_status.Metaclass_GetNetworkStatus_Response.__import_type_support__()


class GetNetworkStatus(metaclass=Metaclass_GetNetworkStatus):
    from aura_msgs.srv._get_network_status import GetNetworkStatus_Request as Request
    from aura_msgs.srv._get_network_status import GetNetworkStatus_Response as Response

    def __init__(self):
        raise NotImplementedError('Service classes can not be instantiated')
