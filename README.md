# Skillbeater
Dead by Daylight Skillcheck Beater

# How it works
Skillbeater takes screenshots of a portion of your screen (around the middle) and then scans for a certain density of white pixels. If the density check is met it figures which `block` (10x10 area of pixels) has the highest count of white pixels. The high density area is *(usually)* the `Great` area on a skillcheck. The solver will then repeatedly take pictures of the zone just around the previous found `high density area` until it detects enough red *(the tick marker on the skillcheck)*
