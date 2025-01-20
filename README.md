# Tsokoban
TUI game with 45 playable levels.

# How to build
```bash
git clone https://github.com/hdvpdrm/tsokoban.git
cd tsokoban
mkdir build
cd build
cmake -S .. -B . 
make
chmod +x tsokoban
```

# CLI options
```
tsokoban [-h] [--help] - print this message.
tsokoban n - run game and play nth level.
tsokoban - run game and start at the first level.
tsokoban n solution_file - execute solution for n level.


Solution is simple sequence of 'w','a','s','d'.
w is up
s is down
a is left
d is right

```
