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

#include "tvision.hh"
#include "application.hh"
#include "point.hh"
#include "rect.hh"
#include "object.hh"
#include "view.hh"
#include "group.hh"
#include "event.hh"

VALUE Tvision_Ruby::mTvision = 0;

extern "C" void
Init_tvision(void)
{
    Tvision_Ruby::mTvision = rb_define_module("TVision");
    Tvision_Ruby::WrObject::init_wrapper();
    Tvision_Ruby::WrPoint::init_wrapper();
    Tvision_Ruby::WrRect::init_wrapper();
    Tvision_Ruby::WrEvent::init_wrapper();
}
