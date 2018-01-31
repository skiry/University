'''
Created on 4 dec. 2017

@author: Skiry
'''
from os import fdopen

class UndoController:
    '''
    class for undo/redo 
    '''


    def __init__(self):
        '''
        Constructor
        '''
        self._actions = []
        self._index = -1
        
    def recordOperation(self,op):
        self._actions.append(op)
        self._index += 1
        
    def undo(self):
        if self._index == -1:
            return False
        operation = self._actions[self._index]
        self._index -= 1
        operation.undo()
        return True
    
    def redo(self):
        if self._index == len(self._actions) -1:
            return False
        self._index += 1
        operation = self._actions[self._index]
        operation.redo()
        return True
    
class FunctionCall:
    '''
    class for function calling
    input : action and parameters 
    '''
    def __init__(self,action,*parameters):
        self._action = action
        self._params = parameters
    
    def call(self):
        self._action(*self._params)
    
class Operation:
    '''
    class for calling the above functions with undo and redo
    '''
    def __init__(self,functionDo,functionUndo):
        self._functionDo = functionDo
        self._functionUndo = functionUndo
        
    def undo(self):
        self._functionUndo.call()
        
    def redo(self):
        self._functionDo.call()
        
class CascadedOperations:
    def __init__(self):
        self._actions = []
        
    def add(self,action):
        self._actions.append(action)
    
    def undo(self):
        for i in range(len(self._actions) -1, -1, -1):
            self._actions[i].undo()
        
    def redo(self):
        for i in range(len(self._actions) -1, -1, -1):
            self._actions[i].redo()
        
        
        
        
        
        
        
        
        
class UndoCtrl:
    def __init__(self):
        self._list = []
        self._index = -1
    def recordOp(self,op):
        self._list.append(op)
        self._index += 1
        
    def undo(self):
        #conditions 
        self._list[self._index].undo()
        self._index -=1
        return True
    
    def redo(self):
        #conditions 
        self._index +=1
        self._list[self._index].redo()
        return True
    
class Operaitionn:
    def __init__(self,fDO,fREDO):
        self._do = fDO
        self._redo = fREDO
        
    def undo(self):
        self._do.call()
        
    def redo(self):
        self._redo.call()
        
class FunctionCall:
    def __init__(self,action,*params):
        self._action = action
        self._params = params
        
    def call(self):
        self._action(*self._params)
        