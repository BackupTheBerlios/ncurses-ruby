#!/usr/bin/env ruby

require "mkmf"

$CFLAGS += " -I/usr/local/include/rhtvision/ "

unless have_library("rhtv", "CLY_Beep")
  raise "rhtv library not found"
end

create_makefile("tvision")
