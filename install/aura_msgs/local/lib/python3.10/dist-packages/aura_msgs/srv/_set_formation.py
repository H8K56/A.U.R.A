# generated from rosidl_generator_py/resource/_idl.py.em
# with input from aura_msgs:srv/SetFormation.idl
# generated code does not contain a copyright notice


# Import statements for member types

import builtins  # noqa: E402, I100

import math  # noqa: E402, I100

import rosidl_parser.definition  # noqa: E402, I100


class Metaclass_SetFormation_Request(type):
    """Metaclass of message 'SetFormation_Request'."""

    _CREATE_ROS_MESSAGE = None
    _CONVERT_FROM_PY = None
    _CONVERT_TO_PY = None
    _DESTROY_ROS_MESSAGE = None
    _TYPE_SUPPORT = None

    __constants = {
        'FORMATION_SPREAD': 0,
        'FORMATION_CLUSTER': 1,
        'FORMATION_LINE': 2,
        'FORMATION_GRID': 3,
        'FORMATION_CUSTOM': 4,
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
                'aura_msgs.srv.SetFormation_Request')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__srv__set_formation__request
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__srv__set_formation__request
            cls._CONVERT_TO_PY = module.convert_to_py_msg__srv__set_formation__request
            cls._TYPE_SUPPORT = module.type_support_msg__srv__set_formation__request
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__srv__set_formation__request

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
            'FORMATION_GRID': cls.__constants['FORMATION_GRID'],
            'FORMATION_CUSTOM': cls.__constants['FORMATION_CUSTOM'],
        }

    @property
    def FORMATION_SPREAD(self):
        """Message constant 'FORMATION_SPREAD'."""
        return Metaclass_SetFormation_Request.__constants['FORMATION_SPREAD']

    @property
    def FORMATION_CLUSTER(self):
        """Message constant 'FORMATION_CLUSTER'."""
        return Metaclass_SetFormation_Request.__constants['FORMATION_CLUSTER']

    @property
    def FORMATION_LINE(self):
        """Message constant 'FORMATION_LINE'."""
        return Metaclass_SetFormation_Request.__constants['FORMATION_LINE']

    @property
    def FORMATION_GRID(self):
        """Message constant 'FORMATION_GRID'."""
        return Metaclass_SetFormation_Request.__constants['FORMATION_GRID']

    @property
    def FORMATION_CUSTOM(self):
        """Message constant 'FORMATION_CUSTOM'."""
        return Metaclass_SetFormation_Request.__constants['FORMATION_CUSTOM']


class SetFormation_Request(metaclass=Metaclass_SetFormation_Request):
    """
    Message class 'SetFormation_Request'.

    Constants:
      FORMATION_SPREAD
      FORMATION_CLUSTER
      FORMATION_LINE
      FORMATION_GRID
      FORMATION_CUSTOM
    """

    __slots__ = [
        '_formation_type',
        '_custom_positions',
        '_spacing_meters',
        '_altitude_meters',
        '_center',
        '_heading_rad',
    ]

    _fields_and_field_types = {
        'formation_type': 'uint8',
        'custom_positions': 'sequence<geometry_msgs/Point>',
        'spacing_meters': 'float',
        'altitude_meters': 'float',
        'center': 'geometry_msgs/Point',
        'heading_rad': 'float',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.BasicType('uint8'),  # noqa: E501
        rosidl_parser.definition.UnboundedSequence(rosidl_parser.definition.NamespacedType(['geometry_msgs', 'msg'], 'Point')),  # noqa: E501
        rosidl_parser.definition.BasicType('float'),  # noqa: E501
        rosidl_parser.definition.BasicType('float'),  # noqa: E501
        rosidl_parser.definition.NamespacedType(['geometry_msgs', 'msg'], 'Point'),  # noqa: E501
        rosidl_parser.definition.BasicType('float'),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        self.formation_type = kwargs.get('formation_type', int())
        self.custom_positions = kwargs.get('custom_positions', [])
        self.spacing_meters = kwargs.get('spacing_meters', float())
        self.altitude_meters = kwargs.get('altitude_meters', float())
        from geometry_msgs.msg import Point
        self.center = kwargs.get('center', Point())
        self.heading_rad = kwargs.get('heading_rad', float())

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
        if self.formation_type != other.formation_type:
            return False
        if self.custom_positions != other.custom_positions:
            return False
        if self.spacing_meters != other.spacing_meters:
            return False
        if self.altitude_meters != other.altitude_meters:
            return False
        if self.center != other.center:
            return False
        if self.heading_rad != other.heading_rad:
            return False
        return True

    @classmethod
    def get_fields_and_field_types(cls):
        from copy import copy
        return copy(cls._fields_and_field_types)

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
    def custom_positions(self):
        """Message field 'custom_positions'."""
        return self._custom_positions

    @custom_positions.setter
    def custom_positions(self, value):
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
                "The 'custom_positions' field must be a set or sequence and each value of type 'Point'"
        self._custom_positions = value

    @builtins.property
    def spacing_meters(self):
        """Message field 'spacing_meters'."""
        return self._spacing_meters

    @spacing_meters.setter
    def spacing_meters(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'spacing_meters' field must be of type 'float'"
            assert not (value < -3.402823466e+38 or value > 3.402823466e+38) or math.isinf(value), \
                "The 'spacing_meters' field must be a float in [-3.402823466e+38, 3.402823466e+38]"
        self._spacing_meters = value

    @builtins.property
    def altitude_meters(self):
        """Message field 'altitude_meters'."""
        return self._altitude_meters

    @altitude_meters.setter
    def altitude_meters(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'altitude_meters' field must be of type 'float'"
            assert not (value < -3.402823466e+38 or value > 3.402823466e+38) or math.isinf(value), \
                "The 'altitude_meters' field must be a float in [-3.402823466e+38, 3.402823466e+38]"
        self._altitude_meters = value

    @builtins.property
    def center(self):
        """Message field 'center'."""
        return self._center

    @center.setter
    def center(self, value):
        if __debug__:
            from geometry_msgs.msg import Point
            assert \
                isinstance(value, Point), \
                "The 'center' field must be a sub message of type 'Point'"
        self._center = value

    @builtins.property
    def heading_rad(self):
        """Message field 'heading_rad'."""
        return self._heading_rad

    @heading_rad.setter
    def heading_rad(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'heading_rad' field must be of type 'float'"
            assert not (value < -3.402823466e+38 or value > 3.402823466e+38) or math.isinf(value), \
                "The 'heading_rad' field must be a float in [-3.402823466e+38, 3.402823466e+38]"
        self._heading_rad = value


# Import statements for member types

# already imported above
# import builtins

# already imported above
# import math

# already imported above
# import rosidl_parser.definition


class Metaclass_SetFormation_Response(type):
    """Metaclass of message 'SetFormation_Response'."""

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
                'aura_msgs.srv.SetFormation_Response')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__srv__set_formation__response
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__srv__set_formation__response
            cls._CONVERT_TO_PY = module.convert_to_py_msg__srv__set_formation__response
            cls._TYPE_SUPPORT = module.type_support_msg__srv__set_formation__response
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__srv__set_formation__response

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
        }


class SetFormation_Response(metaclass=Metaclass_SetFormation_Response):
    """Message class 'SetFormation_Response'."""

    __slots__ = [
        '_success',
        '_message',
        '_estimated_transition_time',
    ]

    _fields_and_field_types = {
        'success': 'boolean',
        'message': 'string',
        'estimated_transition_time': 'float',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.BasicType('boolean'),  # noqa: E501
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
        rosidl_parser.definition.BasicType('float'),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        self.success = kwargs.get('success', bool())
        self.message = kwargs.get('message', str())
        self.estimated_transition_time = kwargs.get('estimated_transition_time', float())

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
        if self.estimated_transition_time != other.estimated_transition_time:
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
    def estimated_transition_time(self):
        """Message field 'estimated_transition_time'."""
        return self._estimated_transition_time

    @estimated_transition_time.setter
    def estimated_transition_time(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'estimated_transition_time' field must be of type 'float'"
            assert not (value < -3.402823466e+38 or value > 3.402823466e+38) or math.isinf(value), \
                "The 'estimated_transition_time' field must be a float in [-3.402823466e+38, 3.402823466e+38]"
        self._estimated_transition_time = value


class Metaclass_SetFormation(type):
    """Metaclass of service 'SetFormation'."""

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
                'aura_msgs.srv.SetFormation')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._TYPE_SUPPORT = module.type_support_srv__srv__set_formation

            from aura_msgs.srv import _set_formation
            if _set_formation.Metaclass_SetFormation_Request._TYPE_SUPPORT is None:
                _set_formation.Metaclass_SetFormation_Request.__import_type_support__()
            if _set_formation.Metaclass_SetFormation_Response._TYPE_SUPPORT is None:
                _set_formation.Metaclass_SetFormation_Response.__import_type_support__()


class SetFormation(metaclass=Metaclass_SetFormation):
    from aura_msgs.srv._set_formation import SetFormation_Request as Request
    from aura_msgs.srv._set_formation import SetFormation_Response as Response

    def __init__(self):
        raise NotImplementedError('Service classes can not be instantiated')
