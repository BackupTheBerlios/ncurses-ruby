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

// $Id: application.hh,v 1.6 2002/03/04 07:09:54 t-peters Exp $

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

        static void
        rb_mark(void*);
        static void
        rb_free(void*);
        
        // This function registers the necessary Application methods with ruby.
        static void
        init_wrapper(void);

        static VALUE
        rb_suspend(VALUE self);
        static VALUE
        rb_resume(VALUE self);

        // class method that returns the current instance if one exists, or nil
        static VALUE
        rb_application(VALUE);

        static VALUE
        wrap(TApplication & c_app);
        static WrApplication &
        unwrap(VALUE rb_application);

        // wrapped from TProgram:
        static VALUE rb_idle(VALUE rb_application);
        virtual void idle();
        static VALUE sleep_time;

        virtual void initScreen();
        static VALUE rb_initScreen(VALUE rb_application);

        virtual void outOfMemory();
        static VALUE rb_outOfMemory(VALUE rb_application);

        virtual void getEvent(TEvent& event);
        static VALUE rb_getEvent(VALUE rb_application, VALUE rb_event);

        // delegate call from framework to virtual method to ruby method
        virtual void run();

        // default ruby run method calls TApplication::run
        static VALUE rb_run(VALUE rb_application);

        // methods for getting and setting the class variable statusLine
        static VALUE rb_get_statusLine(VALUE);
        static VALUE rb_set_statusLine(VALUE, VALUE rb_statusLine);

        // things to wrap from TProgram:
        /*
    virtual TPalette& getPalette() const;
    virtual void handleEvent(TEvent& event);
    virtual void putEvent( TEvent& event );
    void setScreenMode( ushort mode, char *comm=0 );
    TView *validView( TView *p );
    virtual void shutDown();

    // This is a very nasty function only needed if you call
    // TScreen::resume bypassing TProgram::resume. In this case
    // the buffers could get unsychronized. This is done by
    // RHIDE.
    void syncScreenBuffer();
    //   { buffer = TScreen::screenBuffer; }

    static TMenuBar * menuBar;
    static TDeskTop * deskTop;
    static int appPalette;

    // Added by SET
    static clock_t lastIdleClock; // That's the value of clock in the moment
                                  // when idle is called. Used to accumulate
                                  // in the inIdleTime var
    static clock_t inIdleTime;  // That keeps track of the number of clocks
                                // elapsed since we entered in idle
    static Boolean inIdle;      // Indicates that we are in idle, a mouse or
                                // keyboard event resets it
    // I think that sometimes we can have a long elapsed time without events
    // so I provide a way to reset it
    static void resetIdleTime() { inIdle=False; };

protected:

    static TEvent pending;

private:

//    static const char * exitText;
 */
    };
}
#endif
