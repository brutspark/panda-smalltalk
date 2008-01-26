/*
 * st-object.h
 *
 * Copyright (C) 2008 Vincent Geddes <vgeddes@gnome.org>
 *
 * This library is free software: you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation, either
 * version 3 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef __ST_OBJECT_H__
#define __ST_OBJECT_H__

#include <st-types.h>
#include <st-small-integer.h>
#include <st-utils.h>
#include <st-vtable.h>
#include <st-class.h>
#include <st-universe.h>
#include <glib.h>

st_oop st_object_new (st_oop klass);
st_oop st_object_new_arrayed (st_oop klass, st_smi size);

void st_object_initialize_header (st_oop object, st_oop klass);
void st_object_initialize_body (st_oop object, st_smi instance_size);

/* tag tests */
INLINE int st_object_tag (st_oop object);
INLINE bool st_object_is_mark (st_oop object);
INLINE bool st_object_is_heap (st_oop object);
INLINE bool st_object_is_smi (st_oop object);


INLINE st_oop st_object_class (st_oop object);
INLINE guint st_object_hash (st_oop object);
INLINE const STVTable *st_object_virtual (st_oop object);
INLINE bool st_object_equal (st_oop object, st_oop another);
INLINE bool st_object_verify (st_oop object);

/* type tests */
INLINE bool st_object_is_class (st_oop object);
INLINE bool st_object_is_metaclass (st_oop object);
INLINE bool st_object_is_association (st_oop object);
INLINE bool st_object_is_symbol (st_oop object);
INLINE bool st_object_is_compiled_method (st_oop object);
INLINE bool st_object_is_compiled_block (st_oop object);
INLINE bool st_object_is_block_closure (st_oop object);
INLINE bool st_object_is_method_context (st_oop object);
INLINE bool st_object_is_block_context (st_oop object);
INLINE bool st_object_is_arrayed (st_oop object);
INLINE bool st_object_is_array (st_oop object);
INLINE bool st_object_is_byte_array (st_oop object);

const STVTable *st_object_vtable (void);


/* inline definitions */

INLINE int
st_object_tag (st_oop object)
{
    return object & st_tag_mask;
}

INLINE bool
st_object_is_mark (st_oop object)
{
    return st_object_tag (object) == ST_MARK_TAG;
}

INLINE bool
st_object_is_heap (st_oop object)
{
    return st_object_tag (object) == ST_POINTER_TAG;
}

INLINE bool
st_object_is_smi (st_oop object)
{
    return st_object_tag (object) == ST_SMI_TAG;
}



INLINE st_oop
st_object_class (st_oop object)
{
    if (G_UNLIKELY (st_object_is_smi (object)))
	return st_smi_class;

    return st_heap_object_class (object);
}

INLINE const STVTable *
st_object_virtual (st_oop object)
{
    if (G_UNLIKELY (st_object_is_smi (object)))
	return st_smi_vtable ();

    return ST_CLASS_VTABLE (st_object_class (object));
}

INLINE bool
st_object_equal (st_oop object, st_oop another)
{
    return st_object_virtual (object)->equal (object, another);
}

INLINE guint
st_object_hash (st_oop object)
{
    return st_object_virtual (object)->hash (object);
}


INLINE bool
st_object_verify (st_oop object)
{
    return st_object_virtual (object)->verify (object);
}

INLINE char *
st_object_describe (st_oop object)
{
    return st_object_virtual (object)->describe (object);
}

/* type tests
 *
 * We delegate the test to the vtable methods stored in object's class object
 *
 */

INLINE bool
st_object_is_class (st_oop object)
{
    return st_object_is_heap (object) && st_object_virtual (object)->is_class ();
}

INLINE bool
st_object_is_metaclass (st_oop object)
{
    return st_object_is_heap (object) && st_object_virtual (object)->is_metaclass ();
}

INLINE bool
st_object_is_association (st_oop object)
{
    return st_object_is_heap (object) && st_object_virtual (object)->is_association ();
}

INLINE bool
st_object_is_symbol (st_oop object)
{
    return st_object_is_heap (object) && st_object_virtual (object)->is_symbol ();
}

INLINE bool
st_object_is_float (st_oop object)
{
    return st_object_is_heap (object) && st_object_virtual (object)->is_float ();
}

INLINE bool
st_object_is_dictionary (st_oop object)
{
    return st_object_is_heap (object) && st_object_virtual (object)->is_dictionary ();
}

INLINE bool
st_object_is_set (st_oop object)
{
    return st_object_is_heap (object) && st_object_virtual (object)->is_set ();
}

INLINE bool
st_object_is_compiled_method (st_oop object)
{
    return st_object_is_heap (object) && st_object_virtual (object)->is_compiled_method ();
}

INLINE bool
st_object_is_compiled_block (st_oop object)
{
    return st_object_is_heap (object) && st_object_virtual (object)->is_compiled_block ();
}

INLINE bool
st_object_is_block_closure (st_oop object)
{
    return st_object_is_heap (object) && st_object_virtual (object)->is_block_closure ();
}

INLINE bool
st_object_is_method_context (st_oop object)
{
    return st_object_is_heap (object) && st_object_virtual (object)->is_method_context ();
}

INLINE bool
st_object_is_block_context (st_oop object)
{
    return st_object_is_heap (object) && st_object_virtual (object)->is_block_context ();
}

INLINE bool
st_object_is_arrayed (st_oop object)
{
    return st_object_is_heap (object) && st_object_virtual (object)->is_arrayed ();
}

INLINE bool
st_object_is_array (st_oop object)
{
    return st_object_is_heap (object) && st_object_virtual (object)->is_array ();
}

INLINE bool
st_object_is_byte_array (st_oop object)
{
    return st_object_is_heap (object) && st_object_virtual (object)->is_byte_array ();
}

#endif /* __ST_OBJECT_H__ */
