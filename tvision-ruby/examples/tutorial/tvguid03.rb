#!/usr/bin/env ruby
# $Id: tvguid03.rb,v 1.1 2002/03/05 15:07:46 t-peters Exp $

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
#    Taken from the Sergio Sigala <ssigala@globalnet.it> Turbo Vision port to
#  UNIX.
#    LSM: TurboVision for UNIX
#    ftp://sunsite.unc.edu /pub/Linux/devel/lang/c++/tvision-0.6.tar.gz
#    Copying policy: BSD
#    Adapted by Salvador Eduardo Tropea (SET) <set-soft@usa.net>.

#    Here you can see how a menu is added to the application. See how the
#  xoverloaded + operator simplifies the work again. The hcNoContext means no
#  xcontext sensitive help.

CmMyFileOpen = 200 # assign new command values
CmMyNewWin   = 201

class MyApp < TVision::Application

  include TVision

  def initStatusLine()
    rect = getExtent
    rect.a.y = rect.b.y - 1     # move top to 1 line above bottom
    statusline =
      StatusLine.new(rect,
		     # set range of help contexts
		     StatusDef.new(0, 0xFFFF) <<
		     # define an item
		     StatusItem.new("~Alt-X~ Exit", KbAltX, CmQuit) <<
		     # and another one
		     StatusItem.new("~Alt-F3~ Close", KbAltF3, CmClose))
    insert(statusline)
    Application.statusLine = statusline
  end
  def initMenuBar()
    rect = getExtent
    rect.b.y = rect.a.y + 1; # set bottom line 1 line below top line
    menubar = MenuBar.new(rect,
			  [ SubMenu.new("~F~ile", KbAltF) <<
			    MenuItem.new("~O~pen", CmMyFileOpen, KbF3,
					 HcNoContext, "F3") <<
			    MenuItem.new("~N~ew", CmMyNewWin, KbF4,
					 HcNoContext, "F4") <<
			    TVision.newLine() <<
			    MenuItem.new("E~x~it", CmQuit, CmQuit,
					 HcNoContext, "Alt-X" ),
			    SubMenu.new("~W~indow", KbAltW) <<
			    MenuItem.new("~N~ext", CmNext, KbF6,
					 HcNoContext, "F6") <<
			    MenuItem.new("~Z~oom", CmZoom, KbF5,
					 HcNoContext, "F5") ])
    insert(menubar)
    Application.menuBar = menubar
  end
end

myApp = MyApp.new
myApp.run
