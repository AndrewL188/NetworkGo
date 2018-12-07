# Development Documentation

## Week 1
This week I got the GUI and the basic layout of my game engine working, allowing the user to place pieces on the board by clicking in the window. The game engine has basic methods that allow external classes to request to change the board state, and handles some basic illegal moves (like playing outside of the board).


## Week 2
Got the game engine fully functioning, with rules specified in https://www.britgo.org/intro/intro2.html. For scoring, I implemented the Chinese counting system, and players are expected to captures all dead stones within their territory before counting begins. For kos, I implemented a version of go where repeated board positions ARE allowed.

## Week 3
This week I focused on getting the client and server running. Moved the go game engine to the server, so that the server handles all the calculations needed to run a go game, and changed the client to draw a representation of a go board based on a string message from the server rather than needing an instance of a game engine. There are still a few bugs (which I suspect are caused by a loss of information as packets are sent from the server to client) that cause stones to jump around the board when a user clicks a location. Next week, I plan to fix the bug and improve the UI.
