# generated from rosidl_generator_py/resource/_idl.py.em
# with input from aura_msgs:msg/MissionStatus.idl
# generated code does not contain a copyright notice


# Import statements for member types

# Member 'alert_severities'
import array  # noqa: E402, I100

import builtins  # noqa: E402, I100

import math  # noqa: E402, I100

import rosidl_parser.definition  # noqa: E402, I100


class Metaclass_MissionStatus(type):
    """Metaclass of message 'MissionStatus'."""

    _CREATE_ROS_MESSAGE = None
    _CONVERT_FROM_PY = None
    _CONVERT_TO_PY = None
    _DESTROY_ROS_MESSAGE = None
    _TYPE_SUPPORT = None

    __constants = {
        'PHASE_INIT': 0,
        'PHASE_PREFLIGHT': 1,
        'PHASE_LAUNCH': 2,
        'PHASE_TRANSIT': 3,
        'PHASE_DEPLOY': 4,
        'PHASE_OPERATIONS': 5,
        'PHASE_RECOVERY': 6,
        'PHASE_COMPLETE': 7,
        'PHASE_ABORT': 8,
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
                'aura_msgs.msg.MissionStatus')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__msg__mission_status
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__msg__mission_status
            cls._CONVERT_TO_PY = module.convert_to_py_msg__msg__mission_status
            cls._TYPE_SUPPORT = module.type_support_msg__msg__mission_status
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__msg__mission_status

            from builtin_interfaces.msg import Time
            if Time.__class__._TYPE_SUPPORT is None:
                Time.__class__.__import_type_support__()

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
            'PHASE_INIT': cls.__constants['PHASE_INIT'],
            'PHASE_PREFLIGHT': cls.__constants['PHASE_PREFLIGHT'],
            'PHASE_LAUNCH': cls.__constants['PHASE_LAUNCH'],
            'PHASE_TRANSIT': cls.__constants['PHASE_TRANSIT'],
            'PHASE_DEPLOY': cls.__constants['PHASE_DEPLOY'],
            'PHASE_OPERATIONS': cls.__constants['PHASE_OPERATIONS'],
            'PHASE_RECOVERY': cls.__constants['PHASE_RECOVERY'],
            'PHASE_COMPLETE': cls.__constants['PHASE_COMPLETE'],
            'PHASE_ABORT': cls.__constants['PHASE_ABORT'],
        }

    @property
    def PHASE_INIT(self):
        """Message constant 'PHASE_INIT'."""
        return Metaclass_MissionStatus.__constants['PHASE_INIT']

    @property
    def PHASE_PREFLIGHT(self):
        """Message constant 'PHASE_PREFLIGHT'."""
        return Metaclass_MissionStatus.__constants['PHASE_PREFLIGHT']

    @property
    def PHASE_LAUNCH(self):
        """Message constant 'PHASE_LAUNCH'."""
        return Metaclass_MissionStatus.__constants['PHASE_LAUNCH']

    @property
    def PHASE_TRANSIT(self):
        """Message constant 'PHASE_TRANSIT'."""
        return Metaclass_MissionStatus.__constants['PHASE_TRANSIT']

    @property
    def PHASE_DEPLOY(self):
        """Message constant 'PHASE_DEPLOY'."""
        return Metaclass_MissionStatus.__constants['PHASE_DEPLOY']

    @property
    def PHASE_OPERATIONS(self):
        """Message constant 'PHASE_OPERATIONS'."""
        return Metaclass_MissionStatus.__constants['PHASE_OPERATIONS']

    @property
    def PHASE_RECOVERY(self):
        """Message constant 'PHASE_RECOVERY'."""
        return Metaclass_MissionStatus.__constants['PHASE_RECOVERY']

    @property
    def PHASE_COMPLETE(self):
        """Message constant 'PHASE_COMPLETE'."""
        return Metaclass_MissionStatus.__constants['PHASE_COMPLETE']

    @property
    def PHASE_ABORT(self):
        """Message constant 'PHASE_ABORT'."""
        return Metaclass_MissionStatus.__constants['PHASE_ABORT']


class MissionStatus(metaclass=Metaclass_MissionStatus):
    """
    Message class 'MissionStatus'.

    Constants:
      PHASE_INIT
      PHASE_PREFLIGHT
      PHASE_LAUNCH
      PHASE_TRANSIT
      PHASE_DEPLOY
      PHASE_OPERATIONS
      PHASE_RECOVERY
      PHASE_COMPLETE
      PHASE_ABORT
    """

    __slots__ = [
        '_timestamp',
        '_mission_id',
        '_phase',
        '_progress_percent',
        '_elapsed_time_sec',
        '_estimated_remaining_sec',
        '_coverage_achieved',
        '_network_quality',
        '_connections_established',
        '_data_transferred_mb',
        '_active_alerts',
        '_alert_severities',
        '_drones_operational',
        '_drones_degraded',
        '_drones_failed',
    ]

    _fields_and_field_types = {
        'timestamp': 'builtin_interfaces/Time',
        'mission_id': 'string',
        'phase': 'uint8',
        'progress_percent': 'float',
        'elapsed_time_sec': 'float',
        'estimated_remaining_sec': 'float',
        'coverage_achieved': 'float',
        'network_quality': 'float',
        'connections_established': 'uint32',
        'data_transferred_mb': 'uint32',
        'active_alerts': 'sequence<string>',
        'alert_severities': 'sequence<uint8>',
        'drones_operational': 'uint8',
        'drones_degraded': 'uint8',
        'drones_failed': 'uint8',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.NamespacedType(['builtin_interfaces', 'msg'], 'Time'),  # noqa: E501
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
        rosidl_parser.definition.BasicType('uint8'),  # noqa: E501
        rosidl_parser.definition.BasicType('float'),  # noqa: E501
        rosidl_parser.definition.BasicType('float'),  # noqa: E501
        rosidl_parser.definition.BasicType('float'),  # noqa: E501
        rosidl_parser.definition.BasicType('float'),  # noqa: E501
        rosidl_parser.definition.BasicType('float'),  # noqa: E501
        rosidl_parser.definition.BasicType('uint32'),  # noqa: E501
        rosidl_parser.definition.BasicType('uint32'),  # noqa: E501
        rosidl_parser.definition.UnboundedSequence(rosidl_parser.definition.UnboundedString()),  # noqa: E501
        rosidl_parser.definition.UnboundedSequence(rosidl_parser.definition.BasicType('uint8')),  # noqa: E501
        rosidl_parser.definition.BasicType('uint8'),  # noqa: E501
        rosidl_parser.definition.BasicType('uint8'),  # noqa: E501
        rosidl_parser.definition.BasicType('uint8'),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        from builtin_interfaces.msg import Time
        self.timestamp = kwargs.get('timestamp', Time())
        self.mission_id = kwargs.get('mission_id', str())
        self.phase = kwargs.get('phase', int())
        self.progress_percent = kwargs.get('progress_percent', float())
        self.elapsed_time_sec = kwargs.get('elapsed_time_sec', float())
        self.estimated_remaining_sec = kwargs.get('estimated_remaining_sec', float())
        self.coverage_achieved = kwargs.get('coverage_achieved', float())
        self.network_quality = kwargs.get('network_quality', float())
        self.connections_established = kwargs.get('connections_established', int())
        self.data_transferred_mb = kwargs.get('data_transferred_mb', int())
        self.active_alerts = kwargs.get('active_alerts', [])
        self.alert_severities = array.array('B', kwargs.get('alert_severities', []))
        self.drones_operational = kwargs.get('drones_operational', int())
        self.drones_degraded = kwargs.get('drones_degraded', int())
        self.drones_failed = kwargs.get('drones_failed', int())

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
        if self.mission_id != other.mission_id:
            return False
        if self.phase != other.phase:
            return False
        if self.progress_percent != other.progress_percent:
            return False
        if self.elapsed_time_sec != other.elapsed_time_sec:
            return False
        if self.estimated_remaining_sec != other.estimated_remaining_sec:
            return False
        if self.coverage_achieved != other.coverage_achieved:
            return False
        if self.network_quality != other.network_quality:
            return False
        if self.connections_established != other.connections_established:
            return False
        if self.data_transferred_mb != other.data_transferred_mb:
            return False
        if self.active_alerts != other.active_alerts:
            return False
        if self.alert_severities != other.alert_severities:
            return False
        if self.drones_operational != other.drones_operational:
            return False
        if self.drones_degraded != other.drones_degraded:
            return False
        if self.drones_failed != other.drones_failed:
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
    def phase(self):
        """Message field 'phase'."""
        return self._phase

    @phase.setter
    def phase(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'phase' field must be of type 'int'"
            assert value >= 0 and value < 256, \
                "The 'phase' field must be an unsigned integer in [0, 255]"
        self._phase = value

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

    @builtins.property
    def estimated_remaining_sec(self):
        """Message field 'estimated_remaining_sec'."""
        return self._estimated_remaining_sec

    @estimated_remaining_sec.setter
    def estimated_remaining_sec(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'estimated_remaining_sec' field must be of type 'float'"
            assert not (value < -3.402823466e+38 or value > 3.402823466e+38) or math.isinf(value), \
                "The 'estimated_remaining_sec' field must be a float in [-3.402823466e+38, 3.402823466e+38]"
        self._estimated_remaining_sec = value

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
    def network_quality(self):
        """Message field 'network_quality'."""
        return self._network_quality

    @network_quality.setter
    def network_quality(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'network_quality' field must be of type 'float'"
            assert not (value < -3.402823466e+38 or value > 3.402823466e+38) or math.isinf(value), \
                "The 'network_quality' field must be a float in [-3.402823466e+38, 3.402823466e+38]"
        self._network_quality = value

    @builtins.property
    def connections_established(self):
        """Message field 'connections_established'."""
        return self._connections_established

    @connections_established.setter
    def connections_established(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'connections_established' field must be of type 'int'"
            assert value >= 0 and value < 4294967296, \
                "The 'connections_established' field must be an unsigned integer in [0, 4294967295]"
        self._connections_established = value

    @builtins.property
    def data_transferred_mb(self):
        """Message field 'data_transferred_mb'."""
        return self._data_transferred_mb

    @data_transferred_mb.setter
    def data_transferred_mb(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'data_transferred_mb' field must be of type 'int'"
            assert value >= 0 and value < 4294967296, \
                "The 'data_transferred_mb' field must be an unsigned integer in [0, 4294967295]"
        self._data_transferred_mb = value

    @builtins.property
    def active_alerts(self):
        """Message field 'active_alerts'."""
        return self._active_alerts

    @active_alerts.setter
    def active_alerts(self, value):
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
                "The 'active_alerts' field must be a set or sequence and each value of type 'str'"
        self._active_alerts = value

    @builtins.property
    def alert_severities(self):
        """Message field 'alert_severities'."""
        return self._alert_severities

    @alert_severities.setter
    def alert_severities(self, value):
        if isinstance(value, array.array):
            assert value.typecode == 'B', \
                "The 'alert_severities' array.array() must have the type code of 'B'"
            self._alert_severities = value
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
                 all(isinstance(v, int) for v in value) and
                 all(val >= 0 and val < 256 for val in value)), \
                "The 'alert_severities' field must be a set or sequence and each value of type 'int' and each unsigned integer in [0, 255]"
        self._alert_severities = array.array('B', value)

    @builtins.property
    def drones_operational(self):
        """Message field 'drones_operational'."""
        return self._drones_operational

    @drones_operational.setter
    def drones_operational(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'drones_operational' field must be of type 'int'"
            assert value >= 0 and value < 256, \
                "The 'drones_operational' field must be an unsigned integer in [0, 255]"
        self._drones_operational = value

    @builtins.property
    def drones_degraded(self):
        """Message field 'drones_degraded'."""
        return self._drones_degraded

    @drones_degraded.setter
    def drones_degraded(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'drones_degraded' field must be of type 'int'"
            assert value >= 0 and value < 256, \
                "The 'drones_degraded' field must be an unsigned integer in [0, 255]"
        self._drones_degraded = value

    @builtins.property
    def drones_failed(self):
        """Message field 'drones_failed'."""
        return self._drones_failed

    @drones_failed.setter
    def drones_failed(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'drones_failed' field must be of type 'int'"
            assert value >= 0 and value < 256, \
                "The 'drones_failed' field must be an unsigned integer in [0, 255]"
        self._drones_failed = value
