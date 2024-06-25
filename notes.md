# app icon

[from here](https://martin.hoppenheit.info/blog/2016/where-to-put-application-icons-on-linux/):

The guide on the Debian Menu System has this to say:

- Icon files should go to /usr/share/pixmaps/.
- They should be in XPM format.
- They should not be larger than 32x32 px, smaller sizes are okay.
- They should have a transparent background.

The freedesktop.org Icon Theme Specification (version 0.11) gives us the following advice:

- An icon file sized 48x48 px (probably PNG?) should go to /usr/share/icons/hicolor/48x48/apps/
- Aditionally, bigger or smaller icons may be provided in other /usr/share/icons/hicolor/\*/apps/ directories, in particular an SVG file in /usr/share/icons/hicolor/scalable/apps/.

This sounds somewhat contradictory but on a current Debian Jessie, you will in fact find icon files in all of the mentioned directories. So if you like to be pragmatic you should probably install an icon file in at least three places to ensure optimal performance:

- A 32x32 px XPM file in /usr/share/pixmaps/.
- A 48x48 px PNG file in /usr/share/icons/hicolor/48x48/apps/.
- Optionally, an SVG file in /usr/share/icons/hicolor/scalable/apps/.

Of course you also need a desktop file in /usr/share/applications/ for your program.
[also check arch linux desktop entries wiki](https://wiki.archlinux.org/title/Desktop_entries)
