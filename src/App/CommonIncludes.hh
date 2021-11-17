//
// Created by fleur on 14/11/2021.
//

#ifndef GOLPHOOK_FUN_COMMONINCLUDES_HH
#define GOLPHOOK_FUN_COMMONINCLUDES_HH


#include "iostream"
#include "string"
#include "sstream"
#include "format"
#include "chrono"
#include "vector"
#include "thread"

#include "Windows.h"

#include "plog/Log.h"
#include "plog/Formatters/TxtFormatter.h"
#include "plog/Appenders/ColorConsoleAppender.h"

#define NK_INCLUDE_FIXED_TYPES
#define NK_INCLUDE_STANDARD_IO
#define NK_INCLUDE_STANDARD_VARARGS
#define NK_INCLUDE_DEFAULT_ALLOCATOR
#define NK_INCLUDE_VERTEX_BUFFER_OUTPUT
#define NK_INCLUDE_FONT_BAKING
#define NK_INCLUDE_DEFAULT_FONT
#include "nuklear.h"
#include "nuklear_d3d9.h"

struct nk_context;


#endif //GOLPHOOK_FUN_COMMONINCLUDES_HH
