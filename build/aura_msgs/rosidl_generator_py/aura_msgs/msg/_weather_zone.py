# generated from rosidl_generator_py/resource/_idl.py.em
# with input from aura_msgs:msg/WeatherZone.idl
# generated code does not contain a copyright notice


# Import statements for member types

import builtins  # noqa: E402, I100

import math  # noqa: E402, I100

import rosidl_parser.definition  # noqa: E402, I100


class Metaclass_WeatherZone(type):
    """Metaclass of message 'WeatherZone'."""

    _CREATE_ROS_MESSAGE = None
    _CONVERT_FROM_PY = None
    _CONVERT_TO_PY = None
    _DESTROY_ROS_MESSAGE = None
    _TYPE_SUPPORT = None

    __constants = {
        'WEATHER_CLEAR': 0,
        'WEATHER_RAIN': 1,
        'WEATHER_HEAVY_RAIN': 2,
        'WEATHER_WIND': 3,
        'WEATHER_SEVERE_WIND': 4,
        'WEATHER_DUST': 5,
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
                'aura_msgs.msg.WeatherZone')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__msg__weather_zone
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__msg__weather_zone
            cls._CONVERT_TO_PY = module.convert_to_py_msg__msg__weather_zone
            cls._TYPE_SUPPORT = module.type_support_msg__msg__weather_zone
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__msg__weather_zone

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
            'WEATHER_CLEAR': cls.__constants['WEATHER_CLEAR'],
            'WEATHER_RAIN': cls.__constants['WEATHER_RAIN'],
            'WEATHER_HEAVY_RAIN': cls.__constants['WEATHER_HEAVY_RAIN'],
            'WEATHER_WIND': cls.__constants['WEATHER_WIND'],
            'WEATHER_SEVERE_WIND': cls.__constants['WEATHER_SEVERE_WIND'],
            'WEATHER_DUST': cls.__constants['WEATHER_DUST'],
        }

    @property
    def WEATHER_CLEAR(self):
        """Message constant 'WEATHER_CLEAR'."""
        return Metaclass_WeatherZone.__constants['WEATHER_CLEAR']

    @property
    def WEATHER_RAIN(self):
        """Message constant 'WEATHER_RAIN'."""
        return Metaclass_WeatherZone.__constants['WEATHER_RAIN']

    @property
    def WEATHER_HEAVY_RAIN(self):
        """Message constant 'WEATHER_HEAVY_RAIN'."""
        return Metaclass_WeatherZone.__constants['WEATHER_HEAVY_RAIN']

    @property
    def WEATHER_WIND(self):
        """Message constant 'WEATHER_WIND'."""
        return Metaclass_WeatherZone.__constants['WEATHER_WIND']

    @property
    def WEATHER_SEVERE_WIND(self):
        """Message constant 'WEATHER_SEVERE_WIND'."""
        return Metaclass_WeatherZone.__constants['WEATHER_SEVERE_WIND']

    @property
    def WEATHER_DUST(self):
        """Message constant 'WEATHER_DUST'."""
        return Metaclass_WeatherZone.__constants['WEATHER_DUST']


class WeatherZone(metaclass=Metaclass_WeatherZone):
    """
    Message class 'WeatherZone'.

    Constants:
      WEATHER_CLEAR
      WEATHER_RAIN
      WEATHER_HEAVY_RAIN
      WEATHER_WIND
      WEATHER_SEVERE_WIND
      WEATHER_DUST
    """

    __slots__ = [
        '_timestamp',
        '_zone_id',
        '_center',
        '_radius_meters',
        '_min_altitude',
        '_max_altitude',
        '_weather_type',
        '_severity',
        '_wind_speed_ms',
        '_wind_direction_rad',
        '_signal_attenuation_db',
        '_no_fly',
        '_start_time',
        '_end_time',
        '_is_active',
    ]

    _fields_and_field_types = {
        'timestamp': 'builtin_interfaces/Time',
        'zone_id': 'uint32',
        'center': 'geometry_msgs/Point',
        'radius_meters': 'float',
        'min_altitude': 'float',
        'max_altitude': 'float',
        'weather_type': 'uint8',
        'severity': 'float',
        'wind_speed_ms': 'float',
        'wind_direction_rad': 'float',
        'signal_attenuation_db': 'float',
        'no_fly': 'boolean',
        'start_time': 'builtin_interfaces/Time',
        'end_time': 'builtin_interfaces/Time',
        'is_active': 'boolean',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.NamespacedType(['builtin_interfaces', 'msg'], 'Time'),  # noqa: E501
        rosidl_parser.definition.BasicType('uint32'),  # noqa: E501
        rosidl_parser.definition.NamespacedType(['geometry_msgs', 'msg'], 'Point'),  # noqa: E501
        rosidl_parser.definition.BasicType('float'),  # noqa: E501
        rosidl_parser.definition.BasicType('float'),  # noqa: E501
        rosidl_parser.definition.BasicType('float'),  # noqa: E501
        rosidl_parser.definition.BasicType('uint8'),  # noqa: E501
        rosidl_parser.definition.BasicType('float'),  # noqa: E501
        rosidl_parser.definition.BasicType('float'),  # noqa: E501
        rosidl_parser.definition.BasicType('float'),  # noqa: E501
        rosidl_parser.definition.BasicType('float'),  # noqa: E501
        rosidl_parser.definition.BasicType('boolean'),  # noqa: E501
        rosidl_parser.definition.NamespacedType(['builtin_interfaces', 'msg'], 'Time'),  # noqa: E501
        rosidl_parser.definition.NamespacedType(['builtin_interfaces', 'msg'], 'Time'),  # noqa: E501
        rosidl_parser.definition.BasicType('boolean'),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        from builtin_interfaces.msg import Time
        self.timestamp = kwargs.get('timestamp', Time())
        self.zone_id = kwargs.get('zone_id', int())
        from geometry_msgs.msg import Point
        self.center = kwargs.get('center', Point())
        self.radius_meters = kwargs.get('radius_meters', float())
        self.min_altitude = kwargs.get('min_altitude', float())
        self.max_altitude = kwargs.get('max_altitude', float())
        self.weather_type = kwargs.get('weather_type', int())
        self.severity = kwargs.get('severity', float())
        self.wind_speed_ms = kwargs.get('wind_speed_ms', float())
        self.wind_direction_rad = kwargs.get('wind_direction_rad', float())
        self.signal_attenuation_db = kwargs.get('signal_attenuation_db', float())
        self.no_fly = kwargs.get('no_fly', bool())
        from builtin_interfaces.msg import Time
        self.start_time = kwargs.get('start_time', Time())
        from builtin_interfaces.msg import Time
        self.end_time = kwargs.get('end_time', Time())
        self.is_active = kwargs.get('is_active', bool())

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
        if self.zone_id != other.zone_id:
            return False
        if self.center != other.center:
            return False
        if self.radius_meters != other.radius_meters:
            return False
        if self.min_altitude != other.min_altitude:
            return False
        if self.max_altitude != other.max_altitude:
            return False
        if self.weather_type != other.weather_type:
            return False
        if self.severity != other.severity:
            return False
        if self.wind_speed_ms != other.wind_speed_ms:
            return False
        if self.wind_direction_rad != other.wind_direction_rad:
            return False
        if self.signal_attenuation_db != other.signal_attenuation_db:
            return False
        if self.no_fly != other.no_fly:
            return False
        if self.start_time != other.start_time:
            return False
        if self.end_time != other.end_time:
            return False
        if self.is_active != other.is_active:
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
    def zone_id(self):
        """Message field 'zone_id'."""
        return self._zone_id

    @zone_id.setter
    def zone_id(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'zone_id' field must be of type 'int'"
            assert value >= 0 and value < 4294967296, \
                "The 'zone_id' field must be an unsigned integer in [0, 4294967295]"
        self._zone_id = value

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
    def radius_meters(self):
        """Message field 'radius_meters'."""
        return self._radius_meters

    @radius_meters.setter
    def radius_meters(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'radius_meters' field must be of type 'float'"
            assert not (value < -3.402823466e+38 or value > 3.402823466e+38) or math.isinf(value), \
                "The 'radius_meters' field must be a float in [-3.402823466e+38, 3.402823466e+38]"
        self._radius_meters = value

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
    def weather_type(self):
        """Message field 'weather_type'."""
        return self._weather_type

    @weather_type.setter
    def weather_type(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'weather_type' field must be of type 'int'"
            assert value >= 0 and value < 256, \
                "The 'weather_type' field must be an unsigned integer in [0, 255]"
        self._weather_type = value

    @builtins.property
    def severity(self):
        """Message field 'severity'."""
        return self._severity

    @severity.setter
    def severity(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'severity' field must be of type 'float'"
            assert not (value < -3.402823466e+38 or value > 3.402823466e+38) or math.isinf(value), \
                "The 'severity' field must be a float in [-3.402823466e+38, 3.402823466e+38]"
        self._severity = value

    @builtins.property
    def wind_speed_ms(self):
        """Message field 'wind_speed_ms'."""
        return self._wind_speed_ms

    @wind_speed_ms.setter
    def wind_speed_ms(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'wind_speed_ms' field must be of type 'float'"
            assert not (value < -3.402823466e+38 or value > 3.402823466e+38) or math.isinf(value), \
                "The 'wind_speed_ms' field must be a float in [-3.402823466e+38, 3.402823466e+38]"
        self._wind_speed_ms = value

    @builtins.property
    def wind_direction_rad(self):
        """Message field 'wind_direction_rad'."""
        return self._wind_direction_rad

    @wind_direction_rad.setter
    def wind_direction_rad(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'wind_direction_rad' field must be of type 'float'"
            assert not (value < -3.402823466e+38 or value > 3.402823466e+38) or math.isinf(value), \
                "The 'wind_direction_rad' field must be a float in [-3.402823466e+38, 3.402823466e+38]"
        self._wind_direction_rad = value

    @builtins.property
    def signal_attenuation_db(self):
        """Message field 'signal_attenuation_db'."""
        return self._signal_attenuation_db

    @signal_attenuation_db.setter
    def signal_attenuation_db(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'signal_attenuation_db' field must be of type 'float'"
            assert not (value < -3.402823466e+38 or value > 3.402823466e+38) or math.isinf(value), \
                "The 'signal_attenuation_db' field must be a float in [-3.402823466e+38, 3.402823466e+38]"
        self._signal_attenuation_db = value

    @builtins.property
    def no_fly(self):
        """Message field 'no_fly'."""
        return self._no_fly

    @no_fly.setter
    def no_fly(self, value):
        if __debug__:
            assert \
                isinstance(value, bool), \
                "The 'no_fly' field must be of type 'bool'"
        self._no_fly = value

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
    def end_time(self):
        """Message field 'end_time'."""
        return self._end_time

    @end_time.setter
    def end_time(self, value):
        if __debug__:
            from builtin_interfaces.msg import Time
            assert \
                isinstance(value, Time), \
                "The 'end_time' field must be a sub message of type 'Time'"
        self._end_time = value

    @builtins.property
    def is_active(self):
        """Message field 'is_active'."""
        return self._is_active

    @is_active.setter
    def is_active(self, value):
        if __debug__:
            assert \
                isinstance(value, bool), \
                "The 'is_active' field must be of type 'bool'"
        self._is_active = value
