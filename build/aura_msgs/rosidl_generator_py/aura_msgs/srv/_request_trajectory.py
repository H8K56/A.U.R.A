# generated from rosidl_generator_py/resource/_idl.py.em
# with input from aura_msgs:srv/RequestTrajectory.idl
# generated code does not contain a copyright notice


# Import statements for member types

import builtins  # noqa: E402, I100

import math  # noqa: E402, I100

import rosidl_parser.definition  # noqa: E402, I100


class Metaclass_RequestTrajectory_Request(type):
    """Metaclass of message 'RequestTrajectory_Request'."""

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
                'aura_msgs.srv.RequestTrajectory_Request')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__srv__request_trajectory__request
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__srv__request_trajectory__request
            cls._CONVERT_TO_PY = module.convert_to_py_msg__srv__request_trajectory__request
            cls._TYPE_SUPPORT = module.type_support_msg__srv__request_trajectory__request
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__srv__request_trajectory__request

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


class RequestTrajectory_Request(metaclass=Metaclass_RequestTrajectory_Request):
    """Message class 'RequestTrajectory_Request'."""

    __slots__ = [
        '_drone_id',
        '_goal_position',
        '_max_velocity',
        '_max_time',
        '_avoid_weather_zones',
    ]

    _fields_and_field_types = {
        'drone_id': 'uint8',
        'goal_position': 'geometry_msgs/Point',
        'max_velocity': 'double',
        'max_time': 'double',
        'avoid_weather_zones': 'boolean',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.BasicType('uint8'),  # noqa: E501
        rosidl_parser.definition.NamespacedType(['geometry_msgs', 'msg'], 'Point'),  # noqa: E501
        rosidl_parser.definition.BasicType('double'),  # noqa: E501
        rosidl_parser.definition.BasicType('double'),  # noqa: E501
        rosidl_parser.definition.BasicType('boolean'),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        self.drone_id = kwargs.get('drone_id', int())
        from geometry_msgs.msg import Point
        self.goal_position = kwargs.get('goal_position', Point())
        self.max_velocity = kwargs.get('max_velocity', float())
        self.max_time = kwargs.get('max_time', float())
        self.avoid_weather_zones = kwargs.get('avoid_weather_zones', bool())

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
        if self.drone_id != other.drone_id:
            return False
        if self.goal_position != other.goal_position:
            return False
        if self.max_velocity != other.max_velocity:
            return False
        if self.max_time != other.max_time:
            return False
        if self.avoid_weather_zones != other.avoid_weather_zones:
            return False
        return True

    @classmethod
    def get_fields_and_field_types(cls):
        from copy import copy
        return copy(cls._fields_and_field_types)

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
    def max_velocity(self):
        """Message field 'max_velocity'."""
        return self._max_velocity

    @max_velocity.setter
    def max_velocity(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'max_velocity' field must be of type 'float'"
            assert not (value < -1.7976931348623157e+308 or value > 1.7976931348623157e+308) or math.isinf(value), \
                "The 'max_velocity' field must be a double in [-1.7976931348623157e+308, 1.7976931348623157e+308]"
        self._max_velocity = value

    @builtins.property
    def max_time(self):
        """Message field 'max_time'."""
        return self._max_time

    @max_time.setter
    def max_time(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'max_time' field must be of type 'float'"
            assert not (value < -1.7976931348623157e+308 or value > 1.7976931348623157e+308) or math.isinf(value), \
                "The 'max_time' field must be a double in [-1.7976931348623157e+308, 1.7976931348623157e+308]"
        self._max_time = value

    @builtins.property
    def avoid_weather_zones(self):
        """Message field 'avoid_weather_zones'."""
        return self._avoid_weather_zones

    @avoid_weather_zones.setter
    def avoid_weather_zones(self, value):
        if __debug__:
            assert \
                isinstance(value, bool), \
                "The 'avoid_weather_zones' field must be of type 'bool'"
        self._avoid_weather_zones = value


# Import statements for member types

# already imported above
# import builtins

# already imported above
# import math

# already imported above
# import rosidl_parser.definition


class Metaclass_RequestTrajectory_Response(type):
    """Metaclass of message 'RequestTrajectory_Response'."""

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
                'aura_msgs.srv.RequestTrajectory_Response')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__srv__request_trajectory__response
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__srv__request_trajectory__response
            cls._CONVERT_TO_PY = module.convert_to_py_msg__srv__request_trajectory__response
            cls._TYPE_SUPPORT = module.type_support_msg__srv__request_trajectory__response
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__srv__request_trajectory__response

            from aura_msgs.msg import TrajectoryBroadcast
            if TrajectoryBroadcast.__class__._TYPE_SUPPORT is None:
                TrajectoryBroadcast.__class__.__import_type_support__()

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
        }


class RequestTrajectory_Response(metaclass=Metaclass_RequestTrajectory_Response):
    """Message class 'RequestTrajectory_Response'."""

    __slots__ = [
        '_success',
        '_message',
        '_trajectory',
        '_estimated_time',
        '_estimated_energy',
    ]

    _fields_and_field_types = {
        'success': 'boolean',
        'message': 'string',
        'trajectory': 'aura_msgs/TrajectoryBroadcast',
        'estimated_time': 'double',
        'estimated_energy': 'double',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.BasicType('boolean'),  # noqa: E501
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
        rosidl_parser.definition.NamespacedType(['aura_msgs', 'msg'], 'TrajectoryBroadcast'),  # noqa: E501
        rosidl_parser.definition.BasicType('double'),  # noqa: E501
        rosidl_parser.definition.BasicType('double'),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        self.success = kwargs.get('success', bool())
        self.message = kwargs.get('message', str())
        from aura_msgs.msg import TrajectoryBroadcast
        self.trajectory = kwargs.get('trajectory', TrajectoryBroadcast())
        self.estimated_time = kwargs.get('estimated_time', float())
        self.estimated_energy = kwargs.get('estimated_energy', float())

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
        if self.trajectory != other.trajectory:
            return False
        if self.estimated_time != other.estimated_time:
            return False
        if self.estimated_energy != other.estimated_energy:
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
    def trajectory(self):
        """Message field 'trajectory'."""
        return self._trajectory

    @trajectory.setter
    def trajectory(self, value):
        if __debug__:
            from aura_msgs.msg import TrajectoryBroadcast
            assert \
                isinstance(value, TrajectoryBroadcast), \
                "The 'trajectory' field must be a sub message of type 'TrajectoryBroadcast'"
        self._trajectory = value

    @builtins.property
    def estimated_time(self):
        """Message field 'estimated_time'."""
        return self._estimated_time

    @estimated_time.setter
    def estimated_time(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'estimated_time' field must be of type 'float'"
            assert not (value < -1.7976931348623157e+308 or value > 1.7976931348623157e+308) or math.isinf(value), \
                "The 'estimated_time' field must be a double in [-1.7976931348623157e+308, 1.7976931348623157e+308]"
        self._estimated_time = value

    @builtins.property
    def estimated_energy(self):
        """Message field 'estimated_energy'."""
        return self._estimated_energy

    @estimated_energy.setter
    def estimated_energy(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'estimated_energy' field must be of type 'float'"
            assert not (value < -1.7976931348623157e+308 or value > 1.7976931348623157e+308) or math.isinf(value), \
                "The 'estimated_energy' field must be a double in [-1.7976931348623157e+308, 1.7976931348623157e+308]"
        self._estimated_energy = value


class Metaclass_RequestTrajectory(type):
    """Metaclass of service 'RequestTrajectory'."""

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
                'aura_msgs.srv.RequestTrajectory')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._TYPE_SUPPORT = module.type_support_srv__srv__request_trajectory

            from aura_msgs.srv import _request_trajectory
            if _request_trajectory.Metaclass_RequestTrajectory_Request._TYPE_SUPPORT is None:
                _request_trajectory.Metaclass_RequestTrajectory_Request.__import_type_support__()
            if _request_trajectory.Metaclass_RequestTrajectory_Response._TYPE_SUPPORT is None:
                _request_trajectory.Metaclass_RequestTrajectory_Response.__import_type_support__()


class RequestTrajectory(metaclass=Metaclass_RequestTrajectory):
    from aura_msgs.srv._request_trajectory import RequestTrajectory_Request as Request
    from aura_msgs.srv._request_trajectory import RequestTrajectory_Response as Response

    def __init__(self):
        raise NotImplementedError('Service classes can not be instantiated')
