# generated from rosidl_generator_py/resource/_idl.py.em
# with input from aura_msgs:msg/CoverageMap.idl
# generated code does not contain a copyright notice


# Import statements for member types

# Member 'demand_level'
# Member 'coverage_quality'
# Member 'priority_zone_radii'
# Member 'priority_zone_weights'
import array  # noqa: E402, I100

import builtins  # noqa: E402, I100

import math  # noqa: E402, I100

import rosidl_parser.definition  # noqa: E402, I100


class Metaclass_CoverageMap(type):
    """Metaclass of message 'CoverageMap'."""

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
                'aura_msgs.msg.CoverageMap')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__msg__coverage_map
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__msg__coverage_map
            cls._CONVERT_TO_PY = module.convert_to_py_msg__msg__coverage_map
            cls._TYPE_SUPPORT = module.type_support_msg__msg__coverage_map
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__msg__coverage_map

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


class CoverageMap(metaclass=Metaclass_CoverageMap):
    """Message class 'CoverageMap'."""

    __slots__ = [
        '_timestamp',
        '_grid_size_x',
        '_grid_size_y',
        '_cell_size_meters',
        '_origin',
        '_is_covered',
        '_is_target',
        '_demand_level',
        '_coverage_quality',
        '_priority_zone_centers',
        '_priority_zone_radii',
        '_priority_zone_weights',
    ]

    _fields_and_field_types = {
        'timestamp': 'builtin_interfaces/Time',
        'grid_size_x': 'uint32',
        'grid_size_y': 'uint32',
        'cell_size_meters': 'float',
        'origin': 'geometry_msgs/Point',
        'is_covered': 'sequence<boolean>',
        'is_target': 'sequence<boolean>',
        'demand_level': 'sequence<float>',
        'coverage_quality': 'sequence<float>',
        'priority_zone_centers': 'sequence<geometry_msgs/Point>',
        'priority_zone_radii': 'sequence<float>',
        'priority_zone_weights': 'sequence<float>',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.NamespacedType(['builtin_interfaces', 'msg'], 'Time'),  # noqa: E501
        rosidl_parser.definition.BasicType('uint32'),  # noqa: E501
        rosidl_parser.definition.BasicType('uint32'),  # noqa: E501
        rosidl_parser.definition.BasicType('float'),  # noqa: E501
        rosidl_parser.definition.NamespacedType(['geometry_msgs', 'msg'], 'Point'),  # noqa: E501
        rosidl_parser.definition.UnboundedSequence(rosidl_parser.definition.BasicType('boolean')),  # noqa: E501
        rosidl_parser.definition.UnboundedSequence(rosidl_parser.definition.BasicType('boolean')),  # noqa: E501
        rosidl_parser.definition.UnboundedSequence(rosidl_parser.definition.BasicType('float')),  # noqa: E501
        rosidl_parser.definition.UnboundedSequence(rosidl_parser.definition.BasicType('float')),  # noqa: E501
        rosidl_parser.definition.UnboundedSequence(rosidl_parser.definition.NamespacedType(['geometry_msgs', 'msg'], 'Point')),  # noqa: E501
        rosidl_parser.definition.UnboundedSequence(rosidl_parser.definition.BasicType('float')),  # noqa: E501
        rosidl_parser.definition.UnboundedSequence(rosidl_parser.definition.BasicType('float')),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        from builtin_interfaces.msg import Time
        self.timestamp = kwargs.get('timestamp', Time())
        self.grid_size_x = kwargs.get('grid_size_x', int())
        self.grid_size_y = kwargs.get('grid_size_y', int())
        self.cell_size_meters = kwargs.get('cell_size_meters', float())
        from geometry_msgs.msg import Point
        self.origin = kwargs.get('origin', Point())
        self.is_covered = kwargs.get('is_covered', [])
        self.is_target = kwargs.get('is_target', [])
        self.demand_level = array.array('f', kwargs.get('demand_level', []))
        self.coverage_quality = array.array('f', kwargs.get('coverage_quality', []))
        self.priority_zone_centers = kwargs.get('priority_zone_centers', [])
        self.priority_zone_radii = array.array('f', kwargs.get('priority_zone_radii', []))
        self.priority_zone_weights = array.array('f', kwargs.get('priority_zone_weights', []))

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
        if self.grid_size_x != other.grid_size_x:
            return False
        if self.grid_size_y != other.grid_size_y:
            return False
        if self.cell_size_meters != other.cell_size_meters:
            return False
        if self.origin != other.origin:
            return False
        if self.is_covered != other.is_covered:
            return False
        if self.is_target != other.is_target:
            return False
        if self.demand_level != other.demand_level:
            return False
        if self.coverage_quality != other.coverage_quality:
            return False
        if self.priority_zone_centers != other.priority_zone_centers:
            return False
        if self.priority_zone_radii != other.priority_zone_radii:
            return False
        if self.priority_zone_weights != other.priority_zone_weights:
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
    def is_covered(self):
        """Message field 'is_covered'."""
        return self._is_covered

    @is_covered.setter
    def is_covered(self, value):
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
                "The 'is_covered' field must be a set or sequence and each value of type 'bool'"
        self._is_covered = value

    @builtins.property
    def is_target(self):
        """Message field 'is_target'."""
        return self._is_target

    @is_target.setter
    def is_target(self, value):
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
                "The 'is_target' field must be a set or sequence and each value of type 'bool'"
        self._is_target = value

    @builtins.property
    def demand_level(self):
        """Message field 'demand_level'."""
        return self._demand_level

    @demand_level.setter
    def demand_level(self, value):
        if isinstance(value, array.array):
            assert value.typecode == 'f', \
                "The 'demand_level' array.array() must have the type code of 'f'"
            self._demand_level = value
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
                "The 'demand_level' field must be a set or sequence and each value of type 'float' and each float in [-340282346600000016151267322115014000640.000000, 340282346600000016151267322115014000640.000000]"
        self._demand_level = array.array('f', value)

    @builtins.property
    def coverage_quality(self):
        """Message field 'coverage_quality'."""
        return self._coverage_quality

    @coverage_quality.setter
    def coverage_quality(self, value):
        if isinstance(value, array.array):
            assert value.typecode == 'f', \
                "The 'coverage_quality' array.array() must have the type code of 'f'"
            self._coverage_quality = value
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
                "The 'coverage_quality' field must be a set or sequence and each value of type 'float' and each float in [-340282346600000016151267322115014000640.000000, 340282346600000016151267322115014000640.000000]"
        self._coverage_quality = array.array('f', value)

    @builtins.property
    def priority_zone_centers(self):
        """Message field 'priority_zone_centers'."""
        return self._priority_zone_centers

    @priority_zone_centers.setter
    def priority_zone_centers(self, value):
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
                "The 'priority_zone_centers' field must be a set or sequence and each value of type 'Point'"
        self._priority_zone_centers = value

    @builtins.property
    def priority_zone_radii(self):
        """Message field 'priority_zone_radii'."""
        return self._priority_zone_radii

    @priority_zone_radii.setter
    def priority_zone_radii(self, value):
        if isinstance(value, array.array):
            assert value.typecode == 'f', \
                "The 'priority_zone_radii' array.array() must have the type code of 'f'"
            self._priority_zone_radii = value
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
                "The 'priority_zone_radii' field must be a set or sequence and each value of type 'float' and each float in [-340282346600000016151267322115014000640.000000, 340282346600000016151267322115014000640.000000]"
        self._priority_zone_radii = array.array('f', value)

    @builtins.property
    def priority_zone_weights(self):
        """Message field 'priority_zone_weights'."""
        return self._priority_zone_weights

    @priority_zone_weights.setter
    def priority_zone_weights(self, value):
        if isinstance(value, array.array):
            assert value.typecode == 'f', \
                "The 'priority_zone_weights' array.array() must have the type code of 'f'"
            self._priority_zone_weights = value
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
                "The 'priority_zone_weights' field must be a set or sequence and each value of type 'float' and each float in [-340282346600000016151267322115014000640.000000, 340282346600000016151267322115014000640.000000]"
        self._priority_zone_weights = array.array('f', value)
