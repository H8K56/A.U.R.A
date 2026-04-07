# generated from rosidl_generator_py/resource/_idl.py.em
# with input from aura_msgs:msg/SwarmState.idl
# generated code does not contain a copyright notice


# Import statements for member types

import builtins  # noqa: E402, I100

import math  # noqa: E402, I100

import rosidl_parser.definition  # noqa: E402, I100


class Metaclass_SwarmState(type):
    """Metaclass of message 'SwarmState'."""

    _CREATE_ROS_MESSAGE = None
    _CONVERT_FROM_PY = None
    _CONVERT_TO_PY = None
    _DESTROY_ROS_MESSAGE = None
    _TYPE_SUPPORT = None

    __constants = {
        'MISSION_IDLE': 0,
        'MISSION_PREFLIGHT': 1,
        'MISSION_TAKEOFF': 2,
        'MISSION_TRANSIT': 3,
        'MISSION_FORMATION': 4,
        'MISSION_OPERATIONS': 5,
        'MISSION_RTL': 6,
        'MISSION_COMPLETE': 7,
        'MISSION_ABORT': 8,
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
                'aura_msgs.msg.SwarmState')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__msg__swarm_state
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__msg__swarm_state
            cls._CONVERT_TO_PY = module.convert_to_py_msg__msg__swarm_state
            cls._TYPE_SUPPORT = module.type_support_msg__msg__swarm_state
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__msg__swarm_state

            from aura_msgs.msg import DroneState
            if DroneState.__class__._TYPE_SUPPORT is None:
                DroneState.__class__.__import_type_support__()

            from builtin_interfaces.msg import Time
            if Time.__class__._TYPE_SUPPORT is None:
                Time.__class__.__import_type_support__()

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
            'MISSION_IDLE': cls.__constants['MISSION_IDLE'],
            'MISSION_PREFLIGHT': cls.__constants['MISSION_PREFLIGHT'],
            'MISSION_TAKEOFF': cls.__constants['MISSION_TAKEOFF'],
            'MISSION_TRANSIT': cls.__constants['MISSION_TRANSIT'],
            'MISSION_FORMATION': cls.__constants['MISSION_FORMATION'],
            'MISSION_OPERATIONS': cls.__constants['MISSION_OPERATIONS'],
            'MISSION_RTL': cls.__constants['MISSION_RTL'],
            'MISSION_COMPLETE': cls.__constants['MISSION_COMPLETE'],
            'MISSION_ABORT': cls.__constants['MISSION_ABORT'],
        }

    @property
    def MISSION_IDLE(self):
        """Message constant 'MISSION_IDLE'."""
        return Metaclass_SwarmState.__constants['MISSION_IDLE']

    @property
    def MISSION_PREFLIGHT(self):
        """Message constant 'MISSION_PREFLIGHT'."""
        return Metaclass_SwarmState.__constants['MISSION_PREFLIGHT']

    @property
    def MISSION_TAKEOFF(self):
        """Message constant 'MISSION_TAKEOFF'."""
        return Metaclass_SwarmState.__constants['MISSION_TAKEOFF']

    @property
    def MISSION_TRANSIT(self):
        """Message constant 'MISSION_TRANSIT'."""
        return Metaclass_SwarmState.__constants['MISSION_TRANSIT']

    @property
    def MISSION_FORMATION(self):
        """Message constant 'MISSION_FORMATION'."""
        return Metaclass_SwarmState.__constants['MISSION_FORMATION']

    @property
    def MISSION_OPERATIONS(self):
        """Message constant 'MISSION_OPERATIONS'."""
        return Metaclass_SwarmState.__constants['MISSION_OPERATIONS']

    @property
    def MISSION_RTL(self):
        """Message constant 'MISSION_RTL'."""
        return Metaclass_SwarmState.__constants['MISSION_RTL']

    @property
    def MISSION_COMPLETE(self):
        """Message constant 'MISSION_COMPLETE'."""
        return Metaclass_SwarmState.__constants['MISSION_COMPLETE']

    @property
    def MISSION_ABORT(self):
        """Message constant 'MISSION_ABORT'."""
        return Metaclass_SwarmState.__constants['MISSION_ABORT']


class SwarmState(metaclass=Metaclass_SwarmState):
    """
    Message class 'SwarmState'.

    Constants:
      MISSION_IDLE
      MISSION_PREFLIGHT
      MISSION_TAKEOFF
      MISSION_TRANSIT
      MISSION_FORMATION
      MISSION_OPERATIONS
      MISSION_RTL
      MISSION_COMPLETE
      MISSION_ABORT
    """

    __slots__ = [
        '_timestamp',
        '_num_drones_total',
        '_num_drones_active',
        '_num_hubs',
        '_num_leaves',
        '_mission_state',
        '_coverage_percent',
        '_coverage_quality',
        '_avg_throughput_mbps',
        '_avg_latency_ms',
        '_packet_loss_percent',
        '_mesh_connected',
        '_backhaul_connected',
        '_drones',
    ]

    _fields_and_field_types = {
        'timestamp': 'builtin_interfaces/Time',
        'num_drones_total': 'uint8',
        'num_drones_active': 'uint8',
        'num_hubs': 'uint8',
        'num_leaves': 'uint8',
        'mission_state': 'uint8',
        'coverage_percent': 'float',
        'coverage_quality': 'float',
        'avg_throughput_mbps': 'float',
        'avg_latency_ms': 'float',
        'packet_loss_percent': 'float',
        'mesh_connected': 'boolean',
        'backhaul_connected': 'boolean',
        'drones': 'sequence<aura_msgs/DroneState>',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.NamespacedType(['builtin_interfaces', 'msg'], 'Time'),  # noqa: E501
        rosidl_parser.definition.BasicType('uint8'),  # noqa: E501
        rosidl_parser.definition.BasicType('uint8'),  # noqa: E501
        rosidl_parser.definition.BasicType('uint8'),  # noqa: E501
        rosidl_parser.definition.BasicType('uint8'),  # noqa: E501
        rosidl_parser.definition.BasicType('uint8'),  # noqa: E501
        rosidl_parser.definition.BasicType('float'),  # noqa: E501
        rosidl_parser.definition.BasicType('float'),  # noqa: E501
        rosidl_parser.definition.BasicType('float'),  # noqa: E501
        rosidl_parser.definition.BasicType('float'),  # noqa: E501
        rosidl_parser.definition.BasicType('float'),  # noqa: E501
        rosidl_parser.definition.BasicType('boolean'),  # noqa: E501
        rosidl_parser.definition.BasicType('boolean'),  # noqa: E501
        rosidl_parser.definition.UnboundedSequence(rosidl_parser.definition.NamespacedType(['aura_msgs', 'msg'], 'DroneState')),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        from builtin_interfaces.msg import Time
        self.timestamp = kwargs.get('timestamp', Time())
        self.num_drones_total = kwargs.get('num_drones_total', int())
        self.num_drones_active = kwargs.get('num_drones_active', int())
        self.num_hubs = kwargs.get('num_hubs', int())
        self.num_leaves = kwargs.get('num_leaves', int())
        self.mission_state = kwargs.get('mission_state', int())
        self.coverage_percent = kwargs.get('coverage_percent', float())
        self.coverage_quality = kwargs.get('coverage_quality', float())
        self.avg_throughput_mbps = kwargs.get('avg_throughput_mbps', float())
        self.avg_latency_ms = kwargs.get('avg_latency_ms', float())
        self.packet_loss_percent = kwargs.get('packet_loss_percent', float())
        self.mesh_connected = kwargs.get('mesh_connected', bool())
        self.backhaul_connected = kwargs.get('backhaul_connected', bool())
        self.drones = kwargs.get('drones', [])

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
        if self.num_drones_total != other.num_drones_total:
            return False
        if self.num_drones_active != other.num_drones_active:
            return False
        if self.num_hubs != other.num_hubs:
            return False
        if self.num_leaves != other.num_leaves:
            return False
        if self.mission_state != other.mission_state:
            return False
        if self.coverage_percent != other.coverage_percent:
            return False
        if self.coverage_quality != other.coverage_quality:
            return False
        if self.avg_throughput_mbps != other.avg_throughput_mbps:
            return False
        if self.avg_latency_ms != other.avg_latency_ms:
            return False
        if self.packet_loss_percent != other.packet_loss_percent:
            return False
        if self.mesh_connected != other.mesh_connected:
            return False
        if self.backhaul_connected != other.backhaul_connected:
            return False
        if self.drones != other.drones:
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
    def num_drones_total(self):
        """Message field 'num_drones_total'."""
        return self._num_drones_total

    @num_drones_total.setter
    def num_drones_total(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'num_drones_total' field must be of type 'int'"
            assert value >= 0 and value < 256, \
                "The 'num_drones_total' field must be an unsigned integer in [0, 255]"
        self._num_drones_total = value

    @builtins.property
    def num_drones_active(self):
        """Message field 'num_drones_active'."""
        return self._num_drones_active

    @num_drones_active.setter
    def num_drones_active(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'num_drones_active' field must be of type 'int'"
            assert value >= 0 and value < 256, \
                "The 'num_drones_active' field must be an unsigned integer in [0, 255]"
        self._num_drones_active = value

    @builtins.property
    def num_hubs(self):
        """Message field 'num_hubs'."""
        return self._num_hubs

    @num_hubs.setter
    def num_hubs(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'num_hubs' field must be of type 'int'"
            assert value >= 0 and value < 256, \
                "The 'num_hubs' field must be an unsigned integer in [0, 255]"
        self._num_hubs = value

    @builtins.property
    def num_leaves(self):
        """Message field 'num_leaves'."""
        return self._num_leaves

    @num_leaves.setter
    def num_leaves(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'num_leaves' field must be of type 'int'"
            assert value >= 0 and value < 256, \
                "The 'num_leaves' field must be an unsigned integer in [0, 255]"
        self._num_leaves = value

    @builtins.property
    def mission_state(self):
        """Message field 'mission_state'."""
        return self._mission_state

    @mission_state.setter
    def mission_state(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'mission_state' field must be of type 'int'"
            assert value >= 0 and value < 256, \
                "The 'mission_state' field must be an unsigned integer in [0, 255]"
        self._mission_state = value

    @builtins.property
    def coverage_percent(self):
        """Message field 'coverage_percent'."""
        return self._coverage_percent

    @coverage_percent.setter
    def coverage_percent(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'coverage_percent' field must be of type 'float'"
            assert not (value < -3.402823466e+38 or value > 3.402823466e+38) or math.isinf(value), \
                "The 'coverage_percent' field must be a float in [-3.402823466e+38, 3.402823466e+38]"
        self._coverage_percent = value

    @builtins.property
    def coverage_quality(self):
        """Message field 'coverage_quality'."""
        return self._coverage_quality

    @coverage_quality.setter
    def coverage_quality(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'coverage_quality' field must be of type 'float'"
            assert not (value < -3.402823466e+38 or value > 3.402823466e+38) or math.isinf(value), \
                "The 'coverage_quality' field must be a float in [-3.402823466e+38, 3.402823466e+38]"
        self._coverage_quality = value

    @builtins.property
    def avg_throughput_mbps(self):
        """Message field 'avg_throughput_mbps'."""
        return self._avg_throughput_mbps

    @avg_throughput_mbps.setter
    def avg_throughput_mbps(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'avg_throughput_mbps' field must be of type 'float'"
            assert not (value < -3.402823466e+38 or value > 3.402823466e+38) or math.isinf(value), \
                "The 'avg_throughput_mbps' field must be a float in [-3.402823466e+38, 3.402823466e+38]"
        self._avg_throughput_mbps = value

    @builtins.property
    def avg_latency_ms(self):
        """Message field 'avg_latency_ms'."""
        return self._avg_latency_ms

    @avg_latency_ms.setter
    def avg_latency_ms(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'avg_latency_ms' field must be of type 'float'"
            assert not (value < -3.402823466e+38 or value > 3.402823466e+38) or math.isinf(value), \
                "The 'avg_latency_ms' field must be a float in [-3.402823466e+38, 3.402823466e+38]"
        self._avg_latency_ms = value

    @builtins.property
    def packet_loss_percent(self):
        """Message field 'packet_loss_percent'."""
        return self._packet_loss_percent

    @packet_loss_percent.setter
    def packet_loss_percent(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'packet_loss_percent' field must be of type 'float'"
            assert not (value < -3.402823466e+38 or value > 3.402823466e+38) or math.isinf(value), \
                "The 'packet_loss_percent' field must be a float in [-3.402823466e+38, 3.402823466e+38]"
        self._packet_loss_percent = value

    @builtins.property
    def mesh_connected(self):
        """Message field 'mesh_connected'."""
        return self._mesh_connected

    @mesh_connected.setter
    def mesh_connected(self, value):
        if __debug__:
            assert \
                isinstance(value, bool), \
                "The 'mesh_connected' field must be of type 'bool'"
        self._mesh_connected = value

    @builtins.property
    def backhaul_connected(self):
        """Message field 'backhaul_connected'."""
        return self._backhaul_connected

    @backhaul_connected.setter
    def backhaul_connected(self, value):
        if __debug__:
            assert \
                isinstance(value, bool), \
                "The 'backhaul_connected' field must be of type 'bool'"
        self._backhaul_connected = value

    @builtins.property
    def drones(self):
        """Message field 'drones'."""
        return self._drones

    @drones.setter
    def drones(self, value):
        if __debug__:
            from aura_msgs.msg import DroneState
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
                 all(isinstance(v, DroneState) for v in value) and
                 True), \
                "The 'drones' field must be a set or sequence and each value of type 'DroneState'"
        self._drones = value
