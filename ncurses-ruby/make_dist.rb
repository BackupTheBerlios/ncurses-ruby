#!/usr/bin/env ruby

# $Id: make_dist.rb,v 1.7 2011/05/30 18:29:32 t-peters Exp $

require "fileutils"

def sys(i)
  puts("\"#{i}\"")
  system(i)
end

dir  = File.dirname(__FILE__)
base = File.basename(dir)
base = "ncurses-ruby" if base == "."

files = IO.readlines(dir + "/MANIFEST").collect{|filename|filename.chomp}

Version = File.new("#{dir}/VERSION").readline.chomp

FileUtils.mkdir "#{base}-#{Version}"
files.each{|filename|
  if filename.index "/"
    FileUtils.mkdir_p "#{base}-#{Version}/#{File.dirname(filename)}"
  end
  sys "cp #{dir}/#{filename} #{base}-#{Version}/#{filename}"
}
sys "tar cjf #{base}-#{Version}.tar.bz2 --owner=0 --group=0 #{base}-#{Version}"

sys "rm -r #{base}-#{Version}/"
