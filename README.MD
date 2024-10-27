# ***UniClock***

Have two or more clocks in one app!

## Installation

### Prerequisites
Make sure GTK3 is installed on your system. If not, you can install it with the following command:
```bash
sudo apt-get install libgtk-3-dev
```

### Compilation
After installing the required libraries, compile the app using:

```bash
gcc -o uniclock main.c `pkg-config --cflags --libs gtk+-3.0`
```

Running the Application
Once compiled, run the application with:
```bash
./uniclock
```

## Features
- Name clocks
- Set offset

## To-Do
Below is a list of potential features that can be added in future versions of the app:

- [X] **Password Strength Indicator:** Displays an indicator for the strength of the password.
- [ ] **Dark Theme:** Button will change a theme.

# License

This project is licenced under the MIT.
