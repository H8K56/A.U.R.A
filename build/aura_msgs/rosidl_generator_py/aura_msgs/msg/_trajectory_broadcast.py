# generated from rosidl_generator_py/resource/_idl.py.em
# with input from aura_msgs:msg/TrajectoryBroadcast.idl
# generated code does not contain a copyright notice


# Import statements for member types

# Member 'time_allocation'
import array  # noqa: E402, I100

import builtins  # noqa: E402, I100

import math  # noqa: E402, I100

import rosidl_parser.definition  # noqa: E402, I100


class Metaclass_TrajectoryBroadcast(type):
    """Metaclass of message 'TrajectoryBroadcast'."""

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
                'aura_msgs.msg.TrajectoryBroadcast')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__msg__trajectory_broadcast
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__msg__trajectory_broadcast
            cls._CONVERT_TO_PY = module.convert_to_py_msg__msg__trajectory_broadcast
            cls._TYPE_SUPPORT = module.type_support_msg__msg__trajectory_broadcast
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__msg__trajectory_broadcast

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
        }


class TrajectoryBroadcast(metaclass=Metaclass_TrajectoryBroadcast):
    """Message class 'TrajectoryBroadcast'."""

    __slots__ = [
        '_timestamp',
        '_drone_id',
        '_start_time',
        '_waypoints',
        '_time_allocation',
        '_total_duration',
        '_num_pieces',
        '_is_valid',
        '_max_velocity',
        '_clearance',
        '_goal_position',
        '_goal_reached',
    ]

    _fields_and_field_types = {
        'timestamp': 'builtin_interfaces/Time',
        'drone_id': 'uint8',
        'start_time': 'builtin_interfaces/Time',
        'waypoints': 'sequence<geometry_msgs/Point>',
        'time_allocation': 'sequence<double>',
        'total_duration': 'double',
        'num_pieces': 'uint8',
        'is_valid': 'boolean',
        'max_velocity': 'float',
        'clearance': 'float',
        'goal_position': 'geometry_msgs/Point',
        'goal_reached': 'boolean',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.NamespacedType(['builtin_interfaces', 'msg'], 'Time'),  # noqa: E501
        rosidl_parser.definition.BasicType('uint8'),  # noqa: E501
        rosidl_parser.definition.NamespacedType(['builtin_interfaces', 'msg'], 'Time'),  # noqa: E501
        rosidl_parser.definition.UnboundedSequence(rosidl_parser.definition.NamespacedType(['geometry_msgs', 'msg'], 'Point')),  # noqa: E501
        rosidl_parser.definition.UnboundedSequence(rosidl_parser.definition.BasicType('double')),  # noqa: E501
        rosidl_parser.definition.BasicType('double'),  # noqa: E501
        rosidl_parser.definition.BasicType('uint8'),  # noqa: E501
        rosidl_parser.definition.BasicType('boolean'),  # noqa: E501
        rosidl_parser.definition.BasicType('float'),  # noqa: E501
        rosidl_parser.definition.BasicType('float'),  # noqa: E501
        rosidl_parser.definition.NamespacedType(['geometry_msgs', 'msg'], 'Point'),  # noqa: E501
        rosidl_parser.definition.BasicType('boolean'),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        from builtin_interfaces.msg import Time
        self.timestamp = kwargs.get('timestamp', Time())
        self.drone_id = kwargs.get('drone_id', int())
        from builtin_interfaces.msg import Time
        self.start_time = kwargs.get('start_time', Time())
        self.waypoints = kwargs.get('waypoints', [])
        self.time_allocation = array.array('d', kwargs.get('time_allocation', []))
        self.total_duration = kwargs.get('total_duration', float())
        self.num_pieces = kwargs.get('num_pieces', int())
        self.is_valid = kwargs.get('is_valid', bool())
        self.max_velocity = kwargs.get('max_velocity', float())
        self.clearance = kwargs.get('clearance', float())
        from geometry_msgs.msg import Point
        self.goal_position = kwargs.get('goal_position', Point())
        self.goal_reached = kwargs.get('goal_reached', bool())

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
        if self.start_time != other.start_time:
            return False
        if self.waypoints != other.waypoints:
            return False
        if self.time_allocation != other.time_allocation:
            return False
        if self.total_duration != other.total_duration:
            return False
        if self.num_pieces != other.num_pieces:
            return False
        if self.is_valid != other.is_valid:
            return False
        if self.max_velocity != other.max_velocity:
            return False
        if self.clearance != other.clearance:
            return False
        if self.goal_position != other.goal_position:
            return False
        if self.goal_reached != other.goal_reached:
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
    def start_time(self):
        """Message field 'start_time'."""
        return self._start_time

    @start_time.setter
    def start_time(self, value):
        if __debug__:
            from builtin_interfaces.msg import Time
            assert \
                isinstance(value, Time), \
                "The 'start_time' field must be a sub message of type 'Time'"
        self._start_time = value

    @builtins.property
    def waypoints(self):
        """Message field 'waypoints'."""
        return self._waypoints

    @waypoints.setter
    def waypoints(self, value):
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
                "The 'waypoints' field must be a set or sequence and each value of type 'Point'"
        self._waypoints = value

    @builtins.property
    def time_allocation(self):
        """Message field 'time_allocation'."""
        return self._time_allocation

    @time_allocation.setter
    def time_allocation(self, value):
        if isinstance(value, array.array):
            assert value.typecode == 'd', \
                "The 'time_allocation' array.array() must have the type code of 'd'"
            self._time_allocation = value
            return
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
                 all(isinstance(v, float) for v in value) and
                 all(not (val < -1.7976931348623157e+308 or val > 1.7976931348623157e+308) or math.isinf(val) for val in value)), \
                "The 'time_allocation' field must be a set or sequence and each value of type 'float' and each double in [-179769313486231570814527423731704356798070567525844996598917476803157260780028538760589558632766878171540458953514382464234321326889464182768467546703537516986049910576551282076245490090389328944075868508455133942304583236903222948165808559332123348274797826204144723168738177180919299881250404026184124858368.000000, 179769313486231570814527423731704356798070567525844996598917476803157260780028538760589558632766878171540458953514382464234321326889464182768467546703537516986049910576551282076245490090389328944075868508455133942304583236903222948165808559332123348274797826204144723168738177180919299881250404026184124858368.000000]"
        self._time_allocation = array.array('d', value)

    @builtins.property
    def total_duration(self):
        """Message field 'total_duration'."""
        return self._total_duration

    @total_duration.setter
    def total_duration(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'total_duration' field must be of type 'float'"
            assert not (value < -1.7976931348623157e+308 or value > 1.7976931348623157e+308) or math.isinf(value), \
                "The 'total_duration' field must be a double in [-1.7976931348623157e+308, 1.7976931348623157e+308]"
        self._total_duration = value

    @builtins.property
    def num_pieces(self):
        """Message field 'num_pieces'."""
        return self._num_pieces

    @num_pieces.setter
    def num_pieces(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'num_pieces' field must be of type 'int'"
            assert value >= 0 and value < 256, \
                "The 'num_pieces' field must be an unsigned integer in [0, 255]"
        self._num_pieces = value

    @builtins.property
    def is_valid(self):
        """Message field 'is_valid'."""
        return self._is_valid

    @is_valid.setter
    def is_valid(self, value):
        if __debug__:
            assert \
                isinstance(value, bool), \
                "The 'is_valid' field must be of type 'bool'"
        self._is_valid = value

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
    def clearance(self):
        """Message field 'clearance'."""
        return self._clearance

    @clearance.setter
    def clearance(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'clearance' field must be of type 'float'"
            assert not (value < -3.402823466e+38 or value > 3.402823466e+38) or math.isinf(value), \
                "The 'clearance' field must be a float in [-3.402823466e+38, 3.402823466e+38]"
        self._clearance = value

    @builtins.property
    def goal_position(self):
        """Message field 'goal_position'."""
        return self._goal_position

    @goal_position.setter
    def goal_position(self, value):
        if __debug__:
            from geometry_msgs.msg import Point
            assert \
                isinstance(value, Point), \
                "The 'goal_position' field must be a sub message of type 'Point'"
        self._goal_position = value

    @builtins.property
    def goal_reached(self):
        """Message field 'goal_reached'."""
        return self._goal_reached

    @goal_reached.setter
    def goal_reached(self, value):
        if __debug__:
            assert \
                isinstance(value, bool), \
                "The 'goal_reached' field must be of type 'bool'"
        self._goal_reached = value
