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

#include "application.hh"

VALUE Tvision_Ruby::WrApplication::cTApplication = 0;

Tvision_Ruby::WrApplication::WrApplication(VALUE c_application)
    // set createStatusLine, createMenuBar, and createDeskTop to 0. They
    // will not be called from the TProgram constructor. We do the
    // initialization here in this constructor.
    : TProgInit(0,0,0)
{
    // wrap the c++ application object in a ruby object
    VALUE self = Data_Wrap_Struct(c_application,
                                  &Tvision_Ruby::WrApplication::rb_mark,
                                  &Tvision_Ruby::WrApplication::rb_free,
                                  this);

    // register this application object in a global variable
    rb_iv_set(Tvision_Ruby::mTvision, "@application", self);

    // The ruby initializer might call the methods initStatusLine,
    // initMenuBar and initDeskTop.
    rb_obj_call_init(self, 0, 0);
}

// The default ruby initializer: This one calls the three init functions.
// It may be overridden in this or a derived class.
VALUE
Tvision_Ruby::WrApplication::rb_initialize(VALUE self)
{
    rb_funcall(self, rb_intern("initStatusLine"), 0);
    rb_funcall(self, rb_intern("initMenuBar"), 0);
    rb_funcall(self, rb_intern("initDeskTop"), 0);
    return self;
}

// The new method of ruby's "Application" class
VALUE
Tvision_Ruby::WrApplication::rb_new(VALUE application_class)
{
    // assert that application_class is derived from cTApplication
    VALUE ancestors = rb_funcall(application_class, rb_intern("ancestors"), 0);
    if (RTEST(rb_funcall(ancestors, rb_intern("include?"), 1,
                         Tvision_Ruby::WrApplication::cTApplication))) {
        VALUE          rb_app = rb_iv_get(Tvision_Ruby::mTvision,
                                          "@application");
        if (RTEST(rb_app)) {
            rb_raise(rb_eRuntimeError, "Only one Tvision application object "
                     "may be created in each ruby application.  There is "
                     "already a living Tvision application object: %s",
                     STR2CSTR(rb_inspect(rb_app)));
            return Qnil;
        }
        WrApplication * c_app = new WrApplication(application_class);
        rb_app = rb_iv_get(Tvision_Ruby::mTvision, "@application");
        if (DATA_PTR(rb_app) != c_app) {
            rb_raise(rb_eRuntimeError, "Bug in Tvision wrapper: could not "
                     "create application object.  Maybe two application "
                     "objects were created simultaneously in different "
                     "threads? File: %s, Line: %d", __FILE__, __LINE__);
            return Qnil;
        }
        return rb_app;
    }
    else {
        rb_raise(rb_eRuntimeError, "Bug in Tvision wrapper: Tvision::"
                 "Application::new called for a class object not derived "
                 "from Tvision::Application. File: %s, Line: %d",
                 __FILE__, __LINE__);
    }
    return Qnil;
}
VALUE
Tvision_Ruby::WrApplication::rb_initStatusLine(VALUE self)
{
    WrApplication * c_app;
    Data_Get_Struct(self, WrApplication, c_app);
    c_app->c_initStatusLine();
    return Qnil;
}
void
Tvision_Ruby::WrApplication::c_initStatusLine(void)
{
    statusLine = TApplication::initStatusLine(getExtent());
    insert(statusLine);
}

VALUE
Tvision_Ruby::WrApplication::rb_initMenuBar(VALUE self)
{
    WrApplication * c_app;
    Data_Get_Struct(self, WrApplication, c_app);
    c_app->c_initMenuBar();
    return Qnil;
}
void
Tvision_Ruby::WrApplication::c_initMenuBar(void)
{
    menuBar = TApplication::initMenuBar(getExtent());
    insert(menuBar);
}

VALUE
Tvision_Ruby::WrApplication::rb_initDeskTop(VALUE self)
{
    WrApplication * c_app;
    Data_Get_Struct(self, WrApplication, c_app);
    c_app->c_initDeskTop();
    return Qnil;
}
void
Tvision_Ruby::WrApplication::c_initDeskTop(void)
{
    deskTop = TApplication::initDeskTop(getExtent());
    insert(deskTop);
}

void
Tvision_Ruby::WrApplication::rb_mark(void*)
{
    // Not yet anything to mark
}
void
Tvision_Ruby::WrApplication::rb_free(void * c_app)
{
    TObject::destroy(reinterpret_cast<Tvision_Ruby::WrApplication*>(c_app));
}

void
Tvision_Ruby::WrApplication::init_wrapper(void)
{
    // define class Application in module Tvision
    Tvision_Ruby::WrApplication::cTApplication =
        rb_define_class_under(Tvision_Ruby::mTvision, "Application",
                              rb_cObject);

    // overwrite Application::new(). It will allocate a C++ TApplication
    rb_define_module_function(Tvision_Ruby::WrApplication::cTApplication,
                              "new",
                              reinterpret_cast<VALUE(*)(...)>
                              (&Tvision_Ruby::WrApplication::rb_new), 0);

    // define Application#initialize(), it may be overwritten by derived
    // classes
    rb_define_method(Tvision_Ruby::WrApplication::cTApplication,
                     "initialize",
                     reinterpret_cast<VALUE(*)(...)>
                     (&Tvision_Ruby::WrApplication::rb_initialize), 0);

    // Application#initStatusLine() is called from Application#initialize().
    // It will construct a statusline in the bottommost line of the screen
    rb_define_method(Tvision_Ruby::WrApplication::cTApplication,
                     "initStatusLine",
                     reinterpret_cast<VALUE(*)(...)>
                     (&Tvision_Ruby::WrApplication::rb_initStatusLine), 0);

    // Application#initMenuBar() is similarly called from
    // Application#initialize(), and will allocate a menubar in the topmost
    // line of the screen
    rb_define_method(Tvision_Ruby::WrApplication::cTApplication,
                     "initMenuBar",
                     reinterpret_cast<VALUE(*)(...)>
                     (&Tvision_Ruby::WrApplication::rb_initMenuBar), 0);

    // Application#initDeskTop() places a desktop between the menubar and the
    // statusline. It is also called from Application#initialize()
    rb_define_method(Tvision_Ruby::WrApplication::cTApplication,
                     "initDeskTop",
                     reinterpret_cast<VALUE(*)(...)>
                     (&Tvision_Ruby::WrApplication::rb_initDeskTop), 0);

    // Application is a singleton, disallow clone and dup.
    rb_funcall(Tvision_Ruby::WrApplication::cTApplication,
               rb_intern("private"), 2,
               rb_str_new2("clone"), rb_str_new2("dup"));
};
