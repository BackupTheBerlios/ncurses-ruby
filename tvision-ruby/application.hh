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

#ifndef TVISION_RUBY_APPLICATION_HH
#define TVISION_RUBY_APPLICATION_HH

#include "tvision.hh"

namespace Tvision_Ruby {
    // A class derived from TApplication to ease the wrapping
    class WrApplication : public TApplication {
    public:
        // The ruby Application class
        static VALUE cTApplication;

        // The constructor takes the Ruby class derived from application as its
        // argument
        WrApplication(VALUE application_class);

        // The default ruby initializer. The ruby initializer is called from
        // the WrApplication constructor. This initializer calls the three init
        // functions.  It may be overridden in this or a derived class.
        static VALUE
        rb_initialize(VALUE self);

        // The new method of ruby's application class
        static VALUE
        rb_new(VALUE application_class);

        // These are the default ruby initializers for the statusline, menubar,
        // and desktop. They will call the corresponding TApplication init
        // functions.
        static VALUE
        rb_initStatusLine(VALUE self);
        static VALUE
        rb_initMenuBar(VALUE self);
        static VALUE
        rb_initDeskTop(VALUE self);

        // These are the methods that the ruby initializers will call for
        // initialization of their parts:
        virtual void
        c_initStatusLine(void);
        virtual void
        c_initMenuBar(void);
        virtual void
        c_initDeskTop(void);

        static void
        rb_mark(void*);
        static void
        rb_free(void*);
        
        // This function registers the necessary Application methods with ruby.
        static void
        init_wrapper(void);
    };
}
#endif
