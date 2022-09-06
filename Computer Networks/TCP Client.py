from socket import *
# Client need to know the server’s host name or IP address and port number
serverName = "10.249.40.44"
serverPort = 12000
# Create a TCP client socket
clientSocket = socket(AF_INET, SOCK_STREAM)
# Client connects to server
clientSocket.connect((serverName,serverPort))
# Client send user’s input to server
sentence = input("Input lowercase sentence:")
clientSocket.send(sentence.encode())
# Client receive server’s message back and print it out
modifiedSentence = clientSocket.recv(2048)
print ("From Server: " + modifiedSentence.decode())
# Close socket connection
clientSocket.close()