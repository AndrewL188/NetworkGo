# Development Documentation

## Week 1
This week I got the GUI and the basic layout of my game engine working, allowing the user to place pieces on the board by clicking in the window. The game engine has basic methods that allow external classes to request to change the board state, and handles some basic illegal moves (like playing outside of the board).


## Week 2
Got the game engine fully functioning, with rules specified in https://www.britgo.org/intro/intro2.html. For scoring, I implemented the Chinese counting system, and players are expected to captures all dead stones within their territory before counting begins. For kos, I implemented a version of go where repeated board positions ARE allowed.
