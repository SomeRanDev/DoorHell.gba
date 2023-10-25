These are the Blender files and scripts used to generate the prerendered frames.

# Rendering Frames or Doorbell
First set the playback frames to be:
```
Start: 1
End 68
```

Then render with either the `Foreground`, `Background`, or one of the doorbell/overlay objects.

## Adding Doorbell or Overlay Object to Game
If rendering a doorbell or overlay object, run the `delete_empty_images.ts` script to remove empty images. This will generate a header file for the images and store them in a folder named `NAME_out`.

Use Aseprite to convert the .png files into valid 16 color, 256x256px .bmp files into `NAME_out/out`. Copy `NAME_out/out` to a `graphics/` folder. Add it to `Makefile`.

## Rendering and Adding Animation
First render the animation with its corresponding frames in Blender. For example, "Close Bell Press" is `Start: 110` `End: 120` as can be seen in its `generate_dh_close_bell_press.bat` file.

Once rendered, simply run the correlating `.bat` file.

Go to its `graphics/` folder, for example: `graphics/dh/dh_close_bell_press/`. Open the `.bmp` images with Aseprite and:
 * Restrict the palette to 16 colors
 * Resize the image to 256pc by 256px
 * Ensure the first color in the palette is the bright blue color that's added

Finally add `graphics/dh/dh_close_bell_press` or whatever the path is to the `Makefile`.
