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

// $Id: view.cc,v 1.5 2002/03/04 07:11:24 t-peters Exp $

#include "view.hh"
#include "object.hh"
#include "group.hh"
#include "rect.hh"
#include "statusline.hh"

VALUE Tvision_Ruby::WrView::cTView = Qnil;

void
Tvision_Ruby::WrView::init_wrapper(void)
{
    // define class Application in module Tvision
    Tvision_Ruby::WrView::cTView =
        rb_define_class_under(Tvision_Ruby::mTvision, "View",
                              Tvision_Ruby::WrObject::cTObject);

    rb_define_method(Tvision_Ruby::WrView::cTView, "getExtent",
                     reinterpret_cast<VALUE(*)(...)>
                     (&Tvision_Ruby::WrView::rb_getExtent), 0);
    Tvision_Ruby::WrGroup::init_wrapper();
    Tvision_Ruby::WrStatusLine::init_wrapper();
}

VALUE
Tvision_Ruby::WrView::wrap(TView & c_view)
{
    VALUE rb_view = Qnil;
    if (TGroup * c_group = dynamic_cast<TGroup*>(&c_view)) {
        rb_view = Tvision_Ruby::WrGroup::wrap(*c_group);
    }
    else if (TStatusLine * c_statusline =
             dynamic_cast<TStatusLine *>(&c_view)) {
        rb_view = Tvision_Ruby::WrStatusLine::wrap(*c_statusline);
    }
    return rb_view;
}

TView &
Tvision_Ruby::WrView::unwrap(VALUE rb_view)
{
    TView * c_view =
        dynamic_cast<TView *>(&Tvision_Ruby::WrObject::unwrap(rb_view));
    if (c_view) {
        return *c_view;
    }
    rb_raise(rb_eRuntimeError, "C++:Tvision_Ruby::WrView::unwrap: VALUE %x "
             "does not wrap a TView. File: %s, Line: %d", rb_view, __FILE__,
             __LINE__);
    return *c_view;
}
VALUE
Tvision_Ruby::WrView::rb_getExtent(VALUE rb_view)
{
    TView & c_view = Tvision_Ruby::WrView::unwrap(rb_view);
    return Tvision_Ruby::WrRect::wrap(c_view.getExtent());
}
void
Tvision_Ruby::WrView::rb_free(void * c_pointer)
{
    assert(c_pointer != 0);
    TView & c_view = * reinterpret_cast<TView *>(c_pointer);
    if (c_view.owner == 0) {
        // view is not associated with any other view
        destroy(&c_view);
    }
}

