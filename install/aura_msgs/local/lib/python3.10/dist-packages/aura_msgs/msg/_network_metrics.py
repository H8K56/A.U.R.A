# generated from rosidl_generator_py/resource/_idl.py.em
# with input from aura_msgs:msg/NetworkMetrics.idl
# generated code does not contain a copyright notice


# Import statements for member types

# Member 'signal_strength_dbm'
# Member 'throughput_mbps'
# Member 'latency_ms'
# Member 'link_from_drone'
# Member 'link_to_drone'
# Member 'link_throughput_mbps'
# Member 'link_latency_ms'
# Member 'link_rssi_dbm'
import array  # noqa: E402, I100

import builtins  # noqa: E402, I100

import math  # noqa: E402, I100

import rosidl_parser.definition  # noqa: E402, I100


class Metaclass_NetworkMetrics(type):
    """Metaclass of message 'NetworkMetrics'."""

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
                'aura_msgs.msg.NetworkMetrics')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__msg__network_metrics
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__msg__network_metrics
            cls._CONVERT_TO_PY = module.convert_to_py_msg__msg__network_metrics
            cls._TYPE_SUPPORT = module.type_support_msg__msg__network_metrics
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__msg__network_metrics

            from builtin_interfaces.msg import Time
            if Time.__class__._TYPE_SUPPORT is None:
                Time.__class__.__import_type_support__()

            from geometry_msgs.msg import Point
            if Point.__class__._TYPE_SUPPORT is None:
                Point.__class__.__import_type_support__()

            from std_msgs.msg import Header
            if Header.__class__._TYPE_SUPPORT is None:
                Header.__class__.__import_type_support__()

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
        }


class NetworkMetrics(metaclass=Metaclass_NetworkMetrics):
    """Message class 'NetworkMetrics'."""

    __slots__ = [
        '_header',
        '_timestamp',
        '_grid_size_x',
        '_grid_size_y',
        '_cell_size_meters',
        '_origin',
        '_signal_strength_dbm',
        '_throughput_mbps',
        '_latency_ms',
        '_coverage_mask',
        '_total_coverage_percent',
        '_avg_signal_strength_dbm',
        '_avg_throughput_mbps',
        '_avg_latency_ms',
        '_packet_loss_percent',
        '_link_from_drone',
        '_link_to_drone',
        '_link_throughput_mbps',
        '_link_latency_ms',
        '_link_rssi_dbm',
        '_mesh_connected',
        '_backhaul_active',
        '_backhaul_throughput_mbps',
        '_backhaul_latency_ms',
    ]

    _fields_and_field_types = {
        'header': 'std_msgs/Header',
        'timestamp': 'builtin_interfaces/Time',
        'grid_size_x': 'uint32',
        'grid_size_y': 'uint32',
        'cell_size_meters': 'float',
        'origin': 'geometry_msgs/Point',
        'signal_strength_dbm': 'sequence<float>',
        'throughput_mbps': 'sequence<float>',
        'latency_ms': 'sequence<float>',
        'coverage_mask': 'sequence<boolean>',
        'total_coverage_percent': 'float',
        'avg_signal_strength_dbm': 'float',
        'avg_throughput_mbps': 'float',
        'avg_latency_ms': 'float',
        'packet_loss_percent': 'float',
        'link_from_drone': 'sequence<uint8>',
        'link_to_drone': 'sequence<uint8>',
        'link_throughput_mbps': 'sequence<float>',
        'link_latency_ms': 'sequence<float>',
        'link_rssi_dbm': 'sequence<float>',
        'mesh_connected': 'boolean',
        'backhaul_active': 'boolean',
        'backhaul_throughput_mbps': 'float',
        'backhaul_latency_ms': 'float',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.NamespacedType(['std_msgs', 'msg'], 'Header'),  # noqa: E501
        rosidl_parser.definition.NamespacedType(['builtin_interfaces', 'msg'], 'Time'),  # noqa: E501
        rosidl_parser.definition.BasicType('uint32'),  # noqa: E501
        rosidl_parser.definition.BasicType('uint32'),  # noqa: E501
        rosidl_parser.definition.BasicType('float'),  # noqa: E501
        rosidl_parser.definition.NamespacedType(['geometry_msgs', 'msg'], 'Point'),  # noqa: E501
        rosidl_parser.definition.UnboundedSequence(rosidl_parser.definition.BasicType('float')),  # noqa: E501
        rosidl_parser.definition.UnboundedSequence(rosidl_parser.definition.BasicType('float')),  # noqa: E501
        rosidl_parser.definition.UnboundedSequence(rosidl_parser.definition.BasicType('float')),  # noqa: E501
        rosidl_parser.definition.UnboundedSequence(rosidl_parser.definition.BasicType('boolean')),  # noqa: E501
        rosidl_parser.definition.BasicType('float'),  # noqa: E501
        rosidl_parser.definition.BasicType('float'),  # noqa: E501
        rosidl_parser.definition.BasicType('float'),  # noqa: E501
        rosidl_parser.definition.BasicType('float'),  # noqa: E501
        rosidl_parser.definition.BasicType('float'),  # noqa: E501
        rosidl_parser.definition.UnboundedSequence(rosidl_parser.definition.BasicType('uint8')),  # noqa: E501
        rosidl_parser.definition.UnboundedSequence(rosidl_parser.definition.BasicType('uint8')),  # noqa: E501
        rosidl_parser.definition.UnboundedSequence(rosidl_parser.definition.BasicType('float')),  # noqa: E501
        rosidl_parser.definition.UnboundedSequence(rosidl_parser.definition.BasicType('float')),  # noqa: E501
        rosidl_parser.definition.UnboundedSequence(rosidl_parser.definition.BasicType('float')),  # noqa: E501
        rosidl_parser.definition.BasicType('boolean'),  # noqa: E501
        rosidl_parser.definition.BasicType('boolean'),  # noqa: E501
        rosidl_parser.definition.BasicType('float'),  # noqa: E501
        rosidl_parser.definition.BasicType('float'),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        from std_msgs.msg import Header
        self.header = kwargs.get('header', Header())
        from builtin_interfaces.msg import Time
        self.timestamp = kwargs.get('timestamp', Time())
        self.grid_size_x = kwargs.get('grid_size_x', int())
        self.grid_size_y = kwargs.get('grid_size_y', int())
        self.cell_size_meters = kwargs.get('cell_size_meters', float())
        from geometry_msgs.msg import Point
        self.origin = kwargs.get('origin', Point())
        self.signal_strength_dbm = array.array('f', kwargs.get('signal_strength_dbm', []))
        self.throughput_mbps = array.array('f', kwargs.get('throughput_mbps', []))
        self.latency_ms = array.array('f', kwargs.get('latency_ms', []))
        self.coverage_mask = kwargs.get('coverage_mask', [])
        self.total_coverage_percent = kwargs.get('total_coverage_percent', float())
        self.avg_signal_strength_dbm = kwargs.get('avg_signal_strength_dbm', float())
        self.avg_throughput_mbps = kwargs.get('avg_throughput_mbps', float())
        self.avg_latency_ms = kwargs.get('avg_latency_ms', float())
        self.packet_loss_percent = kwargs.get('packet_loss_percent', float())
        self.link_from_drone = array.array('B', kwargs.get('link_from_drone', []))
        self.link_to_drone = array.array('B', kwargs.get('link_to_drone', []))
        self.link_throughput_mbps = array.array('f', kwargs.get('link_throughput_mbps', []))
        self.link_latency_ms = array.array('f', kwargs.get('link_latency_ms', []))
        self.link_rssi_dbm = array.array('f', kwargs.get('link_rssi_dbm', []))
        self.mesh_connected = kwargs.get('mesh_connected', bool())
        self.backhaul_active = kwargs.get('backhaul_active', bool())
        self.backhaul_throughput_mbps = kwargs.get('backhaul_throughput_mbps', float())
        self.backhaul_latency_ms = kwargs.get('backhaul_latency_ms', float())

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
        if self.header != other.header:
            return False
        if self.timestamp != other.timestamp:
            return False
        if self.grid_size_x != other.grid_size_x:
            return False
        if self.grid_size_y != other.grid_size_y:
            return False
        if self.cell_size_meters != other.cell_size_meters:
            return False
        if self.origin != other.origin:
            return False
        if self.signal_strength_dbm != other.signal_strength_dbm:
            return False
        if self.throughput_mbps != other.throughput_mbps:
            return False
        if self.latency_ms != other.latency_ms:
            return False
        if self.coverage_mask != other.coverage_mask:
            return False
        if self.total_coverage_percent != other.total_coverage_percent:
            return False
        if self.avg_signal_strength_dbm != other.avg_signal_strength_dbm:
            return False
        if self.avg_throughput_mbps != other.avg_throughput_mbps:
            return False
        if self.avg_latency_ms != other.avg_latency_ms:
            return False
        if self.packet_loss_percent != other.packet_loss_percent:
            return False
        if self.link_from_drone != other.link_from_drone:
            return False
        if self.link_to_drone != other.link_to_drone:
            return False
        if self.link_throughput_mbps != other.link_throughput_mbps:
            return False
        if self.link_latency_ms != other.link_latency_ms:
            return False
        if self.link_rssi_dbm != other.link_rssi_dbm:
            return False
        if self.mesh_connected != other.mesh_connected:
            return False
        if self.backhaul_active != other.backhaul_active:
            return False
        if self.backhaul_throughput_mbps != other.backhaul_throughput_mbps:
            return False
        if self.backhaul_latency_ms != other.backhaul_latency_ms:
            return False
        return True

    @classmethod
    def get_fields_and_field_types(cls):
        from copy import copy
        return copy(cls._fields_and_field_types)

    @builtins.property
    def header(self):
        """Message field 'header'."""
        return self._header

    @header.setter
    def header(self, value):
        if __debug__:
            from std_msgs.msg import Header
            assert \
                isinstance(value, Header), \
                "The 'header' field must be a sub message of type 'Header'"
        self._header = value

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
    def grid_size_x(self):
        """Message field 'grid_size_x'."""
        return self._grid_size_x

    @grid_size_x.setter
    def grid_size_x(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'grid_size_x' field must be of type 'int'"
            assert value >= 0 and value < 4294967296, \
                "The 'grid_size_x' field must be an unsigned integer in [0, 4294967295]"
        self._grid_size_x = value

    @builtins.property
    def grid_size_y(self):
        """Message field 'grid_size_y'."""
        return self._grid_size_y

    @grid_size_y.setter
    def grid_size_y(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'grid_size_y' field must be of type 'int'"
            assert value >= 0 and value < 4294967296, \
                "The 'grid_size_y' field must be an unsigned integer in [0, 4294967295]"
        self._grid_size_y = value

    @builtins.property
    def cell_size_meters(self):
        """Message field 'cell_size_meters'."""
        return self._cell_size_meters

    @cell_size_meters.setter
    def cell_size_meters(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'cell_size_meters' field must be of type 'float'"
            assert not (value < -3.402823466e+38 or value > 3.402823466e+38) or math.isinf(value), \
                "The 'cell_size_meters' field must be a float in [-3.402823466e+38, 3.402823466e+38]"
        self._cell_size_meters = value

    @builtins.property
    def origin(self):
        """Message field 'origin'."""
        return self._origin

    @origin.setter
    def origin(self, value):
        if __debug__:
            from geometry_msgs.msg import Point
            assert \
                isinstance(value, Point), \
                "The 'origin' field must be a sub message of type 'Point'"
        self._origin = value

    @builtins.property
    def signal_strength_dbm(self):
        """Message field 'signal_strength_dbm'."""
        return self._signal_strength_dbm

    @signal_strength_dbm.setter
    def signal_strength_dbm(self, value):
        if isinstance(value, array.array):
            assert value.typecode == 'f', \
                "The 'signal_strength_dbm' array.array() must have the type code of 'f'"
            self._signal_strength_dbm = value
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
                 all(not (val < -3.402823466e+38 or val > 3.402823466e+38) or math.isinf(val) for val in value)), \
                "The 'signal_strength_dbm' field must be a set or sequence and each value of type 'float' and each float in [-340282346600000016151267322115014000640.000000, 340282346600000016151267322115014000640.000000]"
        self._signal_strength_dbm = array.array('f', value)

    @builtins.property
    def throughput_mbps(self):
        """Message field 'throughput_mbps'."""
        return self._throughput_mbps

    @throughput_mbps.setter
    def throughput_mbps(self, value):
        if isinstance(value, array.array):
            assert value.typecode == 'f', \
                "The 'throughput_mbps' array.array() must have the type code of 'f'"
            self._throughput_mbps = value
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
                 all(not (val < -3.402823466e+38 or val > 3.402823466e+38) or math.isinf(val) for val in value)), \
                "The 'throughput_mbps' field must be a set or sequence and each value of type 'float' and each float in [-340282346600000016151267322115014000640.000000, 340282346600000016151267322115014000640.000000]"
        self._throughput_mbps = array.array('f', value)

    @builtins.property
    def latency_ms(self):
        """Message field 'latency_ms'."""
        return self._latency_ms

    @latency_ms.setter
    def latency_ms(self, value):
        if isinstance(value, array.array):
            assert value.typecode == 'f', \
                "The 'latency_ms' array.array() must have the type code of 'f'"
            self._latency_ms = value
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
                 all(not (val < -3.402823466e+38 or val > 3.402823466e+38) or math.isinf(val) for val in value)), \
                "The 'latency_ms' field must be a set or sequence and each value of type 'float' and each float in [-340282346600000016151267322115014000640.000000, 340282346600000016151267322115014000640.000000]"
        self._latency_ms = array.array('f', value)

    @builtins.property
    def coverage_mask(self):
        """Message field 'coverage_mask'."""
        return self._coverage_mask

    @coverage_mask.setter
    def coverage_mask(self, value):
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
                 all(isinstance(v, bool) for v in value) and
                 True), \
                "The 'coverage_mask' field must be a set or sequence and each value of type 'bool'"
        self._coverage_mask = value

    @builtins.property
    def total_coverage_percent(self):
        """Message field 'total_coverage_percent'."""
        return self._total_coverage_percent

    @total_coverage_percent.setter
    def total_coverage_percent(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'total_coverage_percent' field must be of type 'float'"
            assert not (value < -3.402823466e+38 or value > 3.402823466e+38) or math.isinf(value), \
                "The 'total_coverage_percent' field must be a float in [-3.402823466e+38, 3.402823466e+38]"
        self._total_coverage_percent = value

    @builtins.property
    def avg_signal_strength_dbm(self):
        """Message field 'avg_signal_strength_dbm'."""
        return self._avg_signal_strength_dbm

    @avg_signal_strength_dbm.setter
    def avg_signal_strength_dbm(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'avg_signal_strength_dbm' field must be of type 'float'"
            assert not (value < -3.402823466e+38 or value > 3.402823466e+38) or math.isinf(value), \
                "The 'avg_signal_strength_dbm' field must be a float in [-3.402823466e+38, 3.402823466e+38]"
        self._avg_signal_strength_dbm = value

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
    def link_from_drone(self):
        """Message field 'link_from_drone'."""
        return self._link_from_drone

    @link_from_drone.setter
    def link_from_drone(self, value):
        if isinstance(value, array.array):
            assert value.typecode == 'B', \
                "The 'link_from_drone' array.array() must have the type code of 'B'"
            self._link_from_drone = value
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
                "The 'link_from_drone' field must be a set or sequence and each value of type 'int' and each unsigned integer in [0, 255]"
        self._link_from_drone = array.array('B', value)

    @builtins.property
    def link_to_drone(self):
        """Message field 'link_to_drone'."""
        return self._link_to_drone

    @link_to_drone.setter
    def link_to_drone(self, value):
        if isinstance(value, array.array):
            assert value.typecode == 'B', \
                "The 'link_to_drone' array.array() must have the type code of 'B'"
            self._link_to_drone = value
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
                "The 'link_to_drone' field must be a set or sequence and each value of type 'int' and each unsigned integer in [0, 255]"
        self._link_to_drone = array.array('B', value)

    @builtins.property
    def link_throughput_mbps(self):
        """Message field 'link_throughput_mbps'."""
        return self._link_throughput_mbps

    @link_throughput_mbps.setter
    def link_throughput_mbps(self, value):
        if isinstance(value, array.array):
            assert value.typecode == 'f', \
                "The 'link_throughput_mbps' array.array() must have the type code of 'f'"
            self._link_throughput_mbps = value
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
                 all(not (val < -3.402823466e+38 or val > 3.402823466e+38) or math.isinf(val) for val in value)), \
                "The 'link_throughput_mbps' field must be a set or sequence and each value of type 'float' and each float in [-340282346600000016151267322115014000640.000000, 340282346600000016151267322115014000640.000000]"
        self._link_throughput_mbps = array.array('f', value)

    @builtins.property
    def link_latency_ms(self):
        """Message field 'link_latency_ms'."""
        return self._link_latency_ms

    @link_latency_ms.setter
    def link_latency_ms(self, value):
        if isinstance(value, array.array):
            assert value.typecode == 'f', \
                "The 'link_latency_ms' array.array() must have the type code of 'f'"
            self._link_latency_ms = value
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
                 all(not (val < -3.402823466e+38 or val > 3.402823466e+38) or math.isinf(val) for val in value)), \
                "The 'link_latency_ms' field must be a set or sequence and each value of type 'float' and each float in [-340282346600000016151267322115014000640.000000, 340282346600000016151267322115014000640.000000]"
        self._link_latency_ms = array.array('f', value)

    @builtins.property
    def link_rssi_dbm(self):
        """Message field 'link_rssi_dbm'."""
        return self._link_rssi_dbm

    @link_rssi_dbm.setter
    def link_rssi_dbm(self, value):
        if isinstance(value, array.array):
            assert value.typecode == 'f', \
                "The 'link_rssi_dbm' array.array() must have the type code of 'f'"
            self._link_rssi_dbm = value
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
                 all(not (val < -3.402823466e+38 or val > 3.402823466e+38) or math.isinf(val) for val in value)), \
                "The 'link_rssi_dbm' field must be a set or sequence and each value of type 'float' and each float in [-340282346600000016151267322115014000640.000000, 340282346600000016151267322115014000640.000000]"
        self._link_rssi_dbm = array.array('f', value)

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
    def backhaul_active(self):
        """Message field 'backhaul_active'."""
        return self._backhaul_active

    @backhaul_active.setter
    def backhaul_active(self, value):
        if __debug__:
            assert \
                isinstance(value, bool), \
                "The 'backhaul_active' field must be of type 'bool'"
        self._backhaul_active = value

    @builtins.property
    def backhaul_throughput_mbps(self):
        """Message field 'backhaul_throughput_mbps'."""
        return self._backhaul_throughput_mbps

    @backhaul_throughput_mbps.setter
    def backhaul_throughput_mbps(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'backhaul_throughput_mbps' field must be of type 'float'"
            assert not (value < -3.402823466e+38 or value > 3.402823466e+38) or math.isinf(value), \
                "The 'backhaul_throughput_mbps' field must be a float in [-3.402823466e+38, 3.402823466e+38]"
        self._backhaul_throughput_mbps = value

    @builtins.property
    def backhaul_latency_ms(self):
        """Message field 'backhaul_latency_ms'."""
        return self._backhaul_latency_ms

    @backhaul_latency_ms.setter
    def backhaul_latency_ms(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'backhaul_latency_ms' field must be of type 'float'"
            assert not (value < -3.402823466e+38 or value > 3.402823466e+38) or math.isinf(value), \
                "The 'backhaul_latency_ms' field must be a float in [-3.402823466e+38, 3.402823466e+38]"
        self._backhaul_latency_ms = value
