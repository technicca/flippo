```g++ main.cpp flip.cpp ascii.cpp -o flippo ***```

- ./flippo "input" to flip the text
- ./flippo -ascii to generate ascii art
- flippo --ascii --gradient red,blue,green to generate ascii art and apply a gradient to it.

## TODO:
- Add the ascii art for space
- Add color selection, gradients, alignment (left, right, center, or specified number of pixels) for ascii art
- Add different ascii styles
- Turn into a library


### generate_ascii_art can be represented as class to avoid using extern gradientIndex:

The `gradientIndex` variable is used to keep track of the current color in the gradient. It needs to be defined in a scope that is accessible to both the `main` function and the `generate_ascii_art` function. 

One way to do this is to define `gradientIndex` as a global variable at the top of your `main.cpp` file. However, global variables are generally discouraged in C++ because they can lead to code that is hard to understand and debug.

A better solution would be to encapsulate the functionality of your program into a class. The `gradientIndex` would then be a private member of this class, and the `main` function and `generate_ascii_art` function would be methods of this class. This way, both methods can access `gradientIndex`, but it is not accessible from other parts of your program.

Here's how you could define this class:

```cpp
class AsciiArtGenerator {
private:
    unsigned gradientIndex = 0;

public:
    void generate_ascii_art(const std::string& text, const std::vector<std::string>& colors) {
        // ... same as before, but replace gradientIndex with this->gradientIndex
    }

    int main(int argc, char* argv[]) {
        // ... same as before, but replace gradientIndex with this->gradientIndex
    }
};
```

Then, in your actual `main` function, you would create an instance of this class and call its `main` method:

```cpp
int main(int argc, char* argv[]) {
    AsciiArtGenerator generator;
    return generator.main(argc, argv);
}
```

Regarding your `generate_ascii_art` function declaration in `ascii.hpp`, it doesn't need to be updated. The function signature remains the same. The only thing that changes is how you call this function (you now need to call it on an instance of `AsciiArtGenerator`), and how you access `gradientIndex` inside the function (you now need to use `this->gradientIndex`).