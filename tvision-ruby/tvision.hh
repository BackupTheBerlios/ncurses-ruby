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

#ifndef TVISION_RUBY_HH
#define TVISION_RUBY_HH

#include <ruby.h>

#define Uses_TApplication
#define Uses_TStatusLine
#define Uses_TStatusItem
#define Uses_TStatusDef
#define Uses_TMenuBar
#define Uses_TDeskTop
#define Uses_TPoint
#define Uses_TRect

#include <rhtvision/tv.h>

namespace Tvision_Ruby {
    // The ruby Tvision module
    extern VALUE mTvision;
}

extern "C" void
Init_tvision(void);
#endif
