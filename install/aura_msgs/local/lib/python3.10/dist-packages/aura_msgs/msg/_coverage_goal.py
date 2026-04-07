# generated from rosidl_generator_py/resource/_idl.py.em
# with input from aura_msgs:msg/CoverageGoal.idl
# generated code does not contain a copyright notice


# Import statements for member types

import builtins  # noqa: E402, I100

import math  # noqa: E402, I100

import rosidl_parser.definition  # noqa: E402, I100


class Metaclass_CoverageGoal(type):
    """Metaclass of message 'CoverageGoal'."""

    _CREATE_ROS_MESSAGE = None
    _CONVERT_FROM_PY = None
    _CONVERT_TO_PY = None
    _DESTROY_ROS_MESSAGE = None
    _TYPE_SUPPORT = None

    __constants = {
        'FORMATION_SPREAD': 0,
        'FORMATION_CLUSTER': 1,
        'FORMATION_LINE': 2,
        'FORMATION_ADAPTIVE': 3,
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
                'aura_msgs.msg.CoverageGoal')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__msg__coverage_goal
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__msg__coverage_goal
            cls._CONVERT_TO_PY = module.convert_to_py_msg__msg__coverage_goal
            cls._TYPE_SUPPORT = module.type_support_msg__msg__coverage_goal
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__msg__coverage_goal

            from builtin_interfaces.msg import Time
            if Time.__class__._TYPE_SUPPORT is None:
                Time.__class__.__import_type_support__()

            from geometry_msgs.msg import Point
            if Point.__class__._TYPE_SUPPORT is None:
                Point.__class__.__import_type_support__()

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
            'FORMATION_SPREAD': cls.__constants['FORMATION_SPREAD'],
            'FORMATION_CLUSTER': cls.__constants['FORMATION_CLUSTER'],
            'FORMATION_LINE': cls.__constants['FORMATION_LINE'],
            'FORMATION_ADAPTIVE': cls.__constants['FORMATION_ADAPTIVE'],
        }

    @property
    def FORMATION_SPREAD(self):
        """Message constant 'FORMATION_SPREAD'."""
        return Metaclass_CoverageGoal.__constants['FORMATION_SPREAD']

    @property
    def FORMATION_CLUSTER(self):
        """Message constant 'FORMATION_CLUSTER'."""
        return Metaclass_CoverageGoal.__constants['FORMATION_CLUSTER']

    @property
    def FORMATION_LINE(self):
        """Message constant 'FORMATION_LINE'."""
        return Metaclass_CoverageGoal.__constants['FORMATION_LINE']

    @property
    def FORMATION_ADAPTIVE(self):
        """Message constant 'FORMATION_ADAPTIVE'."""
        return Metaclass_CoverageGoal.__constants['FORMATION_ADAPTIVE']


class CoverageGoal(metaclass=Metaclass_CoverageGoal):
    """
    Message class 'CoverageGoal'.

    Constants:
      FORMATION_SPREAD
      FORMATION_CLUSTER
      FORMATION_LINE
      FORMATION_ADAPTIVE
    """

    __slots__ = [
        '_timestamp',
        '_drone_id',
        '_position',
        '_desired_arrival_time',
        '_formation_type',
        '_priority',
        '_min_altitude',
        '_max_altitude',
        '_max_velocity',
        '_required_throughput_mbps',
        '_required_coverage_radius',
    ]

    _fields_and_field_types = {
        'timestamp': 'builtin_interfaces/Time',
        'drone_id': 'uint8',
        'position': 'geometry_msgs/Point',
        'desired_arrival_time': 'double',
        'formation_type': 'uint8',
        'priority': 'float',
        'min_altitude': 'float',
        'max_altitude': 'float',
        'max_velocity': 'float',
        'required_throughput_mbps': 'float',
        'required_coverage_radius': 'float',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.NamespacedType(['builtin_interfaces', 'msg'], 'Time'),  # noqa: E501
        rosidl_parser.definition.BasicType('uint8'),  # noqa: E501
        rosidl_parser.definition.NamespacedType(['geometry_msgs', 'msg'], 'Point'),  # noqa: E501
        rosidl_parser.definition.BasicType('double'),  # noqa: E501
        rosidl_parser.definition.BasicType('uint8'),  # noqa: E501
        rosidl_parser.definition.BasicType('float'),  # noqa: E501
        rosidl_parser.definition.BasicType('float'),  # noqa: E501
        rosidl_parser.definition.BasicType('float'),  # noqa: E501
        rosidl_parser.definition.BasicType('float'),  # noqa: E501
        rosidl_parser.definition.BasicType('float'),  # noqa: E501
        rosidl_parser.definition.BasicType('float'),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        from builtin_interfaces.msg import Time
        self.timestamp = kwargs.get('timestamp', Time())
        self.drone_id = kwargs.get('drone_id', int())
        from geometry_msgs.msg import Point
        self.position = kwargs.get('position', Point())
        self.desired_arrival_time = kwargs.get('desired_arrival_time', float())
        self.formation_type = kwargs.get('formation_type', int())
        self.priority = kwargs.get('priority', float())
        self.min_altitude = kwargs.get('min_altitude', float())
        self.max_altitude = kwargs.get('max_altitude', float())
        self.max_velocity = kwargs.get('max_velocity', float())
        self.required_throughput_mbps = kwargs.get('required_throughput_mbps', float())
        self.required_coverage_radius = kwargs.get('required_coverage_radius', float())

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
        if self.timestamp != other.timestamp:
            return False
        if self.drone_id != other.drone_id:
            return False
        if self.position != other.position:
            return False
        if self.desired_arrival_time != other.desired_arrival_time:
            return False
        if self.formation_type != other.formation_type:
            return False
        if self.priority != other.priority:
            return False
        if self.min_altitude != other.min_altitude:
            return False
        if self.max_altitude != other.max_altitude:
            return False
        if self.max_velocity != other.max_velocity:
            return False
        if self.required_throughput_mbps != other.required_throughput_mbps:
            return False
        if self.required_coverage_radius != other.required_coverage_radius:
            return False
        return True

    @classmethod
    def get_fields_and_field_types(cls):
        from copy import copy
        return copy(cls._fields_and_field_types)

    @builtins.property
    def timestamp(self):
        """Message field 'timestamp'."""
        return self._timestamp

    @timestamp.setter
    def timestamp(self, value):
        if __debug__:
            from builtin_interfaces.msg import Time
            assert \
                isinstance(value, Time), \
                "The 'timestamp' field must be a sub message of type 'Time'"
        self._timestamp = value

    @builtins.property
    def drone_id(self):
        """Message field 'drone_id'."""
        return self._drone_id

    @drone_id.setter
    def drone_id(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'drone_id' field must be of type 'int'"
            assert value >= 0 and value < 256, \
                "The 'drone_id' field must be an unsigned integer in [0, 255]"
        self._drone_id = value

    @builtins.property
    def position(self):
        """Message field 'position'."""
        return self._position

    @position.setter
    def position(self, value):
        if __debug__:
            from geometry_msgs.msg import Point
            assert \
                isinstance(value, Point), \
                "The 'position' field must be a sub message of type 'Point'"
        self._position = value

    @builtins.property
    def desired_arrival_time(self):
        """Message field 'desired_arrival_time'."""
        return self._desired_arrival_time

    @desired_arrival_time.setter
    def desired_arrival_time(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'desired_arrival_time' field must be of type 'float'"
            assert not (value < -1.7976931348623157e+308 or value > 1.7976931348623157e+308) or math.isinf(value), \
                "The 'desired_arrival_time' field must be a double in [-1.7976931348623157e+308, 1.7976931348623157e+308]"
        self._desired_arrival_time = value

    @builtins.property
    def formation_type(self):
        """Message field 'formation_type'."""
        return self._formation_type

    @formation_type.setter
    def formation_type(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'formation_type' field must be of type 'int'"
            assert value >= 0 and value < 256, \
                "The 'formation_type' field must be an unsigned integer in [0, 255]"
        self._formation_type = value

    @builtins.property
    def priority(self):
        """Message field 'priority'."""
        return self._priority

    @priority.setter
    def priority(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'priority' field must be of type 'float'"
            assert not (value < -3.402823466e+38 or value > 3.402823466e+38) or math.isinf(value), \
                "The 'priority' field must be a float in [-3.402823466e+38, 3.402823466e+38]"
        self._priority = value

    @builtins.property
    def min_altitude(self):
        """Message field 'min_altitude'."""
        return self._min_altitude

    @min_altitude.setter
    def min_altitude(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'min_altitude' field must be of type 'float'"
            assert not (value < -3.402823466e+38 or value > 3.402823466e+38) or math.isinf(value), \
                "The 'min_altitude' field must be a float in [-3.402823466e+38, 3.402823466e+38]"
        self._min_altitude = value

    @builtins.property
    def max_altitude(self):
        """Message field 'max_altitude'."""
        return self._max_altitude

    @max_altitude.setter
    def max_altitude(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'max_altitude' field must be of type 'float'"
            assert not (value < -3.402823466e+38 or value > 3.402823466e+38) or math.isinf(value), \
                "The 'max_altitude' field must be a float in [-3.402823466e+38, 3.402823466e+38]"
        self._max_altitude = value

    @builtins.property
    def max_velocity(self):
        """Message field 'max_velocity'."""
        return self._max_velocity

    @max_velocity.setter
    def max_velocity(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'max_velocity' field must be of type 'float'"
            assert not (value < -3.402823466e+38 or value > 3.402823466e+38) or math.isinf(value), \
                "The 'max_velocity' field must be a float in [-3.402823466e+38, 3.402823466e+38]"
        self._max_velocity = value

    @builtins.property
    def required_throughput_mbps(self):
        """Message field 'required_throughput_mbps'."""
        return self._required_throughput_mbps

    @required_throughput_mbps.setter
    def required_throughput_mbps(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'required_throughput_mbps' field must be of type 'float'"
            assert not (value < -3.402823466e+38 or value > 3.402823466e+38) or math.isinf(value), \
                "The 'required_throughput_mbps' field must be a float in [-3.402823466e+38, 3.402823466e+38]"
        self._required_throughput_mbps = value

    @builtins.property
    def required_coverage_radius(self):
        """Message field 'required_coverage_radius'."""
        return self._required_coverage_radius

    @required_coverage_radius.setter
    def required_coverage_radius(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'required_coverage_radius' field must be of type 'float'"
            assert not (value < -3.402823466e+38 or value > 3.402823466e+38) or math.isinf(value), \
                "The 'required_coverage_radius' field must be a float in [-3.402823466e+38, 3.402823466e+38]"
        self._required_coverage_radius = value
