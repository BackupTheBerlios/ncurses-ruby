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

// $Id: statusline.hh,v 1.2 2002/03/06 21:38:41 t-peters Exp $

#ifndef TVISION_RUBY_STATUSLINE_HH
#define TVISION_RUBY_STATUSLINE_HH

#include "tvision.hh"

namespace Tvision_Ruby {
    class WrStatusLine : public TStatusLine {
        WrStatusLine();
    public:
        static VALUE cTStatusLine;
        static void
        init_wrapper(void);
        static VALUE
        wrap(TStatusLine &);
        static TStatusLine &
        unwrap(VALUE);

        static void
        rb_mark(void *);

        static VALUE
        rb_new(VALUE rb_class, VALUE rb_rect, VALUE rb_statusdefs);
        static VALUE
        rb_initialize(VALUE rb_statusline, VALUE rb_rect, VALUE rb_statusdefs)
        {(void)rb_rect; (void)rb_statusdefs; return rb_statusline;}
    };
}
#endif
