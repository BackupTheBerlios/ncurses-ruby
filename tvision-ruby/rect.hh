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

#ifndef TVISION_RUBY_RECT_HH
#define TVISION_RUBY_RECT_HH

#include "tvision.hh"

namespace Tvision_Ruby {
    class WrRect : public TRect {
    public:
        static VALUE cTRect;

        static
        VALUE rb_new(int argc, VALUE *argv, VALUE self);

        static
        VALUE rb_initialize(int argc, VALUE *argv, VALUE rb_rect);

        static
        VALUE rb_dup(VALUE rb_rect);

        static
        VALUE rb_a(VALUE rb_rect);
        static
        VALUE rb_set_a(VALUE rb_rect, VALUE rb_point);
        static
        VALUE rb_b(VALUE rb_rect);
        static
        VALUE rb_set_b(VALUE rb_rect, VALUE rb_point);

        static
        VALUE rb_move(VALUE rb_rect, VALUE aDX, VALUE aDY);
        static
        VALUE rb_grow(VALUE rb_rect, VALUE aDX, VALUE aDY );
        static
        VALUE rb_intersect(VALUE rb_rect, VALUE rb_other);
        static
        VALUE rb_Union(VALUE rb_rect, VALUE rb_other);
        static
        VALUE rb_contains(VALUE rb_rect, VALUE rb_point);
        static
        VALUE rb_equal(VALUE rb_rect, VALUE rb_other);
        static
        VALUE rb_isEmpty(VALUE rb_rect);

        static void
        init_wrapper(void);

        static
        VALUE wrap(const TRect &);
        static
        VALUE wrap(TRect &, VALUE depends_on_object);

    private:
        static
        TRect & unwrap(VALUE rb_rect);
        static
        void rb_free(void *);
    };
}
#endif
