import socket
import time
import os
from copy import copy

# 0 -> AB
# 1 -> BC 
# 2 -> CD
# 3 -> EA
# 4 -> FA


class Simulation():

    def __init__(self):
        self.server = socket.socket()		
        self.port = 8080

        self.variables = {
            0:'-',
            1:'-',
            2:'-',
            3:'-',
            4:'-',
            }
        self.symbols = {
            0:'&',
            1:'@',
            2:'#',
            3:')',
            4:'='
        }

        self.__station = """		.--)--------E
                |
                |
                |
        A -----&-----> B -----@-----> C -----#-----> D
        |
        |
        |
        .--=--------F
        """


    def setup(self):
        print ("Socket successfully created")
        self.server.bind(('', self.port))		 
        print ("socket binded to %s" %(self.port) )
        self.server.listen(5)
        print ("socket is listening")		


    def draw(self):
        os.system('clear')
        curr = copy(self.__station)
        for key in self.variables.keys():
            curr = curr.replace( self.symbols[key] , self.variables[key])
        print(curr)
        

    def start(self):
        c, _ = self.server.accept()
        while True :
            _new = c.recv(1024)
            if not _new : break
            
            try:
                rail, action, metro_ID = _new.decode("utf-8").split(':')

                ## Someone is joining
                if(str(action) == "1"):
                    self.variables[int(rail)] = str(metro_ID)
                ## Someone is leaving
                else :
                    if not self.variables[int(rail)] == str(metro_ID) :
                        c.close()
                        exit(-1)
                    else:
                        self.variables[int(rail)] = '-'
            except ValueError :
                print("failed with : "+ _new.decode("utf-8"))
                c.send(b'-1')
                

            c.send(b'1')
            self.draw()
            
        c.close()

    

if __name__ == '__main__':
    S = Simulation()
    S.setup()
    S.start()
