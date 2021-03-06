#include "aqcc.h"

Type *new_type(int kind, int nbytes)
{
    Type *type = safe_malloc(sizeof(Type));
    type->kind = kind;
    type->nbytes = nbytes;
    type->is_static = type->is_extern = 0;
    return type;
}

void move_static_extern_specifier(Type *src, Type *dst)
{
    if (src->is_static) dst->is_static = 1;
    if (src->is_extern) dst->is_extern = 1;
    src->is_static = src->is_extern = 0;
}

Type *type_int()
{
    static Type *type = NULL;
    if (type == NULL) {
        type = new_type(TY_INT, 4);
    }

    return type;
}

Type *type_char()
{
    static Type *type = NULL;
    if (type == NULL) {
        type = new_type(TY_CHAR, 1);
    }

    return type;
}

Type *type_void()
{
    static Type *type = NULL;
    if (type == NULL) {
        type = new_type(TY_VOID, -1);
    }
    return type;
}

Type *new_pointer_type(Type *src)
{
    Type *type = new_type(TY_PTR, 8);
    type->ptr_of = src;
    return type;
}

Type *new_array_type(Type *src, int len)
{
    Type *type = new_type(TY_ARY, src->nbytes * len);
    type->ary_of = src;
    type->len = len;
    return type;
}

Type *new_struct_or_union_type(int kind, char *stname, Vector *decls)
{
    Type *type = new_type(kind, -1);
    type->stname = stname;
    type->members = NULL;
    type->decls = decls;
    return type;
}

Type *new_typedef_type(char *typedef_name)
{
    Type *type = new_type(TY_TYPEDEF, -1);
    type->typedef_name = typedef_name;
    return type;
}

Type *new_enum_type(char *name, Vector *list)
{
    Type *type = new_type(TY_ENUM, -1);
    type->enname = name;
    type->enum_list = list;
    return type;
}

Type *new_static_type(Type *src)
{
    Type *type = safe_malloc(sizeof(Type));
    memcpy(type, src, sizeof(Type));
    type->is_static = 1;
    return type;
}

Type *new_extern_type(Type *src)
{
    Type *type = safe_malloc(sizeof(Type));
    memcpy(type, src, sizeof(Type));
    type->is_extern = 1;
    return type;
}
