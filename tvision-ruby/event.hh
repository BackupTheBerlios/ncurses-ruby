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

// $Id: event.hh,v 1.2 2002/02/26 10:56:40 t-peters Exp $

#ifndef TVISION_RUBY_EVENT_HH
#define TVISION_RUBY_EVENT_HH

#include "tvision.hh"

namespace Tvision_Ruby {
    // class WrEvent bundles all Event wrapper code
    class WrEvent : public TEvent {
    public:
        // Ruby class object of wrapper class Event
        static VALUE cTEvent;

        // Ruby class object of wrapper class EvMouse, derived from Event
        static VALUE cTEvMouse;

        // Ruby class object of wrapper class EvKeyDown, derived from Event
        static VALUE cTEvKeyDown;

        // Ruby class object of wrapper class EvMessage, derived from Event
        static VALUE cTEvMessage;

        // necessary initialization for Event wrapper code
        static void
        init_wrapper(void);

        // access the wrapped TEvent struct
        static TEvent &
        unwrap(VALUE rb_event);

        // wrap an Event without obtaining its ownership. Event is owned by
        // object wrapped in depends_on. That will destroy it again.
        static VALUE
        wrap(TEvent &, VALUE depends_on);

        // wrap a copy of this Event. Destroy it on finalization.
        static VALUE
        wrap(const TEvent &);
    };
}
#endif
