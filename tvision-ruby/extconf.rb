#!/usr/bin/env ruby
# $Id: extconf.rb,v 1.4 2002/03/04 15:23:18 t-peters Exp $

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

require "mkmf"

# Check if the user specified the location of the rhtvision library
if (ARGV.grep(/^--rhtvision-prefix=/).size > 0)
  # He did.
  rhtvision_prefix = ARGV.grep(/^--rhtvision-prefix=/)[0]
  rhtvision_prefix = rhtvision_prefix[("--rhtvision-prefix=".length .. -1)]
else
  if (File.exist?("/usr/include/rhtvision/tv.h"))
    rhtvision_prefix = "/usr"
  elsif (File.exist?("/usr/local/include/rhtvision/tv.h"))
    rhtvision_prefix = "/usr/local"
  elsif (File.exist?(ENV["HOME"] + "/include/rhtvision/tv.h"))
    rhtvision_prefix = ENV["HOME"]
  else
    raise "could not find the rhtvision library. Please restart " +
      "extconf.rb with a command line argument --rhtvision-prefix=XXX, " +
      "where XXX is the prefix that you used for configuring the rhtvision " +
      "library"
  end
end

$CFLAGS += " -I#{rhtvision_prefix}/include/rhtvision/ "

$LDFLAGS += " -L#{rhtvision_prefix}/lib " 

unless have_library("rhtv", "CLY_Beep")
  raise "rhtv library not found"
end

create_makefile("tvision")

# modify Makefile to install tvision.rb together with tvision.so

makefile = IO.readlines("Makefile")

line_no = makefile.index(makefile.grep(/^install:/)[0])

makefile[line_no] += " $(rubylibdir)$(target_prefix)/tvision.rb\n" +
  "$(rubylibdir)$(target_prefix)/tvision.rb: tvision.rb        \n" +
  "\t@$(RUBY) -r ftools -e 'File::install(ARGV[0], ARGV[1], 0644, true)' " +
  "                   tvision.rb $(rubylibdir)$(target_prefix)/tvision.rb"


File.open("Makefile", "w") {|f|
  f.puts(makefile)
}
