# generated from rosidl_generator_py/resource/_idl.py.em
# with input from aura_msgs:action/ExecuteMission.idl
# generated code does not contain a copyright notice


# Import statements for member types

import builtins  # noqa: E402, I100

import math  # noqa: E402, I100

import rosidl_parser.definition  # noqa: E402, I100


class Metaclass_ExecuteMission_Goal(type):
    """Metaclass of message 'ExecuteMission_Goal'."""

    _CREATE_ROS_MESSAGE = None
    _CONVERT_FROM_PY = None
    _CONVERT_TO_PY = None
    _DESTROY_ROS_MESSAGE = None
    _TYPE_SUPPORT = None

    __constants = {
        'MISSION_COVERAGE': 0,
        'MISSION_SEARCH': 1,
        'MISSION_RELAY': 2,
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
                'aura_msgs.action.ExecuteMission_Goal')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__action__execute_mission__goal
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__action__execute_mission__goal
            cls._CONVERT_TO_PY = module.convert_to_py_msg__action__execute_mission__goal
            cls._TYPE_SUPPORT = module.type_support_msg__action__execute_mission__goal
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__action__execute_mission__goal

            from geometry_msgs.msg import Point
            if Point.__class__._TYPE_SUPPORT is None:
                Point.__class__.__import_type_support__()

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
            'MISSION_COVERAGE': cls.__constants['MISSION_COVERAGE'],
            'MISSION_SEARCH': cls.__constants['MISSION_SEARCH'],
            'MISSION_RELAY': cls.__constants['MISSION_RELAY'],
        }

    @property
    def MISSION_COVERAGE(self):
        """Message constant 'MISSION_COVERAGE'."""
        return Metaclass_ExecuteMission_Goal.__constants['MISSION_COVERAGE']

    @property
    def MISSION_SEARCH(self):
        """Message constant 'MISSION_SEARCH'."""
        return Metaclass_ExecuteMission_Goal.__constants['MISSION_SEARCH']

    @property
    def MISSION_RELAY(self):
        """Message constant 'MISSION_RELAY'."""
        return Metaclass_ExecuteMission_Goal.__constants['MISSION_RELAY']


class ExecuteMission_Goal(metaclass=Metaclass_ExecuteMission_Goal):
    """
    Message class 'ExecuteMission_Goal'.

    Constants:
      MISSION_COVERAGE
      MISSION_SEARCH
      MISSION_RELAY
    """

    __slots__ = [
        '_mission_id',
        '_mission_type',
        '_coverage_area_vertices',
        '_target_altitude',
        '_target_coverage_percent',
        '_max_duration_sec',
    ]

    _fields_and_field_types = {
        'mission_id': 'string',
        'mission_type': 'uint8',
        'coverage_area_vertices': 'sequence<geometry_msgs/Point>',
        'target_altitude': 'float',
        'target_coverage_percent': 'float',
        'max_duration_sec': 'float',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
        rosidl_parser.definition.BasicType('uint8'),  # noqa: E501
        rosidl_parser.definition.UnboundedSequence(rosidl_parser.definition.NamespacedType(['geometry_msgs', 'msg'], 'Point')),  # noqa: E501
        rosidl_parser.definition.BasicType('float'),  # noqa: E501
        rosidl_parser.definition.BasicType('float'),  # noqa: E501
        rosidl_parser.definition.BasicType('float'),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        self.mission_id = kwargs.get('mission_id', str())
        self.mission_type = kwargs.get('mission_type', int())
        self.coverage_area_vertices = kwargs.get('coverage_area_vertices', [])
        self.target_altitude = kwargs.get('target_altitude', float())
        self.target_coverage_percent = kwargs.get('target_coverage_percent', float())
        self.max_duration_sec = kwargs.get('max_duration_sec', float())

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
        if self.mission_id != other.mission_id:
            return False
        if self.mission_type != other.mission_type:
            return False
        if self.coverage_area_vertices != other.coverage_area_vertices:
            return False
        if self.target_altitude != other.target_altitude:
            return False
        if self.target_coverage_percent != other.target_coverage_percent:
            return False
        if self.max_duration_sec != other.max_duration_sec:
            return False
        return True

    @classmethod
    def get_fields_and_field_types(cls):
        from copy import copy
        return copy(cls._fields_and_field_types)

    @builtins.property
    def mission_id(self):
        """Message field 'mission_id'."""
        return self._mission_id

    @mission_id.setter
    def mission_id(self, value):
        if __debug__:
            assert \
                isinstance(value, str), \
                "The 'mission_id' field must be of type 'str'"
        self._mission_id = value

    @builtins.property
    def mission_type(self):
        """Message field 'mission_type'."""
        return self._mission_type

    @mission_type.setter
    def mission_type(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'mission_type' field must be of type 'int'"
            assert value >= 0 and value < 256, \
                "The 'mission_type' field must be an unsigned integer in [0, 255]"
        self._mission_type = value

    @builtins.property
    def coverage_area_vertices(self):
        """Message field 'coverage_area_vertices'."""
        return self._coverage_area_vertices

    @coverage_area_vertices.setter
    def coverage_area_vertices(self, value):
        if __debug__:
            from geometry_msgs.msg import Point
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
                 all(isinstance(v, Point) for v in value) and
                 True), \
                "The 'coverage_area_vertices' field must be a set or sequence and each value of type 'Point'"
        self._coverage_area_vertices = value

    @builtins.property
    def target_altitude(self):
        """Message field 'target_altitude'."""
        return self._target_altitude

    @target_altitude.setter
    def target_altitude(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'target_altitude' field must be of type 'float'"
            assert not (value < -3.402823466e+38 or value > 3.402823466e+38) or math.isinf(value), \
                "The 'target_altitude' field must be a float in [-3.402823466e+38, 3.402823466e+38]"
        self._target_altitude = value

    @builtins.property
    def target_coverage_percent(self):
        """Message field 'target_coverage_percent'."""
        return self._target_coverage_percent

    @target_coverage_percent.setter
    def target_coverage_percent(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'target_coverage_percent' field must be of type 'float'"
            assert not (value < -3.402823466e+38 or value > 3.402823466e+38) or math.isinf(value), \
                "The 'target_coverage_percent' field must be a float in [-3.402823466e+38, 3.402823466e+38]"
        self._target_coverage_percent = value

    @builtins.property
    def max_duration_sec(self):
        """Message field 'max_duration_sec'."""
        return self._max_duration_sec

    @max_duration_sec.setter
    def max_duration_sec(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'max_duration_sec' field must be of type 'float'"
            assert not (value < -3.402823466e+38 or value > 3.402823466e+38) or math.isinf(value), \
                "The 'max_duration_sec' field must be a float in [-3.402823466e+38, 3.402823466e+38]"
        self._max_duration_sec = value


# Import statements for member types

# already imported above
# import builtins

# already imported above
# import math

# already imported above
# import rosidl_parser.definition


class Metaclass_ExecuteMission_Result(type):
    """Metaclass of message 'ExecuteMission_Result'."""

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
                'aura_msgs.action.ExecuteMission_Result')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__action__execute_mission__result
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__action__execute_mission__result
            cls._CONVERT_TO_PY = module.convert_to_py_msg__action__execute_mission__result
            cls._TYPE_SUPPORT = module.type_support_msg__action__execute_mission__result
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__action__execute_mission__result

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
        }


class ExecuteMission_Result(metaclass=Metaclass_ExecuteMission_Result):
    """Message class 'ExecuteMission_Result'."""

    __slots__ = [
        '_success',
        '_message',
        '_coverage_achieved',
        '_total_time_sec',
        '_avg_network_quality',
        '_total_connections_served',
    ]

    _fields_and_field_types = {
        'success': 'boolean',
        'message': 'string',
        'coverage_achieved': 'float',
        'total_time_sec': 'float',
        'avg_network_quality': 'float',
        'total_connections_served': 'uint32',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.BasicType('boolean'),  # noqa: E501
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
        rosidl_parser.definition.BasicType('float'),  # noqa: E501
        rosidl_parser.definition.BasicType('float'),  # noqa: E501
        rosidl_parser.definition.BasicType('float'),  # noqa: E501
        rosidl_parser.definition.BasicType('uint32'),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        self.success = kwargs.get('success', bool())
        self.message = kwargs.get('message', str())
        self.coverage_achieved = kwargs.get('coverage_achieved', float())
        self.total_time_sec = kwargs.get('total_time_sec', float())
        self.avg_network_quality = kwargs.get('avg_network_quality', float())
        self.total_connections_served = kwargs.get('total_connections_served', int())

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
        if self.message != other.message:
            return False
        if self.coverage_achieved != other.coverage_achieved:
            return False
        if self.total_time_sec != other.total_time_sec:
            return False
        if self.avg_network_quality != other.avg_network_quality:
            return False
        if self.total_connections_served != other.total_connections_served:
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
    def message(self):
        """Message field 'message'."""
        return self._message

    @message.setter
    def message(self, value):
        if __debug__:
            assert \
                isinstance(value, str), \
                "The 'message' field must be of type 'str'"
        self._message = value

    @builtins.property
    def coverage_achieved(self):
        """Message field 'coverage_achieved'."""
        return self._coverage_achieved

    @coverage_achieved.setter
    def coverage_achieved(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'coverage_achieved' field must be of type 'float'"
            assert not (value < -3.402823466e+38 or value > 3.402823466e+38) or math.isinf(value), \
                "The 'coverage_achieved' field must be a float in [-3.402823466e+38, 3.402823466e+38]"
        self._coverage_achieved = value

    @builtins.property
    def total_time_sec(self):
        """Message field 'total_time_sec'."""
        return self._total_time_sec

    @total_time_sec.setter
    def total_time_sec(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'total_time_sec' field must be of type 'float'"
            assert not (value < -3.402823466e+38 or value > 3.402823466e+38) or math.isinf(value), \
                "The 'total_time_sec' field must be a float in [-3.402823466e+38, 3.402823466e+38]"
        self._total_time_sec = value

    @builtins.property
    def avg_network_quality(self):
        """Message field 'avg_network_quality'."""
        return self._avg_network_quality

    @avg_network_quality.setter
    def avg_network_quality(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'avg_network_quality' field must be of type 'float'"
            assert not (value < -3.402823466e+38 or value > 3.402823466e+38) or math.isinf(value), \
                "The 'avg_network_quality' field must be a float in [-3.402823466e+38, 3.402823466e+38]"
        self._avg_network_quality = value

    @builtins.property
    def total_connections_served(self):
        """Message field 'total_connections_served'."""
        return self._total_connections_served

    @total_connections_served.setter
    def total_connections_served(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'total_connections_served' field must be of type 'int'"
            assert value >= 0 and value < 4294967296, \
                "The 'total_connections_served' field must be an unsigned integer in [0, 4294967295]"
        self._total_connections_served = value


# Import statements for member types

# already imported above
# import builtins

# already imported above
# import math

# already imported above
# import rosidl_parser.definition


class Metaclass_ExecuteMission_Feedback(type):
    """Metaclass of message 'ExecuteMission_Feedback'."""

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
                'aura_msgs.action.ExecuteMission_Feedback')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__action__execute_mission__feedback
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__action__execute_mission__feedback
            cls._CONVERT_TO_PY = module.convert_to_py_msg__action__execute_mission__feedback
            cls._TYPE_SUPPORT = module.type_support_msg__action__execute_mission__feedback
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__action__execute_mission__feedback

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
        }


class ExecuteMission_Feedback(metaclass=Metaclass_ExecuteMission_Feedback):
    """Message class 'ExecuteMission_Feedback'."""

    __slots__ = [
        '_progress_percent',
        '_current_coverage_percent',
        '_current_network_quality',
        '_drones_active',
        '_current_phase',
        '_elapsed_time_sec',
    ]

    _fields_and_field_types = {
        'progress_percent': 'float',
        'current_coverage_percent': 'float',
        'current_network_quality': 'float',
        'drones_active': 'uint8',
        'current_phase': 'string',
        'elapsed_time_sec': 'float',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.BasicType('float'),  # noqa: E501
        rosidl_parser.definition.BasicType('float'),  # noqa: E501
        rosidl_parser.definition.BasicType('float'),  # noqa: E501
        rosidl_parser.definition.BasicType('uint8'),  # noqa: E501
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
        rosidl_parser.definition.BasicType('float'),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        self.progress_percent = kwargs.get('progress_percent', float())
        self.current_coverage_percent = kwargs.get('current_coverage_percent', float())
        self.current_network_quality = kwargs.get('current_network_quality', float())
        self.drones_active = kwargs.get('drones_active', int())
        self.current_phase = kwargs.get('current_phase', str())
        self.elapsed_time_sec = kwargs.get('elapsed_time_sec', float())

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
        if self.progress_percent != other.progress_percent:
            return False
        if self.current_coverage_percent != other.current_coverage_percent:
            return False
        if self.current_network_quality != other.current_network_quality:
            return False
        if self.drones_active != other.drones_active:
            return False
        if self.current_phase != other.current_phase:
            return False
        if self.elapsed_time_sec != other.elapsed_time_sec:
            return False
        return True

    @classmethod
    def get_fields_and_field_types(cls):
        from copy import copy
        return copy(cls._fields_and_field_types)

    @builtins.property
    def progress_percent(self):
        """Message field 'progress_percent'."""
        return self._progress_percent

    @progress_percent.setter
    def progress_percent(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'progress_percent' field must be of type 'float'"
            assert not (value < -3.402823466e+38 or value > 3.402823466e+38) or math.isinf(value), \
                "The 'progress_percent' field must be a float in [-3.402823466e+38, 3.402823466e+38]"
        self._progress_percent = value

    @builtins.property
    def current_coverage_percent(self):
        """Message field 'current_coverage_percent'."""
        return self._current_coverage_percent

    @current_coverage_percent.setter
    def current_coverage_percent(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'current_coverage_percent' field must be of type 'float'"
            assert not (value < -3.402823466e+38 or value > 3.402823466e+38) or math.isinf(value), \
                "The 'current_coverage_percent' field must be a float in [-3.402823466e+38, 3.402823466e+38]"
        self._current_coverage_percent = value

    @builtins.property
    def current_network_quality(self):
        """Message field 'current_network_quality'."""
        return self._current_network_quality

    @current_network_quality.setter
    def current_network_quality(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'current_network_quality' field must be of type 'float'"
            assert not (value < -3.402823466e+38 or value > 3.402823466e+38) or math.isinf(value), \
                "The 'current_network_quality' field must be a float in [-3.402823466e+38, 3.402823466e+38]"
        self._current_network_quality = value

    @builtins.property
    def drones_active(self):
        """Message field 'drones_active'."""
        return self._drones_active

    @drones_active.setter
    def drones_active(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'drones_active' field must be of type 'int'"
            assert value >= 0 and value < 256, \
                "The 'drones_active' field must be an unsigned integer in [0, 255]"
        self._drones_active = value

    @builtins.property
    def current_phase(self):
        """Message field 'current_phase'."""
        return self._current_phase

    @current_phase.setter
    def current_phase(self, value):
        if __debug__:
            assert \
                isinstance(value, str), \
                "The 'current_phase' field must be of type 'str'"
        self._current_phase = value

    @builtins.property
    def elapsed_time_sec(self):
        """Message field 'elapsed_time_sec'."""
        return self._elapsed_time_sec

    @elapsed_time_sec.setter
    def elapsed_time_sec(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'elapsed_time_sec' field must be of type 'float'"
            assert not (value < -3.402823466e+38 or value > 3.402823466e+38) or math.isinf(value), \
                "The 'elapsed_time_sec' field must be a float in [-3.402823466e+38, 3.402823466e+38]"
        self._elapsed_time_sec = value


# Import statements for member types

# already imported above
# import builtins

# already imported above
# import rosidl_parser.definition


class Metaclass_ExecuteMission_SendGoal_Request(type):
    """Metaclass of message 'ExecuteMission_SendGoal_Request'."""

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
                'aura_msgs.action.ExecuteMission_SendGoal_Request')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__action__execute_mission__send_goal__request
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__action__execute_mission__send_goal__request
            cls._CONVERT_TO_PY = module.convert_to_py_msg__action__execute_mission__send_goal__request
            cls._TYPE_SUPPORT = module.type_support_msg__action__execute_mission__send_goal__request
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__action__execute_mission__send_goal__request

            from aura_msgs.action import ExecuteMission
            if ExecuteMission.Goal.__class__._TYPE_SUPPORT is None:
                ExecuteMission.Goal.__class__.__import_type_support__()

            from unique_identifier_msgs.msg import UUID
            if UUID.__class__._TYPE_SUPPORT is None:
                UUID.__class__.__import_type_support__()

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
        }


class ExecuteMission_SendGoal_Request(metaclass=Metaclass_ExecuteMission_SendGoal_Request):
    """Message class 'ExecuteMission_SendGoal_Request'."""

    __slots__ = [
        '_goal_id',
        '_goal',
    ]

    _fields_and_field_types = {
        'goal_id': 'unique_identifier_msgs/UUID',
        'goal': 'aura_msgs/ExecuteMission_Goal',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.NamespacedType(['unique_identifier_msgs', 'msg'], 'UUID'),  # noqa: E501
        rosidl_parser.definition.NamespacedType(['aura_msgs', 'action'], 'ExecuteMission_Goal'),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        from unique_identifier_msgs.msg import UUID
        self.goal_id = kwargs.get('goal_id', UUID())
        from aura_msgs.action._execute_mission import ExecuteMission_Goal
        self.goal = kwargs.get('goal', ExecuteMission_Goal())

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
        if self.goal_id != other.goal_id:
            return False
        if self.goal != other.goal:
            return False
        return True

    @classmethod
    def get_fields_and_field_types(cls):
        from copy import copy
        return copy(cls._fields_and_field_types)

    @builtins.property
    def goal_id(self):
        """Message field 'goal_id'."""
        return self._goal_id

    @goal_id.setter
    def goal_id(self, value):
        if __debug__:
            from unique_identifier_msgs.msg import UUID
            assert \
                isinstance(value, UUID), \
                "The 'goal_id' field must be a sub message of type 'UUID'"
        self._goal_id = value

    @builtins.property
    def goal(self):
        """Message field 'goal'."""
        return self._goal

    @goal.setter
    def goal(self, value):
        if __debug__:
            from aura_msgs.action._execute_mission import ExecuteMission_Goal
            assert \
                isinstance(value, ExecuteMission_Goal), \
                "The 'goal' field must be a sub message of type 'ExecuteMission_Goal'"
        self._goal = value


# Import statements for member types

# already imported above
# import builtins

# already imported above
# import rosidl_parser.definition


class Metaclass_ExecuteMission_SendGoal_Response(type):
    """Metaclass of message 'ExecuteMission_SendGoal_Response'."""

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
                'aura_msgs.action.ExecuteMission_SendGoal_Response')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__action__execute_mission__send_goal__response
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__action__execute_mission__send_goal__response
            cls._CONVERT_TO_PY = module.convert_to_py_msg__action__execute_mission__send_goal__response
            cls._TYPE_SUPPORT = module.type_support_msg__action__execute_mission__send_goal__response
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__action__execute_mission__send_goal__response

            from builtin_interfaces.msg import Time
            if Time.__class__._TYPE_SUPPORT is None:
                Time.__class__.__import_type_support__()

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
        }


class ExecuteMission_SendGoal_Response(metaclass=Metaclass_ExecuteMission_SendGoal_Response):
    """Message class 'ExecuteMission_SendGoal_Response'."""

    __slots__ = [
        '_accepted',
        '_stamp',
    ]

    _fields_and_field_types = {
        'accepted': 'boolean',
        'stamp': 'builtin_interfaces/Time',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.BasicType('boolean'),  # noqa: E501
        rosidl_parser.definition.NamespacedType(['builtin_interfaces', 'msg'], 'Time'),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        self.accepted = kwargs.get('accepted', bool())
        from builtin_interfaces.msg import Time
        self.stamp = kwargs.get('stamp', Time())

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
        if self.accepted != other.accepted:
            return False
        if self.stamp != other.stamp:
            return False
        return True

    @classmethod
    def get_fields_and_field_types(cls):
        from copy import copy
        return copy(cls._fields_and_field_types)

    @builtins.property
    def accepted(self):
        """Message field 'accepted'."""
        return self._accepted

    @accepted.setter
    def accepted(self, value):
        if __debug__:
            assert \
                isinstance(value, bool), \
                "The 'accepted' field must be of type 'bool'"
        self._accepted = value

    @builtins.property
    def stamp(self):
        """Message field 'stamp'."""
        return self._stamp

    @stamp.setter
    def stamp(self, value):
        if __debug__:
            from builtin_interfaces.msg import Time
            assert \
                isinstance(value, Time), \
                "The 'stamp' field must be a sub message of type 'Time'"
        self._stamp = value


class Metaclass_ExecuteMission_SendGoal(type):
    """Metaclass of service 'ExecuteMission_SendGoal'."""

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
                'aura_msgs.action.ExecuteMission_SendGoal')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._TYPE_SUPPORT = module.type_support_srv__action__execute_mission__send_goal

            from aura_msgs.action import _execute_mission
            if _execute_mission.Metaclass_ExecuteMission_SendGoal_Request._TYPE_SUPPORT is None:
                _execute_mission.Metaclass_ExecuteMission_SendGoal_Request.__import_type_support__()
            if _execute_mission.Metaclass_ExecuteMission_SendGoal_Response._TYPE_SUPPORT is None:
                _execute_mission.Metaclass_ExecuteMission_SendGoal_Response.__import_type_support__()


class ExecuteMission_SendGoal(metaclass=Metaclass_ExecuteMission_SendGoal):
    from aura_msgs.action._execute_mission import ExecuteMission_SendGoal_Request as Request
    from aura_msgs.action._execute_mission import ExecuteMission_SendGoal_Response as Response

    def __init__(self):
        raise NotImplementedError('Service classes can not be instantiated')


# Import statements for member types

# already imported above
# import builtins

# already imported above
# import rosidl_parser.definition


class Metaclass_ExecuteMission_GetResult_Request(type):
    """Metaclass of message 'ExecuteMission_GetResult_Request'."""

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
                'aura_msgs.action.ExecuteMission_GetResult_Request')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__action__execute_mission__get_result__request
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__action__execute_mission__get_result__request
            cls._CONVERT_TO_PY = module.convert_to_py_msg__action__execute_mission__get_result__request
            cls._TYPE_SUPPORT = module.type_support_msg__action__execute_mission__get_result__request
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__action__execute_mission__get_result__request

            from unique_identifier_msgs.msg import UUID
            if UUID.__class__._TYPE_SUPPORT is None:
                UUID.__class__.__import_type_support__()

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
        }


class ExecuteMission_GetResult_Request(metaclass=Metaclass_ExecuteMission_GetResult_Request):
    """Message class 'ExecuteMission_GetResult_Request'."""

    __slots__ = [
        '_goal_id',
    ]

    _fields_and_field_types = {
        'goal_id': 'unique_identifier_msgs/UUID',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.NamespacedType(['unique_identifier_msgs', 'msg'], 'UUID'),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        from unique_identifier_msgs.msg import UUID
        self.goal_id = kwargs.get('goal_id', UUID())

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
        if self.goal_id != other.goal_id:
            return False
        return True

    @classmethod
    def get_fields_and_field_types(cls):
        from copy import copy
        return copy(cls._fields_and_field_types)

    @builtins.property
    def goal_id(self):
        """Message field 'goal_id'."""
        return self._goal_id

    @goal_id.setter
    def goal_id(self, value):
        if __debug__:
            from unique_identifier_msgs.msg import UUID
            assert \
                isinstance(value, UUID), \
                "The 'goal_id' field must be a sub message of type 'UUID'"
        self._goal_id = value


# Import statements for member types

# already imported above
# import builtins

# already imported above
# import rosidl_parser.definition


class Metaclass_ExecuteMission_GetResult_Response(type):
    """Metaclass of message 'ExecuteMission_GetResult_Response'."""

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
                'aura_msgs.action.ExecuteMission_GetResult_Response')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__action__execute_mission__get_result__response
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__action__execute_mission__get_result__response
            cls._CONVERT_TO_PY = module.convert_to_py_msg__action__execute_mission__get_result__response
            cls._TYPE_SUPPORT = module.type_support_msg__action__execute_mission__get_result__response
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__action__execute_mission__get_result__response

            from aura_msgs.action import ExecuteMission
            if ExecuteMission.Result.__class__._TYPE_SUPPORT is None:
                ExecuteMission.Result.__class__.__import_type_support__()

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
        }


class ExecuteMission_GetResult_Response(metaclass=Metaclass_ExecuteMission_GetResult_Response):
    """Message class 'ExecuteMission_GetResult_Response'."""

    __slots__ = [
        '_status',
        '_result',
    ]

    _fields_and_field_types = {
        'status': 'int8',
        'result': 'aura_msgs/ExecuteMission_Result',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.BasicType('int8'),  # noqa: E501
        rosidl_parser.definition.NamespacedType(['aura_msgs', 'action'], 'ExecuteMission_Result'),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        self.status = kwargs.get('status', int())
        from aura_msgs.action._execute_mission import ExecuteMission_Result
        self.result = kwargs.get('result', ExecuteMission_Result())

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
        if self.status != other.status:
            return False
        if self.result != other.result:
            return False
        return True

    @classmethod
    def get_fields_and_field_types(cls):
        from copy import copy
        return copy(cls._fields_and_field_types)

    @builtins.property
    def status(self):
        """Message field 'status'."""
        return self._status

    @status.setter
    def status(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'status' field must be of type 'int'"
            assert value >= -128 and value < 128, \
                "The 'status' field must be an integer in [-128, 127]"
        self._status = value

    @builtins.property
    def result(self):
        """Message field 'result'."""
        return self._result

    @result.setter
    def result(self, value):
        if __debug__:
            from aura_msgs.action._execute_mission import ExecuteMission_Result
            assert \
                isinstance(value, ExecuteMission_Result), \
                "The 'result' field must be a sub message of type 'ExecuteMission_Result'"
        self._result = value


class Metaclass_ExecuteMission_GetResult(type):
    """Metaclass of service 'ExecuteMission_GetResult'."""

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
                'aura_msgs.action.ExecuteMission_GetResult')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._TYPE_SUPPORT = module.type_support_srv__action__execute_mission__get_result

            from aura_msgs.action import _execute_mission
            if _execute_mission.Metaclass_ExecuteMission_GetResult_Request._TYPE_SUPPORT is None:
                _execute_mission.Metaclass_ExecuteMission_GetResult_Request.__import_type_support__()
            if _execute_mission.Metaclass_ExecuteMission_GetResult_Response._TYPE_SUPPORT is None:
                _execute_mission.Metaclass_ExecuteMission_GetResult_Response.__import_type_support__()


class ExecuteMission_GetResult(metaclass=Metaclass_ExecuteMission_GetResult):
    from aura_msgs.action._execute_mission import ExecuteMission_GetResult_Request as Request
    from aura_msgs.action._execute_mission import ExecuteMission_GetResult_Response as Response

    def __init__(self):
        raise NotImplementedError('Service classes can not be instantiated')


# Import statements for member types

# already imported above
# import builtins

# already imported above
# import rosidl_parser.definition


class Metaclass_ExecuteMission_FeedbackMessage(type):
    """Metaclass of message 'ExecuteMission_FeedbackMessage'."""

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
                'aura_msgs.action.ExecuteMission_FeedbackMessage')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__action__execute_mission__feedback_message
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__action__execute_mission__feedback_message
            cls._CONVERT_TO_PY = module.convert_to_py_msg__action__execute_mission__feedback_message
            cls._TYPE_SUPPORT = module.type_support_msg__action__execute_mission__feedback_message
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__action__execute_mission__feedback_message

            from aura_msgs.action import ExecuteMission
            if ExecuteMission.Feedback.__class__._TYPE_SUPPORT is None:
                ExecuteMission.Feedback.__class__.__import_type_support__()

            from unique_identifier_msgs.msg import UUID
            if UUID.__class__._TYPE_SUPPORT is None:
                UUID.__class__.__import_type_support__()

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
        }


class ExecuteMission_FeedbackMessage(metaclass=Metaclass_ExecuteMission_FeedbackMessage):
    """Message class 'ExecuteMission_FeedbackMessage'."""

    __slots__ = [
        '_goal_id',
        '_feedback',
    ]

    _fields_and_field_types = {
        'goal_id': 'unique_identifier_msgs/UUID',
        'feedback': 'aura_msgs/ExecuteMission_Feedback',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.NamespacedType(['unique_identifier_msgs', 'msg'], 'UUID'),  # noqa: E501
        rosidl_parser.definition.NamespacedType(['aura_msgs', 'action'], 'ExecuteMission_Feedback'),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        from unique_identifier_msgs.msg import UUID
        self.goal_id = kwargs.get('goal_id', UUID())
        from aura_msgs.action._execute_mission import ExecuteMission_Feedback
        self.feedback = kwargs.get('feedback', ExecuteMission_Feedback())

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
        if self.goal_id != other.goal_id:
            return False
        if self.feedback != other.feedback:
            return False
        return True

    @classmethod
    def get_fields_and_field_types(cls):
        from copy import copy
        return copy(cls._fields_and_field_types)

    @builtins.property
    def goal_id(self):
        """Message field 'goal_id'."""
        return self._goal_id

    @goal_id.setter
    def goal_id(self, value):
        if __debug__:
            from unique_identifier_msgs.msg import UUID
            assert \
                isinstance(value, UUID), \
                "The 'goal_id' field must be a sub message of type 'UUID'"
        self._goal_id = value

    @builtins.property
    def feedback(self):
        """Message field 'feedback'."""
        return self._feedback

    @feedback.setter
    def feedback(self, value):
        if __debug__:
            from aura_msgs.action._execute_mission import ExecuteMission_Feedback
            assert \
                isinstance(value, ExecuteMission_Feedback), \
                "The 'feedback' field must be a sub message of type 'ExecuteMission_Feedback'"
        self._feedback = value


class Metaclass_ExecuteMission(type):
    """Metaclass of action 'ExecuteMission'."""

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
                'aura_msgs.action.ExecuteMission')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._TYPE_SUPPORT = module.type_support_action__action__execute_mission

            from action_msgs.msg import _goal_status_array
            if _goal_status_array.Metaclass_GoalStatusArray._TYPE_SUPPORT is None:
                _goal_status_array.Metaclass_GoalStatusArray.__import_type_support__()
            from action_msgs.srv import _cancel_goal
            if _cancel_goal.Metaclass_CancelGoal._TYPE_SUPPORT is None:
                _cancel_goal.Metaclass_CancelGoal.__import_type_support__()

            from aura_msgs.action import _execute_mission
            if _execute_mission.Metaclass_ExecuteMission_SendGoal._TYPE_SUPPORT is None:
                _execute_mission.Metaclass_ExecuteMission_SendGoal.__import_type_support__()
            if _execute_mission.Metaclass_ExecuteMission_GetResult._TYPE_SUPPORT is None:
                _execute_mission.Metaclass_ExecuteMission_GetResult.__import_type_support__()
            if _execute_mission.Metaclass_ExecuteMission_FeedbackMessage._TYPE_SUPPORT is None:
                _execute_mission.Metaclass_ExecuteMission_FeedbackMessage.__import_type_support__()


class ExecuteMission(metaclass=Metaclass_ExecuteMission):

    # The goal message defined in the action definition.
    from aura_msgs.action._execute_mission import ExecuteMission_Goal as Goal
    # The result message defined in the action definition.
    from aura_msgs.action._execute_mission import ExecuteMission_Result as Result
    # The feedback message defined in the action definition.
    from aura_msgs.action._execute_mission import ExecuteMission_Feedback as Feedback

    class Impl:

        # The send_goal service using a wrapped version of the goal message as a request.
        from aura_msgs.action._execute_mission import ExecuteMission_SendGoal as SendGoalService
        # The get_result service using a wrapped version of the result message as a response.
        from aura_msgs.action._execute_mission import ExecuteMission_GetResult as GetResultService
        # The feedback message with generic fields which wraps the feedback message.
        from aura_msgs.action._execute_mission import ExecuteMission_FeedbackMessage as FeedbackMessage

        # The generic service to cancel a goal.
        from action_msgs.srv._cancel_goal import CancelGoal as CancelGoalService
        # The generic message for get the status of a goal.
        from action_msgs.msg._goal_status_array import GoalStatusArray as GoalStatusMessage

    def __init__(self):
        raise NotImplementedError('Action classes can not be instantiated')
