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

// $Id: event.cc,v 1.3 2002/03/04 07:09:27 t-peters Exp $

#include "event.hh"

VALUE Tvision_Ruby::WrEvent::cTEvent;
VALUE Tvision_Ruby::WrEvent::cTEventMouse;
VALUE Tvision_Ruby::WrEvent::cTEventKeyDown;
VALUE Tvision_Ruby::WrEvent::cTEventMessage;

void
Tvision_Ruby::WrEvent::init_wrapper(void)
{
    // define class Event in module Tvision
    Tvision_Ruby::WrEvent::cTEvent =
        rb_define_class_under(Tvision_Ruby::mTvision, "Event",
                              rb_cObject);

    // define class EvMouse, EvKeyDown, EvMessage as a childclasses of Event
    Tvision_Ruby::WrEvent::cTEventMouse =
        rb_define_class_under(Tvision_Ruby::mTvision, "EventMouse",
                              Tvision_Ruby::WrEvent::cTEvent);
    Tvision_Ruby::WrEvent::cTEventKeyDown =
        rb_define_class_under(Tvision_Ruby::mTvision, "EventKeyDown",
                              Tvision_Ruby::WrEvent::cTEvent);
    Tvision_Ruby::WrEvent::cTEventMessage =
        rb_define_class_under(Tvision_Ruby::mTvision, "EventMessage",
                              Tvision_Ruby::WrEvent::cTEvent);
}

// returns the wrapped TEvent struct
TEvent &
Tvision_Ruby::WrEvent::unwrap(VALUE rb_event)
{
    TEvent * c_event;
    Data_Get_Struct(rb_event, TEvent, c_event);
    return *c_event;
}

VALUE
Tvision_Ruby::WrEvent::wrap(TEvent & c_event, VALUE depends_on)
{
    VALUE rb_class = Tvision_Ruby::WrEvent::cTEvent;
    if (c_event.what & evMouse)
        rb_class = Tvision_Ruby::WrEvent::cTEventMouse;
    else if (c_event.what & evKeyboard)
        rb_class = Tvision_Ruby::WrEvent::cTEventKeyDown;
    else if (c_event.what & evMessage)
        rb_class = Tvision_Ruby::WrEvent::cTEventMessage;
    VALUE rb_event = Data_Wrap_Struct(rb_class, 0, 0, &c_event);

    // containing object may not go out of scope before this object
    rb_iv_set(rb_event, "@containing_object", depends_on);
    return rb_event;
}

static void delete_TEvent(void * v_event)
{
    delete reinterpret_cast<TEvent *>(v_event);
}

VALUE
Tvision_Ruby::WrEvent::wrap(const TEvent & c_event)
{
    VALUE rb_class = Tvision_Ruby::WrEvent::cTEvent;
    if (c_event.what & evMouse)
        rb_class = Tvision_Ruby::WrEvent::cTEventMouse;
    else if (c_event.what & evKeyboard)
        rb_class = Tvision_Ruby::WrEvent::cTEventKeyDown;
    else if (c_event.what & evMessage)
        rb_class = Tvision_Ruby::WrEvent::cTEventMessage;
    TEvent * cp_event = new TEvent;
    *cp_event = c_event;
    VALUE rb_event = Data_Wrap_Struct(rb_class, 0, &delete_TEvent,
                                      cp_event);
    return rb_event;
}
