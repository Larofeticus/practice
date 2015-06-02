def isfloat(v): #i'm shocked there isn't something built in to do this
    try:
        float(v)
        return True
    except:
        return False

#exception classes
class EmptyOperationsList(Exception): pass
class InvalidOperationsList(Exception): pass
class DivideByZero(Exception): pass

def rpn(ops):
    if(len(ops) == 0):
        raise EmptyOperationsList()
    
    if(len(ops) == 1):
        #check if ops are invalid because the last item
        #isn't a number
        if(not isfloat(ops[0])): raise InvalidOperationsList()
        return ops[0]

    #two items regardless of kind must be invalid list
    if(len(ops) == 2): raise InvalidOperationsList()

    #now search ops for the case of 2 digits followed by an operation
    for i in range(0, len(ops)-2):
        a = ops[i]
        b = ops[i+1]
        c = ops[i+2]
        if(isfloat(a) and isfloat(b) and c in ['+', '-', '*','/']):
            a = float(a)
            b = float(b)
            out = 0;
            if(c == '+'):
                out = a + b
            if(c == '-'):
                out = a - b
            if(c == '*'):
                out = a * b
            if(c == '/'):
                if(b == 0): raise DivideByZero()
                out = a / b
            #splice a new list with the performed operation replaced with it's output
            return rpn(ops[:i] + [str(out)] + ops[i+3:]);
    #if the for loop found no valid operations to perform
    raise InvalidOperationsList()

print(rpn(['5', '6.2', '-4', '-', '+', '10.6', '*']))
print(rpn(['5', '6.2', '-4', '-', '+', '10.6', '*', '0.0', '/']))
