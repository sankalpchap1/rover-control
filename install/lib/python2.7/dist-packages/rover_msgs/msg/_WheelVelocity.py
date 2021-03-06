# This Python file uses the following encoding: utf-8
"""autogenerated by genpy from rover_msgs/WheelVelocity.msg. Do not edit."""
import sys
python3 = True if sys.hexversion > 0x03000000 else False
import genpy
import struct


class WheelVelocity(genpy.Message):
  _md5sum = "0d2806f4fca14fdb81a14e092651232e"
  _type = "rover_msgs/WheelVelocity"
  _has_header = False #flag to mark the presence of a Header object
  _full_text = """float64 left_front_vel
float64 right_front_vel
float64 left_middle_vel
float64 right_middle_vel
float64 left_back_vel
float64 right_back_vel

"""
  __slots__ = ['left_front_vel','right_front_vel','left_middle_vel','right_middle_vel','left_back_vel','right_back_vel']
  _slot_types = ['float64','float64','float64','float64','float64','float64']

  def __init__(self, *args, **kwds):
    """
    Constructor. Any message fields that are implicitly/explicitly
    set to None will be assigned a default value. The recommend
    use is keyword arguments as this is more robust to future message
    changes.  You cannot mix in-order arguments and keyword arguments.

    The available fields are:
       left_front_vel,right_front_vel,left_middle_vel,right_middle_vel,left_back_vel,right_back_vel

    :param args: complete set of field values, in .msg order
    :param kwds: use keyword arguments corresponding to message field names
    to set specific fields.
    """
    if args or kwds:
      super(WheelVelocity, self).__init__(*args, **kwds)
      #message fields cannot be None, assign default values for those that are
      if self.left_front_vel is None:
        self.left_front_vel = 0.
      if self.right_front_vel is None:
        self.right_front_vel = 0.
      if self.left_middle_vel is None:
        self.left_middle_vel = 0.
      if self.right_middle_vel is None:
        self.right_middle_vel = 0.
      if self.left_back_vel is None:
        self.left_back_vel = 0.
      if self.right_back_vel is None:
        self.right_back_vel = 0.
    else:
      self.left_front_vel = 0.
      self.right_front_vel = 0.
      self.left_middle_vel = 0.
      self.right_middle_vel = 0.
      self.left_back_vel = 0.
      self.right_back_vel = 0.

  def _get_types(self):
    """
    internal API method
    """
    return self._slot_types

  def serialize(self, buff):
    """
    serialize message into buffer
    :param buff: buffer, ``StringIO``
    """
    try:
      _x = self
      buff.write(_struct_6d.pack(_x.left_front_vel, _x.right_front_vel, _x.left_middle_vel, _x.right_middle_vel, _x.left_back_vel, _x.right_back_vel))
    except struct.error as se: self._check_types(struct.error("%s: '%s' when writing '%s'" % (type(se), str(se), str(locals().get('_x', self)))))
    except TypeError as te: self._check_types(ValueError("%s: '%s' when writing '%s'" % (type(te), str(te), str(locals().get('_x', self)))))

  def deserialize(self, str):
    """
    unpack serialized message in str into this message instance
    :param str: byte array of serialized message, ``str``
    """
    try:
      end = 0
      _x = self
      start = end
      end += 48
      (_x.left_front_vel, _x.right_front_vel, _x.left_middle_vel, _x.right_middle_vel, _x.left_back_vel, _x.right_back_vel,) = _struct_6d.unpack(str[start:end])
      return self
    except struct.error as e:
      raise genpy.DeserializationError(e) #most likely buffer underfill


  def serialize_numpy(self, buff, numpy):
    """
    serialize message with numpy array types into buffer
    :param buff: buffer, ``StringIO``
    :param numpy: numpy python module
    """
    try:
      _x = self
      buff.write(_struct_6d.pack(_x.left_front_vel, _x.right_front_vel, _x.left_middle_vel, _x.right_middle_vel, _x.left_back_vel, _x.right_back_vel))
    except struct.error as se: self._check_types(struct.error("%s: '%s' when writing '%s'" % (type(se), str(se), str(locals().get('_x', self)))))
    except TypeError as te: self._check_types(ValueError("%s: '%s' when writing '%s'" % (type(te), str(te), str(locals().get('_x', self)))))

  def deserialize_numpy(self, str, numpy):
    """
    unpack serialized message in str into this message instance using numpy for array types
    :param str: byte array of serialized message, ``str``
    :param numpy: numpy python module
    """
    try:
      end = 0
      _x = self
      start = end
      end += 48
      (_x.left_front_vel, _x.right_front_vel, _x.left_middle_vel, _x.right_middle_vel, _x.left_back_vel, _x.right_back_vel,) = _struct_6d.unpack(str[start:end])
      return self
    except struct.error as e:
      raise genpy.DeserializationError(e) #most likely buffer underfill

_struct_I = genpy.struct_I
_struct_6d = struct.Struct("<6d")
