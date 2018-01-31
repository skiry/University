'''
Created on 7 dec. 2017

@author: Skiry
'''
from datetime import date,time
from _datetime import datetime
class MyData:
    '''
    My own data structure
    '''


    def __init__(self):
        '''
        Constructor
        '''
        self.__dict = {}
        self._index = 0
        
    def __setitem__(self,key,value):
        if key not in self.__dict:
            self.__dict[key] = [value]
        else:
            self.__dict[key].append(value)
            
    def __getitem__(self,key):
        return self.__dict[key]
    
    def __eq__(self, myL):
        return self.__dict == myL
    
    def __delitem__(self,key):
        del self.__dict[key]
        
    def __next__(self):
        try:
           item = self.__dict[list(self.__dict)[self._index]]
        except IndexError:
            self._index = 0
            raise StopIteration()
        self._index += 1
        return item
    
    def urmEl(self):
        try:
           item = self.__dict[list(self.__dict)[self._index+1]]
        except IndexError:
            self._index = 0
            raise StopIteration()
        return item
    
    def __iter__(self):
        return self

def defaultCmp(a,b):
    return a<=b

def gnomeSort(lista, cmp = None):
    i = 0;
    if cmp == None:
        cmp = defaultCmp
    while i < len(lista):
        if i == 0 or cmp(lista[i-1],lista[i]) == True:
            i += 1
        else:
            lista[i],lista[i-1] = lista[i-1],lista[i]
            i -= 1
    return lista

def filter(lista, acceptance = None):
    if acceptance ==  None:
        return lista
    newList = []
    for i in lista:
        if acceptance(i):
            newList.append(i)
    return newList
