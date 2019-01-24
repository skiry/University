import copy

class State:
    def state(self):
        '''
        hold a path of configurations
        '''
        self.__values = []

    def setValues(self, values):
        self.__values = copy.deepcopy(values)

    def getValues(self):
        return self.__values
