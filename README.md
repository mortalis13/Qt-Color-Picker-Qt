# QtColorPicker

If you'd like to make a donation via **PayPal** or with a **Credit Card**:  
<a href="https://www.paypal.com/donate/?cmd=_s-xclick&hosted_button_id=4U6VKXLGU6LLU&source=url&locale.x=en_US"><img src="https://i.postimg.cc/2jXPm7TJ/btn-donate-2.png"></a>

## Main features

- Hue, Saturation, Value selectors
- Conversion of selected color to text represented in text fields
- Buttons to copy color values and past **Hex** value
- Color sliders and spinners for 3 color models (**HSV, RGB, CMYK**)


## Additional features

- Main window and sliders window can be moved by dragging background window space with **left/right/middle** mouse buttons
- When mouse is on color selectors or sliders the parent window can be moved with the **middle** mouse button
- Windows can be closed with the **middle button** click on any element except *text fields, color sample and spinners*
- Separate component values in the text fields can be *increased/decreased* with **Up/Down** keys
- In text fields selection of the *next/previous* component can be performed with **Tab/Shift+Tab** keys
- Mouse scrolling can be used to *increase/decrease* values by 1 and by 10 with **Ctrl** key for selectors, sliders and spinners (to change **Saturation** on the selector with scrolling **Shift** is held)
- **Left/Right click** on the color sample can be used to copy **Hex** color without and with leading # respectively


## Usage

- To *increase/decrease* value of a color component in text fields set text cursor near it or select it and press **Up/Down** keys or mouse scroll
- To select *next/previous* color component in the same field press **Tab/Shift+Tab**
- To toggle **Sliders window** click with middle mouse button on the color sample or use **Ctrl+S**
- To **close** any window **middle click** somewhere on it
- To **move** any window drag it with any mouse button by any part (except *selector, sliders, spinners, buttons and text fields* on which the middle button can be used)


## Shortcuts

- **F1 - F5** - copy color values (HSV, RGB, CMYK, Hex, # Hex)
- **F6** - paste Hex value
- **Shift+F1 - Shift+F4** - focus text fields (HSV, RGB, CMYK, Hex)
- **Ctrl+S** - open/close Sliders window
- **Esc** or mouse wheel press - exit
- mouse wheel press on the color sample - open/close Sliders window
- left/right mouse click on the color sample - copy Hex value (without/with leading #)
- mouse scroll on the vertical Hue selector - change the Hue value by 1
- mouse scroll on the rectangular Saturation/Value selector - change Value component by 1, with **Shift** - change Saturation component
- mouse scroll with **Ctrl** - change values by 10

## Download

Portable packages:

[All releases](https://github.com/mortalis13/Qt-Color-Picker-Qt/releases) <br>
[SourceForge](https://sourceforge.net/projects/qtcolorpicker/files) <br>
[Softpedia v1.0.0](http://www.softpedia.com/get/PORTABLE-SOFTWARE/Multimedia/Graphics/Portable-QtColorPicker.shtml)

## Build

The program was created with [Qt 5.3.1](http://download.qt.io/official_releases/qt/5.3/5.3.1/) using MinGW compiler in [Qt Creator 3.1.2](http://download.qt.io/official_releases/qtcreator/3.1/3.1.2/).


## Screenshots

![QtColorPicker-main](/files/qtcolorpicker-1.png)  
![QtColorPicker-sliders](/files/qtcolorpicker-2.png)
