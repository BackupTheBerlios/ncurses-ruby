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

// $Id: group.cc,v 1.5 2002/03/04 07:10:03 t-peters Exp $

#include "group.hh"
#include "view.hh"
#include "application.hh"

VALUE Tvision_Ruby::WrGroup::cTGroup = Qnil;

void
Tvision_Ruby::WrGroup::init_wrapper(void)
{
    // define class Application in module Tvision
    Tvision_Ruby::WrGroup::cTGroup =
        rb_define_class_under(Tvision_Ruby::mTvision, "Group",
                              Tvision_Ruby::WrView::cTView);
    rb_define_method(Tvision_Ruby::WrGroup::cTGroup, "insert",
                     reinterpret_cast<VALUE(*)(...)>
                     (&Tvision_Ruby::WrGroup::rb_insert), 1);
    Tvision_Ruby::WrApplication::init_wrapper();
}

VALUE
Tvision_Ruby::WrGroup::wrap(TGroup & c_group)
{
    VALUE rb_group = Qnil;
    if (TApplication * c_prog = dynamic_cast<TApplication*>(&c_group)) {
        rb_group = Tvision_Ruby::WrApplication::wrap(*c_prog);
    }
    return rb_group;
}

TGroup &
Tvision_Ruby::WrGroup::unwrap(VALUE rb_group)
{
    TGroup * c_group =
        dynamic_cast<TGroup *>(&Tvision_Ruby::WrView::unwrap(rb_group));
    if (c_group) {
        return *c_group;
    }
    rb_raise(rb_eRuntimeError, "C++:Tvision_Ruby::WrGroup::unwrap: VALUE %x "
             "does not wrap a TGroup. File: %s, Line: %d", rb_group, __FILE__,
             __LINE__);
    return *c_group;
}

VALUE
Tvision_Ruby::WrGroup::rb_insert(VALUE rb_group, VALUE rb_view)
{
    TGroup & c_group = Tvision_Ruby::WrGroup::unwrap(rb_group);
    TView &  c_view  = Tvision_Ruby::WrView::unwrap(rb_view);
    c_group.insert(&c_view);
    return Qnil;
}
