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

// $Id: menuview.cc,v 1.1 2002/03/06 21:39:26 t-peters Exp $

#include "menuview.hh"
#include "menubar.hh"
#include "view.hh"
#include "rect.hh"

VALUE Tvision_Ruby::WrMenuView::cTMenuView = Qnil;

void
Tvision_Ruby::WrMenuView::init_wrapper(void)
{
    // define class MenuView in module TVision
    Tvision_Ruby::WrMenuView::cTMenuView =
        rb_define_class_under(Tvision_Ruby::mTvision, "MenuView",
                              Tvision_Ruby::WrView::cTView);
}

VALUE
Tvision_Ruby::WrMenuView::wrap(TMenuView & c_menuview)
{
    VALUE rb_menuview = Qnil;
    if (dynamic_cast<TMenuBar *>(&c_menuview)) {
        rb_statusline = Tvision_Ruby::WrMenuBar::
            wrap(static_cast<TMenuBar &>(c_menuview));
    }
    return rb_statusline;
}

TMenuView &
Tvision_Ruby::WrMenuView::unwrap(VALUE rb_menuview)
{
    TMenuView * c_menuview =
        dynamic_cast<TMenuView *>(&Tvision_Ruby::WrView::
                                  unwrap(rb_menuview));
    if (c_menuview) {
        return *c_menuview;
    }
    rb_raise(rb_eRuntimeError, "C++:Tvision_Ruby::WrMenuView::unwrap: "
             "VALUE %x does not wrap a TMenuView. File: %s, Line: %d", 
             rb_menuview, __FILE__, __LINE__);
    return *c_menuview;
}
