/*
  tvision-ruby is a ruby extension for accessing the text user interface
  framework "rhtvision" accessible from the Ruby programming language

  Copyright (C) 2002  Tobias Peters <t-peters@users.berlios.de>

  This program is free software; you can redistribute it and/or
  modify it under the terms of the GNU General Public License
  as published by the Free Software Foundation; either version 2
  of the License, or (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program; if not, write to the Free Software
  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
*/

// $ID$

#include "point.hh"

VALUE Tvision_Ruby::WrPoint::cTPoint = 0;

Tvision_Ruby::WrPoint::WrPoint(VALUE rb_point)
    : Tpoint(Tvision_Ruby::WrPoint::unwrap(rb_point))
{}

Tvision_Ruby::WrPoint::WrPoint(void)
{}

VALUE
Tvision_Ruby::WrPoint::wrap(const Tpoint & point)
{
    WrPoint * c_point = new WrPoint;
    c_point->x = point.x;
    c_point->y = point.y;
    return Data_wrap_struct(Tvision_Ruby::WrPoint::cTPoint, 0,
                            &Tvision_Ruby::WrPoint::rb_free, c_point);
}

VALUE
Tvision_Ruby::WrPoint::rb_plus(VALUE rb_point1, VALUE rb_point2)
{
    return Tvision_Ruby::WrPoint::
        wrap(Tvision_Ruby::WrPoint::unwrap(rb_point1) +
             Tvision_Ruby::WrPoint::unwrap(rb_point2));
}

VALUE
Tvision_Ruby::WrPoint::rb_minus(VALUE rb_point1, VALUE rb_point2)
{
    return Tvision_Ruby::WrPoint::
        wrap(Tvision_Ruby::WrPoint::unwrap(rb_point1) -
             Tvision_Ruby::WrPoint::unwrap(rb_point2));
}

VALUE
Tvision_Ruby::WrPoint::rb_equal(VALUE rb_point1, VALUE rb_point2)
{
    return (Tvision_Ruby::WrPoint::unwrap(rb_point1) ==
            Tvision_Ruby::WrPoint::unwrap(rb_point2)) ? Qtrue : Qfalse;
}

VALUE
Tvision_Ruby::WrPoint::rb_x(VALUE rb_point)
{
    return INT2NUM(Tvision_Ruby::WrPoint::unwrap(rb_point).x);
}
VALUE
Tvision_Ruby::WrPoint:rb_y(VALUE rb_point)
{
    return INT2NUM(Tvision_Ruby::WrPoint::unwrap(rb_point).x);
}
VALUE
Tvision_Ruby::WrPoint:rb_set_x(VALUE rb_point, VALUE rb_x)
{
    Tvision_Ruby::WrPoint::unwrap(rb_point).x = NUM2INT(rb_x);
    return rb_x;
}
VALUE
Tvision_Ruby::WrPoint::rb_set_y(VALUE rb_point, VALUE rb_y)
{
    Tvision_Ruby::WrPoint::unwrap(rb_point).y = NUM2INT(rb_y);
    return rb_y;
}
void
Tvision_Ruby::WrPoint::rb_free(void * c_point)
{
    delete c_point;
}

void
Tvision_Ruby::WrPoint::rb_new(int argc, VALUE *argv, VALUE self)
{
    VALUE x = INT2NUM(0);
    VALUE y = INT2NUM(0);

    if (argc >= 1)
        x = argv[0];
    if (argc >= 2)
        y = argv[1];
    if (argc > 2)
        
    
void
Tvision_Ruby::WrPoint::init_wrapper(void)
{
    Tvision_Ruby::WrPoint::cTPoint =
        rb_define_class_under(Tvision_Ruby::mTvision, "Point", rb_cObject);
    rb_define_method(Tvision_Ruby::WrPoint::cTPoint, "+",
                     reinterpret_cast<VALUE(*)(...)>
                     (&Tvision_Ruby::WrPoint::rb_plus), 1);
    rb_define_method(Tvision_Ruby::WrPoint::cTPoint, "-",
                     reinterpret_cast<VALUE(*)(...)>
                     (&Tvision_Ruby::WrPoint::rb_minus), 1);
    rb_define_method(Tvision_Ruby::WrPoint::cTPoint, "==",
                     reinterpret_cast<VALUE(*)(...)>
                     (&Tvision_Ruby::WrPoint::rb_equal), 1);
    rb_define_method(Tvision_Ruby::WrPoint::cTPoint, "x",
                     reinterpret_cast<VALUE(*)(...)>
                     (&Tvision_Ruby::WrPoint::rb_x), 0);
    rb_define_method(Tvision_Ruby::WrPoint::cTPoint, "x=",
                     reinterpret_cast<VALUE(*)(...)>
                     (&Tvision_Ruby::WrPoint::rb_set_x), 1);
    rb_define_method(Tvision_Ruby::WrPoint::cTPoint, "y",
                     reinterpret_cast<VALUE(*)(...)>
                     (&Tvision_Ruby::WrPoint::rb_y), 0);
    rb_define_method(Tvision_Ruby::WrPoint::cTPoint, "y=",
                     reinterpret_cast<VALUE(*)(...)>
                     (&Tvision_Ruby::WrPoint::rb_set_y), 1);
}
    
    
