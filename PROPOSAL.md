# Final Project Proposal

My proposal for the final project is a rhythm game that provides a simple and intuitive user interface that allows the user to select a song, and then tap along to the beat and melody of that song. Short segments of “lights” that fall from the top of the window will indicate when and where on the keyboard the user should press, and players will be scored based on the accuracy and consistency of their key-pressing. A leaderboard documenting the top scores for each song will also be provided.

All rhythm games are primarily comprised of 3 features: graphics indicating how the user should play the game, music for the player to play along to, and a user interface that allows the user to interact and “respond” to the music being played. Consequently, I’ve identified three libraries provided by openFrameworks that will be crucial to my project: openGL, the ofSoundPlayer library, and the events module - each of which correspond, respectively, to the three features of rhythm games mentioned above. 

As for a more challenging extension of the project, I would like to implement a piece of functionality that allows the user to upload their own mp3 file containing a song, and generate a sequence of beats that the user can play the game to. For this aspect, I intend to use aubio, a library designed to extract features from both existing audio files and live audio. Aubio conveniently includes beat and pitch detection, both of which are absolutely necessary for the creation of the “beats” of a rhythm game.

Although I do not much have experience writing software of this scale, I do have much experience in what a rhythm game looks and feels like (from my childhood), and therefore have a relatively clear picture of the components that I need and the short-term goals I should set for myself in implementing this project.

Links to documentation of libraries and additional resources:
  * https://aubio.org/
  * https://openframeworks.cc/documentation/sound/
  * https://openframeworks.cc/documentation/gl/
  * https://openframeworks.cc/documentation/events/
