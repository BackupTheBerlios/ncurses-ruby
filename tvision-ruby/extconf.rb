#!/usr/bin/env ruby
# $Id: extconf.rb,v 1.2 2002/02/27 12:38:59 t-peters Exp $

require "mkmf"

if (ARGV.grep(/^--rhtvision-prefix=/).size > 0)
  rhtvision_prefix = ARGV.grep(/^--rhtvision-prefix=/)[0]
  rhtvision_prefix = rhtvision_prefix[("--rhtvision-prefix=".length .. -1)]
else
  if (File.exist?("/usr/include/rhtvision/tv.h"))
    rhtvision_prefix = "/usr"
  elsif (File.exist?("/usr/local/include/rhtvision/tv.h"))
    rhtvision_prefix = "/usr/local"
  elsif (File.exist?(ENV["HOME"] + "/include/rhtvision/tv.h"))
    rhtvision_prefix = ENV["HOME"]
  end
end

$CFLAGS += " -I#{rhtvision_prefix}/include/rhtvision/ "

$LDFLAGS += " -L#{rhtvision_prefix}/lib " 

unless have_library("rhtv", "CLY_Beep")
  raise "rhtv library not found"
end

create_makefile("tvision")
