/*
 * st-descriptor.h
 *
 * Copyright (C) 2008 Vincent Geddes
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
*/

#ifndef __ST_DESCRIPTOR_H__
#define __ST_DESCRIPTOR_H__

#include <st-types.h>
#include <glib.h>

typedef enum
{
    ST_FORMAT_OBJECT,
    ST_FORMAT_FLOAT,
    ST_FORMAT_LARGE_INTEGER,
    ST_FORMAT_ARRAY,
    ST_FORMAT_BYTE_ARRAY,
    ST_FORMAT_FLOAT_ARRAY,
    ST_FORMAT_INTEGER_ARRAY,
    ST_FORMAT_CONTEXT,

    ST_NUM_FORMATS
} STFormat;

typedef struct
{
    STFormat format;

    /* allocation */
    st_oop (*allocate) (st_oop klass);

    st_oop (*allocate_arrayed) (st_oop klass, st_smi size);
    
} STDescriptor;

extern const STDescriptor *st_descriptors[ST_NUM_FORMATS];

#endif /* __ST_VTABLE_H__ */
