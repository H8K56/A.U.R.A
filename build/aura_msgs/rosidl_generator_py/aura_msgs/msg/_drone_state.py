# generated from rosidl_generator_py/resource/_idl.py.em
# with input from aura_msgs:msg/DroneState.idl
# generated code does not contain a copyright notice


# Import statements for member types

import builtins  # noqa: E402, I100

import math  # noqa: E402, I100

import rosidl_parser.definition  # noqa: E402, I100


class Metaclass_DroneState(type):
    """Metaclass of message 'DroneState'."""

    _CREATE_ROS_MESSAGE = None
    _CONVERT_FROM_PY = None
    _CONVERT_TO_PY = None
    _DESTROY_ROS_MESSAGE = None
    _TYPE_SUPPORT = None

    __constants = {
        'ROLE_LEAF': 0,
        'ROLE_HUB': 1,
        'FLIGHT_MODE_IDLE': 0,
        'FLIGHT_MODE_TAKEOFF': 1,
        'FLIGHT_MODE_TRANSIT': 2,
        'FLIGHT_MODE_FORMATION': 3,
        'FLIGHT_MODE_OPERATIONS': 4,
        'FLIGHT_MODE_RTL': 5,
        'FLIGHT_MODE_EMERGENCY': 6,
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
                'aura_msgs.msg.DroneState')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__msg__drone_state
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__msg__drone_state
            cls._CONVERT_TO_PY = module.convert_to_py_msg__msg__drone_state
            cls._TYPE_SUPPORT = module.type_support_msg__msg__drone_state
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__msg__drone_state

            from builtin_interfaces.msg import Time
            if Time.__class__._TYPE_SUPPORT is None:
                Time.__class__.__import_type_support__()

            from geometry_msgs.msg import Point
            if Point.__class__._TYPE_SUPPORT is None:
                Point.__class__.__import_type_support__()

            from geometry_msgs.msg import Quaternion
            if Quaternion.__class__._TYPE_SUPPORT is None:
                Quaternion.__class__.__import_type_support__()

            from geometry_msgs.msg import Vector3
            if Vector3.__class__._TYPE_SUPPORT is None:
                Vector3.__class__.__import_type_support__()

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
            'ROLE_LEAF': cls.__constants['ROLE_LEAF'],
            'ROLE_HUB': cls.__constants['ROLE_HUB'],
            'FLIGHT_MODE_IDLE': cls.__constants['FLIGHT_MODE_IDLE'],
            'FLIGHT_MODE_TAKEOFF': cls.__constants['FLIGHT_MODE_TAKEOFF'],
            'FLIGHT_MODE_TRANSIT': cls.__constants['FLIGHT_MODE_TRANSIT'],
            'FLIGHT_MODE_FORMATION': cls.__constants['FLIGHT_MODE_FORMATION'],
            'FLIGHT_MODE_OPERATIONS': cls.__constants['FLIGHT_MODE_OPERATIONS'],
            'FLIGHT_MODE_RTL': cls.__constants['FLIGHT_MODE_RTL'],
            'FLIGHT_MODE_EMERGENCY': cls.__constants['FLIGHT_MODE_EMERGENCY'],
        }

    @property
    def ROLE_LEAF(self):
        """Message constant 'ROLE_LEAF'."""
        return Metaclass_DroneState.__constants['ROLE_LEAF']

    @property
    def ROLE_HUB(self):
        """Message constant 'ROLE_HUB'."""
        return Metaclass_DroneState.__constants['ROLE_HUB']

    @property
    def FLIGHT_MODE_IDLE(self):
        """Message constant 'FLIGHT_MODE_IDLE'."""
        return Metaclass_DroneState.__constants['FLIGHT_MODE_IDLE']

    @property
    def FLIGHT_MODE_TAKEOFF(self):
        """Message constant 'FLIGHT_MODE_TAKEOFF'."""
        return Metaclass_DroneState.__constants['FLIGHT_MODE_TAKEOFF']

    @property
    def FLIGHT_MODE_TRANSIT(self):
        """Message constant 'FLIGHT_MODE_TRANSIT'."""
        return Metaclass_DroneState.__constants['FLIGHT_MODE_TRANSIT']

    @property
    def FLIGHT_MODE_FORMATION(self):
        """Message constant 'FLIGHT_MODE_FORMATION'."""
        return Metaclass_DroneState.__constants['FLIGHT_MODE_FORMATION']

    @property
    def FLIGHT_MODE_OPERATIONS(self):
        """Message constant 'FLIGHT_MODE_OPERATIONS'."""
        return Metaclass_DroneState.__constants['FLIGHT_MODE_OPERATIONS']

    @property
    def FLIGHT_MODE_RTL(self):
        """Message constant 'FLIGHT_MODE_RTL'."""
        return Metaclass_DroneState.__constants['FLIGHT_MODE_RTL']

    @property
    def FLIGHT_MODE_EMERGENCY(self):
        """Message constant 'FLIGHT_MODE_EMERGENCY'."""
        return Metaclass_DroneState.__constants['FLIGHT_MODE_EMERGENCY']


class DroneState(metaclass=Metaclass_DroneState):
    """
    Message class 'DroneState'.

    Constants:
      ROLE_LEAF
      ROLE_HUB
      FLIGHT_MODE_IDLE
      FLIGHT_MODE_TAKEOFF
      FLIGHT_MODE_TRANSIT
      FLIGHT_MODE_FORMATION
      FLIGHT_MODE_OPERATIONS
      FLIGHT_MODE_RTL
      FLIGHT_MODE_EMERGENCY
    """

    __slots__ = [
        '_timestamp',
        '_drone_id',
        '_role',
        '_position',
        '_velocity',
        '_orientation',
        '_flight_mode',
        '_battery_percent',
        '_battery_voltage',
        '_signal_strength_dbm',
        '_gps_fix',
        '_num_satellites',
        '_throughput_mbps',
        '_latency_ms',
        '_connected_neighbors',
    ]

    _fields_and_field_types = {
        'timestamp': 'builtin_interfaces/Time',
        'drone_id': 'uint8',
        'role': 'uint8',
        'position': 'geometry_msgs/Point',
        'velocity': 'geometry_msgs/Vector3',
        'orientation': 'geometry_msgs/Quaternion',
        'flight_mode': 'uint8',
        'battery_percent': 'float',
        'battery_voltage': 'float',
        'signal_strength_dbm': 'float',
        'gps_fix': 'boolean',
        'num_satellites': 'uint8',
        'throughput_mbps': 'float',
        'latency_ms': 'float',
        'connected_neighbors': 'uint8',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.NamespacedType(['builtin_interfaces', 'msg'], 'Time'),  # noqa: E501
        rosidl_parser.definition.BasicType('uint8'),  # noqa: E501
        rosidl_parser.definition.BasicType('uint8'),  # noqa: E501
        rosidl_parser.definition.NamespacedType(['geometry_msgs', 'msg'], 'Point'),  # noqa: E501
        rosidl_parser.definition.NamespacedType(['geometry_msgs', 'msg'], 'Vector3'),  # noqa: E501
        rosidl_parser.definition.NamespacedType(['geometry_msgs', 'msg'], 'Quaternion'),  # noqa: E501
        rosidl_parser.definition.BasicType('uint8'),  # noqa: E501
        rosidl_parser.definition.BasicType('float'),  # noqa: E501
        rosidl_parser.definition.BasicType('float'),  # noqa: E501
        rosidl_parser.definition.BasicType('float'),  # noqa: E501
        rosidl_parser.definition.BasicType('boolean'),  # noqa: E501
        rosidl_parser.definition.BasicType('uint8'),  # noqa: E501
        rosidl_parser.definition.BasicType('float'),  # noqa: E501
        rosidl_parser.definition.BasicType('float'),  # noqa: E501
        rosidl_parser.definition.BasicType('uint8'),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        from builtin_interfaces.msg import Time
        self.timestamp = kwargs.get('timestamp', Time())
        self.drone_id = kwargs.get('drone_id', int())
        self.role = kwargs.get('role', int())
        from geometry_msgs.msg import Point
        self.position = kwargs.get('position', Point())
        from geometry_msgs.msg import Vector3
        self.velocity = kwargs.get('velocity', Vector3())
        from geometry_msgs.msg import Quaternion
        self.orientation = kwargs.get('orientation', Quaternion())
        self.flight_mode = kwargs.get('flight_mode', int())
        self.battery_percent = kwargs.get('battery_percent', float())
        self.battery_voltage = kwargs.get('battery_voltage', float())
        self.signal_strength_dbm = kwargs.get('signal_strength_dbm', float())
        self.gps_fix = kwargs.get('gps_fix', bool())
        self.num_satellites = kwargs.get('num_satellites', int())
        self.throughput_mbps = kwargs.get('throughput_mbps', float())
        self.latency_ms = kwargs.get('latency_ms', float())
        self.connected_neighbors = kwargs.get('connected_neighbors', int())

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
        if self.role != other.role:
            return False
        if self.position != other.position:
            return False
        if self.velocity != other.velocity:
            return False
        if self.orientation != other.orientation:
            return False
        if self.flight_mode != other.flight_mode:
            return False
        if self.battery_percent != other.battery_percent:
            return False
        if self.battery_voltage != other.battery_voltage:
            return False
        if self.signal_strength_dbm != other.signal_strength_dbm:
            return False
        if self.gps_fix != other.gps_fix:
            return False
        if self.num_satellites != other.num_satellites:
            return False
        if self.throughput_mbps != other.throughput_mbps:
            return False
        if self.latency_ms != other.latency_ms:
            return False
        if self.connected_neighbors != other.connected_neighbors:
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
    def role(self):
        """Message field 'role'."""
        return self._role

    @role.setter
    def role(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'role' field must be of type 'int'"
            assert value >= 0 and value < 256, \
                "The 'role' field must be an unsigned integer in [0, 255]"
        self._role = value

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
    def velocity(self):
        """Message field 'velocity'."""
        return self._velocity

    @velocity.setter
    def velocity(self, value):
        if __debug__:
            from geometry_msgs.msg import Vector3
            assert \
                isinstance(value, Vector3), \
                "The 'velocity' field must be a sub message of type 'Vector3'"
        self._velocity = value

    @builtins.property
    def orientation(self):
        """Message field 'orientation'."""
        return self._orientation

    @orientation.setter
    def orientation(self, value):
        if __debug__:
            from geometry_msgs.msg import Quaternion
            assert \
                isinstance(value, Quaternion), \
                "The 'orientation' field must be a sub message of type 'Quaternion'"
        self._orientation = value

    @builtins.property
    def flight_mode(self):
        """Message field 'flight_mode'."""
        return self._flight_mode

    @flight_mode.setter
    def flight_mode(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'flight_mode' field must be of type 'int'"
            assert value >= 0 and value < 256, \
                "The 'flight_mode' field must be an unsigned integer in [0, 255]"
        self._flight_mode = value

    @builtins.property
    def battery_percent(self):
        """Message field 'battery_percent'."""
        return self._battery_percent

    @battery_percent.setter
    def battery_percent(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'battery_percent' field must be of type 'float'"
            assert not (value < -3.402823466e+38 or value > 3.402823466e+38) or math.isinf(value), \
                "The 'battery_percent' field must be a float in [-3.402823466e+38, 3.402823466e+38]"
        self._battery_percent = value

    @builtins.property
    def battery_voltage(self):
        """Message field 'battery_voltage'."""
        return self._battery_voltage

    @battery_voltage.setter
    def battery_voltage(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'battery_voltage' field must be of type 'float'"
            assert not (value < -3.402823466e+38 or value > 3.402823466e+38) or math.isinf(value), \
                "The 'battery_voltage' field must be a float in [-3.402823466e+38, 3.402823466e+38]"
        self._battery_voltage = value

    @builtins.property
    def signal_strength_dbm(self):
        """Message field 'signal_strength_dbm'."""
        return self._signal_strength_dbm

    @signal_strength_dbm.setter
    def signal_strength_dbm(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'signal_strength_dbm' field must be of type 'float'"
            assert not (value < -3.402823466e+38 or value > 3.402823466e+38) or math.isinf(value), \
                "The 'signal_strength_dbm' field must be a float in [-3.402823466e+38, 3.402823466e+38]"
        self._signal_strength_dbm = value

    @builtins.property
    def gps_fix(self):
        """Message field 'gps_fix'."""
        return self._gps_fix

    @gps_fix.setter
    def gps_fix(self, value):
        if __debug__:
            assert \
                isinstance(value, bool), \
                "The 'gps_fix' field must be of type 'bool'"
        self._gps_fix = value

    @builtins.property
    def num_satellites(self):
        """Message field 'num_satellites'."""
        return self._num_satellites

    @num_satellites.setter
    def num_satellites(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'num_satellites' field must be of type 'int'"
            assert value >= 0 and value < 256, \
                "The 'num_satellites' field must be an unsigned integer in [0, 255]"
        self._num_satellites = value

    @builtins.property
    def throughput_mbps(self):
        """Message field 'throughput_mbps'."""
        return self._throughput_mbps

    @throughput_mbps.setter
    def throughput_mbps(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'throughput_mbps' field must be of type 'float'"
            assert not (value < -3.402823466e+38 or value > 3.402823466e+38) or math.isinf(value), \
                "The 'throughput_mbps' field must be a float in [-3.402823466e+38, 3.402823466e+38]"
        self._throughput_mbps = value

    @builtins.property
    def latency_ms(self):
        """Message field 'latency_ms'."""
        return self._latency_ms

    @latency_ms.setter
    def latency_ms(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'latency_ms' field must be of type 'float'"
            assert not (value < -3.402823466e+38 or value > 3.402823466e+38) or math.isinf(value), \
                "The 'latency_ms' field must be a float in [-3.402823466e+38, 3.402823466e+38]"
        self._latency_ms = value

    @builtins.property
    def connected_neighbors(self):
        """Message field 'connected_neighbors'."""
        return self._connected_neighbors

    @connected_neighbors.setter
    def connected_neighbors(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'connected_neighbors' field must be of type 'int'"
            assert value >= 0 and value < 256, \
                "The 'connected_neighbors' field must be an unsigned integer in [0, 255]"
        self._connected_neighbors = value
