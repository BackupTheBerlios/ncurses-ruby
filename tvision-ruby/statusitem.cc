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

#include "statusitem.hh"

Tvision_Ruby::WrStatusItem::WrStatusItem(VALUE rb_statusitem,
                                         TStatusItem * next_item)
    : TStatusItem(STR2CSTR(rb_funcall(rb_statusitem, rb_intern("text"), 0)),
                  NUM2INT(rb_funcall(rb_statusitem, rb_intern("keyCode"), 0)),
                  NUM2INT(rb_funcall(rb_statusitem, rb_intern("command"), 0)),
                  next_item)
{}

TStatusItem *
Tvision_Ruby::WrStatusItem::create_statusitem_chain(VALUE rb_statusitem_array)
{
    TStatusItem * item = 0;
    int n = NUM2INT(rb_funcall(rb_statusitem_array, rb_intern("size"), 0));
    while (--n >= 0) {
        item = new Tvision_Ruby::WrStatusItem(rb_funcall(rb_statusitem_array,
                                                         rb_intern("[]"),
                                                         1,
                                                         INT2NUM(n)),
                                              item);
    }
    return item;
}
