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

#include "tvision.hh"

// using namespace Tvision_Ruby;

VALUE Tvision_Ruby::mTvision = 0;
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

// The new method of ruby's application class
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
Tvision_Ruby::WrApplication::init_wrapper(void)
{
    Tvision_Ruby::WrApplication::cTApplication =
        rb_define_class_under(mTvision, "TApplication", rb_cObject);
    rb_define_module_function(Tvision_Ruby::WrApplication::cTApplication,
                              "new",
                              reinterpret_cast<VALUE(*)(...)>
                              (&Tvision_Ruby::WrApplication::rb_new), 0);
    rb_define_method(Tvision_Ruby::WrApplication::cTApplication,
                     "initialize",
                     reinterpret_cast<VALUE(*)(...)>
                     (&Tvision_Ruby::WrApplication::rb_initialize), 0);
    rb_define_method(Tvision_Ruby::WrApplication::cTApplication,
                     "initStatusLine",
                     reinterpret_cast<VALUE(*)(...)>
                     (&Tvision_Ruby::WrApplication::rb_initStatusLine), 0);
    rb_define_method(Tvision_Ruby::WrApplication::cTApplication,
                     "initMenuBar",
                     reinterpret_cast<VALUE(*)(...)>
                     (&Tvision_Ruby::WrApplication::rb_initMenuBar), 0);
    rb_define_method(Tvision_Ruby::WrApplication::cTApplication,
                     "initDeskTop",
                     reinterpret_cast<VALUE(*)(...)>
                     (&Tvision_Ruby::WrApplication::rb_initDeskTop), 0);
};

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

Tvision_Ruby::WrStatusItem::WrStatusItem(VALUE rb_statusitem)
    : TStatusItem(STR2CSTR(rb_iv_get(rb_statusitem, "@text")),
                  NUM2INT(rb_iv_get(rb_statusitem, "@key")),
                  NUM2INT(rb_iv_get(rb_statusitem, "@cmd")),
                  0)
{
    VALUE rb_next = rb_iv_get(rb_statusitem, "@next");
    if (rb_next != Qnil)
        next = new Tvision_Ruby::WrStatusItem(rb_next);
}

extern "C" void
Init_tvision(void)
{
    Tvision_Ruby::mTvision = rb_define_module("Tvision");
    rb_iv_set(Tvision_Ruby::mTvision, "@application", Qnil);
    Tvision_Ruby::WrApplication::init_wrapper();
}
