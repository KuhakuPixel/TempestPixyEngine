
# TempestPixyEngine
- A simple chess engine (under 3000 lines ) written in c++  which is easy and simple to read / understand
- Uses Minimax and alphabeta pruning to search and evaluate the current position

# Playing with TempestPixyEngine
 this engine can be played [here](https://lichess.org/@/TempestPixyEngine) (Make sure that you are signed in)

# Compiling
Build the project using python (at least version 3.0)
```sh
 python3 build.py
```
Run unit tests  with
```sh
python3 build.py test
```
# TODO:
- use cmake to build the project
- use google benchmark to test performance
- Improve performance
- planning to make this into a simple machine learning framework for board and zero sum games 

# Deploying Engine to lichess.org
- https://lichess.org/forum/general-chess-discussion/how-to-create-a-httpslichessorg-bot
- https://github.com/ShailChoksi/lichess-bot
- https://github.com/ShailChoksi/lichess-bot/issues/312 (some issues)

# Credits
- https://www.chessprogramming.org/Main_Page
- https://www.youtube.com/watch?v=STjW3eH0Cik&t=1735s&ab_channel=MITOpenCourseWare (For understanding about minimax and alphabeta pruning algorithm)
