#import socket module
from socket import *
import sys # In order to terminate the program
serverSocket = socket(AF_INET, SOCK_STREAM)
#Prepare a sever socket
serverPort = 42069
#Fill in start
serverSocket.bind(("", serverPort))
#Fill in end
serverSocket.listen(1)

while True:
 #Establish the connection
 print('Ready to serve...')
 connectionSocket, addr = serverSocket.accept() #Fill in start #Fill in end
 try:
  message = connectionSocket.recv(2048).decode() #Fill in start #Fill in end
# Extract the path of the requested object from the message
# The path is the second part of HTTP message
  filename = message.split()[1]
# Because the path includes a character ‘/‘ read from second character
  f = open(filename[1:])
  outputdata = f.read() #Fill in start #Fill in end
 #Send one HTTP header line into socket
 response =
 #Fill in start
 #Fill in end
 #Send the content of the requested file to the client
 for i in range(0, len(outputdata)):
 connectionSocket.send(outputdata[i].encode())
 connectionSocket.send("\r\n".encode())

 connectionSocket.close()