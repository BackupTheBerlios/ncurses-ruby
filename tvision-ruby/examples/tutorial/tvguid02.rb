#!/usr/bin/env ruby
# $Id: tvguid02.rb,v 1.1 2002/03/04 07:12:12 t-peters Exp $

# tvision-ruby is a ruby wrapper for the text-mode application framework
# developed by Borland.
# Copyright (C) 2002 Tobias Peters <t-peters@users.berlios.de>
#
# This program is free software; you can redistribute it and/or
# modify it under the terms of the GNU General Public License
# as published by the Free Software Foundation; either version 2
# of the License, or (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License along
# with this program; if not, write to the Free Software Foundation, Inc.,
# 59 Temple Place, Suite 330, Boston, MA 02111-1307, USA.

#  /*---------------------------------------------------------*/
#  /*                                                         */
#  /*   Turbo Vision 1.0                                      */
#  /*   TVGUID02 Demo Source File                             */
#  /*   Copyright (c) 1991 by Borland International           */
#  /*                                                         */
#  /*---------------------------------------------------------*/

require "tvision.rb"

#  /*
#    Taked from the Sergio Sigala <ssigala@globalnet.it> Turbo Vision port to
#  UNIX.
#    LSM: TurboVision for UNIX
#    ftp://sunsite.unc.edu /pub/Linux/devel/lang/c++/tvision-0.6.tar.gz
#    Copying policy: BSD
#    Adapted by Salvador Eduardo Tropea (SET) <set-soft@usa.net>.

#    Here you can see how a new item is added to the status bar of the
#  application. See how the << operator simplifies the work. The
#  0,0xFFFF is the range where the this status items are showed. It is related
#  to the context sensitive help and you'll see it latter.
#  */


class MyApp < TVision::Application
  def initStatusLine()
    rect = getExtent
    rect.a.y = rect.b.y - 1     # move top to 1 line above bottom
    statusline =
      TVision::StatusLine.new(rect,
			      # set range of help contexts
			      TVision::StatusDef.new(0, 0xFFFF) <<
			      # define an item
			      TVision::StatusItem.new("~Alt-X~ Exit",
						      TVision::KbAltX,
						      TVision::CmQuit) <<
			      # and another one
			      TVision::StatusItem.new("~Alt-F3~ Close",
						      TVision::KbAltF3, 
						      TVision::CmClose))
    insert(statusline)
    TVision::Application.statusLine = statusline
  end
end

myApp = MyApp.new
myApp.run
