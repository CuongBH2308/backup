"""
python scope esstential:
http://www.saltycrane.com/blog/2008/01/python-variable-scope-notes/
1. Not like java/c++, if/else, try/except won't create a new scope
2. Only function create a new scope
3. You can assign to a global variable in an inner scope by lifting: global gvar
4. You can't assign to a outer variable by lifting as lifting only lift to global scope
5. A workaround is to define the outer variable as: func.out_var
"""
def if_else_not_scope():
    var1 = ''
    if True:
        var1 = 'assign to var1 in "if" does not create a new variable'
    print var1
    
    if True:
        var2 = 'variable defined in "if" is also valid outside it'
    print var2
    
if_else_not_scope()

def try_except_not_scope():
    var1 = ''
    try:
        var1 = 'assign to var1 in "try" does not create a new variable'
    except:
        pass
    print var1
    
    try:
        var2 = 'variable defined in "try" is also valid outside it'
    finally:
        print var2
    print var2

try_except_not_scope()

gvar1 = 'global variable can not be assign directly in a function'
def not_assign_global_varialbe():
    gvar1 = 'create a new gvar1 in this scope, rather than change the global one'
not_assign_global_varialbe()
print gvar1

def assign_global_varialbe():
    global gvar1
    gvar1 = 'create a new gvar1 in this scope, rather than change the global one'
assign_global_varialbe()
print gvar1

def how_to_assign_out_variable():
    how_to_assign_out_variable.out_var = ''
    def inner_func():
        how_to_assign_out_variable.out_var = 'change out_var'
    inner_func()
    print how_to_assign_out_variable.out_var
how_to_assign_out_variable()

    
    