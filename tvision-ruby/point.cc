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

// $Id: point.cc,v 1.3 2002/02/26 10:56:40 t-peters Exp $

#include "point.hh"

VALUE Tvision_Ruby::WrPoint::cTPoint = 0;

Tvision_Ruby::WrPoint::WrPoint(VALUE rb_point)
    : TPoint(Tvision_Ruby::WrPoint::unwrap(rb_point))
{}

Tvision_Ruby::WrPoint::WrPoint(void)
{}

VALUE
Tvision_Ruby::WrPoint::wrap(const TPoint & point)
{
    TPoint * c_point = new TPoint(point);
    //    c_point->x = point.x;
    //    c_point->y = point.y;
    return Data_Wrap_Struct(Tvision_Ruby::WrPoint::cTPoint, 0,
                            &Tvision_Ruby::WrPoint::rb_free, c_point);
}

VALUE
Tvision_Ruby::WrPoint::wrap(TPoint & point, VALUE depends_on_object)
{
    VALUE rb_point = Data_Wrap_Struct(Tvision_Ruby::WrPoint::cTPoint, 0,
                                      0, // don't free this point,
                                      &point);
    // containing object may not go out of scope before this object
    rb_iv_set(rb_point, "@containing_object", depends_on_object);
    return rb_point;
}

TPoint &
Tvision_Ruby::WrPoint::unwrap(VALUE rb_point)
{
    TPoint * c_point;
    Data_Get_Struct(rb_point, TPoint, c_point);
    return *c_point;
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
Tvision_Ruby::WrPoint::rb_y(VALUE rb_point)
{
    return INT2NUM(Tvision_Ruby::WrPoint::unwrap(rb_point).y);
}
VALUE
Tvision_Ruby::WrPoint::rb_set_x(VALUE rb_point, VALUE rb_x)
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
    delete reinterpret_cast<TPoint *>(c_point);
}

VALUE
Tvision_Ruby::WrPoint::rb_new(int argc, VALUE *argv, VALUE self)
{
    TPoint c_point;
    if (argc == 2) {
        c_point.x = NUM2INT(argv[0]);
        c_point.y = NUM2INT(argv[1]);
    }
    else if (argc == 0) {
        c_point.x = c_point.y = 0;
    }
    else {
        rb_raise(rb_eArgError, "Point::new takes either 2 or no arguments");
        return Qnil;
    }
    return Tvision_Ruby::WrPoint::wrap(c_point);
}

VALUE
Tvision_Ruby::WrPoint::rb_dup(VALUE rb_point)
{
    VALUE rb_coord[2];
    rb_coord[0] = rb_funcall3(rb_point, rb_intern("x"), 0, 0);
    rb_coord[1] = rb_funcall3(rb_point, rb_intern("y"), 0, 0);
    return rb_funcall3(rb_funcall3(rb_point, rb_intern("type"), 0, 0),
                       rb_intern("new"), 2, rb_coord);
}

void
Tvision_Ruby::WrPoint::init_wrapper(void)
{
    // define class "Point" in module "Tvision"
    Tvision_Ruby::WrPoint::cTPoint =
        rb_define_class_under(Tvision_Ruby::mTvision, "Point", rb_cObject);

    // add 2 Point-s using operator Point#+
    rb_define_method(Tvision_Ruby::WrPoint::cTPoint, "+",
                     reinterpret_cast<VALUE(*)(...)>
                     (&Tvision_Ruby::WrPoint::rb_plus), 1);

    // compute difference between 2 points with operator Point#-
    rb_define_method(Tvision_Ruby::WrPoint::cTPoint, "-",
                     reinterpret_cast<VALUE(*)(...)>
                     (&Tvision_Ruby::WrPoint::rb_minus), 1);

    // compare 2 points with operator Point#==
    rb_define_method(Tvision_Ruby::WrPoint::cTPoint, "==",
                     reinterpret_cast<VALUE(*)(...)>
                     (&Tvision_Ruby::WrPoint::rb_equal), 1);

    // read the x component of a point with Point#x
    rb_define_method(Tvision_Ruby::WrPoint::cTPoint, "x",
                     reinterpret_cast<VALUE(*)(...)>
                     (&Tvision_Ruby::WrPoint::rb_x), 0);

    // Point#x= sets the x component
    rb_define_method(Tvision_Ruby::WrPoint::cTPoint, "x=",
                     reinterpret_cast<VALUE(*)(...)>
                     (&Tvision_Ruby::WrPoint::rb_set_x), 1);

    // Point#y reads the y component
    rb_define_method(Tvision_Ruby::WrPoint::cTPoint, "y",
                     reinterpret_cast<VALUE(*)(...)>
                     (&Tvision_Ruby::WrPoint::rb_y), 0);

    // Point#y= sets the y component
    rb_define_method(Tvision_Ruby::WrPoint::cTPoint, "y=",
                     reinterpret_cast<VALUE(*)(...)>
                     (&Tvision_Ruby::WrPoint::rb_set_y), 1);

    // Point::new constructs a new point, either from explicit coordinates
    // given as arguments, or from (0,0) when no arguments are given
    rb_define_module_function(Tvision_Ruby::WrPoint::cTPoint, "new",
                              reinterpret_cast<VALUE(*)(...)>
                              (&Tvision_Ruby::WrPoint::rb_new), -1);

    // Point#dup has to call Point::new to allocate a new C++ object
    rb_define_method(Tvision_Ruby::WrPoint::cTPoint, "dup",
                     reinterpret_cast<VALUE(*)(...)>
                     (&Tvision_Ruby::WrPoint::rb_dup), 0);

    // Point#clone is an alias for dup.
    rb_define_method(Tvision_Ruby::WrPoint::cTPoint, "clone",
                     reinterpret_cast<VALUE(*)(...)>
                     (&Tvision_Ruby::WrPoint::rb_dup), 0);
}

    
