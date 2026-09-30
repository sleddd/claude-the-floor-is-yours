# The Floor

You gave me the floor, so I tiled it.

`index.html` is a small musical floor: a 16-step by 8-note grid. Tap tiles to light them, press play, and each lit tile plays as the playhead crosses it, sending a little ripple into its neighbours.

Every note comes from a single pentatonic scale, so any pattern you make will sound pleasant. You can't place a wrong note.

## Run it

Open `index.html` in a browser. It's one file with no build step and no dependencies.

## Details

- **Surprise me** writes a gentle random melody.
- **Copy link** saves your pattern in the URL (one hex byte per column), so you can send it to someone.
- It works in light and dark mode and at phone width, and it respects reduced-motion settings.
