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

// $Id: application.cc,v 1.8 2002/03/04 07:09:40 t-peters Exp $

#include "application.hh"
#include "group.hh"
#include "object.hh"
#include "event.hh"
#include "statusline.hh"

VALUE Tvision_Ruby::WrApplication::cTApplication = 0;
VALUE Tvision_Ruby::WrApplication::sleep_time    = 0;

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
    rb_cv_set(Tvision_Ruby::WrApplication::cTApplication, "@@application_id",
              rb_funcall(self, rb_intern("__id__"), 0));
    // we only register it's id to enable Garbage Collection of an unused
    // Application object

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
        VALUE  rb_app = Tvision_Ruby::WrApplication::
            rb_application(Tvision_Ruby::WrApplication::cTApplication);
        if (RTEST(rb_app)) {
            rb_raise(rb_eRuntimeError, "Only one Tvision application object "
                     "may be created in each ruby application.  There is "
                     "already a living Tvision application object: %s",
                     STR2CSTR(rb_inspect(rb_app)));
            return Qnil;
        }
        // create a new C++ WrApplication object. It will be registered in the
        // @@application_id class variable of the ruby class
        // Tvision::Application
        WrApplication * c_app = new WrApplication(application_class);

        // Ensure the Application object is registered in the map that lists
        // the ruby object corresponding to a c++ object. This will call
        // WrApplication::wrap now, which will call delegate the call to
        // WrApplication::rb_application
        rb_app = Tvision_Ruby::WrObject::wrap(*c_app);

        // Ensure that we have only one Application Object
        if (TYPE(rb_app) != T_DATA || DATA_PTR(rb_app) != c_app) {
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
    TApplication * c_app = &Tvision_Ruby::WrApplication::unwrap(self);
    TApplication::statusLine =
        TApplication::initStatusLine(c_app->getExtent());
    c_app->insert(statusLine);
    return Qnil;
}

VALUE
Tvision_Ruby::WrApplication::rb_initMenuBar(VALUE self)
{
    TApplication * c_app = &Tvision_Ruby::WrApplication::unwrap(self);
    TApplication::menuBar = TApplication::initMenuBar(c_app->getExtent());
    c_app->insert(menuBar);
    return Qnil;
}

VALUE
Tvision_Ruby::WrApplication::rb_initDeskTop(VALUE self)
{
    TApplication * c_app = &Tvision_Ruby::WrApplication::unwrap(self);
    TApplication::deskTop = TApplication::initDeskTop(c_app->getExtent());
    c_app->insert(deskTop);
    return Qnil;
}

void
Tvision_Ruby::WrApplication::rb_mark(void * c_app)
{
    Tvision_Ruby::WrGroup::rb_mark(c_app);
}
void
Tvision_Ruby::WrApplication::rb_free(void * c_app)
{
    TObject::destroy(reinterpret_cast<Tvision_Ruby::WrApplication*>(c_app));
}


VALUE
Tvision_Ruby::WrApplication::rb_suspend(VALUE self)
{
    TApplication * c_app = &Tvision_Ruby::WrApplication::unwrap(self);
    static_cast<WrApplication *>(c_app)->suspend();
    return self;
}
VALUE
Tvision_Ruby::WrApplication::rb_resume(VALUE self)
{
    TApplication * c_app = &Tvision_Ruby::WrApplication::unwrap(self);
    static_cast<WrApplication *>(c_app)->resume();
    return self;
}

void
Tvision_Ruby::WrApplication::init_wrapper(void)
{
    // define class Application in module Tvision
    Tvision_Ruby::WrApplication::cTApplication =
        rb_define_class_under(Tvision_Ruby::mTvision, "Application",
                              Tvision_Ruby::WrGroup::cTGroup);

    // set a class variable in this class to the id of the currently living
    // Application object
    rb_define_class_variable(Tvision_Ruby::WrApplication::cTApplication,
                             "@@application_id", Qnil);

    // set a class constant in this class to the prefered sleeping time
    rb_define_const(Tvision_Ruby::WrApplication::cTApplication,
                    "SLEEPING_TIME",
                    Tvision_Ruby::WrApplication::sleep_time =
                    rb_float_new(0.1));
    
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

    // Application#suspend() temporarily exits the ncurses screen usage mode.
    // Useful for shelling out.
    rb_define_method(Tvision_Ruby::WrApplication::cTApplication,
                     "suspend",
                     reinterpret_cast<VALUE(*)(...)>
                     (&Tvision_Ruby::WrApplication::rb_suspend), 0);
    
    // Application#resume() restores the TUI screen after a call to suspend()
    rb_define_method(Tvision_Ruby::WrApplication::cTApplication,
                     "resume",
                     reinterpret_cast<VALUE(*)(...)>
                     (&Tvision_Ruby::WrApplication::rb_resume), 0);

    // Application::application will give return the living Application object
    // if one exists currently. Otherwise, nil will be returned.
    rb_define_module_function(Tvision_Ruby::WrApplication::cTApplication,
                              "application",
                              reinterpret_cast<VALUE(*)(...)>
                              (&Tvision_Ruby::WrApplication::rb_application),
                              0);

    // we implement our own CPU release in WrApplication::idle
    TProgram::doNotReleaseCPU = 1;

    // Application#idle will be called from the framework as a part of the main
    // loop. This method is supposed to sleep for a short time.
    rb_define_method(Tvision_Ruby::WrApplication::cTApplication, "idle",
                     reinterpret_cast<VALUE(*)(...)>
                     (&Tvision_Ruby::WrApplication::rb_idle), 0);

    // Application#initScreen
    rb_define_method(Tvision_Ruby::WrApplication::cTApplication, "initScreen",
                     reinterpret_cast<VALUE(*)(...)>
                     (&Tvision_Ruby::WrApplication::rb_initScreen), 0);

    // Application#outOfMemory
    rb_define_method(Tvision_Ruby::WrApplication::cTApplication, "outOfMemory",
                     reinterpret_cast<VALUE(*)(...)>
                     (&Tvision_Ruby::WrApplication::rb_outOfMemory), 0);

    // Application#getEvent
    rb_define_method(Tvision_Ruby::WrApplication::cTApplication, "getEvent",
                     reinterpret_cast<VALUE(*)(...)>
                     (&Tvision_Ruby::WrApplication::rb_getEvent), 1);

    
    // Application#run
    rb_define_method(Tvision_Ruby::WrApplication::cTApplication, "run",
                     reinterpret_cast<VALUE(*)(...)>
                     (&Tvision_Ruby::WrApplication::rb_run), 0);

    // Application::statusLine=
    rb_define_module_function(Tvision_Ruby::WrApplication::cTApplication,
                              "statusLine=",
                              reinterpret_cast<VALUE(*)(...)>
                              (&Tvision_Ruby::WrApplication::
                               rb_set_statusLine), 1);
    // Application::statusLine
    rb_define_module_function(Tvision_Ruby::WrApplication::cTApplication,
                              "statusLine",
                              reinterpret_cast<VALUE(*)(...)>
                              (&Tvision_Ruby::WrApplication::
                               rb_get_statusLine), 0);
};

static VALUE call_id2ref(VALUE id) {
    VALUE rb_mObjectSpace = rb_const_get(rb_cObject, rb_intern("ObjectSpace"));
    VALUE app = rb_funcall(rb_mObjectSpace, rb_intern("_id2ref"), 1, id);
    return app;
}
VALUE
Tvision_Ruby::WrApplication::rb_application(VALUE)
{
    int exception_raised = 0;
    VALUE id = rb_cv_get(Tvision_Ruby::WrApplication::cTApplication,
                         "@@application_id");
    if (id == Qnil)
        return Qnil;
    VALUE app = rb_protect(reinterpret_cast<VALUE(*)(...)>(&call_id2ref), id,
                           &exception_raised);
    if (exception_raised) {
        rb_cv_set(Tvision_Ruby::WrApplication::cTApplication,
                  "@@application_id", Qnil);
        return Qnil;
    }
    return app;
}
VALUE
Tvision_Ruby::WrApplication::wrap(TApplication & c_app)
{
    VALUE rb_app = Tvision_Ruby::WrApplication::
        rb_application(Tvision_Ruby::WrApplication::cTApplication);
    if (rb_app == Qnil) {
        rb_raise(rb_eRuntimeError, "C++:Tvision_Ruby::WrApplication::wrap: "
                 "cannot wrap TApplication object outside "
                 "Ruby:Tvision::Application::new constructor. File: %s, "
                 "Line: %d", __FILE__, __LINE__);
        return Qnil;
    }
    if (&Tvision_Ruby::WrApplication::unwrap(rb_app) != &c_app) {
        rb_raise(rb_eRuntimeError, "C++:Tvision_Ruby::WrApplication::wrap: "
                 "cannot wrap additional TApplication object, and outside "
                 "Ruby:Tvision::Application::new constructor. File: %s, "
                 "Line: %d", __FILE__, __LINE__);
        return Qnil;
    }
    return rb_app;
}


Tvision_Ruby::WrApplication &
Tvision_Ruby::WrApplication::unwrap(VALUE rb_application)
{
    Tvision_Ruby::WrApplication * c_application =
        dynamic_cast<Tvision_Ruby::WrApplication *>
        (&Tvision_Ruby::WrGroup::unwrap(rb_application));
    if (c_application) {
        return *c_application;
    }
    rb_raise(rb_eRuntimeError, "C++:Tvision_Ruby::WrApplication::unwrap: "
             "VALUE %x does not wrap a WrApplication. File: %s, Line: %d",
             rb_application, __FILE__, __LINE__);
    return *c_application;
}

VALUE
Tvision_Ruby::WrApplication::rb_idle(VALUE rb_application)
{
    TProgram::doNotReleaseCPU = 1;
    Tvision_Ruby::WrApplication::unwrap(rb_application).TApplication::idle();

    // sleep inside the ruby interpreter to allow internal multithreading
    rb_funcall(rb_mKernel, rb_intern("sleep"), 1,
               Tvision_Ruby::WrApplication::sleep_time);
    return Qnil;
}
void
Tvision_Ruby::WrApplication::idle()
{
    // delegate virtual function call to the corresponding ruby method
    rb_funcall(Tvision_Ruby::WrApplication::wrap(*this), rb_intern("idle"), 0);
}


void
Tvision_Ruby::WrApplication::initScreen()
{
    // delegate virtual function call to the corresponding ruby method
    rb_funcall(Tvision_Ruby::WrApplication::wrap(*this),
               rb_intern("initScreen"), 0);
}
VALUE
Tvision_Ruby::WrApplication::rb_initScreen(VALUE rb_application)
{
    Tvision_Ruby::WrApplication::
        unwrap(rb_application).TApplication::initScreen();
    return Qnil;
}

void
Tvision_Ruby::WrApplication::outOfMemory()
{
    // delegate virtual function call to the corresponding ruby method
    rb_funcall(Tvision_Ruby::WrApplication::wrap(*this),
               rb_intern("outOfMemory"), 0);
}
VALUE
Tvision_Ruby::WrApplication::rb_outOfMemory(VALUE rb_application)
{
    Tvision_Ruby::WrApplication::unwrap(rb_application).outOfMemory();
    return Qnil;
}

void
Tvision_Ruby::WrApplication::getEvent(TEvent& c_event)
{
    VALUE rb_event = Tvision_Ruby::WrEvent::wrap(c_event);
    VALUE rb_app   = Tvision_Ruby::WrApplication::wrap(*this);
    rb_funcall(rb_app, rb_intern("getEvent"), 1, rb_event);
    c_event = Tvision_Ruby::WrEvent::unwrap(rb_event);
}

VALUE
Tvision_Ruby::WrApplication::rb_getEvent(VALUE rb_application, VALUE rb_event)
{
    Tvision_Ruby::WrApplication::
        unwrap(rb_application).TApplication::
        getEvent(Tvision_Ruby::WrEvent::unwrap(rb_event));
    return Qnil;
}

void
Tvision_Ruby::WrApplication::run()
{
    VALUE rb_app   = Tvision_Ruby::WrApplication::wrap(*this);
    rb_funcall(rb_app, rb_intern("run"), 0);
}
VALUE
Tvision_Ruby::WrApplication::rb_run(VALUE rb_application)
{
    TApplication & c_app = Tvision_Ruby::WrApplication::unwrap(rb_application);
    c_app.TApplication::run();
}

VALUE
Tvision_Ruby::WrApplication::rb_get_statusLine(VALUE)
{
    if (TApplication::statusLine) {
        return Tvision_Ruby::WrObject::wrap(*TApplication::statusLine);
    }
    return Qnil;
}
VALUE
Tvision_Ruby::WrApplication::rb_set_statusLine(VALUE, VALUE rb_statusLine)
{
    if (rb_statusLine == Qnil) {
        TApplication::statusLine = 0; return Qnil;
    }
    TStatusLine & c_statusline =
        Tvision_Ruby::WrStatusLine::unwrap(rb_statusLine);
    TApplication::statusLine = &c_statusline;
    return Tvision_Ruby::WrApplication::rb_get_statusLine(0);
}

