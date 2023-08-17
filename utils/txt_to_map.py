# Generates a map in the format of character : ascii character for target_chars. 
# All characters in the text file should be placed in the exact order specified in target_chars, separated by an empty line.
# See an example in ascii.txt

def generate_cpp_map():
    # Open your ascii.txt file
    with open('utils/ascii.txt', 'r') as file:
        lines = file.readlines()

    target_chars = 'abcdefghijklmnopqrstuvwxyz0123456789!"#$%&\'()*+,-./:;<=>?[]{}'
    char_pointer = 0

    # Initialize the output for the code
    cpp_map_code = 'inline std::map<char, Letter> letters = {\n'
    ascii_art = ''

    for line in lines:
        cleaned_line = line.strip()
        if cleaned_line == "":
            next_char = target_chars[char_pointer]

            # Escape certain characters
            if next_char in ('\'', '\\'):
                next_char = '\\' + next_char

            cpp_map_code += '    {{\'{}\', Letter(R"(\n{}\n)")}},\n'.format(next_char, ascii_art.rstrip())
            char_pointer += 1
            ascii_art = ''
            continue

        ascii_art += cleaned_line + '\n'
        
    cpp_map_code += '};\n'

    # Save the generated code to a file
    with open('utils/cpp_map.cpp', 'w') as cpp_map_code_file:
        cpp_map_code_file.write(cpp_map_code)


generate_cpp_map()
