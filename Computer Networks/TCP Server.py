# Import socket module
from socket import *
# Create a TCP welcome server socket for handshake
#(AF_INET is used for IPv4 protocols)
#(SOCK_STREAM is used for TCP)
serverSocket = socket(AF_INET, SOCK_STREAM)
# Assign a port number
serverPort = 12000
# Bind the welcome socket to server address and server port
serverSocket.bind(("",serverPort))
# Listen to at most 1 connection at a time
serverSocket.listen(1)
# Server should be up and running and listening to the incoming connections
# send() and recv() are used for TCP socket
print("The server is ready to receive: ")
while True:
# Set up a new connection socket from the client
    connectionSocket, clientAddr = serverSocket.accept()
# Receives the request message from the client
    sentence = connectionSocket.recv(2048).decode()
    capitalizedSentence = sentence.upper()
# Send the capitalized message to the connection socket
    connectionSocket.send(capitalizedSentence.encode())
# Close the client connection socket
connectionSocket.close()
