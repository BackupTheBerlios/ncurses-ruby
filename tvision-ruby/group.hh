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

// $Id: group.hh,v 1.3 2002/03/04 07:10:11 t-peters Exp $

#ifndef TVISION_RUBY_GROUP_HH
#define TVISION_RUBY_GROUP_HH

#include "tvision.hh"

namespace Tvision_Ruby {
    // this class only acts as a namespace for functions related to wrapping
    // TGroups functions, but is implemented as a class derived from TGroup for
    // consistency with wrapping other classes
    class WrGroup : public TGroup {
        WrGroup();
    public:
        static VALUE cTGroup;
        static void
        init_wrapper(void);
        static VALUE
        wrap(TGroup &);
        static TGroup &
        unwrap(VALUE);

        static void
        rb_mark(void *);


        static VALUE
        rb_insert(VALUE rb_group, VALUE rb_view);
    };
}
#endif
