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

// $Id: statusdef.cc,v 1.2 2002/02/26 10:56:40 t-peters Exp $

#include "statusdef.hh"
#include "statusitem.hh"

Tvision_Ruby::WrStatusDef::WrStatusDef(VALUE rb_statusdef,
                                       TStatusDef * next_def)
    : TStatusDef(NUM2INT(rb_funcall(rb_statusdef, rb_intern("min"), 0)),
                 NUM2INT(rb_funcall(rb_statusdef, rb_intern("max"), 0)),
                 Tvision_Ruby::WrStatusItem::
                                  create_statusitem_chain(rb_statusdef),
                 next_def)
{}
TStatusDef *
Tvision_Ruby::WrStatusDef::create_statusdef_chain(VALUE rb_statusdef_array)
{
    TStatusDef * def = 0;
    int n = NUM2INT(rb_funcall(rb_statusdef_array, rb_intern("size"), 0));
    while (--n >= 0) {
        def = new Tvision_Ruby::WrStatusDef(rb_funcall(rb_statusdef_array,
                                                       rb_intern("[]"),
                                                       1,
                                                       INT2NUM(n)),
                                            def);
    }
    return def;
}
