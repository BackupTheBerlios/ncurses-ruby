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

#ifndef TVISION_RUBY_POINT_HH
#define TVISION_RUBY_POINT_HH

#include "tvision.hh"

namespace Tvision_Ruby {
    class WrPoint : public TPoint {
    public:
        static VALUE cTPoint;
        
        WrPoint(VALUE rb_point);
        WrPoint(void);
        
        static VALUE
        wrap(const TPoint &);

        static VALUE
        wrap(TPoint &, VALUE depends_on_object);

        static VALUE
        rb_plus(VALUE rb_point1, VALUE rb_point2);
        static VALUE
        rb_minus(VALUE rb_point1, VALUE rb_point2);

        static VALUE
        rb_equal(VALUE rb_point1, VALUE rb_point2);

        static VALUE
        rb_x(VALUE rb_point);
        static VALUE
        rb_y(VALUE rb_point);
        static VALUE
        rb_set_x(VALUE rb_point, VALUE rb_x);
        static VALUE
        rb_set_y(VALUE rb_point, VALUE rb_y);

        static void
        rb_free(void *);
        
        static void
        init_wrapper(void);

        static VALUE
        rb_new(int argc, VALUE *argv, VALUE self);

        static VALUE
        rb_dup(VALUE rb_point);
        
        static TPoint &
        unwrap(VALUE rb_point);
    };
}
#endif

