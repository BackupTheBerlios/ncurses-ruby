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

// $Id: statusline.cc,v 1.1 2002/03/04 07:12:12 t-peters Exp $

#include "statusline.hh"
#include "view.hh"
#include "rect.hh"
#include "statusdef.hh"
#include "object.hh"

VALUE Tvision_Ruby::WrStatusLine::cTStatusLine = Qnil;

void
Tvision_Ruby::WrStatusLine::init_wrapper(void)
{
    // define class StatusLine in module TVision
    Tvision_Ruby::WrStatusLine::cTStatusLine =
        rb_define_class_under(Tvision_Ruby::mTvision, "StatusLine",
                              Tvision_Ruby::WrView::cTView);

    rb_define_module_function(Tvision_Ruby::WrStatusLine::cTStatusLine, "new",
                              reinterpret_cast<VALUE(*)(...)>
                              (&Tvision_Ruby::WrStatusLine::rb_new), 2);
}

VALUE
Tvision_Ruby::WrStatusLine::wrap(TStatusLine & c_statusline)
{
    VALUE rb_statusline =
        Data_Wrap_Struct(Tvision_Ruby::WrStatusLine::cTStatusLine,
                         0, &Tvision_Ruby::WrView::rb_free,
                         &c_statusline);
    
    return rb_statusline;
}

TStatusLine &
Tvision_Ruby::WrStatusLine::unwrap(VALUE rb_statusline)
{
    TStatusLine * c_statusline =
        dynamic_cast<TStatusLine *>(&Tvision_Ruby::WrView::unwrap(rb_statusline));
    if (c_statusline) {
        return *c_statusline;
    }
    rb_raise(rb_eRuntimeError, "C++:Tvision_Ruby::WrStatusLine::unwrap: "
             "VALUE %x does not wrap a TStatusLine. File: %s, Line: %d", 
             rb_statusline, __FILE__, __LINE__);
    return *c_statusline;
}

VALUE
Tvision_Ruby::WrStatusLine::rb_new(VALUE rb_class, VALUE rb_rect,
                                   VALUE rb_statusdefs)
{
    if (rb_obj_is_kind_of(rb_rect, Tvision_Ruby::WrRect::cTRect) != Qtrue) {
        rb_raise(rb_eArgError,
                 "StatusLine::new expects a Rect object as the first argument"
                 );
        return Qnil;
    }
    TRect & c_rect = Tvision_Ruby::WrRect::unwrap(rb_rect);
    if (rb_obj_is_kind_of(rb_statusdefs,
                          Tvision_Ruby::WrStatusDef::cTStatusDef) == Qtrue) {
        // put single statusdef in an array
        rb_statusdefs = rb_ary_new3(1, rb_statusdefs);
    }
    
    TStatusDef * c_statusdef = 0;
    if (rb_obj_is_kind_of(rb_statusdefs, rb_cArray) == Qtrue) {
        // initialize c_statusdef
        c_statusdef = WrStatusDef::create_statusdef_chain(rb_statusdefs);
    }
    else {
        rb_raise(rb_eArgError,
                 "StatusLine::new expects one or more StatusDef objects as "
                 "the second argument");
        return Qnil;
    }
    // init and return statusline
    TStatusLine * c_statusline = new TStatusLine(c_rect, *c_statusdef);
    return Tvision_Ruby::WrObject::wrap(*c_statusline);
}


