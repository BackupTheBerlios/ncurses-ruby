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

// $Id: rect.cc,v 1.2 2002/02/26 10:56:40 t-peters Exp $

#include "rect.hh"
#include "point.hh"

VALUE Tvision_Ruby::WrRect::cTRect = 0;

VALUE
Tvision_Ruby::WrRect::wrap(const TRect & rect)
{
    TRect * c_rect = new TRect(rect);
    return Data_Wrap_Struct(Tvision_Ruby::WrRect::cTRect, 0,
                               &Tvision_Ruby::WrRect::rb_free, c_rect);
}
VALUE
Tvision_Ruby::WrRect::wrap(TRect & rect, VALUE depends_on_object)
{
    VALUE rb_rect;
    rb_rect = Data_Wrap_Struct(Tvision_Ruby::WrRect::cTRect, 0,
                               0, // don't free this rect
                               &rect);
    // containing object may not go out of scope before this object
    rb_iv_set(rb_rect, "@containing_object", depends_on_object);
    return rb_rect;
}

TRect &
Tvision_Ruby::WrRect::unwrap(VALUE rb_rect)
{
    TRect * c_rect;
    Data_Get_Struct(rb_rect, TRect, c_rect);
    return *c_rect;
}

void
Tvision_Ruby::WrRect::rb_free(void * c_rect)
{
    delete reinterpret_cast<TRect *>(c_rect);
}
VALUE
Tvision_Ruby::WrRect::rb_new(int argc, VALUE *argv, VALUE self)
{
    VALUE rb_rect = Tvision_Ruby::WrRect::wrap(TRect());
    rb_obj_call_init(rb_rect, argc, argv);
    return rb_rect;
}
VALUE
Tvision_Ruby::WrRect::rb_initialize(int argc, VALUE *argv, VALUE rb_rect)
{
   VALUE ax, ay, bx, by;
    switch(argc) {
    case 4:
        ax = argv[0]; ay = argv[1]; bx = argv[2]; by = argv[3];
        break;
    case 2:
        ax = rb_funcall3(argv[0], rb_intern("x"), 0, 0);
        ay = rb_funcall3(argv[0], rb_intern("y"), 0, 0);
        bx = rb_funcall3(argv[1], rb_intern("x"), 0, 0);
        by = rb_funcall3(argv[1], rb_intern("y"), 0, 0);
        break;
    case 0:
        ax = ay = bx = by = INT2FIX(0);
        break;
    default:
        rb_raise(rb_eArgError,
                 "Rect#initialize takes either 4, 2, or no arguments");
        return Qnil;
    }
    TRect & c_rect = Tvision_Ruby::WrRect::unwrap(rb_rect);
    c_rect.a.x = NUM2INT(ax);
    c_rect.a.y = NUM2INT(ay);
    c_rect.b.x = NUM2INT(bx);
    c_rect.b.y = NUM2INT(by);
    return rb_rect;
}

VALUE
Tvision_Ruby::WrRect::rb_dup(VALUE rb_rect)
{
    return Tvision_Ruby::WrRect::wrap(Tvision_Ruby::WrRect::unwrap(rb_rect));
}

VALUE
Tvision_Ruby::WrRect::rb_a(VALUE rb_rect)
{
    return Tvision_Ruby::WrPoint::wrap(Tvision_Ruby::WrRect::unwrap(rb_rect).a,
                                       rb_rect);
}
VALUE
Tvision_Ruby::WrRect::rb_set_a(VALUE rb_rect, VALUE rb_point)
{
    TPoint & c_rect_point = Tvision_Ruby::WrRect::unwrap(rb_rect).a;
    TPoint & c_point      = Tvision_Ruby::WrPoint::unwrap(rb_point);
    c_rect_point = c_point;
    return Tvision_Ruby::WrPoint::wrap(c_rect_point, rb_rect);
}

VALUE
Tvision_Ruby::WrRect::rb_b(VALUE rb_rect)
{
    return Tvision_Ruby::WrPoint::wrap(Tvision_Ruby::WrRect::unwrap(rb_rect).b,
                                       rb_rect);
}
VALUE
Tvision_Ruby::WrRect::rb_set_b(VALUE rb_rect, VALUE rb_point)
{
    TPoint & c_rect_point = Tvision_Ruby::WrRect::unwrap(rb_rect).b;
    TPoint & c_point      = Tvision_Ruby::WrPoint::unwrap(rb_point);
    c_rect_point = c_point;
    return Tvision_Ruby::WrPoint::wrap(c_rect_point, rb_rect);
}

VALUE
Tvision_Ruby::WrRect::rb_move(VALUE rb_rect, VALUE aDX, VALUE aDY)
{
    Tvision_Ruby::WrRect::unwrap(rb_rect).move(NUM2INT(aDX), NUM2INT(aDY));
    return rb_rect;
}

VALUE
Tvision_Ruby::WrRect::rb_grow(VALUE rb_rect, VALUE aDX, VALUE aDY)
{
    Tvision_Ruby::WrRect::unwrap(rb_rect).grow(NUM2INT(aDX), NUM2INT(aDY));
    return rb_rect;
}

VALUE Tvision_Ruby::WrRect::rb_intersect(VALUE rb_rect, VALUE rb_other)
{
    Tvision_Ruby::WrRect::unwrap(rb_rect).
        intersect(Tvision_Ruby::WrRect::unwrap(rb_other));
    return rb_rect;
}

VALUE Tvision_Ruby::WrRect::rb_Union(VALUE rb_rect, VALUE rb_other)
{
    Tvision_Ruby::WrRect::unwrap(rb_rect).
        Union(Tvision_Ruby::WrRect::unwrap(rb_other));
    return rb_rect;
}

VALUE Tvision_Ruby::WrRect::rb_equal(VALUE rb_rect, VALUE rb_other)
{
    if (rb_funcall3(rb_other, rb_intern("kind_of?"), 1,
                    &Tvision_Ruby::WrRect::cTRect) == Qfalse) {
        return Qfalse;
    }
    return (Tvision_Ruby::WrRect::unwrap(rb_rect) ==
            Tvision_Ruby::WrRect::unwrap(rb_other)) ? Qtrue : Qfalse;
}

VALUE Tvision_Ruby::WrRect::rb_isEmpty(VALUE rb_rect)
{
    return Tvision_Ruby::WrRect::unwrap(rb_rect).isEmpty() ? Qtrue : Qfalse;
}

VALUE
Tvision_Ruby::WrRect::rb_contains(VALUE rb_rect, VALUE rb_point)
{
    return Tvision_Ruby::WrRect::unwrap(rb_rect).
        contains(Tvision_Ruby::WrPoint::unwrap(rb_point)) ? Qtrue : Qfalse;
}

void
Tvision_Ruby::WrRect::init_wrapper(void)
{
    // define class "Rect" in module "Tvision"
    Tvision_Ruby::WrRect::cTRect =
        rb_define_class_under(Tvision_Ruby::mTvision, "Rect", rb_cObject);

    // Rect::new constructs a new rect, either from explicit coordinates
    // or Point-s given as arguments, or from (0,0,0,0) when no arguments are
    // given. It does this by first wrapping a Trect and than calling
    // the initializer with its arguments
    rb_define_module_function(Tvision_Ruby::WrRect::cTRect, "new",
                              reinterpret_cast<VALUE(*)(...)>
                              (&Tvision_Ruby::WrRect::rb_new), -1);
    // Rect::initialize evaluates the construction arguments.
    rb_define_method(Tvision_Ruby::WrRect::cTRect, "initialize",
                     reinterpret_cast<VALUE(*)(...)>
                     (&Tvision_Ruby::WrRect::rb_initialize), -1);

    // Rect#dup allocates and wraps a new C++ object
    rb_define_method(Tvision_Ruby::WrRect::cTRect, "dup",
                     reinterpret_cast<VALUE(*)(...)>
                     (&Tvision_Ruby::WrRect::rb_dup), 0);
    // Rect#clone is an alias for dup.
    rb_define_method(Tvision_Ruby::WrRect::cTRect, "clone",
                     reinterpret_cast<VALUE(*)(...)>
                     (&Tvision_Ruby::WrRect::rb_dup), 0);

     // read Point a of a rect with Rect#a
    rb_define_method(Tvision_Ruby::WrRect::cTRect, "a",
                     reinterpret_cast<VALUE(*)(...)>
                     (&Tvision_Ruby::WrRect::rb_a), 0);

    // Rect#a= sets the a Point
    rb_define_method(Tvision_Ruby::WrRect::cTRect, "a=",
                     reinterpret_cast<VALUE(*)(...)>
                     (&Tvision_Ruby::WrRect::rb_set_a), 1);

    // Rect#b reads the b Point
    rb_define_method(Tvision_Ruby::WrRect::cTRect, "b",
                     reinterpret_cast<VALUE(*)(...)>
                     (&Tvision_Ruby::WrRect::rb_b), 0);

    // Rect#b= sets the b Point
    rb_define_method(Tvision_Ruby::WrRect::cTRect, "b=",
                     reinterpret_cast<VALUE(*)(...)>
                     (&Tvision_Ruby::WrRect::rb_set_b), 1);

    // Rect#grow! extends all borders by the given coordinate differences
    rb_define_method(Tvision_Ruby::WrRect::cTRect, "grow!",
                     reinterpret_cast<VALUE(*)(...)>
                     (&Tvision_Ruby::WrRect::rb_grow), 2);

    // Rect#move! moves the whole rectangle by the given coordinates
    rb_define_method(Tvision_Ruby::WrRect::cTRect, "move!",
                     reinterpret_cast<VALUE(*)(...)>
                     (&Tvision_Ruby::WrRect::rb_move), 2);

    // Rect#intersect! clips this Rect by the other Rect
    rb_define_method(Tvision_Ruby::WrRect::cTRect, "intersect!",
                     reinterpret_cast<VALUE(*)(...)>
                     (&Tvision_Ruby::WrRect::rb_intersect), 1);

    // Rect#union! enlarges this rectangle so that it also contains the other
    rb_define_method(Tvision_Ruby::WrRect::cTRect, "union!",
                     reinterpret_cast<VALUE(*)(...)>
                     (&Tvision_Ruby::WrRect::rb_Union), 1);

    // Rect#contains? checks if the given Point is inside this Rect
    rb_define_method(Tvision_Ruby::WrRect::cTRect, "contains?",
                     reinterpret_cast<VALUE(*)(...)>
                     (&Tvision_Ruby::WrRect::rb_contains), 1);

    // Rect#== checks if two rectangles have equal extensions
    rb_define_method(Tvision_Ruby::WrRect::cTRect, "==",
                     reinterpret_cast<VALUE(*)(...)>
                     (&Tvision_Ruby::WrRect::rb_equal), 1);

    // Rect#isEmpty? checks if this Rect contains no charcells
    rb_define_method(Tvision_Ruby::WrRect::cTRect, "isEmpty?",
                     reinterpret_cast<VALUE(*)(...)>
                     (&Tvision_Ruby::WrRect::rb_isEmpty), 0);
}
