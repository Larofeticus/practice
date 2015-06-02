def isfloat(v): #i'm shocked there isn't something built in to do this
    try:
        float(v)
        return True
    except:
        return False

def rpn(ops):
    if(len(ops) == 0):
        return ['empty operations list']
    
    if(len(ops) == 1):
        #check if ops are invalid because only an operation remains
        if(ops[0] in ['+','-','/','*']):
            return ['invalid operations list 1']
        return ops #either an error string or a single number
    
    #two items regardless of kind must be invalid list
    if(len(ops) == 2):
        return ['invalid operations list 2']

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
                out = a / b
            #splice a new list with the performed operation replaced with it's output
            outlist = [out]
            if(i>0):
                outlist = ops[:i] + outlist
            if(i < len(ops)-2):
                outlist = outlist + ops[i+3:]
            return rpn(outlist);
    #if the for loop found no valid operations
    return ['error invalid operations list 3']


print(rpn(['5', '6.2', '-4', '-', '+', '10.6', '*']))
