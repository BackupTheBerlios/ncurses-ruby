#!/usr/bin/env ruby
# $Id: tvguid01.rb,v 1.1 2002/02/28 15:56:20 t-peters Exp $

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
#  /*   TVGUID01 Demo Source File                             */
#  /*   Copyright (c) 1991 by Borland International           */
#  /*                                                         */
#  /*---------------------------------------------------------*/

#  /*
#    Taked from the Sergio Sigala <ssigala@globalnet.it> Turbo Vision port to
#    UNIX.
#    LSM: TurboVision for UNIX
#    ftp://sunsite.unc.edu /pub/Linux/devel/lang/c++/tvision-0.6.tar.gz
#    Copying policy: BSD
#    Adapted by Salvador Eduardo Tropea (SET) <set-soft@usa.net>.

#    That's the minimal TVision application.
#  */

require "tvision.rb"
# module TVision contains all needed TVision classes

class MyApp < TVision::Application
  # For this first example, there is no need to extent the Application class
end

myApp = MyApp.new
myApp.run


