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

#include "object.hh"
#include "view.hh"
#include <cassert>

VALUE Tvision_Ruby::WrObject::cTObject = Qnil;
VALUE Tvision_Ruby::WrObject::mObjectSpace = Qnil;
std::map<void*,VALUE> * Tvision_Ruby::WrObject::ObjectHash = 0;

void
Tvision_Ruby::WrObject::init_wrapper(void)
{
    Tvision_Ruby::WrObject::ObjectHash = new std::map<void*,VALUE>;
    
    // define class Application in module Tvision
    Tvision_Ruby::WrObject::cTObject =
        rb_define_class_under(Tvision_Ruby::mTvision, "Object",
                              rb_cObject);

    // store the value of module ObjectSpace
    Tvision_Ruby::WrObject::mObjectSpace =
        rb_const_get(rb_cObject, rb_intern("ObjectSpace"));

    rb_funcall(Tvision_Ruby::WrObject::cTObject, rb_intern("private"), 3,
               rb_str_new2("initialize"),  rb_str_new2("clone"),
               rb_str_new2("dup"));

    Tvision_Ruby::WrView::init_wrapper();
}

VALUE
Tvision_Ruby::WrObject::rb_destroy(VALUE, VALUE rb_object)
{
    rb_funcall(rb_object, rb_intern("shutDown"), 0);
    return Qnil;
}

VALUE
Tvision_Ruby::WrObject::rb_shutDown(VALUE rb_object)
{
    TObject & c_object = Tvision_Ruby::WrObject::unwrap(rb_object);
    rb_iv_set(rb_object, "@isShutDown", Qtrue);
    c_object.shutDown();
    return Qnil;
}

static VALUE call_id2ref(VALUE id) {
    VALUE rb_object = rb_funcall(Tvision_Ruby::WrObject::mObjectSpace,
                                 rb_intern("_id2ref"), 1, id);
    return rb_object;
}

VALUE
Tvision_Ruby::WrObject::wrap(TObject & c_object)
{
    void * c_pointer = &c_object;

    if (c_pointer == 0) {
        return Qnil;
    }
    VALUE rb_object = Qnil;

    // try to find a wrapper for this TObject in the wrapper database
    std::map<void*,VALUE>::iterator object_iterator =
        Tvision_Ruby::WrObject::ObjectHash->find(c_pointer);
    if (object_iterator != Tvision_Ruby::WrObject::ObjectHash->end()) {
        // There is an entry in the wrapper database. Check if it corresponds
        // to a living object
        rb_object = (*object_iterator).second;

        int exception_raised = 0;
        VALUE rb_object2 =
            rb_protect(reinterpret_cast<VALUE(*)(...)>(&call_id2ref),
                       INT2NUM(rb_object),
                       &exception_raised);
        if (exception_raised == 0) {
            assert(rb_object == rb_object2);
            return rb_object;
        }
        // else
        // the wrapper object must have been garbage collected. allocate a new
        // one.
        Tvision_Ruby::WrObject::ObjectHash->erase(object_iterator);
        rb_object = Qnil;
    }
    if (TView * c_view = dynamic_cast<TView*>(&c_object)) {
        rb_object = Tvision_Ruby::WrView::wrap(*c_view);
    }
    if (rb_object != Qnil) {
        Tvision_Ruby::WrObject::ObjectHash->
            insert(std::pair<void*,VALUE>(c_pointer, rb_object));
    }
    else {
        rb_raise(rb_eRuntimeError, "C++:Tvision_Ruby::WrObject::wrap: could "
                 "not wrap object at %p. File: %s, Line: %d", &c_object,
                 __FILE__, __LINE__);
    }
    return rb_object;
}

TObject &
Tvision_Ruby::WrObject::unwrap(VALUE rb_object)
{
    TObject * c_object;
    Data_Get_Struct(rb_object, TObject, c_object);
    return *c_object;
}

void
Tvision_Ruby::WrObject::set_dependency(VALUE object1, VALUE object2)
{
    VALUE iv1 = rb_iv_get(object1, "@tvision_dependency");
    if (iv1 == Qnil) {
        iv1 = rb_ary_new();
    }
    rb_ary_push(iv1, object2);
    rb_iv_set(object1, "@tvision_dependency", iv1);
    
    VALUE iv2 = rb_iv_get(object2, "@tvision_dependency");
    if (iv2 == Qnil) {
        iv2 = rb_ary_new();
    }
    rb_ary_push(iv2, object1);
    rb_iv_set(object2, "@tvision_dependency", iv2);
}

void
Tvision_Ruby::WrObject::unset_dependency(VALUE object1, VALUE object2)
{
    VALUE iv1 = rb_iv_get(object1, "@tvision_dependency");
    if (iv1 == Qnil) {
        iv1 = rb_ary_new();
    }
    rb_funcall(iv1, rb_intern("delete"), 1, object2);
    rb_iv_set(object1, "@tvision_dependency", iv1);
    
    VALUE iv2 = rb_iv_get(object2, "@tvision_dependency");
    if (iv2 == Qnil) {
        iv2 = rb_ary_new();
    }
    rb_funcall(iv2, rb_intern("delete"), 1, object1);
    rb_iv_set(object2, "@tvision_dependency", iv2);
}
