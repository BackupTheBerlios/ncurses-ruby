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

#include "view.hh"
#include "object.hh"
#include "group.hh"

VALUE Tvision_Ruby::WrView::cTView = Qnil;

void
Tvision_Ruby::WrView::init_wrapper(void)
{
    // define class Application in module Tvision
    Tvision_Ruby::WrView::cTView =
        rb_define_class_under(Tvision_Ruby::mTvision, "View",
                              Tvision_Ruby::WrObject::cTObject);
}

VALUE
Tvision_Ruby::WrView::wrap(TView & c_view)
{
    VALUE rb_view = Qnil;
    if (TGroup * c_group = dynamic_cast<TGroup*>(&c_view)) {
        rb_view = Tvision_Ruby::WrGroup::wrap(*c_group);
    }
    return rb_view;
}

TView &
Tvision_Ruby::WrView::unwrap(VALUE rb_view)
{
    WrView * c_view =
        dynamic_cast<WrView *>(&Tvision_Ruby::WrObject::unwrap(rb_view));
    if (c_view) {
        return *c_view;
    }
    rb_raise(rb_eRuntimeError, "C++:Tvision_Ruby::WrView::unwrap: VALUE %x "
             "does not wrap a TView. File: %s, Line: %d", rb_view, __FILE__,
             __LINE__);
    return *c_view;
}

